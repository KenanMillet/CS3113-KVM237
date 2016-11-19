#include "LevelHandler.h"
#include "Level.h"

LevelHandler handleLevels;

LevelHandler::LevelHandler()
	: level(nullptr)
{
}

void LevelHandler::unload()
{
	delete level;
}

bool LevelHandler::levelDone() const
{
	return level->done();
}
