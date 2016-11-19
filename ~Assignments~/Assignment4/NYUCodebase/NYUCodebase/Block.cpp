#include "Block.h"
#include "Texture.h"

Block::Block()
	:	TactileEntity::Model(16, getUniformSpriteSheet("sheet.png", 70)),
		TactileEntity::Tactile(width(), height())
{
}

void Block::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Block::tick(uint32_t)
{
}

void Block::collisionX(Tactile *, uint8_t)
{
}

void Block::collisionY(Tactile *, uint8_t)
{
}

void Block::collisionZ(Tactile *, uint8_t)
{
}
