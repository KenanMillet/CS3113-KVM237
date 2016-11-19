#include "Model.h"
#include "Texture.h"
#include "logger.h"

using namespace std;

Model::Model(const char* texture, Matrix& matrix, Render* renderer)
	: Renderable(renderer), w(1.0f), h(1.0f)
{
	loadTexture(texture);
	transMatrix() = matrix;
	this->vertexCoords() = { -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f };
	this->textureCoords() = { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
}

Model::Model(const char* texture, std::initializer_list<float> vertexCoords, float w, float h, std::initializer_list<float> textureCoords, Matrix& matrix, Render* renderer)
	: Renderable(renderer), w(w), h(h)
{
	loadTexture(texture);
	transMatrix() = matrix;
	this->vertexCoords() = vertexCoords;
	this->textureCoords() = textureCoords;
}

Model::Model(const char* texture, SpriteSheet* sheet, float sizeX, float sizeY, Matrix& matrix, Render* renderer)
	: Renderable(renderer)
{
	if(sizeY == 0.0f) sizeY = sizeX;
	auto uvb = sheet->find(texture);
	textureID() = sheet->ID;
	transMatrix() = matrix;
	float a = ((uvb->u2 - uvb->u) * sheet->w) / ((uvb->v2 - uvb->v) * sheet->h);
	this->vertexCoords() = { -0.5f * sizeX * a, -0.5f * sizeY, 0.5f * sizeX * a, 0.5f * sizeY, -0.5f * sizeX * a, 0.5f * sizeY, 0.5f * sizeX * a, 0.5f * sizeY, -0.5f * sizeX * a, -0.5f * sizeY, 0.5f * sizeX * a, -0.5f * sizeY };
	this->textureCoords() = { uvb->u, uvb->v2, uvb->u2, uvb->v, uvb->u, uvb->v, uvb->u2, uvb->v, uvb->u, uvb->v2, uvb->u2, uvb->v2 };
	w = sizeX * a;
	h = sizeY;
}

Model::Model(size_t index, UniformSpriteSheet* sheet, float sizeX, float sizeY, Matrix& matrix, Render* renderer)
	: Renderable(renderer)
{
	if(sizeY == 0.0f) sizeY = sizeX;
	auto uvb = sheet->find(index);
	textureID() = sheet->ID;
	transMatrix() = matrix;
	float a = ((uvb->u2 - uvb->u) * sheet->w) / ((uvb->v2 - uvb->v) * sheet->h);
	this->vertexCoords() = { -0.5f * sizeX * a, -0.5f * sizeY, 0.5f * sizeX * a, 0.5f * sizeY, -0.5f * sizeX * a, 0.5f * sizeY, 0.5f * sizeX * a, 0.5f * sizeY, -0.5f * sizeX * a, -0.5f * sizeY, 0.5f * sizeX * a, -0.5f * sizeY };
	this->textureCoords() = { uvb->u, uvb->v2, uvb->u2, uvb->v, uvb->u, uvb->v, uvb->u2, uvb->v, uvb->u, uvb->v2, uvb->u2, uvb->v2 };
	w = sizeX * a;
	h = sizeY;
}

Model::Model(const char* texture, const char* sheet, const char* atlas, float sizeX, float sizeY, Matrix& matrix, Render* renderer)
	: Renderable(renderer)
{
	SpriteSheet* ss = getSpriteSheet(sheet, atlas);
	if(sizeY == 0.0f) sizeY = sizeX;
	auto uvb = ss->find(texture);
	textureID() = ss->ID;
	transMatrix() = matrix;
	float a = (uvb->u2 - uvb->u) / (uvb->v2 - uvb->v);
	this->vertexCoords() = { -0.5f * sizeX * a, -0.5f * sizeY, 0.5f * sizeX * a, 0.5f * sizeY, -0.5f * sizeX * a, 0.5f * sizeY, 0.5f * sizeX * a, 0.5f * sizeY, -0.5f * sizeX * a, -0.5f * sizeY, 0.5f * sizeX * a, -0.5f * sizeY };
	this->textureCoords() = { uvb->u, uvb->v2, uvb->u2, uvb->v, uvb->u, uvb->v, uvb->u2, uvb->v, uvb->u, uvb->v2, uvb->u2, uvb->v2 };
	w = sizeX * a;
	h = sizeY;
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

Model& Model::resetPosition()
{
	transMatrix().identity();
	return *this;
}

float Model::getX() const
{
	return xPos;
}

float Model::getY() const
{
	return yPos;
}

float Model::getZ() const
{
	return zPos;
}

float Model::width() const
{
	return w;
}

float Model::height() const
{
	return h;
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