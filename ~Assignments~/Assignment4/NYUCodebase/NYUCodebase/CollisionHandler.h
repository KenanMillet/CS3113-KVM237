#pragma once
#include <map>
#include <set>
#include <cstdint>

class Tactile;

class CollisionHandler
{
public:
	void operator()();
	void add(Tactile*);
	void addException(Tactile*, Tactile*);
	void remove(Tactile*);

private:
	uint8_t checkCollision(Tactile*, Tactile*);
	uint8_t checkTouch(Tactile*, Tactile*);

	std::map<Tactile*, std::set<Tactile*>> objects;
};

extern CollisionHandler handleCollisions;