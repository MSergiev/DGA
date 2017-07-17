#include "Board.h"

Board::Board(){}

void Board::setRenderer(SDL_Renderer* renderer){
	//Load texture
	if(renderer!=NULL){
		mBoardTexture.setRenderer(renderer);
		mBoardTexture.load(BOARD_PATH);
	}
}

void Board::render(){
	//Draw board texture to screen
	mBoardTexture.render(0,0);	
}

void Board::free(){
	//Release texture data
	mBoardTexture.free();
	mBoardTexture = NULL;
}

Board::~Board(){}

