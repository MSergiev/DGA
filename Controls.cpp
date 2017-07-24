#include "Controls.h"

//Constructor
Controls::Controls(){}

//UI initializing method
void Controls::init(){
	//Set button textures
	mSoundButton.setTexture(SOUND_ON_PATH);
	mRulesButton.setTexture(RULES_PATH);
	mQuitButton.setTexture(QUIT_PATH);

	//Set button sizes
	mSoundButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	mRulesButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	mQuitButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);

	//Set button SFX
	mSoundButton.setSFX(BUTTON_SFX);
	mRulesButton.setSFX(BUTTON_SFX);
	mQuitButton.setSFX(BUTTON_SFX);

	//Set button locations
	mSoundButton.setLocation(WIDTH-BUTTON_WIDTH-20, VERT_OFFSET/2);
	mRulesButton.setLocation(WIDTH-BUTTON_WIDTH-20, VERT_OFFSET/2+3*BUTTON_HEIGHT/2);
	mQuitButton.setLocation(WIDTH-BUTTON_WIDTH-20, VERT_OFFSET/2+2*VERT_OFFSET);
}

//Event handler
int Controls::eventHandler(SDL_Event & e){
	//Button state holder
	int buttonState = 0;
	
	//Debounce events
	if(UI::debounce()){
		//Get sound button state
		buttonState|=mSoundButton.isClicked(e);		
		//Set correct button texture
		if(Sound::mute) mSoundButton.setTexture(SOUND_OFF_PATH);
		else mSoundButton.setTexture(SOUND_ON_PATH);
		//Shift state holder bits
		buttonState<<=1;
		//Get rules button state
		buttonState|=mRulesButton.isClicked(e);
		//Shift state holder bits
		buttonState<<=1;
		//Get quit button state
		buttonState|=mQuitButton.isClicked(e);
	}
	//Return button states
	return buttonState;
}

//Fade in
void Controls::fadeIn(){
	mSoundButton.fadeIn(FADE_FACTOR);
	mRulesButton.fadeIn(FADE_FACTOR);
	mQuitButton.fadeIn(FADE_FACTOR);
}

//Fade out
void Controls::fadeOut(){
	mSoundButton.fadeOut(FADE_FACTOR);
	mRulesButton.fadeOut(FADE_FACTOR);
	mQuitButton.fadeOut(FADE_FACTOR);
}

//Render method
void Controls::render(){
	mSoundButton.render();
	mRulesButton.render();
	mQuitButton.render();
}

Controls::~Controls() 
{

}

