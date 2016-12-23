#include "Level.h"
#include "Entity.h"
#include "Ticker.h"

Level::Level(Ticker* tick)
	: boundsNorth(0.0f), boundsSouth(0.0f), boundsEast(0.0f), boundsWest(0.0f), fin(false), tick(tick)
{
	handleViews.setActiveView(&camera);
}

Level::Level(float north, float south, float east, float west, Ticker* tick)
	: boundsNorth(north), boundsSouth(south), boundsEast(east), boundsWest(west), fin(false), tick(tick)
{
	camera.projectionMatrix.setOrthoProjection(west, east, south, north, -1.0f, 1.0f);
	handleViews.setActiveView(&camera);
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

size_t Level::numSpawn() const
{
	return entities.numSpawn();
}

void Level::onLoad()
{
}

void Level::finish()
{
	fin = true;
}

Ticker* Level::defaultTick = &::tick;