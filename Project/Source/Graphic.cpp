#include "Graphic.h"
#include "globals.h"

#include "SDL.h"
#include "SDL_image.h"




Graphic::Graphic(){
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Slime game");
}
Graphic::~Graphic(){
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphic::loadImage(const std::string &filePath) {
	if (this->_spriteSheets.count(filePath)==0){
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this -> _spriteSheets[filePath];
}

void Graphic::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, SDL_RendererFlip flip){
	SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, destinationRectangle, NULL, NULL, flip);
}


void Graphic::flip(){
	SDL_RenderPresent(this-> _renderer);
}

void Graphic::clear(){
	SDL_RenderClear(this->_renderer);
}
SDL_Renderer* Graphic::getRenderer() const{
	return this -> _renderer;
}
