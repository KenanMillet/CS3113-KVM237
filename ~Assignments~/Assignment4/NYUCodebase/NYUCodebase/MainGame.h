#pragma once
#include "Level.h"
#include "Tickable.h"
#include "FlareTokenizer.h"

class Camera;

class MainGame : public Level,  public Tickable
{
public:
	MainGame();

	virtual void tick(uint32_t);
private:
	Entity* player;
	float camDirX, camDirY, spd;
	float cx, cy;
	Camera* camera;
	std::vector<std::vector<unsigned char>> tilemap;
	std::vector<FlareTokenizer::EntityData> entityData;
};