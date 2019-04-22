#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include <string>

#include "rect.h"
#include "globals.h"

class Graphic;

class Sprite{
public:
	Sprite();
	Sprite(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY);


	virtual ~Sprite();
	virtual void update();
	void draw(Graphic &graphic, int x, int y, SDL_RendererFlip flipSprite);


	const Rectangle getBB() const;

	const sides::Side getCollideSide(Rectangle &other) const;

	const inline float getX() const {return this->_x;}
	const inline float getY() const {return this->_y;}

	void setSourceRectX(int value);
	void setSourceRectY(int value);
	void setSourceRectW(int value);
	void setSourceRectH(int value);



protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	SDL_RendererFlip _flipSprite= SDL_FLIP_NONE;

	Rectangle _boundingBox;


	float _x,_y;


private:


};

#endif
