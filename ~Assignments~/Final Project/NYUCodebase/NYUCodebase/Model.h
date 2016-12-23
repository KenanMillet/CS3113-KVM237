#pragma once
#include "Renderable.h"
#include "Matrix.h"

class SpriteSheet;
class UniformSpriteSheet;

class Model : virtual public Renderable
{
public:
	Model(const char* = "", Matrix& = Matrix(), Renderer* = Renderable::defaultRender);
	Model(std::initializer_list<Vector>, std::initializer_list<float>, std::initializer_list<float>, Matrix& = Matrix(), Renderer* = Renderable::defaultRender);
	Model(const char*, std::initializer_list<float>, float, float, std::initializer_list<float>, Matrix& = Matrix(), Renderer* = Renderable::defaultRender);
	Model(const char*, SpriteSheet*, float = 1.0f, float = 0.0f, Matrix& = Matrix(), Renderer* = Renderable::defaultRender);
	Model(size_t, UniformSpriteSheet*, float = 1.0f, float = 0.0f, Matrix& = Matrix(), Renderer* = Renderable::defaultRender);
	Model(const char*, const char*, const char*, float = 1.0f, float = 0.0f, Matrix& = Matrix(), Renderer* = Renderable::defaultRender);
	virtual ~Model() = default;

	virtual void prerender() final;
	virtual Renderable::Renderpack* render() final;
	virtual void postrender() final;

	Model& move(float x, float y, float z);
	Model& rotate(float yaw, float pitch, float roll);
	Model& scale(float w, float h, float l);
	Model& resetPosition();

	float getX() const;
	float getY() const;
	float getZ() const;
	float width() const;
	float height() const;
	
protected:
	virtual void setup();
	virtual void draw() = 0;
	virtual void clean();

	void loadTexture(const char*);

	float xPos, yPos, zPos;
	float w, h;
};