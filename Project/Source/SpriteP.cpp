#include "spritep.h"
#include "graphic.h"
#include "globals.h"

SpriteP::SpriteP(){}

SpriteP::SpriteP(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY, float CA, float MA) :
					_x(posX),
					_y(posY)
{
	this->_sourceRectP.x= sourceX;
	this->_sourceRectP.y= sourceY;
	this->_sourceRectP.w= width;
	this->_sourceRectP.h= height;
	this->_CA=CA;
	this->_MA=MA;

	this->_spriteSheetP = SDL_CreateTextureFromSurface(graphic.getRenderer(), graphic.loadImage(filePath));
	if(this->_spriteSheetP ==NULL){
		printf("\nEffor:Unable to load image\n");
	}

	this->_boundingBoxPlayer = Rectangle(this->_x, this->_y, (12)*globals::PSPRITE_SCALE*(((_CA/_MA)*2)+1), (10)*globals::PSPRITE_SCALE*(((_CA/_MA)*2)+1));
}

SpriteP::~SpriteP(){}

void SpriteP::drawP(Graphic &graphic, int x, int y, float CA, float MA, SDL_RendererFlip flipSprite){
	SDL_Rect destinationRectangle ={10,22, (12)*globals::PSPRITE_SCALE*(((CA/MA)*2)+1),
			(10)*globals::PSPRITE_SCALE*(((CA/MA)*2)+1)};
	graphic.blitSurface(this->_spriteSheetP, &this->_sourceRectP, &destinationRectangle, flipSprite);
}

void SpriteP::updateP(float CA, float MA){
	this->_boundingBoxPlayer= Rectangle(this->_x, this->_y, (12)*globals::PSPRITE_SCALE*(((CA/MA)*2)+1),
			(10)*globals::PSPRITE_SCALE*(((CA/MA)*2)+1));
}

const Rectangle SpriteP::getBBP() const{
	return this->_boundingBoxPlayer;
}

const sides::Side SpriteP::getCollideSideP(Rectangle &other) const{
	int amtRight, amtLeft, amtTop, amtBottom;
	amtRight= this->getBBP().getRight()-other.getLeft();
	amtLeft= other.getRight() -this->getBBP().getLeft();
	amtTop= other.getBottom() -this->getBBP().getTop();
	amtBottom= this->getBBP().getBottom() -other.getTop();

	int vals[4] = {abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)};
	int lowest = vals[0];
	for (int i = 0; i<4; i++){
		if (vals[i]<lowest){
			lowest = vals[i];
		}
	}
	return
			lowest==abs(amtRight)? sides::Right:
			lowest==abs(amtLeft)? sides::Left:
			lowest==abs(amtTop)? sides::Top:
			lowest==abs(amtBottom)? sides::Bottom:
			sides::None;
}

void SpriteP::setSourceRectXP(int value){
	this->_sourceRectP.x=value;
}

void SpriteP::setSourceRectYP(int value){
	this->_sourceRectP.y=value;
}

void SpriteP::setSourceRectWP(int value){
	this->_sourceRectP.w=value;
}

void SpriteP::setSourceRectHP(int value){
	this->_sourceRectP.h=value;
}

