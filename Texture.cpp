#include "Texture.h"

SDL_Renderer* Texture::mRenderer = NULL;

Texture::Texture(){
	//Initialize data
	initData();
}

void Texture::load(string path){
	//Create blank texture
	SDL_Texture* board;
	
	//Load image to surface
	SDL_Surface* loaded = IMG_Load(path.c_str());
	
	//Integrity check
	if(loaded==NULL){
		cerr << "Image error: " << IMG_GetError() << endl;
	} else {
		//Create texture from loaded surface
		board = SDL_CreateTextureFromSurface(mRenderer, loaded);
		//Integrity check
		if(board==NULL) {
			cerr << "Texture error: " << SDL_GetError() << endl;
		} else {
			//Assign loaded texture as class texture
			mTexture = board;
			//Set texture dimensions
			mWidth = loaded->w;
			mHeight = loaded->h;
		}
		//Release surface data
		SDL_FreeSurface(loaded);
	}
}

//Text loading method
void Texture::textLoad(string s, TTF_Font* f, SDL_Color c){
	//Load text into surface
	SDL_Surface* loaded = TTF_RenderText_Solid(f, s.c_str(), c);
	//Integrity check
	if(loaded==NULL) {
		cerr << "TTF error: " << TTF_GetError() << endl;
	} else {
		//Create texture from surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, loaded);
		//Integrity check
		if(mTexture==NULL) {
			cerr << "Texture error: " << SDL_GetError() << endl;
		} else {
			//Get text dimensions
			mWidth = loaded->w;
			mHeight = loaded->h;
		}
		//Release surface data
		SDL_FreeSurface(loaded);
	}
}

void Texture::setRenderer(SDL_Renderer* renderer){
	Texture::mRenderer = renderer;
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b){
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::setAlpha(Uint8 a){
	SDL_SetTextureAlphaMod(mTexture, a);
}

void Texture::setBlendMode(SDL_BlendMode b){
	SDL_SetTextureBlendMode(mTexture, b);
}

void Texture::render(int x, int y, SDL_Rect * clip, double a, SDL_Point * c, SDL_RendererFlip f){
	//Set drawing size
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	//Assign rendering size
	if(clip!=NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render image
	SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, a, c, f);
}

int Texture::getWidth() const {
    return mWidth;
}

int Texture::getHeight() const {
    return mHeight;
}

void Texture::free(){
	//Release texture data
	SDL_DestroyTexture(mTexture);
}

void Texture::initData(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture(){
	free();
}
