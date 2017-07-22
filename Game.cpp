#include "Game.h"

//Default constructor
Game::Game(){}

//Game loop
void Game::loop(){
    //Handle events
	eventHandler();
	
	if(mbRules){
		mInfoScreen.render();
	}

	//On game title screen
	if(mbTitle){
		mTitleScreen.render();
	}

	//On gameplay loop
	else if(mbLoop){

#ifdef DEBUG
		cout << "Active: ";
		for(unsigned i = 0; i < BOARD_LENGTH+10; ++i) cout << mPawnsOnSquare[i];
		cout << endl;
		cout << "Pawns:  ";
		for(unsigned i = 0; i < BOARD_LENGTH+10; ++i) cout << (!mBoardLayout[i]?NONE:mBoardLayout[i]->getEColor());
		cout << endl;
#endif
					
		//Render objects
		render();
		
		//Execute player turn
	//	for(unsigned i = 0; i < turnOrder.size(); i++)
	//		if(turnOrder[i]->getEColor()==YELLOW){ turn(turnOrder[i]); break; }
		turn(mTurnOrder.front());

		//Increment turn counter
		miTurns++;
	}

	//On game win
	else if(mbWin){
		mWinScreen.loadData(mTurnOrder);
		mWinScreen.render();
	}
}

//Event container setter
void Game::setEvent(SDL_Event& event){
    this->mEvent = event;
}

//Game inititalizing method
void Game::init(){
    
#ifdef DEBUG
	cout << "InitGame called" << endl;
#endif
    //Load game font
    mFont = TTF_OpenFont(FONT_PATH, 15);
    if(mFont==NULL) cerr << "Font error: " << TTF_GetError() << endl;
    
	//Initialize dice objects
	for(int i = 0; i < PLAYERS; ++i){
		mDice.push_back(new Dice);
		mDice.back()->setPosition(DICE_POS[i].first, DICE_POS[i].second);
	}
	
	//Refresh RNG seed
	mDice.back()->init();

	//Load game board texture
	mBoard.load(BOARD_PATH);

	//Initialize highlighters
	for(int i = 0; i < BOARD_LENGTH+6; ++i)
		mBoardHighlghters[i].setTexture(HIGHLIGHTER_PATH);

    //Initialize UI
    mTitleScreen.init();
    mWinScreen.setFont(mFont);
    mWinScreen.init();
	mInfoScreen.init();
	mControls.init();

	//Try to recover state from XML	
	mTurnOrder = Recovery::ReadFromXML();
	if(!mTurnOrder.size() || mbIgnoreRecovery){
	   cout << "Starting new game" << endl;
   	   determineTurnOrder();
	} else {
		cout << "Recovering state" << endl;
	
	//Set player data
		for(unsigned i = 0; i < mTurnOrder.size(); ++i){
			for(unsigned j = 0; j < mTurnOrder[i]->m_vPawns.size(); ++j){
				if(mTurnOrder[i]->m_vPawns[j]->getIPosition()>-1){
					mPawnsOnSquare[mTurnOrder[i]->m_vPawns[j]->getIPosition()]++;
					mBoardLayout[mTurnOrder[i]->m_vPawns[j]->getIPosition()] = mTurnOrder[i]->m_vPawns[j];
				}
			}
		}
		cout << "Player data:" << endl;
		Recovery::Print(mTurnOrder);
	}
}

//Event handler
void Game::eventHandler(){
    //If on title screen
    if(mbTitle){
        //Get current button states
        int titleState = mTitleScreen.eventHandler(mEvent);
        //If start button is clicked
        if(titleState & TITLE_START){ mbTitle = 0; mbLoop = 1; mbRoll = 1; mbIgnoreRecovery = 1; }
        //If continue button is clicked
        else if(titleState & TITLE_CONTINUE){ mbTitle = 0; mbLoop = 1; mbRoll = 1; }
        //If quit button is clicked
        else if(titleState & TITLE_QUIT){ mbTitle = 0; mbLoop = 0; mbWin = 0; }
    }
    //If on win screen
    else if(mbWin){
        //Get current button states
        int winState = mWinScreen.eventHandler(mEvent);
        //If restart button is clicked
        if(winState & WIN_RESTART){ mbWin = 0; mbTitle = 0; mbLoop = 1; mbIgnoreRecovery = 1; }
        //If exit button is clicked
        else if(winState & WIN_QUIT){ mbWin = 0; mbTitle = 0; mbLoop = 0; }
    }
	//If on rules screen
	else if(mbRules){
		if(mInfoScreen.eventHandler(mEvent)) mbRules = 0;
	}
	//If on game screen
	else {
		//Get current button states
		int controlsState = mControls.eventHandler(mEvent);
		//If rules button is clicked
		if(controlsState & CONTROLS_RULES) mbRules = 1;
		//If quit button is clicked
		if(controlsState & CONTROLS_QUIT) quit = 1;
	}
}

//Render all assets
void Game::render(){

#ifdef DEBUG
	//cout << "Render called" << endl;
#endif

    //Draw game board;
    mBoard.render(0,0);
    
    //Render highlighters
    for(unsigned i = 0; i < mActiveHighlighters.size(); ++i)
        mBoardHighlghters[mActiveHighlighters[i]].render();
    
    //Draw player sprites
    for(unsigned i = 0; i < mTurnOrder.size(); ++i){
        //Get player pawn screen coordinates
        vector<pair<int,int> > pos;
        //Found pawns counter
        int pawnCounter = 0;
        //Traverse current player pawns
        for(unsigned j = 0; j < mTurnOrder[i]->m_vPawns.size(); ++j){
            //If current pawn is active
            if(mTurnOrder[i]->m_vPawns[j]->getIPosition()>=0){
                //Get pawn screen coordinates
                pos.push_back(getCoords(mTurnOrder[i]->getEColor(), mTurnOrder[i]->m_vPawns[j]->getIPosition()));
                //Increment counter
                pawnCounter++;
            }
            //If all active pawns are found
            if(pawnCounter==mTurnOrder[i]->getIActivePawns()) break;
        }
        
        //Idle pawn coordinate holder
        pair<int, int> idleCoords = getCoords(mTurnOrder[i]->getEColor(),-1);
        //Draw idle pawns
        for(int j = 0; j < PAWNS-pawnCounter; ++j){
            //Position pawns correctly
            switch(mTurnOrder[i]->getEColor()){
                case YELLOW: idleCoords.first-=SQUARE_SIZE; break;
                case RED: idleCoords.second+=SQUARE_SIZE; break;
                case BLUE: idleCoords.first+=SQUARE_SIZE; break;
                case NONE: break;
            }
            pos.push_back(idleCoords);
        }
        //Render pawns
        mTurnOrder[i]->Render(pos);
    }

	//Render dice
	for(unsigned i = 0; i < mDice.size(); ++i)
		mDice[i]->render();

	//Render controls
	mControls.render();
}

//Player turn
void Game::turn(Player * p){
    
#ifdef DEBUG
	cout << "Turn called with " << p->getEColor() << endl;
#endif
    
	//If player has rolled before recovery
	if(!Recovery::hasRolled && mbRoll){
		//Roll the dice
		diceRoll();
	} else {

#ifdef DEBUG
	cout << "Player " << p->getEColor() << " rolled " << p->getIDiceRoll() << endl;
#endif
	//Save recovery data
	//Recovery::WriteXML(turnOrder, 1);
	
	//Set player roll
	p->setIDiceRoll(miCurrentRoll);
	
	switch(p->getEColor()){
			case YELLOW: p->setIDiceRoll(6); break;
			case RED: p->setIDiceRoll(4); break;
			default: p->setIDiceRoll(2); break;
	}

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
			if(p->m_vPawns[i]->getIPosition()!=-1){
				cout << "Selected pawn: " << p->m_vPawns[i]->getIPosition() << endl;
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
			//If roll is a 6
			if(p->getIDiceRoll()==6 && p->getIActivePawns()!=PAWNS){
				//Highlight base
				highlight(-1,p->getEColor());
			}
			//Active pawn counter
			int activeCount = 0;	
			//Traverse the board
			for(unsigned i = 0; i < p->m_vPawns.size(); ++i){
				//Find active ones
				if(p->m_vPawns[i]->getIPosition()!=-1){
					//Highlight active pawn
					highlight(p->m_vPawns[i]->getIPosition(), p->getEColor());	
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
		int choice = getHighlightedChoice();
		//If base is selected
		if(choice==-1) activatePawn(p);
		//If field is selected
		else if(choice>=0) movePawn(mBoardLayout[choice], p->getIDiceRoll());	
	}

	//If no highlighters are active
	if(!mbHighlight){	
		//Cycle players
		mTurnOrder.push_back(mTurnOrder.front());
		//Remove current player from queue
		mTurnOrder.pop_front();

		//Save recovery data
	//	Recovery::WriteXML(turnOrder);	
	
		//Raise roll flag for next turn
		mbRoll = 1;
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
	cout << "DiceRoll called" << endl;
#endif

	if((SDL_GetTicks()-miDiceTimer)>100){
		//Save current roll
		miCurrentRoll = mDice[mTurnOrder.front()->getEColor()-1]->roll();
		//Reset timer
		miDiceTimer = SDL_GetTicks();
		//Play SFX
		Sound::play(ON_ROLL);
	}
	//If player clicked the dice
	if(mDice[mTurnOrder.front()->getEColor()-1]->Event(mEvent)){
		//Clear roll flag
		mbRoll = 0;
		//Play SFX
		Sound::play(ON_DICE);
		delay(500);
	}
}

//Pawn movement
void Game::movePawn(Pawn * p, int with){
#ifdef DEBUG
	cout << "MovePawn called with " << p->getIPosition() << " " << with << endl;
#endif

	int to = p->getIPosition()+with;
	//If on active squares
	if(getRelative(p->getEColor(), p->getIPosition()+with)<BOARD_LENGTH) collision(p,to);
	//If on final squares
   	else if(getRelative(p->getEColor(), p->getIPosition()+with)>BOARD_LENGTH+5){
		//Traverse current player pawns
		for(unsigned i = 0; i < mTurnOrder.front()->m_vPawns.size(); ++i){
			//If final space is occupied
			if(mTurnOrder.front()->m_vPawns[i]->getIPosition()==to)
				//Cancel movement
				return;
		}
	}

	cout << "Setting position at " << to << endl;
	//Place pawn in new location
	mBoardLayout[to] = mBoardLayout[p->getIPosition()];
	//Decrease old position pawn counter
	mPawnsOnSquare[p->getIPosition()]--;
	//Increase board pawn counter
	mPawnsOnSquare[to]++;
	//NULL if no more pawns on old position
	if(!mPawnsOnSquare[p->getIPosition()]) mBoardLayout[p->getIPosition()] = NULL;
	//Move pawn forward
	p->setIPosition(to);
	//Add roll to player step count
	mTurnOrder.front()->setISteps(mTurnOrder.front()->getISteps()+with);

#ifdef DEBUG		
	cout << "Moved from " << p->getIPosition() << " with " << mPawnsOnSquare[p->getIPosition()] << " pawns" << endl;
	cout << "Moved to " << to << " with " << mPawnsOnSquare[to] << " pawns" << endl;
#endif	

		//Play SFX
		Sound::play(ON_MOVE);
}

//Collision detection
void Game::collision(Pawn * p, int to){
#ifdef DEBUG
	cout << "Collision called with " << p->getEColor() << " " << to << endl;
#endif
	//If space is already occupied
	if(mPawnsOnSquare[to]!=0){
		//If occupant is a different player
		if(mBoardLayout[to]->getEColor()!=p->getEColor()){
			//Return other pawn to base
			mBoardLayout[to]->setIPosition(-1);
			//Go through players to find occupying pawn owner
			for(unsigned i = 1; i < mTurnOrder.size(); ++i){
				if(mBoardLayout[to]->getEColor()==mTurnOrder[i]->getEColor()){
					//Add to other pawns' owners' lost counter
					mTurnOrder[i]->setILost(mTurnOrder[i]->getILost()+1);
					//Decrease other players' active pawn counter
					mTurnOrder[i]->setIActivePawns(mTurnOrder[i]->getIActivePawns()-1);
					//Decrease board pawn counter
					mPawnsOnSquare[to]--;
					//Play SFX
					Sound::play(ON_COLLISION);
					break;
				}
			}	
			//Add to current players' taken counter
			mTurnOrder.front()->setITaken(mTurnOrder.front()->getITaken()+1);
			cout << mTurnOrder.front()->getEColor() << " took pawn on " << to << endl;
		}
	}
}

//Board square highlighter
void Game::highlight(int index, Colors c){
#ifdef DEBUG
	cout << "Highlight called with " << index << " " << c << endl;
#endif
	//Get current square screen coordinates
	pair<int, int> coords;
	if(index==-1){
		coords = getCoords(c, getAbsolute(c));
		//Position base highlighter
		switch(c){
			case YELLOW: coords.first-=SQUARE_SIZE; break;
			case RED: coords.second+=SQUARE_SIZE; break;
			case BLUE: coords.first+=SQUARE_SIZE; break;
			case NONE: break;
		}
	} else coords = getCoords(mBoardLayout[index]->getEColor(), index);
	//Set highlighter params
	mBoardHighlghters[index+1].setSize(SQUARE_SIZE, SQUARE_SIZE);
	mBoardHighlghters[index+1].setLocation(coords.first-10, coords.second-10);

#ifdef DEBUG
	cout << "Adding highlighter at " << coords.first << " " << coords.second << endl;
#endif
	
	//Add to active highlighter list
	mActiveHighlighters.push_back(index+1);
}

//Highlighted squares event handler
int Game::getHighlightedChoice(){
#ifdef DEBUG
	cout << "GetHighlightedChoice called" << endl;
#endif
	//If active highlighters exist
	if(mActiveHighlighters.size()){
		cout << "Active on ";
		for(unsigned i = 0; i < mActiveHighlighters.size(); i++) cout << (mActiveHighlighters[i]-1) << " ";
		cout << endl;
		//Traverse active highlighters
		for(unsigned i = 0; i < mActiveHighlighters.size(); ++i){
			//If clicked
			if(mBoardHighlghters[mActiveHighlighters[i]].isClicked(mEvent)){
				//Save board index before clearing
				int choice = mActiveHighlighters[i];
				//Clear active highlighters
				while(mActiveHighlighters.size()>0) mActiveHighlighters.pop_back();
				//Play SFX
				Sound::play(camera);
				//Lower highlighter flag
				mbHighlight = 0;
				//Return selected index
				return choice-1;
			}
		}
	}
	//Return invalid value if nothing is selected
	return -2;
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
		if(p->m_vPawns[i]->getIPosition()==-1){
			//Check for collisions
			collision(p->m_vPawns[i], getAbsolute(p->getEColor()));
			//Place pawn on start position
			p->m_vPawns[i]->setIPosition(getAbsolute(p->getEColor()));
			//Place pawn on game board
			mBoardLayout[getAbsolute(p->getEColor())] = p->m_vPawns[i];
			//Increase board pawn counter
			mPawnsOnSquare[getAbsolute(p->getEColor())]++;
			//Increment player active counter
			p->setIActivePawns(p->getIActivePawns()+1);
			//Play SFX
			Sound::play(ON_ACTIVATION);
			break;
		}
	}
}

//Get world coordinates from array index
pair<int, int> Game::getCoords(Colors c, int p){
    
#ifdef DEBUG
	//cout << "GetCoords called with " << c << " " << p <<endl;
#endif
	//Coordinate pair object
	pair<int, int> coords = {ZERO_X_POS, ZERO_Y_POS};
	
	//If in base
	if(p<0){
		coords.first = IDLE_POS[c-1].first;
		coords.second = IDLE_POS[c-1].second;
	}
	//If on active squares
   	else if(p<BOARD_LENGTH){
		for(int i = 0; i < p; ++i){
			coords.first+=NEXT_SQUARE[i].first*SQUARE_SIZE;
			coords.second+=NEXT_SQUARE[i].second*SQUARE_SIZE;
		}
	}
	//If on safe squares
	else if(p<BOARD_LENGTH+5){
		//Find safe zone entry point
		int entry = getAbsolute(c, BOARD_LENGTH-1);
		for(int i = 0; i < entry; ++i){
			coords.first+=NEXT_SQUARE[i].first;
			coords.second+=NEXT_SQUARE[i].second;
		}
		for(int i = 0; i < p-entry; ++i){
			coords.first+=SAFE_SQUARE[i].first;
			coords.second+=SAFE_SQUARE[i].second;
		}
	}
	//If on final squares
   	else {
		coords.first = FINAL_SQUARE[c-1].first;
		coords.second = FINAL_SQUARE[c-1].second;
		for(int i = 0; i < p-(BOARD_LENGTH+5); ++i){
			coords.first+=SPRITE_SCALE[2];
		}
	}
	
	//Return coordinate pair
	return coords;
}

//Get absolute position
int Game::getAbsolute(Colors c, int pos){
	//If in base
	if(pos<0) return -1;
	//If on safe squares
	if(pos>BOARD_LENGTH) return pos;
	//If on active squares
	return (START_POS[c-1]+pos)%BOARD_LENGTH;
}

//Get relative position
int Game::getRelative(Colors c, int pos){
	//If in base
	if(pos<0) return -1;
	//If on safe squares
	if(pos>BOARD_LENGTH) return pos;
	//If on active squares
	return (START_POS[c-1]-pos)%BOARD_LENGTH;
}

//Destructor
Game::~Game(){
    for(unsigned i = 0; i < mTurnOrder.size(); ++i)
		delete mTurnOrder[i];

	for(unsigned i = 0; i < mDice.size(); ++i)
		delete mDice[i];

	//Release font
	TTF_CloseFont(mFont);
}
