#pragma once
#include <map>
#include <set>

class Tactile;

class CollisionHandler
{
public:
	void operator()();
	void add(Tactile*);
	void addException(Tactile*, Tactile*);
	void remove(Tactile*);
private:
	std::map<Tactile*, std::set<Tactile*>> objects;
};

extern CollisionHandler handleCollisions;