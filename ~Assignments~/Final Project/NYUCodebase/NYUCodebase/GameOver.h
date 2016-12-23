#pragma once
#include "Level.h"
#include "EventDependent.h"

class GameOver : public Level, public EventDependent
{
public:
	GameOver();

	virtual void eventFilter(SDL_Event);
private:
	float elapsed;
};