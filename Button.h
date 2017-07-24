///Button class

#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include "Sound.h"

class Button {
public:
	///Constructor
	///Args:
	///int x - top left X coordinate (not required)
	///int y - top left Y coordinatee (not required)
	///int w = button widthe (not required)
	///int h = button heighte (not required)
	Button(int x = 0, int y = 0, int w = 10, int h = 10);

	///Assign label font
	///Args:
	///string label - text for the button label
	///TTF_Font* font - pointer to font for the label (not required)
	///SDL_Color fontColor - font color (not required)
	void setLabel(string label, TTF_Font* font = NULL, SDL_Color fontColor = {255,255,255,255});

	///Assign button texture
	///Args:
	///string texturePath - path to texture
	void setTexture(string texturePath);

	///Size setter
	///Args:
	///int w = button width
	///int h = button height
	void setSize(int w, int h);

	///Location setter
	///Args:
	///int x - top left X coordinate
	///int y - top left Y coordinate
	void setLocation(int x, int y);

	///Button fade in animation
	///Args:
	///float coefficient - animation speed factor (not required)
	bool fadeIn(float factor = 1);

	///Button fade out animation
	///Args:
	///float coefficient - animation speed factor (not required)
	bool fadeOut(float factor = 1);
	
	///Button color setter
	///Args:
	///SDL_Color c - button color
	void setColor(SDL_Color c);

	///Click sound effect setter
	///Args:
	///SEFFECTS sfx - sound effect
	void setSFX(SEFFECTS sfx);

	///Clicked check
	///Args:
	///SDL_Event& e - reference to SDL_Event instance
	bool isClicked(SDL_Event& e);

	///Released check
	///Args:
	///SDL_Event& e - reference to SDL_Event instance
	bool isReleased(SDL_Event& e);

	///Hover check
	///Args:
	///SDL_Event& e - reference to SDL_Event instance
	bool isOver(SDL_Event& e);
	
	///Render button
	///Args:
	void render();

	///Resource releasing method
	void free();

	///Destructor
	~Button();

private:

	///Font pointer
	TTF_Font* mFont;

	///Label texture
	Texture mLabel;

	///Button texture
	Texture mTexture;

	///Button base rectangle
	SDL_Rect mButtonBase;

	///Simple button color
	SDL_Color mButtonColor;

	///Button label
	string msLabel;

	///Button texture path
	string msTexturePath;

	///Label color
	SDL_Color mFontColor;

	///Click SFX
	SEFFECTS meSFX;

	///SFX set flag
	bool mbHasSFX;

	///Animation data
	float mfFactor;
	bool mbIsFadingIn, mbIsFadingOut;
	float miAlpha;
};

#endif
