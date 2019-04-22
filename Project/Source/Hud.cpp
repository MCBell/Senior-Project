#include "hud.h"
#include "graphic.h"
#include "player.h"

Hud::Hud(){}

Hud::Hud(Graphic &graphic,  Player &player){
	this->_player = player;
	this->_gooAmmoSprite= Sprite(graphic, "content/sprites/lifebar.png", 0, 0, 28, 8, 35, 70);
	this->_gooAmmo1 = Sprite(graphic, "content/sprites/numbers.png", 0, 0, 7, 10, 35, 55);
	this->_gooAmmo2 = Sprite(graphic, "content/sprites/numbers.png", 0, 0, 7, 10, 42, 55);
	this->_gooAmmo3 = Sprite(graphic, "content/sprites/numbers.png", 0, 0, 7, 10, 65, 55);
	this->_gooAmmo4 = Sprite(graphic, "content/sprites/numbers.png", 0, 0, 7, 10, 72, 55);

}

void Hud::update(int elapsedTime, float CA, float MA){
	this->_gooAmmoSprite.setSourceRectY(8*(floor(((float)CA/MA)*5)+1));
	this->_gooAmmo1.setSourceRectX(7*floor(CA/10));
	this->_gooAmmo2.setSourceRectX(7*((int)CA%10));
	this->_gooAmmo3.setSourceRectX(7*floor(MA/10));
	this->_gooAmmo4.setSourceRectX(7*((int)MA%10));
}

void Hud::draw(Graphic &graphic){
	this->_gooAmmoSprite.draw(graphic, this->_gooAmmoSprite.getX(), this->_gooAmmoSprite.getY(), SDL_FLIP_NONE);
	this->_gooAmmo1.draw(graphic, this->_gooAmmo1.getX(), this->_gooAmmo1.getY(), SDL_FLIP_NONE);
	this->_gooAmmo2.draw(graphic, this->_gooAmmo2.getX(), this->_gooAmmo2.getY(), SDL_FLIP_NONE);
	this->_gooAmmo3.draw(graphic, this->_gooAmmo3.getX(), this->_gooAmmo3.getY(), SDL_FLIP_NONE);
	this->_gooAmmo4.draw(graphic, this->_gooAmmo4.getX(), this->_gooAmmo4.getY(), SDL_FLIP_NONE);

}
