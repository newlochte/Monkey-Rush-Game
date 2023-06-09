#pragma once
#include<SFML\Graphics.hpp>
class Map
{
	sf::RectangleShape body;
	void setTexture(sf::Vector2f map_size);
	sf::Texture texture;

	std::string path = "img\\map.png";

public:
	Map(sf::Vector2f map_size);
	void draw(sf::RenderWindow* window);
};

