#pragma once
#include <vector>
#include <type_traits>
#include "Spawner.h"
#include "Camera.h"

class Entity;
class Ticker;

class Level
{
	friend Entity;
public:
	Level(Ticker* = defaultTick);
	Level(float, float, float, float, Ticker* = defaultTick);
	virtual ~Level() = default;

	float nBound() const;
	float sBound() const;
	float eBound() const;
	float wBound() const;

	bool done() const;

	void begin();
protected:
	template<class E, class Arg, class... Args> E* spawnEntity(float, float, float, Arg, Args...);
	template<class E> E* spawnEntity(float = 0, float = 0, float = 0);
	template<class E> bool despawnEntity(E*);
	template<class E> bool disown(E*);

	size_t numSpawn() const;

	virtual void onLoad();

	void finish();

	Camera camera;
private:
	float boundsNorth, boundsSouth, boundsEast, boundsWest;

	bool fin;

	Spawner entities;

	Ticker* tick;

	static Ticker* defaultTick;
};

template<class E, class Arg, class... Args>
inline E* Level::spawnEntity(float xPos, float yPos, float zPos, Arg arg, Args... args)
{
	E* e = entities.spawn<E>({ Vector(xPos, yPos, zPos) }, arg, args...);
	((Entity*) e)->_level = this;
	return e;
}

template<class E>
inline E* Level::spawnEntity(float xPos, float yPos, float zPos)
{
	E* e = entities.spawn<E>({ Vector(xPos, yPos, zPos) });
	((Entity*) e)->_level = this;
	return e;
}

template<class E>
inline bool Level::despawnEntity(E* e)
{
	return entities.despawn(e);
}

template<class E>
inline bool Level::disown(E* e)
{
	return entities.disown(e);
}