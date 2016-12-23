#pragma once

#include "TactileEntity.h"
#include "EventDependent.h"
#include <SDL_mixer.h>

class Bullet;
class MainGame;

class Player : public TactileEntity, public EventDependent
{
	friend MainGame;
public:
	Player(const char*, const char*, SDL_Scancode, SDL_Scancode, SDL_Scancode, SDL_Scancode, SDL_Scancode);
	~Player();

	Player& operator=(const Player&);

	virtual void eventFilter(SDL_Event);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void touch(Tactile*, Vector);

private:
	void fire();
	bool ready();

	float accelx, accely, velx, vely;
	float elapsed;

	SDL_Scancode u, d, l, r, f;

	Bullet* bullet;

	float iTime;

	static uint8_t lives;
	static size_t numInstances;
	static Mix_Chunk* fireSound;
	static Mix_Chunk* explosionSound;
	static Mix_Chunk* damageSound;
};