#include "tile.h"
#include "graphic.h"
#include <SDL.h>

Tile::Tile(){}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetposition, Vector2 position):
		_tileset(tileset),
		_size(size),
		_tilesetposition(tilesetposition),
		_position(Vector2(position.x, position.y))
{}

void Tile::update(int elapsedTime){}

void Tile::draw(Graphic &graphic){
	SDL_Rect destRect = {this->_position.x, this->_position.y, this->_size.x,this->_size.y};
	SDL_Rect sourceRect = { this->_tilesetposition.x, this->_tilesetposition.y, this->_size.x, this->_size.y};

	graphic.blitSurface(this->_tileset, &sourceRect, &destRect, SDL_FLIP_NONE);
}
