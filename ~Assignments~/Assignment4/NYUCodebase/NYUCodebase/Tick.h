#pragma once
#include <set>
#include <cstdint>

class Tickable;

class Tick
{
public:
	void operator()();
	void add(Tickable*);
	void remove(Tickable*);
	void reset();
private:
	uint32_t last;
	std::set<Tickable*> objects;
};

extern Tick tick;