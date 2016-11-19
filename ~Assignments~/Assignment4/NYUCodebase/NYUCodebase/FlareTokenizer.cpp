#include "FlareTokenizer.h"
#include "logger.h"

using namespace std;

FlareTokenizer::FlareTokenizer(initializer_list<string> layers)
	: objectLayers(layers)
{
}

const FlareTokenizer* FlareTokenizer::parse(const string& filename)
{
	ifstream infile(filename);
	string line;
	if(!infile) return nullptr;
	while(getline(infile, line))
	{
		if(line == "[header]")
		{
			if(!readHeader(infile))
			{
				return nullptr;
			}
		}
		else if(line == "[layer]")
		{
			readLayerData(infile);
		}
		else if(objectLayers.find(line) != objectLayers.end())
		{
			readEntityData(infile);
		}
	}
	return this;
}

const std::vector<std::vector<unsigned char>>& FlareTokenizer::getLevelData() const
{
	return levelData;
}

const std::vector<FlareTokenizer::EntityData>& FlareTokenizer::getEntityData() const
{
	return entityData;
}

const int FlareTokenizer::getTileWidth() const
{
	return tileWidth;
}

const int FlareTokenizer::getTileHeight() const
{
	return tileHeight;
}

bool FlareTokenizer::readHeader(istream& stream)
{
	string line;
	mapWidth = -1;
	mapHeight = -1;
	while(getline(stream, line))
	{
		if(line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if(key == "width")
		{
			mapWidth = stoi(value);
		}
		else if(key == "height")
		{
			mapHeight = stoi(value);
		}
		else if(key == "tilewidth")
		{
			tileWidth = stoi(value);
		}
		else if(key == "tileheight")
		{
			tileHeight = stoi(value);
		}
	}
	if(mapWidth == -1 || mapHeight == -1)
	{
		return false;
	}
	else
	{ // allocate our map data
		levelData.resize(mapHeight);
		for(int i = 0; i < mapHeight; ++i)
		{
			levelData[i].resize(mapWidth);
		}
		return true;
	}
}

bool FlareTokenizer::readLayerData(istream& stream)
{
	string line;
	while(getline(stream, line))
	{
		if(line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if(key == "data")
		{
			for(int y = 0; y < mapHeight; y++)
			{
				getline(stream, line);
				istringstream lineStream(line);
				string tile;
				for(int x = 0; x < mapWidth; x++)
				{
					getline(lineStream, tile, ',');
					unsigned char val = unsigned char(stoi(tile));
					if(val > 0)
					{
						// be careful, the tiles in this format are indexed from 1 not 0
						levelData[y][x] = val - 1;
					}
					else
					{
						levelData[y][x] = 0;
					}
				}
			}
		}
	}
	return true;
}

bool FlareTokenizer::readEntityData(istream& stream)
{
	string line;
	string type;
	while(getline(stream, line))
	{
		if(line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if(key == "type")
		{
			type = value;
		}
		else if(key == "location")
		{
			istringstream lineStream(value);
			string xPosition, yPosition, xdisp, ydisp;
			getline(lineStream, xPosition, ',');
			getline(lineStream, yPosition, ',');
			getline(lineStream, xdisp, ',');
			getline(lineStream, ydisp, ',');

			float placeX = stof(xPosition) - stof(xdisp);
			float placeY = stof(yPosition) - stof(ydisp);
			entityData.emplace_back(type, placeX, placeY, 0);
		}
	}
	return true;
}

FlareTokenizer::EntityData::EntityData(const std::string& type, float x, float y, float z, std::initializer_list<std::string> props)
	: type(type), x(x), y(y), z(z), properties(props)
{
}
