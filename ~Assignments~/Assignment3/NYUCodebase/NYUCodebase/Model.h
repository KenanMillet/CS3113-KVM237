#pragma once
#include "Renderable.h"

class SpriteSheet;

class Matrix;

class Model : virtual public Renderable
{
public:
	Model(const char* = "", Matrix& = Matrix(), Render* = Renderable::defaultRender);
	Model(const char*, std::initializer_list<float>, float, float, std::initializer_list<float>, Matrix& = Matrix(), Render* = Renderable::defaultRender);
	Model(const char*, SpriteSheet*, float = 1.0f, float = 0.0f, Matrix& = Matrix(), Render* = Renderable::defaultRender);
	Model(const char*, const char*, const char*, float = 1.0f, float = 0.0f, Matrix& = Matrix(), Render* = Renderable::defaultRender);
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