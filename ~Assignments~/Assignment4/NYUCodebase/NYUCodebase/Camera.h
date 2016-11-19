#pragma once
#include "Matrix.h"

class Camera
{
public:
	Camera(Matrix = Matrix(), Matrix = Matrix());
	const Matrix& getViewMatrix() const;
	const Matrix& getProjectionMatrix() const;
//protected:
	Matrix viewMatrix, projectionMatrix;
};