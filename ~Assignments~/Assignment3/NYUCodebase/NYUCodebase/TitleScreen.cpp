#include "TitleScreen.h"
#include "Entities.h"

TitleScreen::TitleScreen()
	:	Level(4.0f, -4.0f, 4.0f, -4.0f),
		EventDependent(SDL_KEYDOWN)
{
	spawnCustomEntity<Text>(0.0f, 0.0f, 0.0f, "Space Invaders!", "font1.png");
	spawnCustomEntity<Text>(0.0f, -1.0f, 0.0f, "Press any key to continue", "font1.png", 0.5f, 0.5f);
}

void TitleScreen::eventFilter(SDL_Event event)
{
	finish();
}
