#include "MainGame.h"
#include "Entities.h"

MainGame::MainGame()
	: Level(4.0f, -4.0f, 4.0f, -4.0f)
{
	spawnEntity<Ship>(0.0f, sBound() + 0.5f);

	for(float y = nBound() - 0.5f; y >= nBound() - 2.0f; y -= 0.5f)
	{
		for(float x = -2.75f; x <= 2.75f; x += 0.5f)
		{
			spawnEntity<Enemy>(x, y);
		}
	}
}