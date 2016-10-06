#ifdef _WINDOWS
	#include <GL/glew.h>
#endif
#include "ShaderProgram.h"
#include "Tick.h"
#include "Render.h"
#include "Game.h"
#include "EventHandler.h"
#include "CollisionHandler.h"
#include "Entities.h"

#ifdef _WINDOWS
	#define RESOURCE_FOLDER ""
#else
	#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

using namespace std;

SDL_Window* displayWindow;
SDL_Event event;

Matrix projectionMatrix;
Matrix viewMatrix;


void setup()
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Assignment 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif

	glViewport(0, 0, 640, 360);

	program = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

	projectionMatrix.setOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);

	glUseProgram(program->programID);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void processEvents()
{
	handleEvents();
}

void update()
{
	tick();
	handleCollisions();
}

void preRender()
{
	program->setProjectionMatrix(projectionMatrix);
	program->setViewMatrix(viewMatrix);
	glClear(GL_COLOR_BUFFER_BIT);
}

void inRender()
{
	render();
}

void postRender()
{
	SDL_GL_SwapWindow(displayWindow);
}

void cleanup()
{
	delete program;
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	setup();
	Ball* ball = new Ball;
	Paddle* p1p = new Paddle(SDL_SCANCODE_W, SDL_SCANCODE_S, -3, ball, 1);
	Paddle* p2p = new Paddle(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, 3, ball, 2);
	Goal* p1g = new Goal(4, 100, ball, p1p);
	Goal* p2g = new Goal(-4, 100, ball, p2p);
	Wall* top = new Wall(2, 3.55 * 2);
	Wall* bottom = new Wall(-2, 3.55 * 2);
	while (game) {
		processEvents();
		update();
		preRender();
		inRender();
		postRender();
	}
	cleanup();
	delete p1p;
	delete p2p;
	delete ball;
	delete top;
	delete bottom;
	delete p1g;
	delete p2g;
	return 0;
}