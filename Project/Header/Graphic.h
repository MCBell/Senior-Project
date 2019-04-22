#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

#include <SDL2/SDL.h>


/*Deals with Graphics
 *
 */

struct SDL_Window;
struct SDL_Renderer;

class Graphic{
public:
	Graphic();
	~Graphic();

	/*Loads images if not already loaded.
	 *
	 */

	SDL_Surface* loadImage(const std::string &filePath);

	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, SDL_RendererFlip flip);

	void flip();

	void clear();

	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif
