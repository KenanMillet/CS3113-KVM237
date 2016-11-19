#include "Level.h"
#include "Entity.h"
#include "Tick.h"

Level::Level(float north, float south, float east, float west, Tick* tick)
	: boundsNorth(north), boundsSouth(south), boundsEast(east), boundsWest(west), fin(false), tick(tick)
{
}

Level::~Level()
{
	for(auto e : entities) delete e;
}

float Level::nBound() const
{
	return boundsNorth;
}

float Level::sBound() const
{
	return boundsSouth;
}

float Level::eBound() const
{
	return boundsEast;
}

float Level::wBound() const
{
	return boundsWest;
}

bool Level::done() const
{
	return fin;
}

void Level::begin()
{
	tick->reset();
	onLoad();
}

void Level::onLoad()
{
}

void Level::finish()
{
	fin = true;
}

void Level::setupEntity(Entity* entity, float xPos, float yPos, float zPos)
{
	entities.push_back(entity);
	entities.back()->xPos = xPos;
	entities.back()->yPos = yPos;
	entities.back()->zPos = zPos;
	entities.back()->level = this;
}

Tick* Level::defaultTick = &::tick;