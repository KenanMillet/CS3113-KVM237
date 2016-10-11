#pragma once
#include <vector>
#include "ShaderProgram.h"

class Renderable;

class Render
{
public:
	Render(ShaderProgram** = defaultProgram);

	void operator()();
	void add(Renderable*);
	void remove(Renderable*);
private:
	ShaderProgram*& program() const;

	std::vector<Renderable*> objects;
	ShaderProgram** programhandle;
	static ShaderProgram** const defaultProgram;
};

extern Render render;