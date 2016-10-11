#pragma once

#include <fstream>
#include <cstdint>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteSheet;

class Texture
{
public:
	Texture(const char*);
	Texture(const char*, float, float, float, float);
	Texture(const char*, SpriteSheet&);
private:
	void load(const char*);

	GLuint ID;
	float uv[2][2];
};

class SpriteSheet
{
public:
	struct uvBounds;
	SpriteSheet(const char*, const char*);

	const uvBounds* find(const std::string&);

	float w, h;
	GLuint ID;
private:
	void load(const char*);

	std::unordered_map<std::string, uvBounds> data;
};

struct SpriteSheet::uvBounds
{
	uvBounds(float = 0, float = 0, float = 0, float = 0);
	float u, v, u2, v2;
};