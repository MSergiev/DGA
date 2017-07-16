//-----------------------------
//-----------INCLUDES----------
//-----------------------------

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

//Include local modules
#include "Shared.h"
#include "Board.h"
#include "Player.h"
#include "Sound.h"
#include "Dice.h"
#include "Button.h"
//#include "Recovery.h"

//Misc library inclusion
#include <iostream>
using std::cerr;
using std::endl;
#include <vector>
using std::vector;
#include <deque>
using std::deque;
#include <algorithm>
using std::random_shuffle;

//-----------------------------
//----------VARIABLES----------
//-----------------------------

//SDL attributes
SDL_Window* window;
SDL_Renderer* renderer;

//Exit flag
bool quit = 0;

//Game state flags
bool title = 0;
bool loop = 1;
bool win = 0;

//Player pawn selection flag
bool canSelect = 0;

//SDL event container
SDL_Event event;

//Game font
TTF_Font* font;

//Game board
Board board;

//Button object
Button button(600, 600, 100, 60);

//Dice object
Dice dice;

//Active board layout (top row leftmost square considered 1)
Pawn* boardLayout[BOARD_LENGTH+10] = {NULL};
unsigned pawnsOnSquare[BOARD_LENGTH+10] = {0};

//Board highlighter array
Button boardHighlghters[BOARD_LENGTH+6];

//Turn counter
int turns = 0;

//Ordered player container
deque<Player*> turnOrder;

//Active highlighter vector
vector<int> activeHighlighters;

//-----------------------------
//---------PROTOTYPES----------
//-----------------------------

//SDL initializing function
bool init();

//Event handler
void eventHandler();

//Resource freeing function
void free();

//Get screen coordinates from pawn position
//Args:
//Colors c - pawn color
//int p - pawn position
pair<int, int> getCoords(Colors c, int p);

//Player turn
//Args:
//Player *p - pointer to active player
void turn(Player *p);

//Determine turn order
void determineTurnOrder();

//Roll the dice
int diceRoll();

//Move pawn
//Args:
//Player* pl - pawn owner pointer
//Pawn* p - pawn pointer
//int from - index on board array to move it from
//int with - amount of spaces to move it with
void movePawn(Player* pl, Pawn* p, int from, int with);

//Collision detection
//Args:
//Player* pl - pawn owner pointer
//Pawn* p - pawn pointer
//int to - index on board array to move to
void collision(Player* pl, Pawn* p, int to);

//Pawn highlighter
//Args:
//int index - square index to highlight
//Colors c - color for base selection (not required)
void highlight(int index, Colors c = NONE);

//Highlighted squares event handler
int getHighlightedChoice();

//Delay
//Args:
//Uint32 ms - milliseconds to delay for
void delay(Uint32 ms);

//Render all assets
void render();

//Activate pawn
//Args:
//Player p* - pointer to player
void activatePawn(Player* p);

//-----------------------------
//------------MAIN-------------
//-----------------------------

int main(int argc, char* argv[]){
	//Unused warning elimination
	argc = 0; argv = 0;

	//Initialize SDL
	if(!init()) return 1;

	//Play BGM
	//Sound::music(rock);
	

	//Game loop
	while(!quit){
		//On game title screen
		while(title){
		}
		
		//On game loop
		while(loop){
			//Handle events
			eventHandler();
			
			//Render objects
			render();
			
			//Cycle players
			turnOrder.push_back(turnOrder.front());
			//Execute player turns
			turn(turnOrder.front());
			//Remove current player from queue
			turnOrder.pop_front();

			//Increment turn counter
			turns++;

			//Draw on screen
			SDL_RenderPresent(renderer);
		}
	
		//On game win
		while(win){
		}
	}

	//Free resources
	free();


	// 	if you want to see how Recovery class works:
		// Statistics is a class that I needed to make for help
		// but i think it is going to be helpful
		//vector<Player> mP;
	 	// to use ReadFromXML method you need to make an object of Recovery class
		//Recovery r;
		// ReadFromXML returns a vector<Player> value
		//mP = r.ReadFromXML();
		// print the value of the xml file:
		//r.Print(mP);
		// writes the statistics in the same file
		//r.WriteXML(mP);


	//Successful exit
	return 0;
}




//-----------------------------
//----------FUNCTIONS----------
//-----------------------------

//Render all assets
void render(){
	//Clear screen
		//SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		//SDL_RenderClear(renderer);

		//Draw game board;
		board.render();
		
		//Draw button
		button.render();
		
		//Render highlighters
		for(unsigned i = 0; i < activeHighlighters.size(); ++i)
			boardHighlghters[activeHighlighters[i]].render();
		
		//Draw player sprites
		for(unsigned i = 0; i < turnOrder.size(); ++i){
			//Get player pawn screen coordinates
			vector<pair<int,int> > pos;
			//Found pawns counter
			int pawnCounter = 0;
			//Traverse current player pawns
			for(unsigned j = 0; j < turnOrder[i]->m_vPawns.size(); ++j){
				//If current pawn is active
				if(turnOrder[i]->m_vPawns[j]->getIPosition()!=-1){
					//Get pawn screen coordinates
					pos.push_back(getCoords(turnOrder[i]->getEColor(), turnOrder[i]->m_vPawns[j]->getIPosition()));
					//Increment counter
					pawnCounter++;
				}
				//If all active pawns are found
				if(pawnCounter==turnOrder[i]->getIActivePawns()) break;
			}
			
			//Idle pawn coordinate holder
			pair<int, int> idleCoords = getCoords(turnOrder[i]->getEColor(), START_POS[turnOrder[i]->getEColor()-1]);
			//Draw idle pawns
			for(int j = 0; j < 5-pawnCounter; ++j){
				//Position pawns correctly
				switch(turnOrder[i]->getEColor()){
					case YELLOW: idleCoords.first-=SQUARE_SIZE; break;
					case RED: idleCoords.second+=SQUARE_SIZE; break;
					case BLUE: idleCoords.first+=SQUARE_SIZE; break;
					case NONE: break;
				}
				pos.push_back(idleCoords);
			}
			//Render pawns
			turnOrder[i]->Render(pos);
		}
}


//SDL inititalizing function
bool init(){
	//Success flag
	bool success = 1;

	//Try to initialize SDL_main
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		cerr << "SDL Error: " << SDL_GetError() << endl;
		success = 0;
	} else {
	//Try to initialize SDL_image
	if(!IMG_Init(IMG_INIT_PNG)){
		cerr << "IMG Error: " << IMG_GetError() << endl;
		success = 0;
	} else {
	//Try to initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
		cerr << "MIX Error: " << Mix_GetError() << endl;
		success = 0;
	} else {
	//Try to initialize SDL_ttf
	if(TTF_Init()==-1){
		cerr << "TTF Error: " << TTF_GetError() << endl;
		success = 0;
	} else {
	//Try to set linear filtering
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			cerr << "- Linear filtering not enabled!" << endl;
		}
		//Create window
		window = SDL_CreateWindow("LUDO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		//Window integrity check
		if(window==NULL){
			cerr << "Window error: " << SDL_GetError() << endl;
			success = 0;
		} else {
			//Create renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
			//Renderer integrity check
			if(renderer==NULL){
				cerr << "Renderer error: " << SDL_GetError() << endl;
				success = 0;
			} else {
				//Load game font
				font = TTF_OpenFont(FONT_PATH, 15);
				if(font==NULL){
					cerr << "Font error: " << TTF_GetError() << endl;
				} else {
					//Initialize game objects
					Sound::load();
					dice.init();
					dice.setRenderer(renderer);
					board.setRenderer(renderer);
					button.setRenderer(renderer);
					button.setLabel("CLICK", font);
					for(int i = 0; i < BOARD_LENGTH+6; ++i)
						boardHighlghters[i].setRenderer(renderer);
					determineTurnOrder();
				}
			}
	}
	}
	}
	}
	}
	//Return success flag
	return success;
}

//Event handler
void eventHandler(){
	while(SDL_PollEvent(&event)!=0){
		//Application quit event
		if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){
			quit = 1;
			title = 0;
			loop = 0;
			win = 0;
		}
		if(button.isClicked(event)) Sound::play(bruh);
	}
}


//Resource freeing function
void free(){
	for(unsigned i = 0; i<turnOrder.size(); ++i)
		delete turnOrder[i];
	
	//Release font
	TTF_CloseFont(font);
	//Release renderer
	SDL_DestroyRenderer(renderer);
	//Release window
	SDL_DestroyWindow(window);
	//SDL Quit functions
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

//Get world coordinates from array index
pair<int, int> getCoords(Colors c, int p){
	//Coordinate pair object
	pair<int, int> coords = {ZERO_X_POS, ZERO_Y_POS};
	//If idle position
	if(p<0){
		coords = {IDLE_POS[c-1][0], IDLE_POS[c-1][1]};
	}
	//If on final squares	
	else if(p>=BOARD_LENGTH){
		//Find entry point
		int entry = START_POS[c-1]-1;
		//Calculate position
		for(int i = 0; i < entry; ++i){
			//If on active board
			if(i<BOARD_LENGTH){
				coords.first+=NEXT_SQUARE[i].first*SQUARE_SIZE;
				coords.second+=NEXT_SQUARE[i].second*SQUARE_SIZE;
			}
		    //If on final 10 squares
			else {	
				coords.first+=FINAL_SQUARE[c-1].first*SQUARE_SIZE;
				coords.second+=FINAL_SQUARE[c-1].second*SQUARE_SIZE;
			}
		}	
	}
	//If on active squares	
	else {
		//Calculate position
		for(int i = 0; i < p; ++i){
			//If on active board
			if(i<BOARD_LENGTH){
				coords.first+=NEXT_SQUARE[i].first*SQUARE_SIZE;
				coords.second+=NEXT_SQUARE[i].second*SQUARE_SIZE;
			}
		}
	}
	//Return coordinate pair
	return coords;
}

//Player turn
void turn(Player *p){
	//Roll the dice
	p->setIDiceRoll(diceRoll());
	p->setIDiceRoll(6);
	cout << "Player " << p->getEColor() << " rolled " << p->getIDiceRoll() << endl;
	delay(500);

	//If roll is a 6 get another turn
	//if(p->getIDiceRoll()==6) turnOrder.push_front(p);
	
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
				//Move pawn forward
				movePawn(p, p->m_vPawns[i], i-1, p->getIDiceRoll());
				break;	
			}
		}
	}
	//If player has more than one active pawn
	else {
		//If roll is a 6
	   	if(p->getIDiceRoll()==6){
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
		
		//Get choice from highlights
		int choice  = getHighlightedChoice();
		//If base is selected, activate pawn
		if(choice<0) activatePawn(p);
		//Else move selected pawn
		else movePawn(p, boardLayout[choice], choice, p->getIDiceRoll());	
	}	
}

//Pawn movement
void movePawn(Player* pl, Pawn* p, int from, int with){
	//If movement is within active range
	if((from+with)<(BOARD_LENGTH)){
		//Move pawn forward
		p->setIPosition((p->getIPosition()+with)%BOARD_LENGTH);
		//Add roll to player step count
		pl->setISteps(pl->getISteps()+with);
		//Check for collisions
		collision(pl, p, from+with);	
		

		//Place pawn in new location
		boardLayout[from+with] = boardLayout[from];
		//Decrease old position pawn counter
		pawnsOnSquare[from]--;
		//Increase board pawn counter
		pawnsOnSquare[from+with]++;
		//NULL if no more pawns on old position
		cout << "Pawns left: " << pawnsOnSquare[from] << endl;
		if(!pawnsOnSquare[from]) boardLayout[from] = NULL;
	}
}

//Collision detection
void collision(Player* pl, Pawn* p, int to){
	//If space is already occupied
	if(pawnsOnSquare[to]!=0){
		//If occupant is a different player
		if(boardLayout[to]->getEColor()!=p->getEColor()){
			//Return other pawn to start
			boardLayout[to]->setIPosition(0);
			//Go through players to find occupying pawn owner
			for(unsigned j = 1; j < turnOrder.size(); ++j){
				if(boardLayout[to]->getEColor()==turnOrder[j]->getEColor()){
					//Add to other pawns' owners' lost counter
					turnOrder[j]->setIHadTaken(turnOrder[j]->getIHadTaken()+1);
					//Decrease other players' active pawn counter
					turnOrder[j]->setIActivePawns(turnOrder[j]->getIActivePawns()-1);
					//Decrease board pawn counter
					pawnsOnSquare[j]--;
					break;
				}
			}	
			//Add to current players' taken counter
			pl->setITaken(pl->getITaken()+1);
			//Play SFX
			Sound::play(suprise);
			cout << pl->getEColor() << " took pawn on " << to << endl;
		}
	}
}

//Dice roll
int diceRoll(){
	//Dice roll variable
	int roll = dice.roll();
	//Wait for player click
	do {
		//Handle events
		eventHandler();
		//Render objects
		render();
		//Animate dice
		roll = dice.roll();
		dice.render();
		SDL_RenderPresent(renderer);
	} while(!dice.Event(event) && !quit);
	//Play SFX
	Sound::play(ding);
	//Return roll	
	return roll;
}

//Activate pawn
void activatePawn(Player* p){
	//Traverse player pawns
	for(unsigned i = 0; i < p->m_vPawns.size(); ++i){
		//If current pawn is inactive
		if(p->m_vPawns[i]->getIPosition()==-1){
			//Place pawn on start position
			p->m_vPawns[i]->setIPosition(START_POS[p->getEColor()-1]);
			//Place pawn on game board
			boardLayout[START_POS[p->getEColor()-1]] = p->m_vPawns[i];
			//Increase board pawn counter
			pawnsOnSquare[START_POS[p->getEColor()-1]]++;
			//Increment player active counter
			p->setIActivePawns(p->getIActivePawns()+1);
			//Check for collisions
			collision(p, p->m_vPawns[i], START_POS[p->getEColor()-1]);
			break;
		}
	}
}

//Board square highlighter
void highlight(int index, Colors c){
	//Highlighter color
	SDL_Color color;
	//Set highlighter color
	switch(c){
		case RED: color = {255,0,0,255}; break;
		case BLUE: color = {0,0,255,255}; break;
		case YELLOW: color = {255,255,0,255}; break;
		case NONE: color = {255,255,255,255};
	}
	//Get current square screen coordinates
	pair<int, int> coords;
	if(index==-1){
		coords = getCoords(c, START_POS[c-1]);
		//Position base highlighter
		switch(c){
			case YELLOW: coords.first-=SQUARE_SIZE; break;
			case RED: coords.second+=SQUARE_SIZE; break;
			case BLUE: coords.first+=SQUARE_SIZE; break;
			case NONE: break;
		}
	} else if(pawnsOnSquare[index])
		coords = getCoords(boardLayout[index]->getEColor(), index);
	//Set highlighter params
	boardHighlghters[index+1].setSize(SQUARE_SIZE, SQUARE_SIZE);
	boardHighlghters[index+1].setLocation(coords.first, coords.second);
	boardHighlghters[index+1].setColor(color);
	//Add to active highlighter list
	activeHighlighters.push_back(index+1);
}

//Highlighted squares event handler
int getHighlightedChoice(){
	//If active highlighters exist
	if(activeHighlighters.size()){
		cout << "Active on ";
		for(unsigned i = 0; i < activeHighlighters.size(); i++) cout << (activeHighlighters[i]-1) << " ";
		cout << endl;
		//Wait for user choice
		while(!quit){
			//Traverse active highlighters
			for(unsigned i = 0; i < activeHighlighters.size(); ++i){
				//If clicked
				if(boardHighlghters[activeHighlighters[i]].isClicked(event)){
					//Save board index before clearing
					int choice = activeHighlighters[i];
					//Clear active highlighters
					while(activeHighlighters.size()>0) activeHighlighters.pop_back();
					//Return pressed index
					return choice-1;
				}
			}
			//Event handler
			eventHandler();
			//Render sprites
			render();
			//Draw image on screen
			SDL_RenderPresent(renderer);
		}
	}
	return 0;
}

//Determine turn order
void determineTurnOrder(){
	//Temporary vector of colors to choose from
	vector<Colors> order = {RED, BLUE, YELLOW};
	//Shuffle vector
	random_shuffle(order.begin(), order.end());
	//Initialize player objects
	for(int i = 0; i < 3; ++i){
		turnOrder.push_back(new Player(order[i]));
		turnOrder.back()->SetRenderer(renderer);
	}
}

//Delay
void delay(Uint32 ms){
	Uint32 timerDelay = SDL_GetTicks();
	while(SDL_GetTicks()-timerDelay<ms && !quit)
		eventHandler();
}
