#pragma once
#include<SDL.h>
#include "EventHandler.h"
#include <cstdint>
#include <set>

class EventDependent
{
	friend void EventHandler::operator()();
public:
	EventDependent(SDL_EventType, EventHandler* = defaultEventHandler);
	EventDependent(std::initializer_list <SDL_EventType>, EventHandler* = defaultEventHandler);
	EventDependent(const EventDependent&);
	EventDependent(EventDependent&&);
	virtual ~EventDependent();

	EventDependent& operator=(const EventDependent&);
	EventDependent& operator=(EventDependent&&);

	virtual void eventFilter(SDL_Event) = 0;

protected:
	uint8_t eventNo;
	SDL_Event event;

	static EventHandler* defaultEventHandler;
private:
	std::set<SDL_EventType> events;
	EventHandler* eventHandler;
};