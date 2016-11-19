#include "Tick.h"
#include "Tickable.h"
#include <SDL.h>

void Tick::operator()()
{
	uint32_t elapsed = SDL_GetTicks() - last;
	last += elapsed;

	for(Tickable* t : objects) t->tick(elapsed);
}

void Tick::add(Tickable* t)
{
	objects.insert(t);
}

void Tick::remove(Tickable* t)
{
	objects.erase(t);
}

void Tick::reset()
{
	last = SDL_GetTicks();
}

Tick tick;