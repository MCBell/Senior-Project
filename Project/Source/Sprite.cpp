#include "sprite.h"
#include "graphic.h"
#include "globals.h"

Sprite::Sprite(){

}



Sprite::Sprite(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY) :
							_x(posX),
							_y(posY)
		{
			this->_sourceRect.x= sourceX;
			this->_sourceRect.y= sourceY;
			this->_sourceRect.w= width;
			this->_sourceRect.h= height;
			this->_spriteSheet = SDL_CreateTextureFromSurface(graphic.getRenderer(), graphic.loadImage(filePath));
				if(this->_spriteSheet ==NULL){
					printf("\nEffor:Unable to load image\n");
				}

				this->_boundingBox = Rectangle(this->_x, this->_y, (width* globals::SPRITE_SCALE), (height* globals::SPRITE_SCALE));
			}
Sprite::~Sprite(){}



void Sprite::draw(Graphic &graphic, int x, int y, SDL_RendererFlip flipSprite){
	SDL_Rect destinationRectangle ={x,y, this-> _sourceRect.w*globals::SPRITE_SCALE,
			this->_sourceRect.h*globals::SPRITE_SCALE};
	graphic.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle, flipSprite);
}



void Sprite::update(){
	this->_boundingBox= Rectangle(this->_x, this->_y, _sourceRect.w* globals::SPRITE_SCALE,_sourceRect.h* globals::SPRITE_SCALE);
}



const Rectangle Sprite::getBB() const{
	return this->_boundingBox;
}

const sides::Side Sprite::getCollideSide(Rectangle &other) const{
	int amtRight, amtLeft, amtTop, amtBottom;
	amtRight= this->getBB().getRight()-other.getLeft();
	amtLeft= other.getRight() -this->getBB().getLeft();
	amtTop= other.getBottom() -this->getBB().getTop();
	amtBottom= this->getBB().getBottom() -other.getTop();

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

void Sprite::setSourceRectX(int value){
	this->_sourceRect.x=value;
}

void Sprite::setSourceRectY(int value){
	this->_sourceRect.y=value;
}

void Sprite::setSourceRectW(int value){
	this->_sourceRect.w=value;
}

void Sprite::setSourceRectH(int value){
	this->_sourceRect.h=value;
}

