#include "fruit.h"


Fruit::Fruit(){}

Fruit::Fruit(Graphic &graphic, std::string filepath, int sourceX, int sourceY, int width, int height, Vector2 Spawnpoint, int timeToUpdate, int HV):
		Sprite(graphic, filepath, sourceX, sourceY, width, height, Spawnpoint.x, Spawnpoint.y),
		_healthValue(HV)
{}


void Fruit::update(int elapsedTime, Player &player){
	Sprite::update();

}

void Fruit::draw(Graphic &graphic){
	Sprite::draw(graphic, this->_x, this->_y, SDL_FLIP_NONE);
}


Apple::Apple(){}

Apple::Apple(Graphic &graphic, Vector2 Spawnpoint):
	Fruit(graphic, "Content/sprites/apple.png", 0, 0, 44, 44, Spawnpoint, 140, 5)
{}


void Apple::update(int elapsedTime, Player &player){
	Fruit::update(elapsedTime, player);
}

void Apple::draw(Graphic &graphic){
	Fruit::draw(graphic);
}

void Apple::touchPlayer(Player* player, float CA, float MA,std::vector<Fruit*> &others, int i){
	if (CA > MA-5){
		player->changeAmmo((MA-CA));
	}

	else{
		player->changeAmmo(5);
	}

}
