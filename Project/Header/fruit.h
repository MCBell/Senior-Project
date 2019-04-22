#ifndef FRUIT_H
#define FRUIT_H

#include "sprite.h"
#include <string>
#include "player.h"

class Graphic;
class Player;

class Fruit: public Sprite{
public:
	Fruit();
	Fruit(Graphic &graphic, std::string filepath, int sourceX, int sourceY, int width, int height, Vector2 Spawnpoint, int timeToUpdate, int HV);

	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphic &graphic);
	virtual void touchPlayer(Player* player,float CA, float MA,std::vector<Fruit*> &others, int i)=0;

	const inline int getHV() const{ return this-> _healthValue;}

protected:
	int _healthValue;
};

class Apple: public Fruit{
public:
	Apple();
	Apple(Graphic &graphic, Vector2 Spawnpoint);
	void update(int elapsedTime, Player &player);
	void draw(Graphic &graphic);
	void touchPlayer(Player* player, float CA, float MA,std::vector<Fruit*> &others, int i);
};

#endif
