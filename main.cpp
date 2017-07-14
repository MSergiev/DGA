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
//Pawn *p - pointer to pawn object
pair<int, int> getCoords(Pawn *p);

//Player turn
//Args:
//Player *p - pointer to active player
void turn(Player *p);

//Determine turn order
void determineTurnOrder();

//Roll the dice
int diceRoll();

//-----------------------------
//------------MAIN-------------
//-----------------------------

int main(int argc, char* argv[]){
	//Unused warning elimination
	argc = 0; argv = 0;

	//Initialize SDL
	if(!init()) return 1;

	//Play BGM
	Sound::music(rock);

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
pair<int, int> getCoords(Pawn *p){
	//Coordinate pair object
	pair<int, int> coords = {ZERO_X_POS, ZERO_Y_POS};
	//Get world position
	int converted = convert(p);
	//Calculate position
	for(int i = 0; i < converted; ++i){
		coords.first+=NEXT_SQUARE[i].first*SQUARE_SIZE;
		coords.second+=NEXT_SQUARE[i].second*SQUARE_SIZE;
	}	
	//Return coordinate pair
	return coords;
}

//Player turn
void turn(Player *p){
	//Roll the dice
	int roll = diceRoll();	
	cout << p->getEColor() << " rolled " << roll << endl;

	//If roll is a 6
	if(roll==6){
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
				//If movement is within range
				if(boardLayout[i]->getUiPosition()+roll<=BOARD_LENGTH+10){
					//If final space is occupied
					if(i > BOARD_LENGTH+5 && boardLayout[i+roll] != NULL) break;
					//Move pawn forward
					boardLayout[i]->setUiPosition(boardLayout[i]->getUiPosition()+roll);
					//Add roll to player step count
					p->setISteps(p->getISteps()+roll);
					//If space is already occupied
					if(boardLayout[i+roll]!=NULL){
						//If occupant is a different player
						if(boardLayout[i+roll]->getEColor()!=p->getEColor()){
							//Return other pawn to start
							boardLayout[i+roll]->setUiPosition(0);
						
							//Go through players to find occupying pawn owner
							for(unsigned j = 1; j < turnOrder.size(); ++j){
								if(boardLayout[i+roll]->getEColor()==turnOrder[j]->getEColor()){
									//Add to other pawns' owners' lost counter
									turnOrder[j]->setIHadTaken(turnOrder[j]->getIHadTaken()+1);
								}
							}	
							
							//Add to current players' taken counter
							p->setITaken(p->getITaken()+1);
						}
					}
					//Place pawn in new location
					boardLayout[i+roll] = boardLayout[i];
					boardLayout[i] = NULL;
					//Exit loop
					break;
				}
			}
		}
	//If player has more than one active pawn
	} else {

	}	
	

	//Check if enough time has passed
	/*if(SDL_GetTicks() - squareTimer >= 1000){
		//Traverse player vector
		for(unsigned i = 0; i < playerVec.size(); ++i){
			//Get dice roll
			int roll = dice.roll();
			//Print roll to console
			std::cout << playerVec[i]->getEColor() << " rolled " << roll << endl;
			//Move "roll" amount of spaces forward
			playerVec[i]->p = (playerVec[i]->p+roll)%BOARD_LENGTH;
		}
		//Reset timer
		squareTimer = SDL_GetTicks();
	}

	//Traverse player vector
	for(unsigned i = 0; i < playerVec.size(); ++i){
		//Set player color
		switch(playerVec[i]->c){
			case RED:
			SDL_SetRenderDrawColor(renderer,255,0,0,255);
			break;
			case BLUE:
			SDL_SetRenderDrawColor(renderer,0,0,255,255);
			break;
			case YELLOW:
			SDL_SetRenderDrawColor(renderer,255,255,0,255);
			break;
			case NONE:;
		}
		//Get screen coordinates
		pair<int, int> coords = getCoords(playerVec[i]);
		//Construct pawn square
		SDL_Rect square = {coords.first, coords.second, SQUARE_SIZE, SQUARE_SIZE};	
		//Render square
		SDL_RenderFillRect(renderer, &square);
	}*/
}

int diceRoll(){
	//Timer
	Uint32 timer = SDL_GetTicks();
	//Dice roll variable
	int roll = 0;
	//Wait for player click
	while(!dice.Event(event) && !quit){
		eventHandler();
		if(SDL_GetTicks()-timer>50){
			roll = dice.roll();
			dice.render();
			SDL_RenderPresent(renderer);
			timer = SDL_GetTicks();
		}
	}
	return roll;
}

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
