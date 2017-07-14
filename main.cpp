//-----------------------------
//-----------INCLUDES----------
//-----------------------------

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

//Include local modules
#include "Shared.h"
#include "Board.h"
//#include "Player.h"
#include "Sound.h"
#include "Dice.h"
//#include "Recovery.h"

//Misc library inclusion
#include <iostream>
using std::cerr;
using std::endl;
#include <vector>
using std::vector;

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

//Game board
Board board;

//Dice object
Dice dice;

//Player objects
//Player red, blue, yellow;

//Players vector
//vector<Player*> playerVec;

//Board square layout (top row leftmost square considered 0)
Colors boardLayout[BOARD_LENGTH] = {NONE};

//Debug data
int x, y;
Uint32 squareTimer = SDL_GetTicks();
int posCounter = 0;
SDL_Rect square = { ZERO_X_POS, ZERO_Y_POS, SQUARE_SIZE, SQUARE_SIZE };
struct Debug_Player{
	Colors c;
	int p;
	int count;
};

Debug_Player red = {RED, 0, 0};
Debug_Player yellow = {BLUE, 0, 0};
Debug_Player blue = {YELLOW, 0, 0};
vector<Debug_Player*> playerVec;

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
//Debug_Player *p - pointer to player object
int convert(Debug_Player *p);

//Get screen coordinates from pawn position
//Args:
//Debug_Player *p - pointer to player object
pair<int, int> getCoords(Debug_Player *p);

//Traverse board
void traverse();

//-----------------------------
//------------MAIN-------------
//-----------------------------

int main(int argc, char* argv[]){
	//Initialize temporary coordinates
	x=y=0;

	//Push player objects
	playerVec.push_back(&red);	
	playerVec.push_back(&blue);	
	playerVec.push_back(&yellow);	
	
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
			
			//Traverse board
			traverse();

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

	//Try to initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		cerr << "SDL Error: " << SDL_GetError() << endl;
		success = 0;
	} else {
		//Try to initialize SDL image
		if(!IMG_Init(IMG_INIT_PNG)){
			cerr << "IMG Error: " << IMG_GetError() << endl;
			success = 0;
		} else {
			//Try to initialize SDL mixer
			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
				cerr << "MIX Error: " << Mix_GetError() << endl;
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
						Sound::load();
						dice.setRenderer(renderer);
						dice.init();
						//Initialize game objects
						board.setRenderer(renderer);
						//for (unsigned i = 0; i < playerVec.size(); ++i)
							//playerVec[i]->setRenderer(renderer);
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
		dice.Event(event);
	}
}


//Resource freeing function
void free(){
	//Release objects
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
int convert(Debug_Player *p){
	return (START_POS[p->c-1]+p->p)%BOARD_LENGTH;
}

//Get screen coordinates from pawn position
pair<int, int> getCoords(Debug_Player *p){
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

//Traverse board
void traverse(){
	//Check if enough time has passed
	if(SDL_GetTicks() - squareTimer >= 1000){
		//Traverse player vector
		for(unsigned i = 0; i < playerVec.size(); ++i){
			//Get dice roll
			int roll = dice.roll();
			//Print roll to console
			std::cout << playerVec[i]->c << " rolled " << roll << endl;
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
	}
}
