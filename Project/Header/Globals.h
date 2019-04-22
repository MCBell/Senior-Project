#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals{

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE =1.0f;

	const float PSPRITE_SCALE =2.0f;


}

namespace sides{
	enum Side{
		Top,
		Bottom,
		Left,
		Right,
		None
	};

	inline Side getOppostieSide(Side side){
		return
				side ==Top? Bottom:
				side == Bottom ? Top:
				side == Left ? Right:
				side == Right ? Left:
				None;
	}
}
enum Directions{

	Left,
	Right,
	Up,
	Down
};
struct Vector2{
	int x, y;
	Vector2():
		x(0),y(0)
	{}
	Vector2(int x, int y):
		x(x),y(y)
	{}
	Vector2 zero(){
		return Vector2(0,0);
	}
};

#endif
