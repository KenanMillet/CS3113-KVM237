#pragma once
#include <vector>
#include <type_traits>

class Entity;
class Tick;

class Level
{
	friend Entity;
public:
	Level(float, float, float, float, Tick* = defaultTick);
	virtual ~Level();

	float nBound() const;
	float sBound() const;
	float eBound() const;
	float wBound() const;

	bool done() const;

	void begin();
protected:
	template<class E> bool spawnEntity(float = 0, float = 0, float = 0);
	template<class E, class... Args> bool spawnCustomEntity(float = 0, float = 0, float = 0, Args...);

	virtual void onLoad();

	void finish();
private:
	float boundsNorth, boundsSouth, boundsEast, boundsWest;

	bool fin;

	void setupEntity(Entity*, float, float, float);
	std::vector<Entity*> entities;

	Tick* tick;

	static Tick* defaultTick;
};

template<class E>
inline bool Level::spawnEntity(float xPos, float yPos, float zPos)
{
	if(!(std::is_base_of<Entity, E>::value)) return false;
	E* e = new E;
	setupEntity(dynamic_cast<Entity*>(e), xPos, yPos, zPos);
	return true;

}

template<class E, class... Args>
inline bool Level::spawnCustomEntity(float xPos, float yPos, float zPos, Args... args)
{
	if(!(std::is_base_of<Entity, E>::value)) return false;
	E* e = new E(args...);
	setupEntity(dynamic_cast<Entity*>(e), xPos, yPos, zPos);
	return true;
}