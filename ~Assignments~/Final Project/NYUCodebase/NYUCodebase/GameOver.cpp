#include "GameOver.h"
#include "Text.h"

GameOver::GameOver()
	: Level(4.0f, -4.0f, 4.0f, -4.0f),
	EventDependent(SDL_KEYDOWN)
{
	spawnEntity<Text>(0.0f, 0.0f, 0.0f, "Game Over.", "font1.png");
	spawnEntity<Text>(0.0f, -2.0f, 0.0f, "Press ENTER to return to the title screen", "font1.png", 0.5f, 0.5f);
}

void GameOver::eventFilter(SDL_Event event)
{
	if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) finish();
}