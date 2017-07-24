#ifndef TEXTURE_H
#define TEXTURE_H

///Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

///Misc inclusions
#include <iostream>
using std::cerr;
using std::endl;
using std::string;

class Texture{
public:

	///Constructor
	Texture();

	///Texture loading method
	///Args:
	///string path - path to image file
	void load(string path);

	///Text loading method
	///Args:
	///string t - string to be drawn
	///TTF_Font* f - pointer to font
	///SDL_Color c - text drawing color
	void textLoad(string t, TTF_Font* f, SDL_Color c);

	///Set color modulation
	///Args:
	///Uint8 r - red value (0-255)
	///Uint8 g - green value (0-255)
	///Uint8 b - blue value (0-255)
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	///Set alpha modulation
	///Args:
	///Uint8 a - alpha value (0-255)
	void setAlpha(Uint8 a);

	///Set blend mode
	///Args:
	///SDL_BlendMode b - Blending mode flag
	void setBlendMode(SDL_BlendMode b);

	///Render texture on screen
	///Args:
	///int x - top left X coordinate on screen
	///int y - top left Y coordinate on screen
	///double s - scale factor
	///SDL_Rect* clip - clipping rectangle
	///double a - rotation angle (0-359)
	///SDL_Point* c - rotation center
	///SDL_RendererFlip f - SDL renderer flip flag
	virtual void render(int x, int y, double s = 1, SDL_Rect* clip = NULL, double a = 0,
			SDL_Point* c = NULL, SDL_RendererFlip f = SDL_FLIP_NONE);

	///Get image dimensions
	int getWidth() const;
	int getHeight() const;

	///Resource releasing method;
	virtual void free();

	///Destructor
	virtual ~Texture();

	///SDL renderer pointer
	static SDL_Renderer* mRenderer;

private:

	///SDL tecture pointer
	SDL_Texture* mTexture;

	///Image dimensions
	int mWidth, mHeight;
	
	///Texture and dimension initializer
	void initData();
};

#endif
