#include "Board.h"

Board::Board(SDL_Renderer * renderer){
	setRenderer(renderer);
}

void Board::load(){
	//Create blank texture
	SDL_Texture* board;

	//Load image to surface
	SDL_Surface* loaded = IMG_Load("GFX/board.png");

	//Integrity check
	if(loaded==NULL){
		cerr << "Board image error: " << IMG_GetError() << endl;
	} else {
		//Create texture from loaded surface
		board = SDL_CreateTextureFromSurface(mRenderer, loaded);

		//Integrity check
		if(board==NULL) {
			cerr << "Board texture error: " << SDL_GetError() << endl;
		} else {
			//Assign loaded texture as class texture
			mBoardTexture = board;
		}

		//Release surface data
		SDL_FreeSurface(loaded);
	}
}

void Board::setRenderer(SDL_Renderer* renderer){
	//Assign class renderer
	this->mRenderer = renderer;
}

void Board::render(){
	//Draw board texture to screen
	SDL_RenderCopy(mRenderer, mBoardTexture, NULL, NULL);	
}

void Board::free(){
	//Release texture data
	SDL_DestroyTexture(mBoardTexture);
	mBoardTexture = NULL;
}

Board::~Board(){}

