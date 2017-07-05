#ifndef TEXTURE_H
#define TEXTURE_H

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Misc inclusions
#include <iostream>
using std::cerr;
using std::endl;
using std::string;

#include <vector>
using std::vector;

class Texture{
public:

	//Constructor
	//Args:
	//SDL_Renderer* renderer - renderer to draw the texture with
	Texture(SDL_Renderer* renderer = NULL);

	//Texture loading method
	void load(string path);

	//Set class renderer
	//Args:
	//SDL_Renderer* renderer - pointer to renderer
	void setRenderer(SDL_Renderer* renderer);

	//Set color modulation
	//Args:
	//Uint8 r - red value (0-255)
	//Uint8 g - green value (0-255)
	//Uint8 b - blue value (0-255)
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	//Set alpha modulation
	//Args:
	//Uint8 a - alpha value (0-255)
	void setAlpha(Uint8 a);

	//Set blend mode
	//Args:
	//SDL_BlendMode b - Blending mode flag
	void setBlendMode(SDL_BlendMode b);

	//Render texture on screen
	//Args:
	//int x - top left X coordinate on screen
	//int y - top left Y coordinate on screen
	//SDL_Rect* clip - clipping rectangle
	//double a - rotation angle (0-359)
	//SDL_Point* c - rotation center
	//SDL_RendererFlip f - SDL renderer flip flag
	void render(int x, int y, SDL_Rect* clip = NULL, double a = 0,
			SDL_Point* c = NULL, SDL_RendererFlip f = SDL_FLIP_NONE);

	//Get image dimensions
	int getWidth() const;
	int getHeight() const;

	//Resource releasing method;
	void free();

	//Destructor
	~Texture();

private:

	//SDL renderer pointer
	SDL_Renderer* mRenderer;

	//SDL tecture pointer
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth, mHeight;
	
	//Texture and dimension initializer
	void initData();
};

#endif
