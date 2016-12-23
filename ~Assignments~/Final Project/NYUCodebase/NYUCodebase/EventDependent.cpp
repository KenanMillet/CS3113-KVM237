#include "EventDependent.h"

EventDependent::EventDependent(SDL_EventType e, EventHandler* eventHandler)
	: eventHandler(eventHandler)
{
	eventHandler->add(this, e);
	events.insert(e);
}

EventDependent::EventDependent(std::initializer_list <SDL_EventType> elist, EventHandler* eventHandler)
	: eventHandler(eventHandler)
{
	eventHandler->add(this, elist);
	events.insert(elist);
}

EventDependent::EventDependent(const EventDependent& original)
	: eventHandler(original.eventHandler), events(original.events)
{
	for(SDL_EventType e : events) eventHandler->add(this, e);
}

EventDependent::EventDependent(EventDependent&& temp)
	: eventHandler(temp.eventHandler), events(std::move(temp.events))
{
	for(SDL_EventType e : events) eventHandler->add(this, e);
}

EventDependent::~EventDependent()
{
	for(SDL_EventType e : events) eventHandler->remove(this, e);
}

EventDependent & EventDependent::operator=(const EventDependent& original)
{
	if(&original != this)
	{
		for(SDL_EventType e : events) eventHandler->remove(this, e);
		eventHandler = original.eventHandler;
		events = original.events;
		for(SDL_EventType e : events) eventHandler->add(this, e);
	}
	return *this;
}

EventDependent & EventDependent::operator=(EventDependent&& temp)
{
	if(&temp != this)
	{
		for(SDL_EventType e : events) eventHandler->remove(this, e);
		eventHandler = temp.eventHandler;
		std::swap(events, temp.events);
		for(SDL_EventType e : events) eventHandler->add(this, e);
	}
	return *this;
}

EventHandler* EventDependent::defaultEventHandler = &::handleEvents;