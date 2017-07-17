#include "UI.h"

//Constructor
UI::UI(){
	//Initialize class data
	this->miFontSize = 10;
	this->msFontPath = string();
	this->msBackgroundPath = string();
	this->unload = 1;
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
		mBackground.setRenderer(mRenderer);
		mBackground.load(msBackgroundPath);
	}
}

//Renderer setter
void UI::setRenderer(SDL_Renderer * renderer){
	//Set class renderer
	this->mRenderer = renderer;
	//Load font if path is not empty
	if(msFontPath!=string()) loadFont(msFontPath, miFontSize);
	//Load background if path is not empty
	if(msBackgroundPath!=string()) loadBackground(msBackgroundPath);
}

//Destructor
UI::~UI(){
	//Free font if loaded locally
	if(unload){
		TTF_CloseFont(mFont);
		mFont = NULL;
	}
}
