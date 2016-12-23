#pragma once
#include <functional>
#include <queue>

class Level;

class LevelHandler
{
public:
	LevelHandler();
	
	int operator()();

	template<class L> void addToQueue();
	bool empty() const;

	template<class L> bool load();
	void unload();

	bool levelDone() const;
private:
	std::queue<std::function<bool(void)>> levelQueue;
	Level* level;
};

template<class L>
inline void LevelHandler::addToQueue()
{
	levelQueue.push(std::bind(&LevelHandler::load<L>, this));
}

template<class L>
bool LevelHandler::load()
{
	L* l = new L;
	Level* tmp;
	if(!(tmp = dynamic_cast<Level*>(l)))
	{
		delete l;
		return false;
	}
	if(level) unload();
	level = tmp;
	level->begin();
	return true;
}

extern LevelHandler handleLevels;