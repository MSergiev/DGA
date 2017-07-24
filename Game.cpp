#include "Game.h"

//Default constructor
Game::Game(){
	//Initialize class fields
	miDiceTimer = SDL_GetTicks();
	mbRunning = 0;
	mbHighlight = 0;
	mbIgnoreRecovery = 0;
	miCameraX = 0;
	miCameraY = 0;
	mbTransition = 0;
	mbTransitionState = 0;
	for(int i=0;i<PLAYERS;++i) miCurrentRoll[i]=1;
}




//Game loop
void Game::loop(){
    //Handle events
	eventHandler();
#ifdef DEBUG
		cout << "Active: " << endl;
		for(unsigned i = 0; i < BOARD_HEIGHT; ++i){
			for(unsigned j = 0; j < BOARD_WIDTH; ++j){
				cout << mBoardVector[j][i].size();
			}
			cout << endl;
		}
		cout << endl;
#endif
					
		//Render objects
		render();

		//If game is running
		if(mbRunning){		
			//Execute player turn
			turn(mTurnOrder.front());
			

			//Check for game end
			int finishedPlayers = 0;
			for(unsigned i = 0; i < mTurnOrder.size(); ++i)
				if(mTurnOrder[i]->getIFinishPosition()!=0) finishedPlayers++;
			if(finishedPlayers>=(PLAYERS-1)){
				mbRunning = 0;
				mActiveUI = &mWinScreen;
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
		mDice[i] = new Dice;
		mDice[i]->setPosition(DICE_POS[i].first, DICE_POS[i].second);
	}

    //Initialize UI
    mTitleScreen.init();
    mWinScreen.setFont(mFont);
    mWinScreen.init();
	mInfoScreen.init();
	mControls.init();

	//Draw continue on title screen if recovery is available	
	mbIgnoreRecovery = !(Recovery::ReadFromXML().size()>0);
	mTitleScreen.setContinue(!mbIgnoreRecovery);

	//Set active UI
	mActiveUI = &mTitleScreen;

	//Set current screen
	meScreen = TITLE;
	transition(meScreen);
}

//Game data inititalizing method
void Game::initGame(){
    
#ifdef DEBUG
	cout << "initGame called" << endl;
#endif
    //Initialize final vectors with pawn placeholders
	for(int i = 0; i < PLAYERS; ++i)
		for(int j = 0; j < PAWNS; ++j)
			mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].push_back(new Pawn(NONE));			

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
				//Place pawns on board
				mBoardVector[mTurnOrder[i]->m_vPawns[j]->getIXPosition()][mTurnOrder[i]->m_vPawns[j]->getIYPosition()].push_back(mTurnOrder[i]->m_vPawns[j]);
			}
			miCurrentRoll[mTurnOrder[i]->getEColor()-1]=mTurnOrder[i]->getIDiceRoll();
			mDice[i]->setDiceResult(mTurnOrder[i]->getIDiceRoll());
		}
		cout << "Player data:" << endl;
		Recovery::Print(mTurnOrder);    

		//Set roll flag
		mbRoll = !Recovery::hasRolled;
	}
	
	//Play BGM
	Sound::music(BGM);

	//Refresh RNG seed
	mDice[0]->init();
}






//Event handler
void Game::eventHandler(){	

		//Keyboard scroll
		if(mEvent.key.keysym.sym == SDLK_1) transition(BLANK);
		if(mEvent.key.keysym.sym == SDLK_2) transition(RULES1);
		if(mEvent.key.keysym.sym == SDLK_3) transition(RULES2);
		if(mEvent.key.keysym.sym == SDLK_4) transition(TITLE);
		if(mEvent.key.keysym.sym == SDLK_5) transition(GAME);
		if(mEvent.key.keysym.sym == SDLK_6) transition(WIN);

	
		if(mEvent.key.keysym.sym == SDLK_LEFT)miCameraX+=10;
		if(mEvent.key.keysym.sym == SDLK_RIGHT)miCameraX-=10;
		if(mEvent.key.keysym.sym == SDLK_UP)miCameraY+=10;
		if(mEvent.key.keysym.sym == SDLK_DOWN)miCameraY-=10;
	
	
		//If on rules screen
		if(Info* ptr = dynamic_cast<Info*>(mActiveUI)){
			//Get current button state
			int rulesState = mActiveUI->eventHandler(mEvent);
			//If page 1 back is clicked
			if(rulesState&0b0001) { mActiveUI=&mControls; mbRunning = 1; mActiveUI=&mControls; transition(GAME); }
			//If page 1 next is clicked
			else if(rulesState&0b0010) { transition(RULES2); }
			//If page 2 back is clicked
			else if(rulesState&0b0100) { transition(RULES1); }
			//If page 2 next is clicked
			else if(rulesState&0b1000) { mActiveUI=&mControls; mbRunning = 1; mActiveUI=&mControls; transition(GAME); }
		}
		
		//If on title screen
	 else if(TitleScreen* ptr = dynamic_cast<TitleScreen*>(mActiveUI)){
			//Get current button states
	     int titleState = mActiveUI->eventHandler(mEvent);
	     //If start button is clicked
	     if(titleState & TITLE_START){ transition(GAME); mActiveUI=&mControls; mbRoll = 1; mbRunning = 1; mbIgnoreRecovery = 1; initGame(); }
	     //If continue button is clicked
	     else if(titleState & TITLE_CONTINUE){ transition(GAME); mActiveUI=&mControls; mbRoll = 1; mbRunning = 1; initGame(); }
	     //If quit button is clicked
	     else if(titleState & TITLE_QUIT){ quit = 1;}
		}
		
		//If on win screen
		else if(WinScreen* ptr = dynamic_cast<WinScreen*>(mActiveUI)){
			//Get current button states
	     int winState = mActiveUI->eventHandler(mEvent);
	     //If restart button is clicked
	     if(winState & WIN_RESTART){ transition(GAME); mActiveUI=&mControls; mbRunning = 1; mbRoll = 1; mbIgnoreRecovery = 1; initGame(); }
	     //If exit button is clicked
	     else if(winState & WIN_QUIT){ quit = 1; }
		}
		
		//If on game screen
		else if(Controls* ptr = dynamic_cast<Controls*>(mActiveUI)){
			//Get current button states
			int controlsState = mControls.eventHandler(mEvent);
			//If rules button is clicked
			if(controlsState & CONTROLS_RULES){ transition(RULES1); mActiveUI=&mInfoScreen; mbRunning = 0; }
			//If quit button is clicked
			else if(controlsState & CONTROLS_QUIT) quit = 1;
	
			//If dice is rolling
			if(mbRoll){
				//If player clicked the dice
				if(mDice[mTurnOrder.front()->getEColor()-1]->Event(mEvent)){
					//Clear roll flag
					mbRoll = 0;
					//Play SFX
					if(miCurrentRoll[mTurnOrder.front()->getEColor()-1]==6) Sound::play(ON_SIX);
					else Sound::play(ON_DICE);
					delay(500);
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
	
	//Render sprites 
	if(meScreen==GAME) renderSprite();

    //Render UI
	renderUI();

	//Set transition state
	mbTransitionState = mbTransition;
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
		mBoardHighlghters[mActiveHighlighters[i].second][mActiveHighlighters[i].first].render();
    
	//Render player sprites
    for(unsigned i = 0; i < mTurnOrder.size(); ++i){
        //Get player pawn screen coordinates
        vector<pair<int,int> > pos;
        //Traverse current player pawns
        for(unsigned j = 0; j < mTurnOrder[i]->m_vPawns.size(); ++j){
                //Get pawn screen coordinates
                pos.push_back(getCoords(mTurnOrder[i]->m_vPawns[j]->getIXPosition(), mTurnOrder[i]->m_vPawns[j]->getIYPosition()));
            }
        //Render pawns
        mTurnOrder[i]->Render(pos);
    }	
	
	//Render dice
	for(unsigned i = 0; i < PLAYERS; ++i)
		mDice[i]->render();
}

//Render UI
void Game::renderUI(){

	//If transition has finished
	if(!mbTransition && mbTransitionState) mActiveUI->fadeIn();	
	//If transition has started
	else if(mbTransition && !mbTransitionState) mActiveUI->fadeOut();
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

#ifdef DEBUG
	cout << "Player " << p->getEColor() << " rolled " << p->getIDiceRoll() << endl;
#endif
		
		//Save recovery data
		Recovery::WriteXML(mTurnOrder, 1);
		
		//Set player roll
		p->setIDiceRoll(miCurrentRoll[p->getEColor()-1]);
		mDice[p->getEColor()-1]->setDiceResult(miCurrentRoll[p->getEColor()-1]);

	/*	switch(p->getEColor()){
				case YELLOW: p->setIDiceRoll(6); break;
				case RED: p->setIDiceRoll(4); break;
				default: p->setIDiceRoll(2); break;
		}
	*/
		//If roll is a 6 get another turn
		//if(p->getIDiceRoll()==6) mTurnOrder.push_front(p);
		
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
					cout << "Selected pawn: " << p->m_vPawns[i]->getEColor() << endl;
					//Move pawn forward
					movePawn(p->m_vPawns[i], p->getIDiceRoll());
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
			else movePawn(mBoardVector[choice.first][choice.second].front(), p->getIDiceRoll());	
		}
	
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
				//Cycle players
				mTurnOrder.push_back(mTurnOrder.front());
				//Remove current player from queue
				mTurnOrder.pop_front();
			}
	
			//Save recovery data
			Recovery::WriteXML(mTurnOrder);	
		
			//Raise roll flag for next turn
			mbRoll = 1;

#ifdef DEBUG
		cout << endl << endl;
#endif
		}
		}
	}
}

//Determine turn order
void Game::determineTurnOrder(){
#ifdef DEBUG
	cout << "DetermineTurnOrder called" << endl;
#endif
	//Clear old data if existing
	for(unsigned i = 0; i < mTurnOrder.size(); ++i){
		delete mTurnOrder.front();
		mTurnOrder.pop_front();
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

	if((SDL_GetTicks()-miDiceTimer)>100){
		//Save current roll
		miCurrentRoll[mTurnOrder.front()->getEColor()-1] = mDice[mTurnOrder.front()->getEColor()-1]->roll();
		//Reset timer
		miDiceTimer = SDL_GetTicks();
		//Play SFX
		Sound::play(ON_ROLL);
	}
	
}

//Pawn movement
void Game::movePawn(Pawn * p, int with){
#ifdef DEBUG
	cout << "MovePawn called with " << p->getEColor() << " " << with << endl;
#endif

	//Use safe zone directions flag
	bool useSafe = 0;
	//Is on final square flag
	bool finished = 0;

	//New pawn position container
	pair<int,int> newPos = {p->getIXPosition(), p->getIYPosition()};
	//Remaining moves
	int remainder = 0;
	//Calculate new position
	for(int i = 0; i < with; ++i){

		//If final square is reached
		if(isFinal(newPos.first, newPos.second, p->getEColor())){
			cout << "Final square" << endl;
			//Get remaining moves
			remainder = with-i;
			finished = 1;
			break;
		}
		//If entry point is reached
		else if(isEntry(newPos.first, newPos.second, p->getEColor())){
			cout << "Safe zone entry" << endl;
			useSafe = 1;
		}

		//Temporary coordinate holder
		pair<int,int> tmp = newPos;
		//If on safe squares
		if(useSafe){
			tmp.first+=NEXT_SAFE[p->getEColor()-1].first;
			tmp.second+=NEXT_SAFE[p->getEColor()-1].second;
		}
		//If on active squares
	   	else {
			tmp.first+=NEXT_SQUARE[newPos.second][newPos.first].first;
			tmp.second+=NEXT_SQUARE[newPos.second][newPos.first].second;
		}
		//Assign new coordinates
		newPos.first = tmp.first;
		newPos.second = tmp.second;	
	}
	//If on active squares
	if(!useSafe && !finished) collision(p,newPos.first, newPos.second);
	//If on final squares
   	else if(finished){
		//If final space is occupied
		if(mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second][remainder-1]->getEColor()!=NONE)
			return;
		//If final space is unoccupied
		else{
			//Delete pawn placeholder
			delete mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second][remainder-1];
			//Set pawn finish flag
			p->setBFinished(1);
			//Place pawn in final vector
			mBoardVector[FINAL_SQUARES[p->getEColor()-1].first][FINAL_SQUARES[p->getEColor()-1].second][remainder-1] = p;	
			//Decrease player active counter
			mTurnOrder.front()->setIActivePawns(mTurnOrder.front()->getIActivePawns()-1);

#ifdef DEBUG
			cout << "Pawn finished" << endl;
#endif
		}
	}
#ifdef DEBUG
	cout << "Setting position at (" << newPos.first << ", " << newPos.second << ")" << endl;
#endif
	
	//Place pawn in new location
	if(!finished) mBoardVector[newPos.first][newPos.second].push_back(p);
	//Remove pawn from old location
	mBoardVector[p->getIXPosition()][p->getIYPosition()].pop_back();
	//Set pawn position
	p->setIXPosition(newPos.first);
	p->setIYPosition(newPos.second);
	//Add roll to player step count
	mTurnOrder.front()->setISteps(mTurnOrder.front()->getISteps()+(with-remainder));

#ifdef DEBUG		
	cout << "Moved to (" << newPos.first << ", " << newPos.second << ")" << endl;
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
			while(mBoardVector[pX][pY].size()){
				//Find free base coords
				pair<int,int> base;
				for(int i = 0; i < PAWNS; ++i){
					base = BASE_SQUARES[mBoardVector[pX][pY].back()->getEColor()-1][i];
					if(!mBoardVector[base.first][base.second].size()) break;
				}
				//Set pawn position
				mBoardVector[pX][pY].back()->setIXPosition(base.first);
				mBoardVector[pX][pY].back()->setIYPosition(base.second);
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
	mBoardHighlghters[pY][pX].setSize(SQUARE_SIZE, SQUARE_SIZE);
	mBoardHighlghters[pY][pX].setLocation(coords.first-10, coords.second-10);

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
			if(mBoardHighlghters[mActiveHighlighters[i].second][mActiveHighlighters[i].first].isClicked(mEvent)){
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
		SDL_RenderPresent(mRenderer);
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
			collision(p->m_vPawns[i], p->m_vPawns[i]->getIXPosition(), p->m_vPawns[i]->getIYPosition());
			//Place pawn location on start position
			p->m_vPawns[i]->setIXPosition(START_SQUARES[p->getEColor()-1].first);
			p->m_vPawns[i]->setIYPosition(START_SQUARES[p->getEColor()-1].second);
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
pair<int, int> Game::getCoords(int pX, int pY){
    
#ifdef DEBUG
	//cout << "GetCoords called with " << c << " " << p <<endl;
#endif
	
	//Return coordinate pair
	return pair<int,int> {pX*SQUARE_SIZE+X_OFF, pY*SQUARE_SIZE+Y_OFF};	
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

//Determine if player has finished
bool Game::hasFinished(Player* p){
	for(unsigned i = 0; i < p->m_vPawns.size(); ++i)
		if(!p->m_vPawns[i]->getBFinished()) return 0;
	return 1;
}


//Screen transition
void Game::transition(Screens to){
#ifdef DEBUG
	cout << "Transition called with " << to << endl;
#endif	

	//Transitioning coordinates
	int newX, newY;
	
	//Determine coordinates
	switch(to){
		case BLANK: newX = 0; newY = 0; break;
		case RULES1: newX = -800; newY = 0; break;
		case RULES2: newX = -1600; newY = 0; break;
		case TITLE: newX = 0; newY = -800; break;
		case GAME: newX = -800; newY = -800; break;
		case WIN: newX = -1600; newY = -800; break;
	}

	//Keep old coordinates
	int oldX = miCameraX;
	int oldY = miCameraY;
	//Find direction vectors
	int vX = newX-oldX;
	int vY = newY-oldY;
	//Find line length
	int length = sqrt(vX*vX+vY*vY);
	//If length is 0
	if(!length) return;
	//Normalize vectors
	vX/=length; vY/=length;

	//Set transition flag
	mbTransition = 1;

	//Traverse line
	for(int i = 0; i < length; i++){
		//Calculate coordinates
		miCameraX = (int)((float)oldX + vX*i);
		miCameraY = (int)((float)oldY + vY*i);
		//eventHandler();
		if(i%12==0){
			render();
			SDL_RenderPresent(mRenderer);
		}
	}

	//Lower transition flag
	mbTransition = 0;

	//Assign screen to variable
	meScreen = to;
}

//Destructor
Game::~Game()
{
	//Release unused pawn placeholders
	for(int i = 0; i < PLAYERS; ++i)
		for(int j = 0; j < PAWNS; ++j)
			if(!mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].back()->getEColor()){
				delete mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].back();
				mBoardVector[FINAL_SQUARES[i].first][FINAL_SQUARES[i].second].pop_back();
			}

	//Release player data
    for(unsigned i = 0; i < mTurnOrder.size(); ++i)
		delete mTurnOrder[i];
	
	//Release dice data
	for(unsigned i = 0; i < PLAYERS; ++i)
		delete mDice[i];

	//Release font
	TTF_CloseFont(mFont);
}
