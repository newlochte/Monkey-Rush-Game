#include "Map.h"

void Map::setTexture(sf::Vector2f map_size)
{
	texture.loadFromFile(path);
	texture.setRepeated(true);
	body.setTexture(&texture);
	body.setTextureRect({ 0,0,(int)map_size.x,(int)map_size.y });
}

Map::Map(sf::Vector2f map_size)
	:body(map_size)
{
	setTexture(map_size);
}

void Map::draw(sf::RenderWindow* window)
{
	window->draw(body);
}
