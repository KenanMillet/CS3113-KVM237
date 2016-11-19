#include "Camera.h"

Camera::Camera(Matrix view, Matrix proj)
	: viewMatrix(view), projectionMatrix(proj)
{
}

const Matrix& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Matrix& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}
