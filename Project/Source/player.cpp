#include "player.h"
#include "graphic.h"
#include "globals.h"

Player::Player(){}

namespace playercon{
	const float WSpeed = 0.2f;

	const float Grav = 0.002f;
	const float GravCap =0.8f;
	const float JumpSpeed =0.7f;



}

Player::Player(Graphic &graphic, Vector2 spawnPoint, SDL_RendererFlip flipSprite, float CA, float MA):
	ASpriteP(graphic, "content/sprites/slimeSheet.png", 0,0,32,32, spawnPoint.x, spawnPoint.y, 100, CA, MA),
	_dx(0),
	_dy(0),
	_facing(Right),
	_grounded(false),
	_maxAmmo(MA),
	_currentAmmo(CA),
	_touched(false),
	_savedTime(0)
{
	graphic.loadImage("content/sprites/slimeSheet.png");
	this->setUpAniP();
	this->playAniP("idle");
	this->_flipSpriteP=SDL_FLIP_HORIZONTAL;
}

void Player::setUpAniP(){
	this->addAniP(10, 10, 54, "Move", 12, 10, Vector2(0,0));
	this->addAniP(10, 10, 22, "idle", 12, 10, Vector2(0,0));
}

void Player::doneAniP(std::string currentAni){}

const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const{
	return this->_y;
}

const float Player::getCA() const{
	return this->_currentAmmo;
}

const float Player::getMaxAmmo() const{
	return this-> _maxAmmo;
}

const bool Player::getTouch() const{
	return this-> _touched;
}

void Player::moveLeft(){
	this->_dx= -playercon::WSpeed;
	this-> playAniP("Move");
	this->_flipSpriteP = SDL_FLIP_NONE;
	this->_facing =Left;
}

void Player::moveRight(){
	this->_dx= +playercon::WSpeed;
	this-> playAniP("Move");
	this->_flipSpriteP = SDL_FLIP_HORIZONTAL;
	this->_facing =Right;
}


void Player::stopMoving(){
	this->_dx= 0.0f;
	this-> playAniP("idle");

}

void Player::Jump(){
	if(this->_grounded){
		this->_dy=0;
		if (_currentAmmo<7){
			this->_dy -= playercon::JumpSpeed/0.6f;
		}

		else {
			this->_dy -= ((_maxAmmo/(float)_currentAmmo)*0.29f)*playercon::JumpSpeed;
		}
		this->_grounded=false;
	}
}

void Player::Shoot(){
	if (_currentAmmo>1){
		_currentAmmo = _currentAmmo- 1;
	}

}


void Player::handleTC(std::vector<Rectangle> &others){
	for (int i= 0; i< others.size(); i++){
		sides::Side collideSides = SpriteP::getCollideSideP(others.at(i));
		if(collideSides !=sides::None){
			switch(collideSides){
			case sides::Top:
				this->_dy=0;
				this->_y= others.at(i).getBottom()+1;
				if (this->_grounded){
					this->_dx=0;
					this->_x=this->_facing == Right ? 1.0f:-1.0f;
				}
				this->_y=others.at(i).getBottom()+1;
				break;
			case sides::Bottom:
				this->_y=others.at(i).getTop()-this->_boundingBoxPlayer.getHeight()-1;
				this->_dy=0;
				this->_grounded=true;
				break;
			case sides::Left:
				this->_x=others.at(i).getRight()+1;
				break;
			case sides::Right:
				this->_x=others.at(i).getLeft()-this->_boundingBoxPlayer.getWidth()-1;
				break;

			}
		}
	}
}

void Player::handleSC(std::vector<Slope> &others){
	for (int i =0; i< others.size(); i++){
		int b =(others.at(i).getP1().y-(others.at(i).getSlope()*fabs(others.at(i).getP1().x)));

		int centerX= this->_boundingBoxPlayer.getCenterX();

		int newY = (others.at(i).getSlope()*centerX)+b;

		if (this->_grounded){
			this->_y =newY -this->_boundingBoxPlayer.getHeight();
			this->_grounded =true;
		}
	}
}

void Player::handleLC(std::vector<NextLevel> &others, Level &level, Graphic &graphic){
	for(int i=0; i <others.size(); i++){
		level = Level(others.at(i).getDest(), graphic);
		this->_x=level.getPSP().x;
		this->_y=level.getPSP().y;
	}
}

void Player::handleEC(std::vector<Enemy*> &others, float elapsedTime){
	for (int i=0; i<others.size(); i++){
		others.at(i)-> touchPlayer(this, _currentAmmo);
	}
}

void Player::changeAmmo(int amount){
	this->_currentAmmo+= amount;
}

void Player::handleFC(std::vector<Fruit*> &others){
	for (int i=0; i<others.size();i++){
		others.at(i)-> touchPlayer(this, _currentAmmo, _maxAmmo, others, i);
	}
}



void Player::update(float elapsedTime){
	if (this->_dy <= playercon::GravCap){
		this->_dy += playercon::Grav*elapsedTime;
	}

	this->_x+=_dx*elapsedTime;

	this->_y+=_dy*elapsedTime;

	ASpriteP::updateP(elapsedTime, _currentAmmo, _maxAmmo);
}

void Player::draw(Graphic &graphic){
	ASpriteP::drawP(graphic, this->_x, this->_y, this->_currentAmmo,this->_maxAmmo, _flipSpriteP);
}
