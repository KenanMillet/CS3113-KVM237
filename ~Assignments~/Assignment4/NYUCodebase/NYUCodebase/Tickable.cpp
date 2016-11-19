#include "Tickable.h"
#include "Tick.h"

Tickable::Tickable(Tick* tick)
	: thetick(tick)
{
	thetick->add(this);
}

Tickable::Tickable(const Tickable& original)
	: thetick(original.thetick)
{
	thetick->add(this);
}

Tickable::Tickable(Tickable&& temp)
	: thetick(temp.thetick)
{
	thetick->add(this);
}

Tickable::~Tickable()
{
	thetick->remove(this);
}

Tickable & Tickable::operator=(const Tickable& original)
{
	if(&original != this)
	{
		if(thetick != original.thetick)
		{
			thetick->remove(this);
			thetick = original.thetick;
			thetick->add(this);
		}
	}
	return *this;
}

Tickable & Tickable::operator=(Tickable&& temp)
{
	if(&temp != this)
	{
		if(thetick != temp.thetick)
		{
			thetick->remove(this);
			thetick = temp.thetick;
			thetick->add(this);
		}
	}
	return *this;
}

Tick* Tickable::defaultTick = &::tick;