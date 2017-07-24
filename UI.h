///UI abstract class

#ifndef UI_H
#define UI_H

///Include local libraries
#include "Button.h"
#include "Shared.h"

class UI{
public:
	///Constructor
	UI();

	///Font loader
	///Args:
	///string fontPath - path to font
	///unsigned fontSize - size of font (not required)
	void loadFont(string fontPath, unsigned fontSize = 10);

	///Font setter
	///Args:
	///TTF_Font* font - pointer to font
	void setFont(TTF_Font* font);

	///Background texture loader
	///Args:
	///string backgroundPath - path to background image
	void loadBackground(string backgroundPath);

	///Event debouncer
	bool debounce();

	///Button fade in
	virtual void fadeIn()=0;

	///Button fade out
	virtual void fadeOut()=0;

	///Get class font
	TTF_Font* getFont() const;

	///Abstract event handler
	///Args:
	///SDL_Event& e - reference to SDL event container
	///Returns:
	///int with button states
	virtual int eventHandler(SDL_Event& e)=0;
	
	///Render method
	virtual void render();

	///Destructor
	virtual ~UI();

private:
	
	///Font object pointer
	TTF_Font* mFont;

	///Background texture path for reloading
	string msBackgroundPath;

	///Font path for reloading
	string msFontPath;

	///Font size for reloading
	unsigned miFontSize;

	///Background texture
	Texture mBackground;

	///Flag not to unload font if set externally
	bool unload;

	///Event debounce timer
	Uint32 eventTimer;
};

#endif
