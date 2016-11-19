#pragma once
#include "EventDependent.h"
#include "Matrix.h"

#include <set>
#include <stack>

class ShaderProgram;
class Render;
class Tick;
class CollisionHandler;
class EventHandler;
class LevelHandler;
class ViewHandler;
class Camera;

class Game : EventDependent
{
public:
	Game(const char* = "", ShaderProgram** const = defaultProgramHandle, Render& = defaultRender, Tick& = defaultTick, CollisionHandler& = defaultCollHandler, EventHandler& = defaultEventHandler, LevelHandler& = defaultLevelHandler, ViewHandler& = defaultViewHandler);
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

	Camera* defaultView;

	bool fin, is_setup;

	Render& render;
	Tick& tick;
	CollisionHandler& handleCollisions;
	EventHandler& handleEvents;
	LevelHandler& handleLevels;
	ViewHandler& handleViews;

	static ShaderProgram** const defaultProgramHandle;
	static Render& defaultRender;
	static Tick& defaultTick;
	static CollisionHandler& defaultCollHandler;
	static EventHandler& defaultEventHandler;
	static LevelHandler& defaultLevelHandler;
	static ViewHandler& defaultViewHandler;
};

extern Game game;