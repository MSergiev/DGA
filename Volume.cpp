#include "Volume.h"

//Constructor
Volume::Volume(){}

//UI initializing method
void Volume::init(){
	//Set slider textures
	mBGM.setBaseTexture(BGM_SLIDER_PATH);
	mSFX.setBaseTexture(SFX_SLIDER_PATH);
	mBGM.setKnobTexture(SLIDER_KNOB_PATH);
	mSFX.setKnobTexture(SLIDER_KNOB_PATH);

	//Set slider sizes
	mBGM.setSize(SLIDER_WIDTH, SLIDER_HEIGHT);
	mSFX.setSize(SLIDER_WIDTH, SLIDER_HEIGHT);

	//Set slider locations
	mBGM.setLocation(WIDTH-SLIDER_WIDTH-20, VERT_OFFSET/2);
	mSFX.setLocation(WIDTH-SLIDER_WIDTH-20, VERT_OFFSET/2+3*SLIDER_HEIGHT/2);

	//Set slider ranges
	mBGM.setRange(120, SLIDER_WIDTH-150);
	mSFX.setRange(120, SLIDER_WIDTH-150);

}

//Event handler
int Volume::eventHandler(SDL_Event& e){
	//Get slider events
	mBGM.eventHandler(e);
	mSFX.eventHandler(e);

	//Set volumes
	Mix_VolumeMusic(mBGM.mapFromSlider(0,128));
	Mix_Volume(-1, mSFX.mapFromSlider(0,128));
    
	return 0;
}

//Fade in
void Volume::fadeIn(){}

//Fade out
void Volume::fadeOut(){};

//Render method
void Volume::render(){
	mBGM.render();
	mSFX.render();
}

//Destructor
Volume::~Volume(){}
