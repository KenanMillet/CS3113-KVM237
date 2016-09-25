#ifdef _WINDOWS
	#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Texture.h"

#ifdef _WINDOWS
	#define RESOURCE_FOLDER ""
#else
	#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Assignment 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif

	glViewport(0, 0, 640, 360);

	ShaderProgram program(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	
	float lastFrameTicks = 0.0;

	GLuint bombTex = LoadTexture(RESOURCE_FOLDER"Bomb.png");
	GLuint fireTex = LoadTexture(RESOURCE_FOLDER"Fire.png");
	GLuint spdTex = LoadTexture(RESOURCE_FOLDER"SpD.png");
	GLuint spuTex = LoadTexture(RESOURCE_FOLDER"SpU.png");

	float bombVert[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float fireVert[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float spdVert[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float spuVert[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float bombTexCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
	float fireTexCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
	float spdTexCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
	float spuTexCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

	float fireAngle = 0.0;
	float bombFireVel = 0.0;
	float g = -0.0075f;
	float bombPos[] = { 0.0, 1.0, 0.0 };
	float firePosRel[] = { -0.35, 0.3, 0.0 };
	float springPos[] = { 0.0, -1.5, 0.0 };
	float springTopRel = 0.6;
	float springtime[] = {0.0, 0.1};
	float springBounce = false;

	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	projectionMatrix.setOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);

	glUseProgram(program.programID);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_Event event;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		float ticks = (float) SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		glClear(GL_COLOR_BUFFER_BIT);

		program.setModelMatrix(modelMatrix);
		program.setProjectionMatrix(projectionMatrix);
		program.setViewMatrix(viewMatrix);
		
		if(bombPos[1] <= springPos[1] + springTopRel && !springBounce)
		{
			bombPos[1] = springPos[1] + springTopRel;
			springtime[0] += elapsed;
			if(springtime[0] >= springtime[1])
			{
				bombFireVel *= -1;
				springBounce = true;
				springtime[0] = 0.0;
			}
		}
		else
		{
			springBounce = false;
			bombFireVel += g * elapsed;
			bombPos[1] += bombFireVel;
			if(bombPos[1] > -springPos[1])
			{
				bombPos[1] = -springPos[1];
				bombFireVel = 0.0;
			}
		}

		modelMatrix.identity();
		modelMatrix.Translate(bombPos[0], bombPos[1], bombPos[2]);
		program.setModelMatrix(modelMatrix);
		glBindTexture(GL_TEXTURE_2D, bombTex);
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, bombVert);
		glEnableVertexAttribArray(program.positionAttribute);
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, bombTexCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);

		modelMatrix.identity();
		modelMatrix.Translate(bombPos[0] + firePosRel[0], bombPos[1] + firePosRel[1], bombPos[2] + firePosRel[2]);
		modelMatrix.Scale(0.5, 0.5, 1.0);
		fireAngle = fireAngle + elapsed*16;
		fireAngle = (fireAngle > 2 * 3.14) ? fireAngle - (2 * 3.14) : fireAngle;
		modelMatrix.Rotate(fireAngle);
		program.setModelMatrix(modelMatrix);
		glBindTexture(GL_TEXTURE_2D, fireTex);
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, fireVert);
		glEnableVertexAttribArray(program.positionAttribute);
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, fireTexCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);

		if(bombPos[1] <= springPos[1] + springTopRel && !springBounce)
		{
			modelMatrix.identity();
			modelMatrix.Translate(springPos[0], springPos[1], springPos[2]);
			program.setModelMatrix(modelMatrix);
			glBindTexture(GL_TEXTURE_2D, spdTex);
			glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, spdVert);
			glEnableVertexAttribArray(program.positionAttribute);
			glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, spdTexCoords);
			glEnableVertexAttribArray(program.texCoordAttribute);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisableVertexAttribArray(program.positionAttribute);
			glDisableVertexAttribArray(program.texCoordAttribute);
		}
		else
		{
			modelMatrix.identity();
			modelMatrix.Translate(springPos[0], springPos[1], springPos[2]);
			program.setModelMatrix(modelMatrix);
			glBindTexture(GL_TEXTURE_2D, spuTex);
			glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, spuVert);
			glEnableVertexAttribArray(program.positionAttribute);
			glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, spuTexCoords);
			glEnableVertexAttribArray(program.texCoordAttribute);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisableVertexAttribArray(program.positionAttribute);
			glDisableVertexAttribArray(program.texCoordAttribute);
		}

		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}