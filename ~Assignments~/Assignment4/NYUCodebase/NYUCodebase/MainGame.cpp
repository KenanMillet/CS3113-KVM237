#include "MainGame.h"
#include "Entities.h"
#include "logger.h"
#include "ViewHandler.h"
#include "Camera.h"
#include "Entity.h"
#include <limits>

MainGame::MainGame()
	: Level(5.0f, -5.0f, 10.0f, -10.0f), camera(new Camera), spd(1.0f)
{
	FlareTokenizer levelFile({ "[Entities]" });
	if(levelFile.parse("map.txt"))
	{
		tilemap = levelFile.getLevelData();
		entityData = levelFile.getEntityData();
		float unitx = float(eBound() - wBound()) / float(tilemap[0].size());
		float unity = float(sBound() - nBound()) / float(tilemap.size());
		float dispx = float(tilemap[0].size()-1) / -2.0f;
		float dispy = float(tilemap.size()-1) / -2.0f;

		for(size_t y = 0; y < tilemap.size(); ++y)
		{
			for(size_t x = 0; x < tilemap[y].size(); ++x)
			{
				char tileid = tilemap[y][x];
				float xPos = (float(x) + dispx) * unitx;
				float yPos = (float(y) + dispy) * unity;
				if(tileid == 0) continue;
				if(tileid == 16) spawnEntity<Block>(xPos, yPos);
			}
		}
		for(auto e : entityData)
		{
			float xPos = (e.x + dispx) * unitx;
			float yPos = (e.y + dispy) * unity;
			if(e.type == "Player") player = spawnEntity<Player>(xPos, yPos, 0);
			if(e.type == "Slimy") spawnEntity<Slimy>(xPos, yPos, 0);
		}
	}
	camera->projectionMatrix.setOrthoProjection(-10.0f, 10.0f, -5.0f, 5.0f, -1.0f, 1.0f);
	handleViews.setActiveView(camera);
}

void MainGame::tick(uint32_t e)
{
	float delta = float(e) / 1000.0f;

	if(player)
	{
		cx = -player->getX();
		cy = -player->getY();
	}

	camera->viewMatrix.identity();
	camera->viewMatrix.Translate(cx, cy, 0);
}
