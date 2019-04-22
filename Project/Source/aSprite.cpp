#include "asprite.h"
#include "graphic.h"
#include "sprite.h"

ASprite::ASprite(){}

ASprite::ASprite(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY, float timeToUpdate):
					Sprite(graphic, filePath, sourceX, sourceY, width, height, posX, posY),
					_frameIndex(0),
					_timeToUpdate(timeToUpdate),
					_visible(true),
					_currentAnimationOnce(false),
					_currentAnimation("")
{}





void ASprite::addAni(int frames, int x, int y, std::string name, int width, int height, Vector2 offset){
	std::vector<SDL_Rect> rectangles;
	for (int i=0; i < frames; i++){
		SDL_Rect newRect = { (i+x)*width, y, width, height};
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}




void ASprite::resetAni(){
	this->_animations.clear();
	this->_offsets.clear();
}

void ASprite::playAni(std::string animation, bool once){
	this->_currentAnimationOnce=once;
	if ( this-> _currentAnimation!= animation){
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}



void ASprite::setVis(bool visible){
	this->_visible = visible;
}



void ASprite::stopAni(){
	this->_frameIndex=0;
	this->doneAni(this->_currentAnimation);
}



void ASprite::update(int elapsedTime){
	Sprite::update();
	this->_timeElapsed += elapsedTime;
	if(this->_timeElapsed> this->_timeToUpdate){
		this->_timeElapsed -=this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size()-1){
			this->_frameIndex++;
		}
		else{
			if (this->_currentAnimationOnce==true){
				this->setVis(false);
			}
			this->_frameIndex = 0;
			this->doneAni(this->_currentAnimation);
		}
	}
}

void ASprite::draw(Graphic &graphic, int x, int y, SDL_RendererFlip flipSprite){
	if (this->_visible){
		SDL_Rect destinationRectangle;
		destinationRectangle.x= x+this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y= y+this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w= (this ->_sourceRect.w);
		destinationRectangle.h= (this ->_sourceRect.h);

		SDL_Rect sourceRect= this-> _animations[this->_currentAnimation][this->_frameIndex];
		graphic.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle, flipSprite);

	}
}

