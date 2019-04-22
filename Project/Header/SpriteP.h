#ifndef SPRITEP_H
#define SPRITEP_H

#include "SDL2/SDL.h"
#include <string>

#include "rect.h"
#include "globals.h"

class Graphic;

class SpriteP{
public:

	SpriteP();
	SpriteP(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY, float CA, float MA);

	virtual ~SpriteP();
	virtual void updateP(float CA, float MA);
	void drawP(Graphic &graphic, int x, int y, float CA, float MA, SDL_RendererFlip flipSprite);


	const Rectangle getBBP() const;

	const sides::Side getCollideSideP(Rectangle &other) const;

	const inline float getXP() const {return this->_x;}
	const inline float getYP() const {return this->_y;}

	void setSourceRectXP(int value);
	void setSourceRectYP(int value);
	void setSourceRectWP(int value);
	void setSourceRectHP(int value);



protected:
	SDL_Rect _sourceRectP;
	SDL_Texture* _spriteSheetP;
	SDL_RendererFlip _flipSpriteP= SDL_FLIP_NONE;

	Rectangle _boundingBoxPlayer;


	float _x,_y,_CA,_MA;


private:


};

#endif
