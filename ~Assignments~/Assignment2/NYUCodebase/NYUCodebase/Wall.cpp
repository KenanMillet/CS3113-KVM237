#include "Wall.h"

Wall::Wall(float ypos, float w)
	: TactileEntity::Tactile(w, 0.5), TactileEntity::Model("wall.png", { -3.6f, -0.25f, 3.6f, -0.25f, 3.6f, 0.25f, -3.6f, -0.25f, 3.6f, 0.25f, -3.6f, 0.25f }, { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 })
{
	y = ypos;
}

void Wall::collision(Tactile*, uint8_t)
{
}

void Wall::draw()
{
	reset().move(0, y, 0);
}

void Wall::tick(uint32_t)
{

}