#include "Ticker.h"
#include "Tickable.h"
#include <SDL.h>

void Ticker::operator()()
{
	uint32_t elapsed = SDL_GetTicks() - last;
	last += elapsed;

	for(Tickable* t : objects) t->tick(elapsed);
}

void Ticker::add(Tickable* t)
{
	objects.insert(t);
}

void Ticker::remove(Tickable* t)
{
	objects.erase(t);
}

void Ticker::reset()
{
	last = SDL_GetTicks();
}

Ticker tick;