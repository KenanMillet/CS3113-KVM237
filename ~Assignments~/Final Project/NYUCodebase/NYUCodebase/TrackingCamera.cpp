#include "TrackingCamera.h"
#include "Entity.h"
#include "Renderer.h"

TrackingCamera::TrackingCamera(Matrix view, Matrix proj)
	: Camera(view, proj),
	Entity::Model()
{
	defaultRender->remove(this);
}

TrackingCamera& TrackingCamera::track(Entity* target)
{
	this->target = target;
	return *this;
}

TrackingCamera& TrackingCamera::trackPosition(float)
{
	return *this;
}

TrackingCamera& TrackingCamera::trackRotation(float)
{
	return *this;
}

TrackingCamera& TrackingCamera::trackPosition(Entity* target, float)
{
	return *this;
}

TrackingCamera& TrackingCamera::trackRotation(Entity* target, float)
{
	return *this;
}

void TrackingCamera::draw()
{
}

void TrackingCamera::tick(uint32_t)
{

}