#include "Render.h"
#include "Renderable.h"

Render::Render(ShaderProgram** programhandle)
	: programhandle(programhandle)
{
}

void Render::operator()()
{
	for(auto r : objects) r->prerender();

	for(auto r : objects)
	{	
		Renderable::Renderpack* info = r->render();
		if(!info->ready()) continue;
		program()->setModelMatrix(*(info->getMatrix()));
		glBindTexture(GL_TEXTURE_2D, *(info->getTextureID()));
		glVertexAttribPointer(program()->positionAttribute, 2, GL_FLOAT, false, 0, info->getVertexCoords());
		glEnableVertexAttribArray(program()->positionAttribute);
		glVertexAttribPointer(program()->texCoordAttribute, 2, GL_FLOAT, false, 0, info->getTextureCoords());
		glEnableVertexAttribArray(program()->texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, info->getSize()/2);
		glDisableVertexAttribArray(program()->positionAttribute);
		glDisableVertexAttribArray(program()->texCoordAttribute);
	}

	for(auto r : objects) r->postrender();
}

void Render::add(Renderable* r)
{
	objects.push_back(r);
}

void Render::remove(Renderable* r)
{
	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		if(*i == r)
		{
			objects.erase(i);
			break;
		}
	}
}

ShaderProgram*& Render::program() const
{
	return *programhandle;
}

Render render;

ShaderProgram** const Render::defaultProgram = &::program;