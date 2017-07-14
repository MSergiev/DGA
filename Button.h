//Button class

#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

class Button {
public:
	//Constructor
	//Args:
	//int x - top left X coordinate
	//int y - top left Y coordinate
	//int width - button width
	//int height - button height
	//SDL_Color color - button color (not required)
	Button(int x, int y, int width, int height, 
			SDL_Color color = {255,0,0,255});
	//Assign button renderer
	//Args:
	//SDL_Renderer* renderer - pointer to renderer
	void setRenderer(SDL_Renderer* renderer);
	//Assign label font
	//Args:
	//string label - text for the button label
	//TTF_Font* font - pointer to font for the label (not required)
	//SDL_Color fontColor - font color (not required)
	void setLabel(string label, TTF_Font* font = NULL, SDL_Color fontColor = {255,255,255,255});
	//Assign button texture
	//Args:
	//string texturePath - path to texture
	void setTexture(string texturePath);
	//Clicked check
	//Args:
	//SDL_Event& e - reference to SDL_Event instance
	bool isClicked(SDL_Event& e);
	//Released check
	//Args:
	//SDL_Event& e - reference to SDL_Event instance
	bool isReleased(SDL_Event& e);
	//Render button
	//Args:
	void render();
	//Resource releasing method
	void free();
	//Destructor
	~Button();

private:
	//SDL renderer
	SDL_Renderer* mRenderer;
	//Font pointer
	TTF_Font* mFont;
	//Label texture
	Texture mLabel;
	//Button texture
	Texture mTexture;
	//Button base rectangle
	SDL_Rect mButtonBase;
	//Simple button color
	SDL_Color mButtonColor;
	//Button label
	string msLabel;
	//Button texture path
	string msTexturePath;
	//Label color
	SDL_Color mFontColor;
};

#endif
