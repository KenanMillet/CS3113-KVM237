#include "Game.h"

Game::Game()
	: EventDependent({SDL_QUIT, SDL_WINDOWEVENT}), fin(false)
{
}

Game::operator bool()
{
	return !fin;
}

void Game::exit()
{
	fin = true;
}

bool Game::is_done() const
{
	return fin;
}

void Game::eventFilter(SDL_Event e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			exit();
			break;
		case SDL_WINDOWEVENT:
			if(e.window.event == SDL_WINDOWEVENT_CLOSE) exit();
			break;
	}
}

Game game;