#include "Text.h"

Text::Text(const std::string& text, const char* fontTexture, float size, float spacing, Alignment align)
	: Entity::Model(fontTexture)
{
	size *= 0.5f;
	spacing *= -0.25f;

	float texture_size = 1.0f / 16.0f;
	vertexCoords() = {};
	textureCoords() = {};

	float offset;

	if(align == LEFT) offset = 0;
	if(align == RIGHT) offset = -1.0f * float((size + spacing) * (text.size() - 1)/* + (size * text.size())*/);
	if(align == CENTERED) offset = -0.5f * float((size + spacing) * (text.size() - 1)/* + (size * text.size())*/);

	for(size_t i = 0; i < text.size(); ++i)
	{
		float texture_x = float(int(text[i]) % 16) / 16.0f;
		float texture_y = float(int(text[i]) / 16) / 16.0f;
		vertexCoords().insert(vertexCoords().end(), {
			((size + spacing) * i) + (-0.5f * size) + offset,  0.5f * size,
			((size + spacing) * i) + (-0.5f * size) + offset, -0.5f * size,
			((size + spacing) * i) + ( 0.5f * size) + offset,  0.5f * size,
			((size + spacing) * i) + ( 0.5f * size) + offset, -0.5f * size,
			((size + spacing) * i) + ( 0.5f * size) + offset,  0.5f * size,
			((size + spacing) * i) + (-0.5f * size) + offset, -0.5f * size
		});
		textureCoords().insert(textureCoords().end(), {
			texture_x, texture_y,
			texture_x, texture_y + texture_size,
			texture_x + texture_size, texture_y,
			texture_x + texture_size, texture_y + texture_size,
			texture_x + texture_size, texture_y,
			texture_x, texture_y + texture_size
		});
	}
}

void Text::setup()
{
}

void Text::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Text::tick(uint32_t)
{
}
