#ifndef ENEMY_H
#define ENEMY_H

#include "aSprite.h"
#include <string>
#include "globals.h"
#include "player.h"
#include "rect.h"

class Graphics;
class Player;
class Level;

class Enemy: public ASprite{
public:
	Enemy();
	Enemy(Graphic & graphic, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint,
			int timeToUpdate, float dX, float dY, Directions facing);

	virtual void update (int elpasedTime, Player &player);
	virtual void draw(Graphic &graphic);
	virtual void touchPlayer(Player* player, float CA) =0;
	void handleTC(std::vector<Rectangle> &others);

	const inline int getMH() const{ return this-> _maxHealth;}
	const inline int getCH() const{ return this-> _currentHealth;}

	const float getX() const;
	const float getY() const;

protected:
	Directions _direction;
	int _maxHealth;
	int _currentHealth;
	float _dx,_dy;
	bool _shouldMoveUp, _shouldMoveLeft;
	SDL_RendererFlip _flipSprite;
	Level _level;

};

class Fly: public Enemy {
public:
	Fly();
	Fly(Graphic &graphic, Vector2 spawnPoint);
	void update (int elapsedTime, Player &player);
	void draw(Graphic &graphic);
	void touchPlayer(Player* player, float CA);
	void handleTC(std::vector<Rectangle> &others);

	void doneAni(std::string currentAnimation);
	void setUpAni();
private:
	float _startX, _startY,_dx,_dy;

};


#endif
