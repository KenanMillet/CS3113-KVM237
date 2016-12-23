#include "EventHandler.h"
#include "EventDependent.h"
#include <set>

void EventHandler::operator()()
{
	SDL_Event event;
	std::set<EventDependent*> called;

	while(SDL_PollEvent(&event))
	{
		SDL_EventType type = SDL_EventType(event.type);
		auto itr = map.equal_range(type).first;
		auto end = map.equal_range(type).second;
		while(itr != end)
		{
			itr->second->eventNo++;
			itr->second->eventFilter(event);
			called.insert(itr->second);
			++itr;
		}
	}
	for(auto c : called) c->eventNo = 0;
}

void EventHandler::add(EventDependent* d, SDL_EventType e)
{
	map.insert(std::make_pair(e, d));
}

void EventHandler::add(EventDependent* d, std::initializer_list <SDL_EventType> elist)
{
	for(SDL_EventType e : elist) add(d, e);
}

void EventHandler::remove(EventDependent* d, SDL_EventType e)
{
	auto itr = map.equal_range(e).first;
	auto end = map.equal_range(e).second;
	while(itr != end)
	{
		if(itr->second == d)
		{
			map.erase(itr);
			break;
		}
		++itr;
	}
}

void EventHandler::remove(EventDependent* d, std::initializer_list <SDL_EventType> elist)
{
	for(SDL_EventType e : elist) remove(d, e);
}

EventHandler handleEvents;