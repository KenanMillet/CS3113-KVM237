#pragma once
#include <cstdint>

class Tick;

class Tickable
{
public:
	Tickable(Tick* = defaultTick);
	Tickable(const Tickable&);
	Tickable(Tickable&&);
	virtual ~Tickable();

	Tickable& operator=(const Tickable&);
	Tickable& operator=(Tickable&&);

	virtual void tick(uint32_t) = 0;

	static Tick* defaultTick;
private:
	Tick* thetick;
};