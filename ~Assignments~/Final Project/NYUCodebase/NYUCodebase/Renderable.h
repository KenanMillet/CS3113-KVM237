#pragma once
#include "Matrix.h"
#include <vector>
#ifdef _WINDOWS
#include <GL/glew.h>
#endif

class Renderer;

class Renderable
{
public:
	class Renderpack;
public:
	Renderable(Renderer* = defaultRender);
	Renderable(const Renderable&);
	Renderable(Renderable&&);
	virtual ~Renderable();
	
	Renderable& operator=(const Renderable&);
	Renderable& operator=(Renderable&&);

	virtual void prerender();
	virtual Renderpack* render() = 0;
	virtual void postrender();
protected:
	Matrix& transMatrix() const;
	GLuint& textureID() const;
	std::vector<float>& vertexCoords() const;
	std::vector<float>& textureCoords() const;

	void unlock();
	void lock();

	static Renderer* defaultRender;
private:
	Renderer* renderer;
	Renderpack* renderpack;
};

class Renderable::Renderpack
{
	friend Renderable;
public:
	bool ready() const;
	const Matrix* getMatrix() const;
	const GLuint* getTextureID() const;
	const float* getVertexCoords() const;
	const float* getTextureCoords() const;
	const float* getVertexColors() const;
	size_t getSize() const;
private:
	bool okay;

	Matrix matrix;
	GLuint textureID;
	std::vector<float> vertexCoords;
	std::vector<float> textureCoords;
	std::vector<float> vertexColors;
};