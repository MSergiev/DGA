#include "UI.h"

//Constructor
UI::UI(){
	//Initialize class data
	this->miFontSize = 10;
	this->msFontPath = string();
	this->msBackgroundPath = string();
	this->unload = 1;
	this->eventTimer = SDL_GetTicks();
}

//Debouncer
bool UI::debounce(){
	//If time has passed
	if((SDL_GetTicks()-eventTimer)>100){
		//Update timer
		eventTimer = SDL_GetTicks();
		return 1;
	}
	return 0;
}

//Font loader
void UI::loadFont(string fontPath, unsigned fontSize){
	//Set class font path
	if(fontPath!=string()){
		this->msFontPath = fontPath;
		this->miFontSize = fontSize;
		//Load font
		TTF_OpenFont(msFontPath.c_str(), miFontSize);
	}
}

//Font setter
void UI::setFont(TTF_Font* font){
	//Set class data
	this->mFont = font;
	//Raise flag not to unload on exit
	unload = 0;
}

//Background loader
void UI::loadBackground(string backgroundPath){
	//Set class background path
	if(backgroundPath!=string()){
	   	this->msBackgroundPath = backgroundPath;
		//Load image into texture
	//	mBackground.setRenderer(mRenderer);
		mBackground.load(msBackgroundPath);
	}
}

//Font getter
TTF_Font* UI::getFont() const {
	return mFont;
}

//Render method
void UI::render(){
	mBackground.render(0,0);
}

//Destructor
UI::~UI(){
	//Free font if loaded locally
	if(unload){
		TTF_CloseFont(mFont);
		mFont = NULL;
	}
}
