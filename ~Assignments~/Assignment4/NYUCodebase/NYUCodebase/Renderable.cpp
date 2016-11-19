#include "Renderable.h"
#include "Render.h"

Renderable::Renderable(Render* render)
	: renderer(render), renderpack(new Renderpack)
{
	renderer->add(this);
}

Renderable::Renderable(const Renderable& original)
	: renderer(original.renderer), renderpack(new Renderpack(*(original.renderpack)))
{
	renderer->add(this);
}

Renderable::Renderable(Renderable&& temp)
	: renderer(temp.renderer), renderpack(temp.renderpack)
{
	renderer->add(this);
	temp.renderpack = nullptr;
}

Renderable::~Renderable()
{
	renderer->remove(this);
	delete renderpack;
}

Renderable & Renderable::operator=(const Renderable& original)
{
	if(this != &original)
	{
		if(renderer != original.renderer)
		{
			renderer->remove(this);
			renderer = original.renderer;
			renderer->add(this);
		}
		delete renderpack;
		renderpack = new Renderpack(*(original.renderpack));
	}
	return *this;
}

Renderable & Renderable::operator=(Renderable&& temp)
{
	if(&temp != this)
	{
		Renderpack* tp = renderpack;
		renderpack = temp.renderpack;
		temp.renderpack = tp;

		if(renderer != temp.renderer)
		{
			renderer->remove(this);
			renderer = temp.renderer;
			renderer->add(this);
		}
	}
	return *this;
}

void Renderable::prerender()
{
}

Renderable::Renderpack* Renderable::render()
{
	return renderpack;
}

void Renderable::postrender()
{
}

Matrix & Renderable::transMatrix() const
{
	return renderpack->matrix;
}

GLuint & Renderable::textureID() const
{
	return renderpack->textureID;
}

std::vector<float>& Renderable::vertexCoords() const
{
	return renderpack->vertexCoords;
}

std::vector<float>& Renderable::textureCoords() const
{
	return renderpack->textureCoords;
}

void Renderable::unlock()
{
	renderpack->okay = true;
}

void Renderable::lock()
{
	renderpack->okay = false;
}



bool Renderable::Renderpack::ready() const
{
	return okay;
}

const Matrix* Renderable::Renderpack::getMatrix() const
{
	if(okay) return &(matrix);
	return nullptr;
}

const GLuint* Renderable::Renderpack::getTextureID() const
{
	if(okay) return &(textureID);
	return nullptr;
}

const float* Renderable::Renderpack::getVertexCoords() const
{
	if(okay) return &(vertexCoords.front());
	return nullptr;
}

const float* Renderable::Renderpack::getTextureCoords() const
{
	if(okay) return &(textureCoords.front());
	return nullptr;
}

size_t Renderable::Renderpack::getSize() const
{
	return vertexCoords.size();
}

Render* Renderable::defaultRender = &::render;