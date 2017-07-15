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

//Board square layout (top row leftmost square considered 0)
Pawn* boardLayout[BOARD_LENGTH+10] = {NULL};

//Board highlighter array
Colors boardHighlghters[BOARD_LENGTH+10] = {NONE};

//Highlight button objects
Button highlightButtons[5];

//Turn counter
int turns = 0;

//Ordered player container
deque<Player*> turnOrder;

//-----------------------------
//---------PROTOTYPES----------
//-----------------------------

//SDL initializing function
bool init();

//Event handler
void eventHandler();

//Resource freeing function
void free();

//Player to world pawn position converter
//Args:
//Pawn *p - pointer to pawn object
int convert(Pawn *p);

//Get screen coordinates from pawn position
//Args:
//ind index - board array index
pair<int, int> getCoords(int index);

//Get screen coordinates from pawn position
//Args:
//Pawn *p - pointer to pawn object
pair<int, int> getPawnCoords(Pawn *p);

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
//Player* p - pawn owner pointer
//int from - index on board array to move it from
//int with - amount of spaces to move it with
void movePawn(Player* p, int from, int with);

//Collision detection
//Args:
//Player* p - pawn owner pointer
//int from - index on board array of moving pawn
//int to - index on board array to move to
void collision(Player* p, int from, int to);

//Pawn highlighter
//Args:
//vector<int> index - vector of board array indices to highlight
bool highlight(vector<int>& index);

//Delay
//Args:
//Uint32 ms - milliseconds to delay for
void delay(Uint32 ms);

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
	
			//Clear screen
			SDL_SetRenderDrawColor(renderer, 255,255,255,255);
			SDL_RenderClear(renderer);
	
			//Draw game board;
			board.render();
			
			//Draw button
			button.render();

			//Render highlighters
			for(int i = 0; i < 5; ++i)
				highlightButtons[i].render();

			//Execute player turns
			for(int i = 0; i < 3; ++i){
				//Cycle players
				turnOrder.push_back(turnOrder.front());
				turn(turnOrder.front());
				turnOrder.pop_front();
			}

			//Increment turn counter
			turns++;

			//Draw player sprites
			//red.render();
			//for(unsigned i = 0; i < playerVec.size(); ++i)
				//playerVec[i]->render(i*100+100, i*100+100);

			//Render dice
			dice.render();

			//Render image on screen
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
					for(int i = 0; i < 5; i++)
						highlightButtons[i].setRenderer(renderer);
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
	//Release player data
	for(unsigned i = 0; i<turnOrder.size(); ++i){
		delete turnOrder.front();
		turnOrder.pop_front();
	}

	//Release board data
	board.free();
	//Release renderer
	SDL_DestroyRenderer(renderer);
	//Release window
	SDL_DestroyWindow(window);
	//SDL Quit functions
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

//Player to world pawn position converter
int convert(Pawn* p){
	return (START_POS[p->getEColor()-1]+p->getUiPosition())%BOARD_LENGTH;
}

//Get screen coordinates from pawn position
pair<int, int> getPawnCoords(Pawn *p){
	//Get world position
	int converted = convert(p);
	//Return coordinate pair
	return getCoords(converted);
}

//Get world coordinates from array index
pair<int, int> getCoords(int index){
	//Coordinate pair object
	pair<int, int> coords = {ZERO_X_POS, ZERO_Y_POS};
	//Calculate position
	for(int i = 0; i < index; ++i){
		coords.first+=NEXT_SQUARE[i].first*SQUARE_SIZE;
		coords.second+=NEXT_SQUARE[i].second*SQUARE_SIZE;
	}	
	//Return coordinate pair
	return coords;
}

//Player turn
void turn(Player *p){
	//Roll the dice
	p->setIDiceRoll(diceRoll());
	cout << "Player " << p->getEColor() << " rolled " << p->getIDiceRoll() << endl;
	delay(500);

	//If roll is a 6
	if(p->getIDiceRoll()==6){
		//Give player another turn
		turnOrder.push_front(p);
		//Offer to add a new pawn
	}
	//If player has only one active pawn
	if(p->getIActivePawns()==1){
		//Traverse the board
		for(int i = 0; i < BOARD_LENGTH; ++i){
			//If pawn and player colors match
			if(boardLayout[i]->getEColor() == p->getEColor()){
				//Move pawn forward
				movePawn(p, i, p->getIDiceRoll());
				break;	
			}
		}
	//If player has more than one active pawn
	} else {

	}	
}

//Pawn movement
void movePawn(Player* p, int from, int with){
	//If movement is within range
	if(boardLayout[from]->getUiPosition()+with<=BOARD_LENGTH+10){
	//If final space is occupied
		if(from+with > BOARD_LENGTH+5 && boardLayout[from+with] != NULL) return;
			//Move pawn forward
			boardLayout[from]->setUiPosition(boardLayout[from]->getUiPosition()+with);
			//Add roll to player step count
			p->setISteps(p->getISteps()+with);
			//If space is already occupied
			if(boardLayout[from+with]!=NULL){
				//If occupant is a different player
				if(boardLayout[from+with]->getEColor()!=p->getEColor()){
					//Return other pawn to start
					boardLayout[from+with]->setUiPosition(0);
					//Go through players to find occupying pawn owner
					for(unsigned j = 1; j < turnOrder.size(); ++j){
						if(boardLayout[from+with]->getEColor()==turnOrder[j]->getEColor()){
							//Add to other pawns' owners' lost counter
							turnOrder[j]->setIHadTaken(turnOrder[j]->getIHadTaken()+1);
						}
					}	
					//Add to current players' taken counter
					p->setITaken(p->getITaken()+1);
				}
			}
		//Place pawn in new location
		boardLayout[from+with] = boardLayout[from];
		boardLayout[from] = NULL;
	}
}

//Dice roll
int diceRoll(){
	//Timer
	Uint32 timer = SDL_GetTicks();
	//Dice roll variable
	int roll = dice.roll();
	//Wait for player click
	do {
		eventHandler();
		if(SDL_GetTicks()-timer>100){
			roll = dice.roll();
			dice.render();
			SDL_RenderPresent(renderer);
			timer = SDL_GetTicks();
		}
	} while(!dice.Event(event) && !quit);
	Sound::play(ding);	
	return roll;
}

//Board square highlighter
bool highlight(vector<int>& index){
	//Highlighter color
	SDL_Color color;
	//Traverse index vector
	for (unsigned i = 0; i < 5; i++) {	
		//If highlighter does not exist
		if(i>=index.size()){
			//Resize and place offscreen
			highlightButtons[i].setSize(10, 10);
			highlightButtons[i].setLocation(-10,-10);
		} else {
		//Set highlighter color
			switch(boardHighlghters[index[i]]){
				case RED:
				color = {255,0,0,255};
				break;
				case BLUE:
				color = {0,0,255,255};
				break;
				case YELLOW:
				color = {255,255,0,255};
				break;
				case NONE:
				color = {255,255,255,255};
			}
			//Get current square screen coordinates
			pair<int, int> coords = getCoords(index[i]);
			//Set highlighter params
			highlightButtons[i].setSize(SQUARE_SIZE, SQUARE_SIZE);
			highlightButtons[i].setLocation(coords.first, coords.second);
			highlightButtons[i].setColor(color);

			cout << coords.first << " " << coords.second << endl;
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
