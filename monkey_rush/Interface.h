#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Player.h"

/*
Klasa odpowiedzialna za wyœwietlania informacji w grze
*/

class Interface
{
	friend class Player;
public:
	Interface(sf::RenderWindow& _window);

	void draw(sf::RenderWindow* _window);
	void update();

private:
	std::vector<std::unique_ptr<sf::Texture>> textures;
	sf::RectangleShape health_bar;
	sf::RectangleShape health_bar_outline;
	
	sf::Text HP;
	sf::Text score;

	Animation gun_tile;
	Animation freez_tile;
	Animation burn_tile;

	sf::Font font;


};

