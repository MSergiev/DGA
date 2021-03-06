#include "Game.h"

//Default constructor
Game::Game()
:mExplosion(SDL_Rect {0,0,EXPLODE_WIDTH,EXPLODE_HEIGHT},EXPLODE_FRAMES,EXPLODE_DELAY),
mShockwave(SDL_Rect {0,0,SHOCK_WIDTH,SHOCK_HEIGHT},SHOCK_FRAMES,SHOCK_DELAY){
	//Initialize class fields
	miDiceTimer = SDL_GetTicks();
	mbRunning = 0;
	mbHighlight = 0;
	mbIgnoreRecovery = 0;
	miCameraX = 0;
	miCameraY = 0;
	mbTransition = 0;
	meScreen = BLANK;
}




//Game loop
void Game::loop(){
					
    //Handle events
	eventHandler();

	//Render objects
	render();

	//If transitioning
	if(mbTransition) transition();	
	//If game is running
	else if(mbRunning){	
		//Execute player turn
		turn(mTurnOrder.front());
	
		//Check for game end
		int finishedPlayers = 0;
		for(unsigned i = 0; i < mTurnOrder.size(); ++i)
			if(mTurnOrder[i]->getIFinishPosition()!=0) finishedPlayers++;
		if(finishedPlayers>=(PLAYERS-1)){
			mbRunning = 0;
			mWinScreen.loadData(mTurnOrder);
			transition(WIN);
		}
	}

}






//Event container setter
void Game::setEvent(SDL_Event& event){
    this->mEvent = event;
}






//Game object inititalizing method
void Game::init(){
    
#ifdef DEBUG
	cout << "Game Init called" << endl;
#endif
    //Load game font
    mFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if(mFont==NULL) cerr << "Font error: " << TTF_GetError() << endl;


	//Load game board texture
	mBoard.load(SCROLLABLE_PATH);

	//Initialize highlighters
	for(int i = 0; i < BOARD_HEIGHT; ++i)
		for(int j = 0; j < BOARD_WIDTH; ++j)
		mBoardHighlghters[i][j].setTexture(HIGHLIGHTER_PATH);

	//Initialize dice
	for(int i = 0; i < PLAYERS; ++i){
		mDice.push_back(new Dice);
		mDice.back()->setPosition(DICE_POS[i].first, DICE_POS[i].second);
	}

    //Initialize UI
    mTitleScreen.init();
    mWinScreen.setFont(mFont);
    mWinScreen.init();
	mInfoScreen.init();
	mControls.init();
	mVolume.init();

	//Draw continue on title screen if recovery is available	
	mbIgnoreRecovery = !(Recovery::ReadFromXML().size()>0);
	mTitleScreen.setContinue(!mbIgnoreRecovery);

	//Set current screen
	transition(TITLE);
}




//Game data inititalizing method
void Game::initGame(){
    
#ifdef DEBUG
	cout << "initGame called" << endl;
#endif

	//Clear old board data
	for(int i = 0; i < BOARD_HEIGHT; ++i){
		for(int j = 0; j < BOARD_WIDTH; ++j){
			while(mBoardVector[i][j].size()){
				mBoardVector[i][j].pop_back();
			}
		}
	}

    //Initialize final vectors with pawn placeholders
	for(int i = 0; i < PLAYERS; ++i){
		for(int j = 0; j < PAWNS; ++j){
			mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].push_back(new Pawn(NONE));		
		}
	}	

	if(mbIgnoreRecovery){
	   cout << "Starting new game" << endl;
   	   determineTurnOrder();
	} else {
		cout << "Recovering state" << endl;

	//Try to recover state from XML	
	mTurnOrder = Recovery::ReadFromXML();

	//Set player data
		for(unsigned i = 0; i < mTurnOrder.size(); ++i){
			for(unsigned j = 0; j < mTurnOrder[i]->m_vPawns.size(); ++j){
				//If current pawn has finished
				if(mTurnOrder[i]->m_vPawns[j]->getIPosition()>(BOARD_LENGTH+5)){
					cout << (mTurnOrder[i]->m_vPawns[j]->getIPosition()-(BOARD_LENGTH+5)-1) << endl;
					//Delete pawn placeholder
					delete mBoardVector[mTurnOrder[i]->m_vPawns[j]->getIXPosition()][mTurnOrder[i]->m_vPawns[j]->getIYPosition()][mTurnOrder[i]->m_vPawns[j]->getIPosition()-(BOARD_LENGTH+5)-1];
					//Place new pawn
					mBoardVector[mTurnOrder[i]->m_vPawns[j]->getIXPosition()][mTurnOrder[i]->m_vPawns[j]->getIYPosition()][mTurnOrder[i]->m_vPawns[j]->getIPosition()-(BOARD_LENGTH+5)-1] = mTurnOrder[i]->m_vPawns[j];
				} 
				//If current pawn is on the active field
				else mBoardVector[mTurnOrder[i]->m_vPawns[j]->getIXPosition()][mTurnOrder[i]->m_vPawns[j]->getIYPosition()].push_back(mTurnOrder[i]->m_vPawns[j]);
			}
			//Set dice data
			mDice[mTurnOrder[i]->getEColor()-1]->setDiceResult(mTurnOrder[i]->getIDiceRoll());
			mDice[i]->setDiceResult(mTurnOrder[i]->getIDiceRoll());
		}
		cout << "Player data:" << endl;
		Recovery::Print(mTurnOrder);    

		//Set roll flag
		mbRoll = !Recovery::hasRolled;
	}
	
	//Play BGM
	Sound::music(BGM);

	//Load SFX
	mExplosion.load(EXPLODE_PATH);
	mShockwave.load(SHOCK_PATH);
}






//Event handler
void Game::eventHandler(){	

	//Keyboard scroll
	if(mEvent.key.keysym.sym == SDLK_1){ mbRoll=0; mDice[mTurnOrder.front()->getEColor()-1]->setDiceResult(1); };
	if(mEvent.key.keysym.sym == SDLK_2){ mbRoll=0; mDice[mTurnOrder.front()->getEColor()-1]->setDiceResult(2); };
	if(mEvent.key.keysym.sym == SDLK_3){ mbRoll=0; mDice[mTurnOrder.front()->getEColor()-1]->setDiceResult(3); };
	if(mEvent.key.keysym.sym == SDLK_4){ mbRoll=0; mDice[mTurnOrder.front()->getEColor()-1]->setDiceResult(4); };
	if(mEvent.key.keysym.sym == SDLK_5){ mbRoll=0; mDice[mTurnOrder.front()->getEColor()-1]->setDiceResult(5); };
	if(mEvent.key.keysym.sym == SDLK_6){ mbRoll=0; mDice[mTurnOrder.front()->getEColor()-1]->setDiceResult(6); };
	
	if(mEvent.key.keysym.sym == SDLK_q) transition(RULES2,1);
	if(mEvent.key.keysym.sym == SDLK_w) transition(RULES1,1);
	if(mEvent.key.keysym.sym == SDLK_e) transition(TITLE,1);
	if(mEvent.key.keysym.sym == SDLK_r) transition(GAME,1);
	if(mEvent.key.keysym.sym == SDLK_t) transition(WIN,1);

	if(mEvent.key.keysym.sym == SDLK_LEFT)miCameraX+=10;
	if(mEvent.key.keysym.sym == SDLK_RIGHT)miCameraX-=10;
	if(mEvent.key.keysym.sym == SDLK_UP)miCameraY+=10;
	if(mEvent.key.keysym.sym == SDLK_DOWN)miCameraY-=10;
	
	//If no UI is active
	if(!mActiveUI) return;
	
	//If on rules screen
	if(dynamic_cast<Info*>(mActiveUI)){
		//Get current button state
		int rulesState = mActiveUI->eventHandler(mEvent);
		//If back is clicked
		if(rulesState&RULES_BACK) {
			//If on first screen
		   	if(meScreen == RULES1){	
			mbRunning = 1; transition(GAME);
		   }
			//If on second screen
		   	else {
			transition(RULES1);
		   }
		}
		//If next is clicked
		else if(rulesState&RULES_NEXT) {
			//If on first screen
		   	if(meScreen == RULES1){	
				transition(RULES2);
		   }
			//If on second screen
		   	else {
			mbRunning = 1; transition(GAME);
		   }
		}		
	}
	
	//If on title screen
	else if(dynamic_cast<TitleScreen*>(mActiveUI)){
		//Get current button states
	     int titleState = mActiveUI->eventHandler(mEvent);
	     //If start button is clicked
	     if(titleState & TITLE_START){ transition(GAME); mbRoll = 1; mbRunning = 1; mbIgnoreRecovery = 1; initGame(); }
	     //If continue button is clicked
	     else if(titleState & TITLE_CONTINUE){ transition(GAME); mbRoll = 1; mbRunning = 1; initGame(); }
	     //If quit button is clicked
	     else if(titleState & TITLE_QUIT){ quit = 1;}
	}
	
	//If on win screen
	else if(dynamic_cast<WinScreen*>(mActiveUI)){
		//Get current button states
	     int winState = mActiveUI->eventHandler(mEvent);
	     //If restart button is clicked
	     if(winState & WIN_RESTART){ transition(GAME); mbRunning = 1; mbRoll = 1; mbIgnoreRecovery = 1; initGame(); }
	     //If exit button is clicked
	     else if(winState & WIN_QUIT){ quit = 1; }
	}
	
	//If on volume screen
	else if(dynamic_cast<Volume*>(mActiveUI)){
	     mActiveUI->eventHandler(mEvent);
	}	
	//If on game screen
	else if(dynamic_cast<Controls*>(mActiveUI)){
		//Get current button states
		int controlsState = mControls.eventHandler(mEvent);
		//If sound button is clicked
		//if(controlsState & CONTROLS_SOUND){ Sound::mute=!Sound::mute; Sound::mute?Sound::pause():Sound::music(BGM);	}
		if(controlsState & CONTROLS_SOUND){ mActiveUI = &mVolume;	}
		//If rules button is clicked
		else if(controlsState & CONTROLS_RULES){ transition(RULES1); mbRunning = 0; }
		//If quit button is clicked
		else if(controlsState & CONTROLS_QUIT) quit = 1;

		//If dice is rolling
		if(mbRoll){
			//If player clicked the dice
			if(mDice[mTurnOrder.front()->getEColor()-1]->Event(mEvent)){
				//Clear roll flag
				mbRoll = 0;
				//Play SFX
				if(mDice[mTurnOrder.front()->getEColor()-1]->getDiceResult()==6){
				   	Sound::play(ON_SIX);
					mbShockwave = 1;
					mShockwaveCoords = DICE_POS[mTurnOrder.front()->getEColor()-1];
					mShockwaveCoords.first-=(SHOCK_WIDTH-DICE_WIDTH)/2;
					mShockwaveCoords.second-=(SHOCK_HEIGHT-DICE_HEIGHT)/2;
					delay(SHOCK_FRAMES*SHOCK_DELAY);
					mbShockwave = 0;
					}
				else {
					Sound::play(ON_DICE);
					delay(500);
				}
			}
		}

	}
}









//Render all assets
void Game::render(){

#ifdef DEBUG
	//cout << "Render called" << endl;
#endif

	//Render background
	renderBackground();
	
	if(!mbTransition){
		//Render sprites 
		if(meScreen==GAME) renderSprite();

		//Render UI
		renderUI();
	}
}

//Render background
void Game::renderBackground(){
    //Draw game board;
    mBoard.render(miCameraX, miCameraY);
}

//Render sprite layer
void Game::renderSprite(){
	//Render highlighters
	for(unsigned i = 0; i < mActiveHighlighters.size(); ++i)
		mBoardHighlghters[mActiveHighlighters[i].first][mActiveHighlighters[i].second].render();
    
	//Render player sprites
    for(unsigned i = 0; i < mTurnOrder.size(); ++i){
        //Get player pawn screen coordinates
        vector<pair<int,int> > pos;
        //Traverse current player pawns
        for(unsigned j = 0; j < mTurnOrder[i]->m_vPawns.size(); ++j){
                //If pawn is finished
                if(mTurnOrder[i]->m_vPawns[j]->getIPosition()>(BOARD_LENGTH+5)){
					//Traverse player final vector
					for(unsigned k = 0; i < mBoardVector[FINAL_SQUARES[mTurnOrder[i]->getEColor()-1].first][FINAL_SQUARES[mTurnOrder[i]->getEColor()-1].second].size(); ++k){
						//If final pawn is the same as the current pawn
						if(mBoardVector[FINAL_SQUARES[mTurnOrder[i]->getEColor()-1].first][FINAL_SQUARES[mTurnOrder[i]->getEColor()-1].second][k]==mTurnOrder[i]->m_vPawns[j]){
							//Get final screen coordinates
							pos.push_back(getFinalCoords(mTurnOrder[i]->getEColor(), k));
							break;
						}
					}
				}	
				//Get screen coordinates
				else pos.push_back(getCoords(mTurnOrder[i]->m_vPawns[j]->getIXPosition(), mTurnOrder[i]->m_vPawns[j]->getIYPosition()));
        }
        //Render pawns
        mTurnOrder[i]->Render(pos);
    }	
	
	//Render shockwave
	if(mbShockwave)
		mShockwave.render(mShockwaveCoords.first, mShockwaveCoords.second);

	//Render dice
	for(unsigned i = 0; i < PLAYERS; ++i)
		mDice[i]->render();
	
	//Render explosion
	if(mbExplosion) 
		mExplosion.render(mExplosionCoords.first, mExplosionCoords.second-50);		
}

//Render UI
void Game::renderUI(){

	//Render controls
	mActiveUI->render();
}








//Player turn
void Game::turn(Player* p){
    
#ifdef DEBUG
	//cout << "Turn called with " << p->getEColor() << endl;
#endif
	//If player has not finished
	if(!p->getIFinishPosition()){
		//If player has rolled before recovery
		if(mbRoll){
			//Roll the dice
			diceRoll();
		} else {
			//If no pawn is moving
			if(!mbMove){
#ifdef DEBUG
//	cout << "Player " << p->getEColor() << " rolled " << p->getIDiceRoll() << endl;
#endif
                //Set player roll
                p->setIDiceRoll(mDice[p->getEColor()-1]->getDiceResult());
        
                //Save recovery data
                Recovery::WriteXML(mTurnOrder, 1);
                
                //If player has no active pawns
				if(p->getIActivePawns()==0){
                    //If roll is a 6
                    if(p->getIDiceRoll()==6){
                        //Add an active pawn
                        activatePawn(p);
                    }
                }
                //If player has only one active pawn
                else if(p->getIActivePawns()==1 && p->getIDiceRoll()!=6){
                    //Traverse the pawns
                    for(unsigned i = 0; i < p->m_vPawns.size(); ++i){
                        //If pawn is on the board
                        if(MOVEABLE_SQUARES[p->m_vPawns[i]->getIYPosition()][p->m_vPawns[i]->getIXPosition()]){
                            //If move is valid
							if(isValid(p->m_vPawns[i])){
								cout << "Selected pawn: " << p->m_vPawns[i]->getEColor() << endl;
								//Raise movement flag
						        mbMove = 1;
								//Assign moving pawn
								mMovingPawn = p->m_vPawns[i];
								//Set pawn as active
								mMovingPawn->setBIdle(0);
								//Assign remaining moves
								miRemaining = p->getIDiceRoll();
							}
                            break;	
                        }
                    }
                }
                //If player has more than one active pawn
                else {
                    //If highglighters have not been set this turn	
                        if(!mbHighlight){
                        //If roll is a 6 and player has inactive pawns
                        if(p->getIDiceRoll()==6 && p->getIActivePawns()!=PAWNS){
                            //Find inactive pawn
                            for(unsigned i = 0; i < p->m_vPawns.size(); ++i){
                                    if(isBase(p->m_vPawns[i]->getIXPosition(), p->m_vPawns[i]->getIYPosition(), p->getEColor())){
                                    //Highlight inactive pawn
                                    highlight(p->m_vPawns[i]->getIXPosition(), p->m_vPawns[i]->getIYPosition());
                                    break;
                                }
                            }
                        }
                        //Active pawn counter
                        int activeCount = 0;	
                        //Traverse the board
                    for(unsigned i = 0; i < p->m_vPawns.size(); ++i){
                            //Find active ones
                            if(MOVEABLE_SQUARES[p->m_vPawns[i]->getIYPosition()][p->m_vPawns[i]->getIXPosition()]){
                                //Highlight active pawn
                                highlight(p->m_vPawns[i]->getIXPosition(), p->m_vPawns[i]->getIYPosition());	
                                //Increase active counter
                                activeCount++;
                                }
                            //Check if more active pawns exist
                            if(activeCount==p->getIActivePawns()) break;
                            }
                        //Raise highlighter flag
                        mbHighlight = 1;
                    }
            
                    //Get choice from highlights
                    pair<int,int> choice = getHighlightedChoice();
                    //If invalid choice
                    if(choice.first<0 || choice.second<0) return;
                    //If base is selected
                    else if(isBase(choice.first, choice.second, p->getEColor())) activatePawn(p);
                    //If field is selected
                    else {
						//If move is valid
						if(isValid(mBoardVector[choice.first][choice.second].back())){
							//Raise movement flag
							mbMove = 1;
							//Assign moving pawn
							mMovingPawn = mBoardVector[choice.first][choice.second].back();
							//Set pawn as active
							mMovingPawn->setBIdle(0);
							//Assign remaining moves
							miRemaining = p->getIDiceRoll();
						}
                    }
                }
            }
			//If remaining moves are available
			else {
				//Delay
				if(SDL_GetTicks()-miMoveDelay>MOVEMENT_DELAY){
					//Reset timer
					miMoveDelay = SDL_GetTicks();	
					//Decrease remaining move counter
					miRemaining--;
					//Move pawn
					movePawn(mMovingPawn, 1);
					//If no more moves remain
					if(!miRemaining){
					   	//Lower movement flag
						mbMove = 0;
						//Set moving pawn to idle
						mMovingPawn->setBIdle(1);
					}
				}
			}
			//If destination square is reached
			if(!miRemaining){
				//If no highlighters are active
				if(!mbHighlight){	
				//If player has finished
					if(hasFinished(mTurnOrder.front())){
					//Determine finish position
						int pos = 1;
						for(unsigned i = 1; i < mTurnOrder.size(); ++i)
							if(hasFinished(mTurnOrder[i])) pos++;
						//Set player finish position
						mTurnOrder.front()->setIFinishPosition(pos);
					}
					else {			
						//If roll is a 6 get another turn
						if(p->getIDiceRoll()!=6){
							//Cycle players
							mTurnOrder.push_back(mTurnOrder.front());
							//Remove current player from queue
							mTurnOrder.pop_front();
						}
					}
	
					//Save recovery data
					Recovery::WriteXML(mTurnOrder);	
		
					//Raise roll flag for next turn
					mbRoll = 1;
#ifdef DEBUG
	/*	cout << "Active: " << endl;
		for(unsigned i = 0; i < BOARD_HEIGHT; ++i){
			for(unsigned j = 0; j < BOARD_WIDTH; ++j){
				cout << mBoardVector[j][i].size() << " ";
			}
			cout << endl;
		}
		cout << endl;
		*/
#endif
				}
			}
		}
	}
	//If player has finished
	else {
		//Push back to the end of the queue
		mTurnOrder.push_back(mTurnOrder.front());
		//Remove current player from queue
		mTurnOrder.pop_front();
	}
}





//Determine turn order
void Game::determineTurnOrder(){
#ifdef DEBUG
	cout << "DetermineTurnOrder called" << endl;
#endif
	//Refresh RNG seed
	srand(time(0));
	//Clear old data if existing
	while(mTurnOrder.size()){
		delete mTurnOrder.back();
		mTurnOrder.pop_back();
	}
	//Temporary vector of colors to choose from
	vector<Colors> order = {RED, BLUE, YELLOW};
	//Shuffle vector
	random_shuffle(order.begin(), order.end());
	//Initialize player objects
	for(int i = 0; i < PLAYERS; ++i){
		mTurnOrder.push_back(new Player(order[i]));
		//Add a starting pawn
		activatePawn(mTurnOrder.back());
	}
#ifdef DEBUG
	cout << "Player turns: " << mTurnOrder[0]->getEColor() << " " << mTurnOrder[1]->getEColor() << " " << mTurnOrder[2]->getEColor() << endl;
#endif
}





//Dice roll
void Game::diceRoll(){

#ifdef DEBUG
	//cout << "DiceRoll called" << endl;
#endif

		//Save current roll
		mDice[mTurnOrder.front()->getEColor()-1]->roll();
	if((SDL_GetTicks()-miDiceTimer)>500){
		//Reset timer
		miDiceTimer = SDL_GetTicks();
		//Play SFX
		Sound::play(ON_ROLL);
	}
	
}





//Pawn movement
void Game::movePawn(Pawn* p, int with){
#ifdef DEBUG
	cout << "MovePawn called with " << p->getEColor() << " " << with << endl;
#endif
	
	//If pawn has finished
	if(p->getIPosition()>(BOARD_LENGTH+5)) return;
	//Use safe zone directions flag
	bool useSafe = 0;
	//Is on final square flag
	bool finished = 0;

	//New pawn position container
	pair<int,int> newCoords = {p->getIXPosition(), p->getIYPosition()};
	//Calculate new position
	for(int i = 0; i < with; ++i){
		//If entry point is reached
		if(isEntry(newCoords.first, newCoords.second, p->getEColor())){
			cout << "Safe zone entry" << endl;
			useSafe = 1;
		}
		//Temporary coordinate holder
		pair<int,int> tmp = newCoords;
		//If on safe squares
		if(useSafe){
			tmp.first+=NEXT_SAFE[p->getEColor()-1].first;
			tmp.second+=NEXT_SAFE[p->getEColor()-1].second;
		}
		//If on active squares
		else {
			tmp.first+=NEXT_SQUARE[newCoords.second][newCoords.first].first;
			tmp.second+=NEXT_SQUARE[newCoords.second][newCoords.first].second;
		}
		//Assign new coordinates
		newCoords.first = tmp.first;
		newCoords.second = tmp.second;

		//If final square is reached
		if(isFinal(newCoords.first, newCoords.second, p->getEColor())){
			cout << "Final square" << endl;
			finished = 1;
			break;
		}
	}
	//If on active squares
	if(!useSafe && !finished && !miRemaining) collision(p,newCoords.first, newCoords.second);
	//If on final squares
   	else if(finished){
		//If final space is occupied
		if(mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second][miRemaining]->getEColor()!=NONE)
			return;
		//If final space is unoccupied
		else{
			//Delete pawn placeholder
			delete mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second][miRemaining];
			//Set pawn finish position
			p->setIPosition(p->getIPosition()+miRemaining);
			//Place pawn in final vector
			mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second][miRemaining] = p;	
			//Decrease player active counter
			mTurnOrder.front()->setIActivePawns(mTurnOrder.front()->getIActivePawns()-1);
			//Lower move flag
			mbMove = 0;
			miRemaining = 0;

#ifdef DEBUG
			cout << "Pawn finished at " << (p->getIPosition()) << endl;
#endif
		}
	}
#ifdef DEBUG
	cout << "Setting position at (" << newCoords.first << ", " << newCoords.second << ")" << endl;
#endif
	
	//Place pawn in new location
	if(!finished) mBoardVector[newCoords.first][newCoords.second].push_back(p);
	//Remove pawn from old location
	mBoardVector[p->getIXPosition()][p->getIYPosition()].pop_back();
	//Set pawn position
	p->setIXPosition(newCoords.first);
	p->setIYPosition(newCoords.second);
	p->setIPosition(p->getIPosition()+with);
	//Add roll to player step count
	mTurnOrder.front()->setISteps(mTurnOrder.front()->getISteps()+with);
	//Set as new moving pawn
	if(mbMove) mMovingPawn = mBoardVector[newCoords.first][newCoords.second].back();

#ifdef DEBUG		
	cout << "Moved to (" << newCoords.first << ", " << newCoords.second << ")" << endl;
#endif	

		//Play SFX
		Sound::play(ON_MOVE);
}





//Collision detection
void Game::collision(Pawn * p, int pX, int pY){
#ifdef DEBUG
	cout << "Collision called with " << p->getEColor() << " " << pX << " " << pY << endl;
#endif
	//If space is already occupied
	if(mBoardVector[pX][pY].size()){
		//If occupant is a different player
		if(mBoardVector[pX][pY].back()->getEColor()!=p->getEColor() && mBoardVector[pX][pY].back()->getEColor()!=NONE){
			//Other player pointer
			Player* owner;
			//Go through players to find occupying pawn owner
			for(unsigned i = 1; i < mTurnOrder.size(); ++i){
				if(mBoardVector[pX][pY].front()->getEColor()==mTurnOrder[i]->getEColor()){
					owner = mTurnOrder[i];
					break;
				}
			}
			//Return other pawns to base
			while(mBoardVector[pX][pY].size()>0){
				//Find free base coords
				pair<int,int> base;
				for(int i = 0; i < PAWNS; ++i){
					base = BASE_SQUARES[mBoardVector[pX][pY].back()->getEColor()-1][i];
					if(!mBoardVector[base.first][base.second].size()) break;
				}
				//Set pawn position
				mBoardVector[pX][pY].back()->setIXPosition(base.first);
				mBoardVector[pX][pY].back()->setIYPosition(base.second);
				mBoardVector[pX][pY].back()->setIPosition(0);
				//Place pawn on base square
				mBoardVector[base.first][base.second].push_back(mBoardVector[pX][pY].back());
				//Remove pawn from active board
				mBoardVector[pX][pY].pop_back();
				//Add to other pawns' owners' lost counter
				owner->setILost(owner->getILost()+1);
				//Decrease other players' active pawn counter
				owner->setIActivePawns(owner->getIActivePawns()-1);
				//Add to current players' taken counter
				mTurnOrder.front()->setITaken(mTurnOrder.front()->getITaken()+1);
			}
#ifdef DEBUG
			cout << mTurnOrder.front()->getEColor() << " took pawn on (" << pX << ", " << pY << ")" << endl;
#endif			
			//Play SFX
			Sound::play(ON_COLLISION);
			//Explode
			mbExplosion = 1;
			mExplosionCoords = getCoords(pX, pY);
			delay(EXPLODE_DELAY*EXPLODE_FRAMES);
			mbExplosion = 0;
		}
	}
}





//Board square highlighter
void Game::highlight(int pX, int pY){
#ifdef DEBUG
	cout << "Highlight called with (" << pX << ", " << pY << ")" << endl;
#endif
	pair<int, int> coords = getCoords(pX, pY);
	
	//Set highlighter params
	mBoardHighlghters[pX][pY].setSize(SQUARE_SIZE, SQUARE_SIZE);
	mBoardHighlghters[pX][pY].setLocation(coords.first-5, coords.second-15);

#ifdef DEBUG
	cout << "Adding highlighter at " << pX << " " << pY << endl;
#endif
	
	//Add to active highlighter list
	mActiveHighlighters.push_back(pair<int,int> {pX, pY});
}





//Highlighted squares event handler
pair<int,int> Game::getHighlightedChoice(){
#ifdef DEBUG
	cout << "GetHighlightedChoice called" << endl;
#endif
	//Selected coordinate container
	pair<int,int> choice = {-1,-1};


	//If active highlighters exist
	if(mActiveHighlighters.size()){
		//Traverse active highlighters
		for(unsigned i = 0; i < mActiveHighlighters.size(); ++i){
			//If clicked
			if(mBoardHighlghters[mActiveHighlighters[i].first][mActiveHighlighters[i].second].isClicked(mEvent)){
				//Save board index before clearing
				choice = mActiveHighlighters[i];
				//Clear active highlighters
				while(mActiveHighlighters.size()>0) mActiveHighlighters.pop_back();
				//Play SFX
				Sound::play(camera);
				//Lower highlighter flag
				mbHighlight = 0;
				cout << "Selected: " << choice.first << " " << choice.second << endl;
				//Return selected index
				return choice;
			}
		}
	}
	//Return invalid value if nothing is selected
	return choice;
}





//Timed delay
void Game::delay(Uint32 ms){
#ifdef DEBUG
	cout << "Delay called with " << ms << endl;
#endif
	Uint32 timerDelay = SDL_GetTicks();
	while(SDL_GetTicks()-timerDelay<ms){
		eventHandler();
		render();
		SDL_RenderPresent(Texture::mRenderer);
	}
}





//Activate pawn
void Game::activatePawn(Player * p){
#ifdef DEBUG
	cout << "ActivatePawn called with " << p->getEColor() << endl;
#endif
	//Traverse player pawns
	for(unsigned i = 0; i < p->m_vPawns.size(); ++i){
		//If current pawn is inactive
		if(isBase(p->m_vPawns[i]->getIXPosition(), p->m_vPawns[i]->getIYPosition(),p->getEColor())){
			//Check for collisions
			collision(p->m_vPawns[i], START_SQUARES[p->getEColor()-1].first, START_SQUARES[p->getEColor()-1].second);
			//Place pawn location on start position
			p->m_vPawns[i]->setIXPosition(START_SQUARES[p->getEColor()-1].first);
			p->m_vPawns[i]->setIYPosition(START_SQUARES[p->getEColor()-1].second);
			p->m_vPawns[i]->setIPosition(1);
			//Place pawn on game board
			mBoardVector[START_SQUARES[p->getEColor()-1].first][START_SQUARES[p->getEColor()-1].second].push_back(p->m_vPawns[i]);
			//Increment player active counter
			p->setIActivePawns(p->getIActivePawns()+1);
			//Play SFX
			Sound::play(ON_ACTIVATION);
			break;
		}
	}
}





//Get world coordinates from array index
pair<int,int> Game::getCoords(int pX, int pY){
    
#ifdef DEBUG
	//cout << "GetCoords called with " << pX << " " << pY <<endl;
#endif
	
	//Return coordinate pair
	return pair<int,int> {pX*SQUARE_SIZE+X_OFF, pY*SQUARE_SIZE+Y_OFF};	
}

//Get screen coordinates for final vector
pair<int,int> Game::getFinalCoords(Colors c, int pos){ 
#ifdef DEBUG
	//cout << "GetFnalCoords called with " << c << " " << pos <<endl;
#endif
	//Coordinate holder
	pair<int,int> coords = getCoords(FINAL_SQUARES[c-1].first, FINAL_SQUARES[c-1].second);
	if(c==YELLOW || c==BLUE) coords.first-=SQUARE_SIZE;
	coords.first+=(pos)*SQUARE_SIZE*0.65;
	coords.second+=10;
	return coords;
}





//Determine if board square is active
bool Game::isActive(int pX, int pY){
	for(int i = 0; i < BOARD_LENGTH; ++i)
		if(pX==ACTIVE_SQUARES[i].first && pY==ACTIVE_SQUARES[i].second)
			return 1;
	return 0;
}

//Determine if board square is safe
bool Game::isSafe(int pX, int pY, Colors c){
	for(int i = 0; i < PAWNS; ++i)
		if(pX==SAFE_SQUARES[c-1][i].first && pY==SAFE_SQUARES[c-1][i].second)
			return 1;
	return 0;
}

//Determine if board square is final
bool Game::isFinal(int pX, int pY, Colors c){
	return (pX==FINAL_SQUARES[c-1].first && pY==FINAL_SQUARES[c-1].second);
}

//Determine if board square is base
bool Game::isBase(int pX, int pY, Colors c){
	for(int i = 0; i < PAWNS; ++i)
		if(pX==BASE_SQUARES[c-1][i].first && pY==BASE_SQUARES[c-1][i].second)
			return 1;
	return 0;
}

//Determine if board square is entry
bool Game::isEntry(int pX, int pY, Colors c){
	return (pX==ENTRY_SQUARES[c-1].first && pY==ENTRY_SQUARES[c-1].second);
}

//Determine if pawn move is valid
bool Game::isValid(Pawn* p){
	//If roll is out of bounds
	if(p->getIPosition()+mTurnOrder.front()->getIDiceRoll()>(BOARD_LENGTH+10)){ cout << "Over" << endl; return 0; }
	//If final position is occupied
	if(p->getIPosition()+mTurnOrder.front()->getIDiceRoll()>(BOARD_LENGTH+5)){
		cout << "In final vector pos: " << ((p->getIPosition()+mTurnOrder.front()->getIDiceRoll())-(BOARD_LENGTH+5)-1) << endl;
		if(mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second]
			[(p->getIPosition()+mTurnOrder.front()->getIDiceRoll())-(BOARD_LENGTH+5)-1]->getEColor()!=NONE){ cout << "Occupied" << endl; return 0; }
	}
	return 1;
}

//Determine if player has finished
bool Game::hasFinished(Player* p){
	for(unsigned i = 0; i < p->m_vPawns.size(); ++i)
		if(p->m_vPawns[i]->getIPosition()<=(BOARD_LENGTH+5)) return 0;
	return 1;
}





//Screen transition
void Game::transition(Screens to, bool instant){
#ifdef DEBUG
	//cout << "Transition called with " << to << endl;
#endif	

	//If not transitioning
	if(!mbTransition){
		cout << "Camera: (" << miCameraX << ", " << miCameraY << ")" << endl;
		//New coordinate holder
		pair<int,int> coords = SCREEN_COORDS[to];
		cout << "Destination: (" << coords.first << ", " << coords.second << ")" << endl;
		//If instant
		if(instant){
			miCameraX = coords.first;
			miCameraY = coords.second;
			meScreen = to;
			switchUI();
			return;
		}
		//Assign destination screen as current
		meScreen = to;
		//Zero current travelled distance
		miCurrentDistance = 0;
		//Keep old coordinates
		miOldTransitionX = miCameraX;
		miOldTransitionY = miCameraY;
		//Raise transition flag
		mbTransition = 1;
		//Find direction vector
		mDirection = {coords.first-miOldTransitionX, coords.second-miOldTransitionY};
		//Find length
		miDestinationDistance = sqrt(mDirection.first*mDirection.first+mDirection.second*mDirection.second);
		cout << "Length: " << miDestinationDistance << endl;
		//If length is 0
		if(!miDestinationDistance) return;
		//Normalize vectors
		mDirection.first/=miDestinationDistance; mDirection.second/=miDestinationDistance;
		cout << "Transitioning with vector (" << mDirection.first << ", " << mDirection.second << ")" << endl;
	}

	//Calculate coordinates
	miCameraX+=10*mDirection.first;
	miCameraY+=10*mDirection.second;

	//Increase travelled distance
	miCurrentDistance+=10;

	//If destination is reached
	if(miCurrentDistance>=miDestinationDistance){
		cout << "Transition end" << endl;
		miCameraX = SCREEN_COORDS[meScreen].first;
		miCameraY = SCREEN_COORDS[meScreen].second;
		cout << "New camera: (" << miCameraX << ", " << miCameraY << ")" << endl;
		//Lower transition flag
		mbTransition = 0;
		//Switch UI
		switchUI();
	}
}





//Active UI switcher
void Game::switchUI(){
	switch(meScreen){
		case BLANK: mActiveUI=NULL; break;
		case RULES1:
		case RULES2: mActiveUI=&mInfoScreen; break;
		case TITLE: mActiveUI=&mTitleScreen; break;
		case GAME: mActiveUI=&mControls; break;
		case WIN: mActiveUI=&mWinScreen; mWinScreen.loadData(mTurnOrder); break;
	}
}





//Destructor
Game::~Game()
{
	//Release unused pawn placeholders
	for(int i = 0; i < PLAYERS; ++i)
		for(unsigned j = 0; j < mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].size(); ++j)
			if(!mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].back()->getEColor()){
				delete mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].back();
				mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].pop_back();
			}

	//Release player data
    for(unsigned i = 0; i < mTurnOrder.size(); ++i)
		delete mTurnOrder[i];
	
	//Release dice data
	for(unsigned i = 0; i < mDice.size(); ++i)
		delete mDice[i];

	//Release font
	TTF_CloseFont(mFont);
}
