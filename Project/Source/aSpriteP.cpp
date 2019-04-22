#include "aspritep.h"
#include "graphic.h"
#include "sprite.h"

ASpriteP::ASpriteP(){}

ASpriteP::ASpriteP(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY, float timeToUpdate, float CA, float MA):
					SpriteP(graphic, filePath, sourceX, sourceY, width, height, posX, posY, CA, MA),
					_frameIndexP(0),
					_timeToUpdateP(timeToUpdate),
					_visibleP(true),
					_currentAnimationOnceP(false),
					_currentAnimationP("")
{}


void ASpriteP::addAniP(int frames, int x, int y, std::string name, int width, int height, Vector2 offset){
	std::vector<SDL_Rect> rectangles;
	for (int i=0; i < frames; i++){
		SDL_Rect newRect = { (i*32)+x, y, width, height};
		rectangles.push_back(newRect);
	}
	this->_animationsP.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsetsP.insert(std::pair<std::string, Vector2>(name, offset));
}

void ASpriteP::resetAniP(){
	this->_animationsP.clear();
	this->_offsetsP.clear();
}

void ASpriteP::playAniP(std::string animation, bool once){
	this->_currentAnimationOnceP=once;
	if ( this-> _currentAnimationP!= animation){
		this->_currentAnimationP = animation;
		this->_frameIndexP = 0;
	}
}

void ASpriteP::setVisP(bool visible){
	this->_visibleP = visible;
}

void ASpriteP::stopAniP(){
	this->_frameIndexP=0;
	this->doneAniP(this->_currentAnimationP);
}

void ASpriteP::updateP(int elapsedTime, float CA, float MA){
	SpriteP::updateP(CA, MA);
	this->_timeElapsedP += elapsedTime;
	if(this->_timeElapsedP> this->_timeToUpdateP){
		this->_timeElapsedP -=this->_timeToUpdateP;
		if (this->_frameIndexP < this->_animationsP[this->_currentAnimationP].size()-1){
			this->_frameIndexP++;
		}
		else{
			if (this->_currentAnimationOnceP==true){
				this->setVisP(false);
			}
			this->_frameIndexP = 0;
			this->doneAniP(this->_currentAnimationP);
		}
	}
}

void ASpriteP::drawP(Graphic &graphic, int x, int y, float CA, float MA, SDL_RendererFlip flipSprite){
	if (this->_visibleP){
		SDL_Rect destinationRectangle;
		destinationRectangle.x= x+this->_offsetsP[this->_currentAnimationP].x;
		destinationRectangle.y= y+this->_offsetsP[this->_currentAnimationP].y;
		destinationRectangle.w= (this ->_sourceRectP.w-20)*globals::PSPRITE_SCALE*(((CA/MA)*2)+1);
		destinationRectangle.h= (this ->_sourceRectP.h-22)*globals::PSPRITE_SCALE*(((CA/MA)*2)+1);

		SDL_Rect sourceRect= this-> _animationsP[this->_currentAnimationP][this->_frameIndexP];
		graphic.blitSurface(this->_spriteSheetP, &sourceRect, &destinationRectangle, flipSprite);

	}
}
