#ifndef ASPRITEP_H
#define ASPRITEP_H

#include "spritep.h"
#include "Globals.h"

#include <map>
#include <string>
#include <vector>



class Graphic;

class ASpriteP: public SpriteP{
public:
	ASpriteP();
	ASpriteP(Graphic &graphic, const std::string &filePath, int sourceX, int sourceY, int width,
			int height, float posX, float posY, float timeToUpdate, float CA, float MA);

	void playAniP(std::string animation, bool once =false);

	void updateP(int elapsedTime, float CA, float MA);

	void drawP(Graphic &graphic, int x, int y, float CA, float MA, SDL_RendererFlip flipSprite);



protected:
	double _timeToUpdateP;
	bool _currentAnimationOnceP;
	std::string _currentAnimationP;

	void addAniP(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void resetAniP();

	void stopAniP();

	void setVisP(bool visible);

	virtual void doneAniP(std::string currentAnimation)= 0;

	virtual void setUpAniP()=0;


private:
	std::map<std::string, std::vector<SDL_Rect>> _animationsP;

	std::map<std::string, Vector2> _offsetsP;

	int _frameIndexP;
	double _timeElapsedP;
	bool _visibleP;

};


#endif
