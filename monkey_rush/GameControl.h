#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<random>

#include"Player.h"
#include"Enemy.h"
#include"Tank.h"
#include"Basic.h"
#include"Range.h"
#include"Map.h"
#include"Missile.h"
#include"Interface.h"

class GameControl
{
	sf::RenderWindow* window;
	sf::Clock game_timer;
	sf::Time frame_time;
	sf::Clock clock;
	sf::View camera;

	//mapa
	sf::Vector2f map_size = { 700,600 };
	Map map;
	//kontenery na obiekty
	Player player;
	Interface GUI;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Missile>> enemy_missiles;
	std::vector<std::unique_ptr<Missile>> player_missiles;


	//liczniki przeciwników i bonusów
	int enemies_count;

	//dane do sterowania
	bool play_with_controller = false;
	bool is_controller_connected;
	int controller_drift = 5;
	sf::Cursor cursor;

	//funkcjie prywatne, dla bardziej czytlenego kodu

	sf::Vector2f controllerMovement();
	sf::Vector2f keyboardMovement();
	void randomEnemySpawn();
	void printV(sf::Vector2f v);
	void playerAtack();

public:
	//inicjalizacja zmiennych globalnych
	GameControl(sf::RenderWindow* window);

	/*void pause();
	void menu();*/

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

