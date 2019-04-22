#ifndef TILE
#define TILE

#include "globals.h"

struct SDL_Texture;
class Graphic;

class Tile{
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetposition, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphic &graphic);

private:
	SDL_Texture* _tileset;
	Vector2 _size;
	Vector2 _tilesetposition;
	Vector2 _position;
};


#endif
