#pragma once
#include "Entity.h"
#include <string>

class SpriteSheet;

class Text : public Entity
{
public:
	enum Alignment { LEFT, CENTERED, RIGHT};

	Text(const std::string&, const char*, float = 1.0f, float = 1.0f, Alignment = CENTERED);
	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);
};