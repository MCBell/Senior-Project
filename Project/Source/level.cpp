#include "level.h"
#include "graphic.h"
#include <SDL.h>
#include "util.h"
#include "tinyxml2.h"
#include "enemy.h"
#include "fruit.h"
#include <sstream>
#include <algorithm>
#include <cmath>


using namespace tinyxml2;

Level::Level(){}

Level::Level(std::string levelName, Graphic &graphic):
		_levelName(levelName),
		_size(Vector2(0,0)),
		_touched(false)
{
	this->loadLevel(levelName, graphic);
}

Level::~Level(){

}
void Level::loadLevel(std::string levelName, Graphic &graphic){

	XMLDocument doc;
	std::stringstream ss;

	ss<<"content/levels/" <<levelName <<".tmx";
	doc.LoadFile(ss.str().c_str());


	XMLElement* levelNode = doc.FirstChildElement("map");

	int width=0, height=0;

	levelNode->QueryIntAttribute("width", &width);
	levelNode->QueryIntAttribute("height", &height);
	this->_size = Vector2(width, height);

	int tileWidth =0 , tileHeight = 0;
	levelNode->QueryIntAttribute("tilewidth", &tileWidth);
	levelNode->QueryIntAttribute("tilewidth", &tileHeight);
	this->_tileSize = Vector2(tileWidth, tileHeight);

	XMLElement* hTileset = levelNode ->FirstChildElement("tileset");
	if (hTileset != NULL){
		while(hTileset){
			int firstg;
			const char* source = hTileset->FirstChildElement("image")->Attribute("source");
			std::string path2 = source;
			path2.replace(0,2,"content");
			char* path;
			hTileset->QueryIntAttribute("firstgid", &firstg);
			SDL_Texture* tex =SDL_CreateTextureFromSurface(graphic.getRenderer(),graphic.loadImage(path2));
			this->_tilesets.push_back(Tileset(tex,firstg));



			hTileset= hTileset-> NextSiblingElement("tileset");
		}
	}

	XMLElement* hLayer = levelNode->FirstChildElement("layer");
	if (hLayer != NULL){
		while (hLayer){
			XMLElement* hData = hLayer->FirstChildElement("data");
			if (hData != NULL){
				while (hData){
					XMLElement* hTile = hData->FirstChildElement("tile");
					if (hTile != NULL){
						int tileCounter = 0;
						while(hTile){
							if (hTile->IntAttribute("gid")==0){
								tileCounter++;
								if(hTile ->NextSiblingElement("tile")){
									hTile = hTile->NextSiblingElement("tile");
									continue;
								}
								else{
									break;
								}
							}

							int gid = hTile->IntAttribute("gid");
							Tileset tls;
							int closest = 0;
							for (int i = 0; i < this->_tilesets.size(); i++) {
								if (this->_tilesets[i].FirstGid <= gid) {
									if (this->_tilesets[i].FirstGid > closest) {
										closest = this->_tilesets[i].FirstGid;
										tls = this->_tilesets.at(i);

									}
								}
							}

							if (tls.FirstGid == -1){
								tileCounter++;
								if (hTile ->NextSiblingElement("tile")){
									hTile= hTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							int xPos =0;
							int yPos =0;

							xPos= tileCounter % width;
							xPos *= tileWidth;
							yPos +=tileHeight * (tileCounter /width);
							Vector2 finalTilePos = Vector2(xPos, yPos);
							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);


							int tsxx = gid % (tilesetWidth / tileWidth)-1;
							tsxx *= tileWidth;
							int tsyy = 0;
							int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
							tsyy = tileHeight * amt;
							Vector2 finalTilesetPos = Vector2(tsxx, tsyy);
							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPos, finalTilePos);

							this->_tileList.push_back(tile);
							tileCounter++;

							hTile= hTile->NextSiblingElement("tile");
						}
					}

					hData= hData -> NextSiblingElement("data");
				}
			}
			hLayer= hLayer -> NextSiblingElement("layer");
		}
	}

	XMLElement* hObjectGroup = levelNode->FirstChildElement("objectgroup");
	if(hObjectGroup != NULL){
		while(hObjectGroup){
			const char* name = hObjectGroup->Attribute("name");
			std::stringstream ss;
			ss<<name;
			if(ss.str()== "collisions"){
				XMLElement* hObject = hObjectGroup->FirstChildElement("object");
				if (hObject!=NULL){
					while (hObject){
						float x, y, width, height;
						x= hObject->FloatAttribute("x");
						y= hObject->FloatAttribute("y");
						width= hObject->FloatAttribute("width");
						height= hObject->FloatAttribute("height");
						this->_collideRects.push_back(Rectangle(std::ceil(x), std::ceil(y), std::ceil(width), std::ceil(height)));
						this->_collideRectsP.push_back(Rectangle(std::ceil(x), std::ceil(y), std::ceil(width), std::ceil(height)));


						hObject= hObject->NextSiblingElement("object");
					}
				}

			}
			else if (ss.str()=="Slopes"){
				XMLElement* hObject=hObjectGroup->FirstChildElement("object");
				if (hObject !=NULL){
					while(hObject){
						std::vector<Vector2> points;
						Vector2 p1;
						p1=Vector2(std::ceil(hObject->FloatAttribute("x")), std::ceil(hObject->FloatAttribute("y")));

						XMLElement* hPoly = hObject->FirstChildElement("polyline");
						if (hPoly != NULL){
							std::vector<std::string> pair;
							const char* pointString = hPoly->Attribute("points");
							std::stringstream ss;
							ss<<pointString;
							Util::split(ss.str(), pair, ' ');

							for(int i=0; i <pair.size(); i++){
								std::vector<std::string> ps;
								Util::split(pair.at(i), ps, ',');
								points.push_back(Vector2(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
							}
						}

						for (int i= 0; i< points.size(); i+=2){
							this->_slopes.push_back(Slope(
									Vector2((p1.x+points.at(i < 2 ? i : i-1).x),
											(p1.y+points.at(i < 2 ? i : i-1).y)),
									Vector2((p1.x+points.at(i < 2 ? i+1 : i).x),
											(p1.y+points.at(i < 2 ? i+1 : i).y))
													));
						}


						hObject= hObject->NextSiblingElement("object");
					}
				}
			}

			else if(ss.str()=="Spawn point"){
				XMLElement* hObject =hObjectGroup->FirstChildElement("object");
				if (hObject != NULL){
					while(hObject){
						float x= hObject ->FloatAttribute("x");
						float y= hObject ->FloatAttribute("y");
						const char* name = hObject->Attribute("name");
						std::stringstream ss;
						ss<< name;
						if (ss.str()=="player"){
							this->_spawnPoint= Vector2(std::ceil(x), std::ceil(y));
						}

						hObject= hObject->NextSiblingElement("object");
					}
				}
			}

			else if(ss.str()=="Leveltrans"){
				XMLElement* hObject=hObjectGroup->FirstChildElement("object");
				if (hObject!=NULL){
					while (hObject){
						float x= hObject ->FloatAttribute("x");
						float y= hObject ->FloatAttribute("y");
						float w= hObject ->FloatAttribute("width");
						float h= hObject ->FloatAttribute("height");
						Rectangle rect = Rectangle(x,y,w,h);

						XMLElement* hProperties= hObject->FirstChildElement("properties");
						if(hProperties != NULL){
							while (hProperties){
								XMLElement* hProperty = hProperties->FirstChildElement("property");
								if (hProperty != NULL){
									while (hProperty){
										const char* name = hProperty->Attribute("name");
										std::stringstream ss;
										ss<<name;
										if(ss.str()== "destination"){
											const char* value = hProperty->Attribute("value");
											std::stringstream ss2;
											ss2 << value;
											NextLevel nextLevel = NextLevel(rect, ss2.str());
											this->_nextLevelList.push_back(nextLevel);
										}


										hProperty = hProperty->NextSiblingElement("property");
									}
								}


								hProperties = hProperties ->NextSiblingElement("properties");
							}
						}

						hObject= hObject->NextSiblingElement("object");
					}
				}
			}

			else if (ss.str()== "enemies"){
				float x,y;
				XMLElement* hObject=hObjectGroup->FirstChildElement("object");
				if (hObject!=NULL){
					while (hObject){
						x= hObject ->FloatAttribute("x");
						y= hObject ->FloatAttribute("y");
						const char* name= hObject->Attribute("name");
						std::stringstream ss;
						ss<< name;
						if (ss.str()=="fly"){
							this->_enemies.push_back(new Fly(graphic, Vector2(std::floor(x),std::floor(y))));
						}

						hObject= hObject->NextSiblingElement("object");

					}
				}
			}

			else if (ss.str()== "fruits"){
				float x,y;
				XMLElement* hObject=hObjectGroup->FirstChildElement("object");
				if (hObject!=NULL){
					while (hObject){
						x= hObject ->FloatAttribute("x");
						y= hObject ->FloatAttribute("y");
						const char* name= hObject->Attribute("name");
						std::stringstream ss;
						ss<< name;
						if (ss.str()=="apple"){
							this->_fruits.push_back(new Apple(graphic, Vector2(std::floor(x),std::floor(y))));
						}

						hObject= hObject->NextSiblingElement("object");

					}
				}
			}

			hObjectGroup = hObjectGroup->NextSiblingElement("objectgroup");
		}
	}

}

void Level::update(int elapsedTime, Player &player){
	for (int i=0; i< this->_enemies.size(); i++){
		this->_enemies.at(i)->update(elapsedTime, player);
	}

	for (int i=0; i< this->_fruits.size(); i++){
		this->_fruits.at(i)->update(elapsedTime, player);
	}
}



std::vector<Rectangle> Level::checkTileCollide(const Rectangle &other){
	std::vector<Rectangle> others;
	for (int i =0; i < this->_collideRectsP.size(); i++){
		if (this->_collideRectsP.at(i).collideWith(other)){
			others.push_back(this->_collideRectsP.at(i));
		}
	}
	return others;
}

std::vector<Slope> Level::checkSC(const Rectangle &other){
	std::vector<Slope> others;
	for (int i=0; i< this->_slopes.size(); i++){
		if(this->_slopes.at(i).collidesWith(other)){
			others.push_back(this->_slopes.at(i));
		}
	}
	return others;
}
std::vector<NextLevel> Level::checkLC(const Rectangle &other){
	std::vector<NextLevel> others;
	for (int i=0; i< this->_nextLevelList.size(); i++){
		if(this->_nextLevelList.at(i).collideWith(other)){
			others.push_back(this->_nextLevelList.at(i));
		}
	}
	return others;
}

std::vector<Enemy*> Level::checkEC(const Rectangle &other){
	std::vector<Enemy*> others;
	for (int i=0; i< this->_enemies.size(); i++){
		if(this->_enemies.at(i)->getBB().collideWith(other)){
			others.push_back(this->_enemies.at(i));
			_enemies.erase(_enemies.begin()+i);
		}
	}

	return others;
}

std::vector<Fruit*> Level::checkFC(const Rectangle &other){
	std::vector<Fruit*> others;
	for (int i=0; i< this->_fruits.size(); i++){
		if(this->_fruits.at(i)->getBB().collideWith(other)){
			others.push_back(this->_fruits.at(i));
			_fruits.erase(_fruits.begin()+i);
		}
	}
	return others;
}

void Level::draw(Graphic &graphic){

	for (int i = 0; i < this->_tileList.size(); i++){
		this->_tileList.at(i).draw(graphic);
	}

	for (int i = 0; i < this->_enemies.size(); i++){
		this->_enemies.at(i)->draw(graphic);
	}

	for (int i = 0; i < this->_fruits.size(); i++){
		this->_fruits.at(i)->draw(graphic);
	}
}

const Vector2 Level::getPSP() const{
	return this->_spawnPoint;
}

