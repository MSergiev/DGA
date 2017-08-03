#include "Slider.h"

//Constructor
Slider::Slider(int x, int y, int w, int h){
	//Set default slider size
	this->mSize = {x,y,w,h};
	this->mRange = {x,y,w,h};
	this->mfPosition = 0;
}

//Base texture setter
void Slider::setBaseTexture(string texturePath){
	//Set class data
	this->mSliderBase.load(texturePath);
}

//Knob texture setter
void Slider::setKnobTexture(string texturePath){
	this->mSliderKnob.load(texturePath);
}

//Size setter
void Slider::setSize(int w, int h){
	this->mSize.w = w;
	this->mSize.h = h;
}

//Location setter
void Slider::setLocation(int x, int y) {
	this->mSize.x = x;
	this->mSize.y = y;
}

//Range setter
void Slider::setRange(int from, int to){
	this->mRange.x = mSize.x+from;
	this->mRange.w = mRange.x+to;
}

//Slider value getter
float Slider::getSliderValue() const {
	return mfPosition;
}

//Event handler
bool Slider::eventHandler(SDL_Event & e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
		if(e.button.button == SDL_BUTTON_LEFT){
			int x,y;
			SDL_GetMouseState(&x, &y);
			std::cout << mRange.x << " " << mRange.w << " " << mSize.y << " " << mSize.h << endl;
			bool state = (x>=mRange.x && x<=mRange.w && y>=mSize.y && y<=mSize.h);
			if(state) mfPosition = mapToSlider(mRange.x, mRange.w, x);
			return state;
		}
	}
	return 0;
}

//Render method
void Slider::render(){
	this->mSliderBase.render(mSize.x, mSize.y);
	this->mSliderKnob.render(mapFromSlider(mRange.x, mRange.w), mSize.y);
}

//Map to slider
float Slider::mapToSlider(int from, int to, int val){
	return ((val-from)/(float)(to-from));
}

//Map from slider
float Slider::mapFromSlider(float from, float to){
	return (mfPosition*(float)(to-from))+from;
}


//Destructor
Slider::~Slider(){}
