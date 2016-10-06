#pragma once
#include "Renderable.h"

class Matrix;

class Model : virtual public Renderable
{
public:
	Model(const char*, std::initializer_list<float>, std::initializer_list<float>, Matrix& = Matrix(), Render* = Renderable::defaultRender);
	Model(const char* = "", std::vector<float>& = std::vector<float>(), std::vector<float>& = std::vector<float>(), Matrix& = Matrix(), Render* = Renderable::defaultRender);

	virtual void prerender() final;
	virtual Renderable::Renderpack* render() final;
	virtual void postrender() final;

	Model& move(float x, float y, float z);
	Model& rotate(float yaw, float pitch, float roll);
	Model& scale(float w, float h, float l);
	Model& reset();

	float getX();
	float getY();
	float getZ();
	
protected:
	virtual void setup();
	virtual void draw() = 0;
	virtual void clean();

	void loadTexture(const char*);

	float x, y, z;
};