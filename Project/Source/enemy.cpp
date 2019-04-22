#include "enemy.h"
#include "globals.h"

namespace Enemycon{
	const float Grav = 0.002f;
	const float GravCap =0.8f;
}


Enemy::Enemy(){}

Enemy::Enemy(Graphic & graphic, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint,
		int timeToUpdate, float dX, float dY, Directions facing):
		ASprite (graphic, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate),
		_direction(Left),
		_maxHealth(0),
		_currentHealth(0),
		_dy(dX),
		_dx(dY),
		_flipSprite(SDL_FLIP_HORIZONTAL),
		_shouldMoveUp(false),
		_shouldMoveLeft(true)
{}

const float Enemy::getX() const {
	return this->_x;
}

const float Enemy::getY() const{
	return this->_y;
}
void Enemy::update(int elapsedTime, Player &player){
	ASprite::update(elapsedTime);
}

void Enemy::draw(Graphic &graphic){
	ASprite::draw(graphic, this->_x, this->_y, _flipSprite);
}

void Enemy::handleTC(std::vector<Rectangle> &others){

}

Fly::Fly(){}


Fly::Fly(Graphic &graphic, Vector2 spawnPoint):
		Enemy(graphic, "content/sprites/fly.png", 0, 0, 50, 37, spawnPoint, 140, 0, 0,  Left),
		_startX(spawnPoint.x),
		_startY(spawnPoint.y),
		_dy(0),
		_dx(0)
{
	this->setUpAni();
	this->playAni("Move");
}

void Fly::update(int elapsedTime, Player &player){
	this->_y += this->_shouldMoveUp ? -.05 : .05;
	this->_x += this->_shouldMoveLeft? -.025 : .025;
	if (this->_y > (this->_startY + 30) || this->_y < this->_startY - 30) {
		this->_shouldMoveUp = !this->_shouldMoveUp;
	}

	if (this->_x > (this->_startX + 100) || this->_x < this->_startX - 100) {
			this->_shouldMoveLeft = !this->_shouldMoveLeft;
			this-> _flipSprite = _shouldMoveLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

	Enemy::update(elapsedTime, player);

}

void Fly::draw(Graphic &graphic){
	Enemy::draw(graphic);
}


void Fly::doneAni(std::string currentAnimation){

}

void Fly::setUpAni(){
	this->addAni(10, 0, 0, "Move", 50, 37, Vector2(0,0));
}

void Fly::touchPlayer(Player* player, float CA){

	if (CA >= 3){
		player->changeAmmo(-2);
	}

	else if (CA <= 2){
		player->changeAmmo(-CA);
	}

}
