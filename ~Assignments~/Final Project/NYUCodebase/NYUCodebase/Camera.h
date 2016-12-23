#pragma once
#include "Matrix.h"
#include "ViewHandler.h"
#include <utility>

class Camera
{
public:
	Camera(Matrix = Matrix(), Matrix = Matrix(), ViewHandler* = defaultViewHandler);
	~Camera();

public:
	virtual std::pair<const Matrix&, const Matrix&> info() const;
//protected:
	Matrix viewMatrix, projectionMatrix;
protected:
	static ViewHandler* defaultViewHandler;
	ViewHandler* viewHandler;
};