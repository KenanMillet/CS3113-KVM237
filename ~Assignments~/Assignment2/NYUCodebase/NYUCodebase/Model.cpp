#include "Model.h"
#include "Matrix.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

using namespace std;

Model::Model(const char* texture, std::initializer_list<float> vertexCoords, std::initializer_list<float> textureCoords, Matrix& matrix, Render* renderer)
	: Renderable(renderer)
{
	loadTexture(texture);
	transMatrix() = matrix;
	this->vertexCoords() = vertexCoords;
	this->textureCoords() = textureCoords;
}

Model::Model(const char* texture, std::vector<float>& vertexCoords, std::vector<float>& textureCoords, Matrix& matrix, Render* renderer)
	: Renderable(renderer)
{
	loadTexture(texture);
	transMatrix() = matrix;
	this->vertexCoords() = vertexCoords;
	this->textureCoords() = textureCoords;
}

void Model::prerender()
{
	setup();
}

Renderable::Renderpack* Model::render()
{
	draw();
	unlock();
	return Renderable::render();
}

void Model::postrender()
{
	clean();
	lock();
}

Model& Model::move(float x, float y, float z)
{
	transMatrix().Translate(x, y, z);
	return *this;
}

Model& Model::rotate(float yaw, float pitch, float roll)
{
	transMatrix().Yaw(yaw);
	transMatrix().Pitch(pitch);
	transMatrix().Roll(roll);
	return *this;
}

Model& Model::scale(float w, float h, float l)
{
	transMatrix().Scale(w, h, l);
	return *this;
}

Model& Model::reset()
{
	transMatrix().identity();
	return *this;
}

float Model::getX()
{
	return x;
}

float Model::getY()
{
	return y;
}

float Model::getZ()
{
	return z;
}

void Model::setup()
{
}

void Model::clean()
{
}

void Model::loadTexture(const char* texture)
{
	SDL_Surface *surface = IMG_Load(texture);

	glGenTextures(1, &textureID());
	glBindTexture(GL_TEXTURE_2D, textureID());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
}
