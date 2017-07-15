#include "Button.h"

//Textured button constructor
Button::Button(int x, int y, int w, int h){
	//Set default button size
	this->mButtonBase = {x,y,w,h};
}

//Renderer setter method
void Button::setRenderer(SDL_Renderer* renderer){
	//Set class renderer
	this->mRenderer = renderer;
	//Set label texture renderer
	mLabel.setRenderer(renderer);
	//Set button texture renderer
	mTexture.setRenderer(renderer);
}

//Font setter method
void Button::setLabel(string label, TTF_Font* font, SDL_Color fontColor){
	//Set class data
	this->msLabel = label;
	this->mFont = font;
	this->mFontColor = fontColor;
	//Load label texture if possible
	if(msLabel!=string()) mLabel.textLoad(msLabel, mFont, mFontColor);
}

//Texture setter method
void Button::setTexture(string texturePath){
	//Set class data
	this->msTexturePath = texturePath;
	//Load button texture if possible
	if(msTexturePath!=string()) mTexture.load(msTexturePath);
}

//Size setter
void Button::setSize(int w, int h){
	this->mButtonBase.w = w;
	this->mButtonBase.h = h;
}

//Location setter
void Button::setLocation(int x, int y){
	this->mButtonBase.x = x;
	this->mButtonBase.y = y;
}

//Color setter
void Button::setColor(SDL_Color c){
	this->mButtonColor = c;
}

//Button click check
bool Button::isClicked(SDL_Event & e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
		if(e.button.button == SDL_BUTTON_LEFT){
			int x,y;
			SDL_GetMouseState(&x, &y);
			return (x>=mButtonBase.x && x<=mButtonBase.x+mButtonBase.w &&
					y>=mButtonBase.y && y<=mButtonBase.y+mButtonBase.h);
		}
	}
	return 0;
}

//Button release check
bool Button::isReleased(SDL_Event & e){
    if(e.type == SDL_MOUSEBUTTONUP){
		if(e.button.button == SDL_BUTTON_LEFT){
			int x,y;
			SDL_GetMouseState(&x, &y);
			return (x>=mButtonBase.x && x<=mButtonBase.x+mButtonBase.w &&
					y>=mButtonBase.y && y<=mButtonBase.y+mButtonBase.h);
		}
	}
	return 0;
}

//Render button
void Button::render(){
	//Render base
	SDL_SetRenderDrawColor(mRenderer, mButtonColor.r, mButtonColor.g, mButtonColor.b, mButtonColor.a);
	SDL_RenderFillRect(mRenderer, &mButtonBase);
	//Render texture
	mTexture.render(mButtonBase.x, mButtonBase.y);
	//Render label
	mLabel.render(((mButtonBase.w-mLabel.getWidth())/2)+mButtonBase.x, ((mButtonBase.h-mLabel.getHeight())/2)+mButtonBase.y);
}

//Resource releasing method
void Button::free(){
	//Release label texture
	mLabel.free();
	//Release button texture
	mTexture.free();
	//Zero renderer
	mRenderer = NULL;
}

//Destructor
Button::~Button(){
	free();
}
