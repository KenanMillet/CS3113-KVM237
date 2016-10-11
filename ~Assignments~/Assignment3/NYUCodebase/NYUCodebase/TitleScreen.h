#pragma once
#include "Level.h"
#include "EventDependent.h"

class TitleScreen : public Level, public EventDependent
{
public:
	TitleScreen();

	virtual void eventFilter(SDL_Event);
};