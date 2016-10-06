#pragma once
#include "EventDependent.h"

class Game : EventDependent
{
public:
	Game();

	operator bool();

	void exit();
	bool is_done() const;

	void eventFilter(SDL_Event);

private:
	bool fin;
};

extern Game game;