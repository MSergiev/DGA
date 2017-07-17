//UI abstract class

#ifndef UI_H
#define UI_H

//Include local libraries
#include "Button.h"
#include "Shared.h"

class UI{
public:
	//Constructor
	UI();

	//Font loader
	//Args:
	//string fontPath - path to font
	//unsigned fontSize - size of font (not required)
	void loadFont(string fontPath, unsigned fontSize = 10);

	//Font setter
	//Args:
	//TTF_Font* font - pointer to font
	void setFont(TTF_Font* font);

	//Background texture loader
	//Args:
	//string backgroundPath - path to background image
	void loadBackground(string backgroundPath);

	//Set class renderer
	//Args:
	//SDL_Renderer* renderer - pointer to renderer to draw with
	virtual void setRenderer(SDL_Renderer* renderer);

	//Get class renderer
	SDL_Renderer* getRenderer() const;

	//Get class font
	TTF_Font* getFont() const;

	//Abstract event handler
	//Args:
	//SDL_Event& e - SDL event container
	//Returns:
	//int with button states
	//(ex. for 3 buttons it could return 100 when button 2 is pressed)
	virtual int eventHandler(SDL_Event& e)=0;
	
	//Render method
	virtual void render();

	//Destructor
	virtual ~UI();

private:
	
	//SDL renderer
	SDL_Renderer* mRenderer;

	//Font object pointer
	TTF_Font* mFont;

	//Background texture path for reloading
	string msBackgroundPath;

	//Font path for reloading
	string msFontPath;

	//Font size for reloading
	unsigned miFontSize;

	//Background texture
	Texture mBackground;

	//Flag not to unload font if set externally
	bool unload;
};

#endif
