#include "SDL.h"

#include "Game.h"
#include "Graphic.h"
#include "Input.h"



namespace{
	const int FPS = 60;
	const int MAXFRAMETIME= 6* 1000/FPS;
}
Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game(){

}
void Game::gameLoop(){
	Graphic graphic;
	Input input;
	SDL_Event event;


	this->_level = Level("TestLevel",  graphic);
	this->_player = Player(graphic, this->_level.getPSP(), SDL_FLIP_NONE, 1.0, 40.0);
	this->_hud = Hud(graphic, this->_player);

	int LASTUPDATETIME = SDL_GetTicks();
	while(true){
		input.beginNewFrame();

		if (SDL_PollEvent(&event)){
			if (event.type == SDL_KEYDOWN){
				if (event.key.repeat ==0){
					input.keyDownEvent(event);

				}
			}
			else if (event.type == SDL_KEYUP){
				input.keyUpEvent(event);
			}
			else if (event.type ==SDL_QUIT){
				return;
			}
		}

		if (_player.getCA()==0){
			this->_level = Level("TestLevel",  graphic);
			this->_player = Player(graphic, this->_level.getPSP(), SDL_FLIP_NONE, 1.0, 40.0);
			this->_hud = Hud(graphic, this->_player);
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)==true){
			return;
		}

		else if (input.wasKeyHeld(SDL_SCANCODE_A)==true){
			this->_player.moveLeft();
		}

		else if (input.wasKeyHeld(SDL_SCANCODE_D)==true){
			this->_player.moveRight();
		}


		if (input.wasKeyPressed(SDL_SCANCODE_SPACE)==true){
			this->_player.Jump();
		}

		if (input.wasKeyPressed(SDL_SCANCODE_E)==true){
			this->_player.Shoot();
		}


		if (!input.wasKeyHeld(SDL_SCANCODE_LEFT)&& !input.wasKeyHeld(SDL_SCANCODE_RIGHT)
				&& !input.wasKeyHeld(SDL_SCANCODE_A)&& !input.wasKeyHeld(SDL_SCANCODE_D)){
			this->_player.stopMoving();
		}

		const int CURRENTTIMEINMS = SDL_GetTicks();
		int ELAPSEDTIMEINMS = CURRENTTIMEINMS-LASTUPDATETIME;
		this-> _graphic = graphic;
		this->update(std::min(ELAPSEDTIMEINMS, MAXFRAMETIME));
		LASTUPDATETIME = CURRENTTIMEINMS;

		this->draw(graphic);
	}
}

void Game::draw(Graphic &graphic){
	graphic.clear();
	this->_level.draw(graphic);
	this->_player.draw(graphic);
	this->_hud.draw(graphic);

	graphic.flip();

}

void Game::update(float elapsedtime){
	this->_player.update(elapsedtime);
	this->_fly.update(elapsedtime, this->_player);
	this->_level.update(elapsedtime, this->_player);
	this->_hud.update(elapsedtime, this->_player.getCA(), this->_player.getMaxAmmo());

	std::vector<Rectangle> others;
	std::vector<Slope> otherSl;
	if ((others = this->_level.checkTileCollide(this->_player.getBBP())).size() > 0) {
		this->_player.handleTC(others);
	}

	if((otherSl= this->_level.checkSC(this->_player.getBBP())).size()>0){
		this->_player.handleSC(otherSl);
	}
	std::vector<NextLevel> otherLevel;
	if((otherLevel=this->_level.checkLC(this->_player.getBBP())).size()>0){
		this->_player.handleLC(otherLevel, this->_level, this->_graphic);
	}

	std::vector<Enemy*> otherEnemies;
	if((otherEnemies=this->_level.checkEC(this->_player.getBBP())).size()>0){
		this->_player.handleEC(otherEnemies, elapsedtime);
	}
	std::vector<Fruit*> otherFruits;
	if((otherFruits=this->_level.checkFC(this->_player.getBBP())).size()>0){
		this->_player.handleFC(otherFruits);
	}


}
