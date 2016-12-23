#include "Camera.h"

Camera::Camera(Matrix view, Matrix proj, ViewHandler* vh)
	: viewMatrix(view), projectionMatrix(proj), viewHandler(vh)
{
}

Camera::~Camera()
{
	if(viewHandler->isViewActive(this)) viewHandler->revertView();
	else viewHandler->removeView(this);
}

std::pair<const Matrix&, const Matrix&> Camera::info() const
{
	return std::pair<const Matrix&, const Matrix&>(viewMatrix, projectionMatrix);
}

ViewHandler* Camera::defaultViewHandler = &::handleViews;