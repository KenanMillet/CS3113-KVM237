#pragma once
#include "EventDependent.h"
#include "Matrix.h"

class ShaderProgram;
class Render;
class Tick;
class CollisionHandler;
class EventHandler;
class LevelHandler;

class Game : EventDependent
{
public:
	Game(const char* = "", ShaderProgram** const = defaultProgramHandle, Render& = defaultRender, Tick& = defaultTick, CollisionHandler& = defaultCollHandler, EventHandler& = defaultEventHandler, LevelHandler& = defaultLevelHandler);
	~Game();

	operator bool();

	void exit();
	bool is_done() const;

	void eventFilter(SDL_Event);

	Game& setup(const char*);
	Game& run();
	Game& processEvents();
	Game& updateObjects();
	Game& preObjectRender();
	Game& renderObjects();
	Game& postObjectRender();
	Game& cleanup();

	ShaderProgram*& program();

private:
	ShaderProgram** programHandle;
	SDL_Window* displayWindow;
	Matrix projectionMatrix;
	Matrix viewMatrix;

	bool fin, is_setup;

	Render& render;
	Tick& tick;
	CollisionHandler& handleCollisions;
	EventHandler& handleEvents;
	LevelHandler& handleLevels;

	static ShaderProgram** const defaultProgramHandle;
	static Render& defaultRender;
	static Tick& defaultTick;
	static CollisionHandler& defaultCollHandler;
	static EventHandler& defaultEventHandler;
	static LevelHandler& defaultLevelHandler;
};

extern Game game;