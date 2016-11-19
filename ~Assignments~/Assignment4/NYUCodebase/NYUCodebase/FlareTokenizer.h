#pragma once
#include "Tokenizer.h"
#include <string>
#include <initializer_list>
#include <vector>
#include <set>

class FlareTokenizer : public Tokenizer
{
public:
	struct EntityData;
	FlareTokenizer(std::initializer_list<std::string> = {});

	virtual const FlareTokenizer* parse(const std::string&);

	const std::vector<std::vector<unsigned char>>& getLevelData() const;
	const std::vector<EntityData>& getEntityData() const;
	const int getTileWidth() const;
	const int getTileHeight() const;
private:
	bool readHeader(std::istream&);
	bool readLayerData(std::istream&);
	bool readEntityData(std::istream&);

	int mapWidth, mapHeight, tileWidth, tileHeight;
	std::vector<std::vector<unsigned char>> levelData;
	std::vector<EntityData> entityData;

	std::set<std::string> objectLayers;
};

struct FlareTokenizer::EntityData
{
	EntityData(const std::string&, float, float, float, std::initializer_list<std::string> = {});
	std::string type;
	std::vector<std::string> properties;
	float x, y, z;
};