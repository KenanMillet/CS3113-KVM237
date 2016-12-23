#pragma once
#include "Camera.h"
#include "Entity.h"

class TrackingCamera : public Camera, virtual public Entity
{
public:
	TrackingCamera(Matrix = Matrix(), Matrix = Matrix());

	TrackingCamera& track(Entity*);
	TrackingCamera& trackPosition(float);
	TrackingCamera& trackRotation(float);
	TrackingCamera& trackPosition(Entity*, float = 0.0f);
	TrackingCamera& trackRotation(Entity*, float = 0.0f);
	virtual void draw();
	virtual void tick(uint32_t);

protected:
	Entity* target;
	float rotationOffset, positionOffset;
};