#pragma once

class Level;

class LevelHandler
{
public:
	LevelHandler();

	template<class L> bool load();
	void unload();

	bool levelDone() const;
private:
	Level* level;
};

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