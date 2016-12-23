#include "LevelHandler.h"
#include "Level.h"
#include "logger.h"

LevelHandler handleLevels;

LevelHandler::LevelHandler()
	: level(nullptr)
{
}

int LevelHandler::operator()()
{
	static int i = 0;
	if(!level || levelDone())
	{
		if(levelQueue.empty()) return -2; //empty queue
		bool res = levelQueue.front()();
		levelQueue.pop();
		return (res ? 1 : -1); //successful load (1) or failed load (-1)
	}
	else return 0; //no change of level
}

bool LevelHandler::empty() const
{
	return levelQueue.empty();
}

void LevelHandler::unload()
{
	delete level;
}

bool LevelHandler::levelDone() const
{
	return level->done();
}
