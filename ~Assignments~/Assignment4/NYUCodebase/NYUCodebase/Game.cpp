#include "Game.h"
#include "Handlers.h"
#include "ShaderProgram.h"
#include "Levels.h"
#include "Camera.h"

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

Game::Game(const char* name, ShaderProgram** const program, Render& render, Tick& tick, CollisionHandler& ch, EventHandler& eh, LevelHandler& ll, ViewHandler& vh)
	: EventDependent({ SDL_QUIT, SDL_WINDOWEVENT }), fin(false), is_setup(false), programHandle(program), render(render), tick(tick), handleCollisions(ch), handleEvents(eh), handleLevels(ll), handleViews(vh)
{
	setup(name);
}

Game::~Game()
{
	cleanup();
}

Game::operator bool()
{
	return !is_done();
}

void Game::exit()
{
	fin = true;
}

bool Game::is_done() const
{
	return fin;
}

void Game::eventFilter(SDL_Event e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			exit();
			break;
		case SDL_WINDOWEVENT:
			if(e.window.event == SDL_WINDOWEVENT_CLOSE) exit();
			break;
	}
}

Game& Game::setup(const char* name)
{
	if(name == "" || is_setup) return *this;

	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif
	glViewport(0, 0, 640, 360);
	program() = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	glUseProgram(program()->programID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	is_setup = true;

	Matrix viewMatrix, projectionMatrix;
	projectionMatrix.setOrthoProjection(-4.0f, 4.0f, -4.0f, 4.0f, -1.0f, 1.0f);

	defaultView = new Camera(viewMatrix, projectionMatrix);

	handleViews.setActiveView(defaultView);

	return *this;
}

Game& Game::run()
{
	handleLevels.load<MainGame>();
	while(!fin)
	{
		processEvents();
		updateObjects();
		preObjectRender();
		renderObjects();
		postObjectRender();
	}
	return *this;
}

Game& Game::processEvents()
{
	handleEvents();
	return *this;
}

Game& Game::updateObjects()
{
	tick();
	handleCollisions();
	return *this;
}

Game& Game::preObjectRender()
{
	handleViews();
	glClear(GL_COLOR_BUFFER_BIT);
	return *this;
}

Game& Game::renderObjects()
{
	render();
	return *this;
}

Game& Game::postObjectRender()
{
	SDL_GL_SwapWindow(displayWindow);
	return *this;
}

Game& Game::cleanup()
{
	delete program();
	delete defaultView;
	defaultView = nullptr;
	program() = nullptr;
	SDL_Quit();
	
	is_setup = false;

	return *this;
}

ShaderProgram*& Game::program()
{
	return *programHandle;
}

Game game;

ShaderProgram** const Game::defaultProgramHandle = &::program;
Render& Game::defaultRender = ::render;
Tick& Game::defaultTick = ::tick;
CollisionHandler& Game::defaultCollHandler = ::handleCollisions;
EventHandler& Game::defaultEventHandler = ::handleEvents;
LevelHandler& Game::defaultLevelHandler = ::handleLevels;
ViewHandler& Game::defaultViewHandler = ::handleViews;