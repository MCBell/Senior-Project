#ifndef PLAYER_H
#define PLAYER_H

class Graphic;
class Level;

#include <string>

#include "aSpriteP.h"
#include "globals.h"
#include "slopes.h"
#include "level.h"
#include "enemy.h"
#include "fruit.h"

class Player: public ASpriteP {
public:
	Player();
	Player(Graphic &graphic, Vector2 spawnPoint, SDL_RendererFlip flipSprite, float CA, float MA);
	void draw(Graphic &graphic);
	void update(float eplapsedTime);



	void moveLeft();
	void backLeft();
	void moveRight();
	void backRight();
	void stopMoving();
	void Jump();
	void Shoot();

	virtual void doneAniP(std::string currentAni);
	virtual void setUpAniP();

	void handleTC(std::vector<Rectangle> &others);
	void handleSC(std::vector<Slope> &others);
	void handleLC(std::vector<NextLevel> &others, Level &level, Graphic &graphic);
	void handleFC(std::vector<Fruit*> &others);
	void handleEC(std::vector<Enemy*> &others, float elapsedTime);

	const float getX() const;
	const float getY() const;

	const float getMaxAmmo() const;
	const float getCA() const;
	const bool getTouch() const;

	void changeAmmo(int ammount);



private:
	float _dx, _dy,_savedTime;

	Directions _facing;

	bool _grounded;
	bool _touched;

	float _maxAmmo;
	float _currentAmmo;

};


#endif
