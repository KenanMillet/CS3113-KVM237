#pragma once
#include "Level.h"
#include "Tickable.h"
#include <SDL_mixer.h>
#include <random>

class MainGame : public Level, public Tickable
{
public:
	MainGame();
	~MainGame();

	virtual void tick(uint32_t);

	static uint32_t score;
private:
	float spawnElapsed;
	float difficulty;

	Entity* scoreText;
	Entity* livesText;

	Mix_Music* music;
	std::default_random_engine generator;
	std::uniform_real_distribution<float> spawnDie;
	std::uniform_real_distribution<float> posDie;
};