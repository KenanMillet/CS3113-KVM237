#pragma once

#include <fstream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteSheet;
class UniformSpriteSheet;

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

extern SpriteSheet* getSpriteSheet(const char*, const char*);
extern UniformSpriteSheet* getUniformSpriteSheet(const char*, size_t, size_t = 0, size_t = 0, size_t = 0);

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

class UniformSpriteSheet
{
public:
	struct uvBounds;
	UniformSpriteSheet(const char*, size_t, size_t = 0, size_t = 0, size_t = 0);

	const uvBounds* find(size_t);

	float w, h;
	GLuint ID;
private:
	void load(const char*);

	std::vector<uvBounds> data;
};

struct UniformSpriteSheet::uvBounds
{
	uvBounds(float = 0, float = 0, float = 0, float = 0);
	float u, v, u2, v2;
};