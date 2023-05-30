#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"Player.h"

class GameControl
{
	sf::RenderWindow* window;
	sf::Time game_timer;
	sf::Time frame_time;
	sf::Clock clock;

	Player player;

	std::vector<sf::Texture> textures;

	bool is_controller_connected;
	int controller_drift = 5;
	sf::Vector2f player_movement;

	/*enum entity_types {
		player, basic, tank, range
	};
	std::map<int, std::string> texture_path = {
		{0, "player.png"},
		{1, "monke.png"},
		{2, "tank.png"},
		{3, "nosacz.png"}
	};*/

	void controllerMovement();
	void keyboardMovement();

public:
	//inicjalizacja zmiennych globalnych
	GameControl(sf::RenderWindow* window);

	void pause();
	void menu();

	// inicjalizacja wszystkich zmiennych potrzebnych do ropoczêcia gry import potrzebnych tekstur
	bool setup(); 
	//obs³uga danych wejœciowych z klaiatury myszki i pada
	void inputs();
	//realizacja wszystkich zmian w grze 
	void actions();
	//rysowanie mówi samo z siebie
	void draw(sf::RenderWindow& _window);
};

