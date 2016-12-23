#include "Renderer.h"
#include "Renderable.h"

Renderer::Renderer(ShaderProgram** programhandle)
	: programhandle(programhandle)
{
}

void Renderer::operator()()
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

void Renderer::add(Renderable* r)
{
	objects.insert(r);
}

void Renderer::remove(Renderable* r)
{
	objects.erase(r);
}

ShaderProgram*& Renderer::program() const
{
	return *programhandle;
}

Renderer render;

ShaderProgram** const Renderer::defaultProgram = &::program;