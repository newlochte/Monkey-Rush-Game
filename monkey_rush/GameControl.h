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
	sf::Clock game_timer;
	sf::Time frame_time;
	sf::Clock clock;
	sf::Vector2f map_size = { 600,600 };
	sf::View camera;

	//kontenery na obiekty
	Player player;
	std::vector<std::unique_ptr<Enemy>> enemies;

	//liczniki przeciwnik�w i bonus�w
	int enemies_count;

	//dane do sterowania
	bool is_controller_connected;
	int controller_drift = 5;
	sf::Vector2f player_movement;

	//funkcjie prywatne, dla bardziej czytlenego kodu

	void controllerMovement();
	void keyboardMovement();
	void randomEnemySpawn();

public:
	//inicjalizacja zmiennych globalnych
	GameControl(sf::RenderWindow* window);

	void pause();
	void menu();

	// inicjalizacja wszystkich zmiennych potrzebnych do ropocz�cia gry import potrzebnych tekstur
	bool setup(); 
	//obs�uga danych wej�ciowych z klaiatury myszki i pada
	void inputs();
	//realizacja wszystkich zmian w grze 
	void actions();
	//rysowanie m�wi samo z siebie
	void draw(sf::RenderWindow& _window);

	static sf::Vector2f randomPosition(sf::Vector2f map_size);
	static int randomInt(int min, int max);
	
};

