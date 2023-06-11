#include "Interface.h"
#include <iostream>

Interface::Interface(sf::RenderWindow& _window, Player& p)
{
	binded_player = &p;
	//load textures
	for (int i = 0; i < 5; i++)
	{
		textures.emplace_back(std::make_unique<sf::Texture>());
		textures.back().get()->loadFromFile("img\\" + std::to_string(i) + "_icon.png");
	}
	font.loadFromFile("Fonts\\arial.ttf");
	
	sf::Vector2f max_position = static_cast<sf::Vector2f>(_window.getSize());
	//create health bar
	sf::Vector2f bar_position = { 10,10 };
	int outline_thickness = 5;
	float bar_height = 20;
	maxhealth = p.health;
	heath_bar_width = (float)maxhealth / 4;
	health_bar.setSize(sf::Vector2f(heath_bar_width,bar_height));
	health_bar.setFillColor(sf::Color::Green);
	health_bar.setPosition(bar_position);

	health_bar_outline.setSize(sf::Vector2f(heath_bar_width+outline_thickness*2, bar_height+2*outline_thickness));
	health_bar_outline.setFillColor(sf::Color::Black);
	health_bar_outline.setPosition(bar_position.x - outline_thickness, bar_position.y - outline_thickness);
	
	//score i HP text
	sf::Vector2f text_offset = {2,0};
	HP.setString("HP");
	HP.setFont(font);
	HP.setPosition(bar_position + text_offset);
	HP.setCharacterSize((int)bar_height-4);
	HP.setStyle(sf::Text::Bold);
	HP.setFillColor(sf::Color::Black);

	score.setString("SCORE: 000000");
	score.setFont(font);
	score.setCharacterSize((int)bar_height+2);
	score.setPosition(max_position.x - 208.f, bar_position.y-4);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color(255, 255, 237));

	//tiles
	gun_tile.setSize(sf::Vector2f(192, 84));
	gun_tile.setTexture(textures[p.gun].get());
	gun_tile.setPosition(0, max_position.y - gun_tile.getSize().y);

	freez_tile.setSize(sf::Vector2f(64, 64));
	freez_tile.setTexture(textures[3].get());
	freez_tile.setPosition(gun_tile.getSize().x, max_position.y - freez_tile.getSize().y);

	burn_tile.setSize(sf::Vector2f(64, 64));
	burn_tile.setTexture(textures[4].get());
	burn_tile.setPosition(gun_tile.getSize().x + freez_tile.getSize().x, max_position.y - burn_tile.getSize().y);
}

void Interface::draw(sf::RenderWindow* _window)
{
	_window->draw(health_bar_outline);
	_window->draw(health_bar);

	_window->draw(HP);
	_window->draw(score);
	
	_window->draw(gun_tile);
	if(tile_info & 0b01) _window->draw(freez_tile);
	if(tile_info & 0b10) _window->draw(burn_tile);
}

void Interface::updateScore(int score)
{
	std::string score_string;
	for (int i = 0; i < 6; i++)
	{
		score_string = std::to_string(score % 10) + score_string;
		score /= 10;
	}
	this->score.setString("SCORE: " + score_string);
}

void Interface::update()
{
	health_bar.setSize(sf::Vector2f(
		(float)binded_player->health / (float)maxhealth * heath_bar_width,
		health_bar.getSize().y));
	
	gun_tile.setTexture(textures[binded_player->gun].get());
	tile_info = binded_player->gun_efeckt;
}


