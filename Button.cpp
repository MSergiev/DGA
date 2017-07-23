#include "Button.h"

//Textured button constructor
Button::Button(int x, int y, int w, int h){
	//Set default button size
	this->mButtonBase = {x,y,w,h};
	this->mbIsFadingIn = 0;
	this->mbIsFadingOut = 0;
	this->mfFactor = 0.5;
	this->miAlpha = 255;
	this->mTexture.setBlendMode(SDL_BLENDMODE_BLEND);
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

//Fade in
bool Button::fadeIn(float factor){
	if(!mbIsFadingIn){ miAlpha = 0; mfFactor = factor, mbIsFadingIn = 1; }
	else {		
		if(miAlpha>=255){
			mfFactor = 0.5;
			mbIsFadingIn = 0;
		   	return 1;
		}
		miAlpha+=factor;
		if(miAlpha>255) miAlpha = 255;
		mTexture.setAlpha(miAlpha);

	}
	return 0;
}

//Fade out
bool Button::fadeOut(float factor){
	if(!mbIsFadingOut){ mfFactor = factor, mbIsFadingOut = 1; }
	else {		
		if(miAlpha<=0){
			mfFactor = 0.5;
			mbIsFadingOut = 0;
		   	return 1;
		}
		miAlpha-=factor;
		if(miAlpha<0) miAlpha = 0;
		mTexture.setAlpha(miAlpha);

	}
	return 0;
}

//Color setter
void Button::setColor(SDL_Color c){
	this->mButtonColor = c;
}

//SFX setter
void Button::setSFX(SEFFECTS sfx){
	this->meSFX = sfx;
	mbHasSFX = 1;
}

//Button click check
bool Button::isClicked(SDL_Event & e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
		if(e.button.button == SDL_BUTTON_LEFT){
			int x,y;
			SDL_GetMouseState(&x, &y);
			bool state = (x>=mButtonBase.x && x<=mButtonBase.x+mButtonBase.w &&
					y>=mButtonBase.y && y<=mButtonBase.y+mButtonBase.h);
			//Play SFX on click
			if(state && mbHasSFX) Sound::play(meSFX);
			return state;
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

//Button hover check
bool Button::isOver(SDL_Event& e){
	if(e.type == SDL_MOUSEMOTION){
		int x,y;
		SDL_GetMouseState(&x, &y);
		return (x>=mButtonBase.x && x<=mButtonBase.x+mButtonBase.w &&
					y>=mButtonBase.y && y<=mButtonBase.y+mButtonBase.h);

	}
	return 0;
}

//Render button
void Button::render(){
	if(mbIsFadingIn) fadeIn(mfFactor);
	else if(mbIsFadingOut) fadeOut(mfFactor);
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
}

//Destructor
Button::~Button(){
	free();
}
