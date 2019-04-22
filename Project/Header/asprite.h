#ifndef ASPRITE_H
#define ASPRITE_H

#include "sprite.h"
#include "Globals.h"

#include <map>
#include <string>
#include <vector>



class Graphic;


class ASprite: public Sprite{
public:
	ASprite();
	ASprite(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY, float timeToUpdate);

	void playAni(std::string animation, bool once =false);

	void update(int elapsedTime);

	void draw(Graphic &graphic, int x, int y, SDL_RendererFlip flipSprite);




protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void addAni(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void resetAni();

	void stopAni();

	void setVis(bool visible);

	virtual void doneAni(std::string currentAnimation)= 0;

	virtual void setUpAni()=0;


private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;

	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;

};


#endif
