#include "Texture.h"
#include <cmath>

using namespace std;

Texture::Texture(const char* texture)
{
	uv[0][0] = 0;
	uv[0][1] = 0;
	uv[1][0] = 1;
	uv[1][1] = 1;
	load(texture);
}

Texture::Texture(const char* texture, float u, float v, float u2, float v2)
{
	uv[0][0] = u;
	uv[0][1] = v;
	uv[1][0] = u2;
	uv[1][1] = v2;
	load(texture);
}

Texture::Texture(const char* texture, SpriteSheet& sheet)
{
	auto uvb = sheet.find(texture);
	if(uvb)
	{
		uv[0][0] = uvb->u;
		uv[0][1] = uvb->v;
		uv[1][0] = uvb->u2;
		uv[1][1] = uvb->v2;
	}
	ID = sheet.ID;
}

void Texture::load(const char* texture)
{
	SDL_Surface *surface = IMG_Load(texture);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
}

SpriteSheet::SpriteSheet(const char* sheet, const char* atlas)
	: w(0), h(0)
{
	string line;
	string name;
	size_t l, r;
	float x, y, width, height;

	load(sheet);

	ifstream file(atlas);
	while(file.good())
	{
		getline(file, line);
		if(line.find("SubTexture") == string::npos) continue;

		l = line.find("name=\"") + 6;
		r = line.find("\"", l);
		name = line.substr(l, r - l);

		l = line.find("x=\"") + 3;
		r = line.find("\"", l);
		x = stof(line.substr(l, r - l));

		l = line.find("y=\"") + 3;
		r = line.find("\"", l);
		y = stof(line.substr(l, r - l));

		l = line.find("width=\"") + 7;
		r = line.find("\"", l);
		width = stof(line.substr(l, r - l));

		l = line.find("height=\"") + 8;
		r = line.find("\"", l);
		height = stof(line.substr(l, r - l));

		data[name] = uvBounds(x/w, y/h, (x + width)/w, (y + height)/h);
	}
}

const SpriteSheet::uvBounds* SpriteSheet::find(const string& texture)
{
	auto itr = data.find(texture);
	if(itr == data.end()) return nullptr;
	return &(itr->second);
}

void SpriteSheet::load(const char* texture)
{
	SDL_Surface *surface = IMG_Load(texture);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	w = float(surface->w);
	h = float(surface->h);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
}

SpriteSheet::uvBounds::uvBounds(float u, float v, float u2, float v2)
	: u(u), v(v), u2(u2), v2(v2)
{
}