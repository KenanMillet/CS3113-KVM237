#include "MainGame.h"
#include "Entities.h"
#include "logger.h"
#include <cmath>
#include <string>

MainGame::MainGame()
	: Level(4.0f, -4.0f, 4.0f, -4.0f), music(Mix_LoadMUS("Sonic Blaster - F-777.mp3")), spawnDie(0.0f, 1.0f), posDie(-4.0f, 4.0f), difficulty(1.0f)
{
	Mix_Volume(-1, 128);
	Mix_VolumeMusic(20);
	Mix_PlayMusic(music, -1);

	spawnEntity<Player>(-3, -3, 0, "playerShip3_blue.png", "laserBlue07.png", SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	spawnEntity<Player>(3, -3, 0, "playerShip3_orange.png", "laserRed07.png", SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J, SDL_SCANCODE_L, SDL_SCANCODE_BACKSPACE);
	score = 0;
}

MainGame::~MainGame()
{
	Mix_FreeMusic(music);
}

void MainGame::tick(uint32_t e)
{
	if(Player::lives < 1) finish();

	std::string scoreStr("Score: ");
	scoreStr += std::to_string(score);
	std::string livesStr("Lives: ");
	livesStr += std::to_string(Player::lives);

	if(scoreText) despawnEntity(scoreText);
	if(livesText) despawnEntity(livesText);
	scoreText = spawnEntity<Text>(3.0f, 3.0f, 0.0f, scoreStr.c_str(), "font1.png", 1.0f, 1.0f, Text::Alignment::RIGHT);
	livesText = spawnEntity<Text>(-3.0f, 3.0f, 0.0f, livesStr.c_str(), "font1.png", 1.0f, 1.0f, Text::Alignment::LEFT);


	float elapsed = float(e) / 1000.0f;
	spawnElapsed += elapsed;
	float spawnChance = 1.0f - powf((1.0f / spawnElapsed), 0.25f * difficulty);
	if(spawnDie(generator) < spawnChance)
	{
		spawnElapsed = 0.0f;
		spawnEntity<Enemy>(posDie(generator), 4.5f);
		Enemy::spd = 0.5f * difficulty;
		Logger::log(numSpawn());
	}
	difficulty += pow(elapsed, difficulty)/2.0f;
}

uint32_t MainGame::score = 0;