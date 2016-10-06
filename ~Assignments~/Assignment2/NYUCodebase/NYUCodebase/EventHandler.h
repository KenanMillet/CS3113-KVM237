#pragma once
#include <unordered_map>
#include <SDL.h>

class EventDependent;

class EventHandler
{
public:
	void operator()();
	void add(EventDependent*, SDL_EventType);
	void add(EventDependent*, std::initializer_list <SDL_EventType>);
	void remove(EventDependent*, SDL_EventType);
	void remove(EventDependent*, std::initializer_list <SDL_EventType>);
private:
	std::unordered_multimap<SDL_EventType, EventDependent*> map;
};

extern EventHandler handleEvents;