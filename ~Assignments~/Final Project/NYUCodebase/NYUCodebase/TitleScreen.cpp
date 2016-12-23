#include "TitleScreen.h"
#include "Text.h"

TitleScreen::TitleScreen()
	:	Level(4.0f, -4.0f, 4.0f, -4.0f),
	EventDependent(SDL_KEYDOWN)
{
	spawnEntity<Text>(0.0f, 0.0f, 0.0f, "Last Line of Defense", "font1.png");
	spawnEntity<Text>(0.0f, -1.0f, 0.0f, "Press ENTER to begin", "font1.png", 0.5f, 0.5f);
	spawnEntity<Text>(0.0f, -2.0f, 0.0f, "Press ESC at any time to quit", "font1.png", 0.5f, 0.5f);
}

void TitleScreen::eventFilter(SDL_Event event)
{
	if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) finish();
}
