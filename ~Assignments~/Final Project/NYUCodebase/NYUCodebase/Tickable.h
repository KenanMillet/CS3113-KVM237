#pragma once
#include <cstdint>

class Ticker;

class Tickable
{
public:
	Tickable(Ticker* = defaultTick);
	Tickable(const Tickable&);
	Tickable(Tickable&&);
	virtual ~Tickable();

	Tickable& operator=(const Tickable&);
	Tickable& operator=(Tickable&&);

	virtual void tick(uint32_t) = 0;

	static Ticker* defaultTick;
private:
	Ticker* thetick;
};