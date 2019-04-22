#ifndef HUD_H
#define HUD_H

#include "sprite.h"
#include "player.h"


class Graphic;
class Player;

class Hud{
public:
	Hud();
	Hud(Graphic &graphic, Player &player);

	void update(int elapsedTime, float CA, float MA);
	void draw(Graphic &graphic);
private:
	Player _player;

	Sprite _gooAmmoSprite;
	Sprite _gooAmmo1;
	Sprite _gooAmmo2;
	Sprite _gooAmmo3;
	Sprite _gooAmmo4;


};


#endif
