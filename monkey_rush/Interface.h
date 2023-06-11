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
public:
	Interface(sf::RenderWindow& _window, Player& p);

	void draw(sf::RenderWindow* _window);
	void updateScore(int score);
	void update();

private:
	std::vector<std::unique_ptr<sf::Texture>> textures;
	sf::RectangleShape health_bar;
	sf::RectangleShape health_bar_outline;
	int maxhealth;
	float heath_bar_width;
	
	sf::Text HP;
	sf::Text score;

	int tile_info = 0b0;
	Animation gun_tile;
	Animation freez_tile;
	Animation burn_tile;

	sf::Font font;

	Player* binded_player;
};

