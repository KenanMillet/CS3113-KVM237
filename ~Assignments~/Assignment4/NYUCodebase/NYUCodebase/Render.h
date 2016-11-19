#pragma once
#include <set>
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

	std::set<Renderable*> objects;
	ShaderProgram** programhandle;
	static ShaderProgram** const defaultProgram;
};

extern Render render;