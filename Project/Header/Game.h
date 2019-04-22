#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
#include "hud.h"
#include "graphic.h"
#include "aSpriteP.h"
#include "enemy.h"

class Graphic;
class ASpriteP;
class Fly;

class Game{
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphic &graphic);
	void update(float elapsedTime);

	Player _player;
	Level _level;
	Graphic _graphic;
	Hud _hud;
	Fly _fly;
};

#endif
