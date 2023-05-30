#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<random>

#include"Player.h"
#include"Enemy.h"
#include"Tank.h"

class GameControl
{
	sf::RenderWindow* window;
	sf::Time game_timer;
	sf::Time frame_time;
	sf::Clock clock;

	Player player;

	std::vector<std::unique_ptr<Enemy>> enemies;

	bool is_controller_connected;
	int controller_drift = 5;
	sf::Vector2f player_movement;

	//funkcjie prywatne, dla bardziej czytlenego kodu

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

	static sf::Vector2f randomPosition(sf::Vector2f map_size);
	static int randomInt(int min, int max);
	
};

