#ifndef LEVEL
#define LEVEL

#include "globals.h"
#include "tile.h"
#include "rect.h"
#include "slopes.h"
#include "NextLevel.h"
#include <string>
#include <vector>


class Graphic;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;
class Enemy;
class Player;
class Fruit;


class Level{
public:
	Level();
	Level(std::string levelName, Graphic &graphic);
	~Level();
	void update(int elapsedTime, Player &player);
	void draw(Graphic &graphic);

	std::vector<Rectangle> checkTileCollide(const Rectangle &other);
	std::vector<Slope> checkSC(const Rectangle &other);
	std::vector<NextLevel> checkLC(const Rectangle &other);
	std::vector<Enemy*> checkEC(const Rectangle &other);
	std::vector<Fruit*> checkFC(const Rectangle &other);


	const Vector2 getPSP() const;

private:
	std::string _levelName;
	Vector2 _spawnPoint;
	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture* _backgroundTexture;

	bool _touched;


	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<Rectangle> _collideRects;
	std::vector<Rectangle> _collideRectsP;
	std::vector<Slope> _slopes;
	std::vector<NextLevel> _nextLevelList;
	std::vector<Enemy*> _enemies;
	std::vector<Fruit*> _fruits;


	void loadLevel(std::string levelName, Graphic &graphic);

	Vector2 getTilesetPos(Tileset tls, int gid, int tileWidth, int tileHeight);

};

struct Tileset{
	SDL_Texture* Texture;
	int FirstGid;

	Tileset(){
		this->FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid){
		this->Texture= texture;
		this->FirstGid = firstGid;
	}
};

#endif
