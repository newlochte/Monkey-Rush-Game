#include "GameControl.h"
#include <iostream>

void GameControl::controllerMovement()
{
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	player_movement = { 0,0 };

	if (abs(x) > controller_drift) {
		player_movement = { x / 100,0 };
	}
	if (abs(y) > controller_drift) {
		player_movement += { 0, y / 100 };
	}
}

void GameControl::keyboardMovement()
{
	player_movement = { 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player_movement += { 0,-1 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player_movement += { 0,1 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player_movement += { 1,0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player_movement += { -1,0 };
	}
}

void GameControl::randomEnemySpawn()
{
	int type = 0;//randomInt(0, 2);
	switch (type)
	{
	case 0:
		enemies.emplace_back(std::make_unique<Tank>(randomPosition(map_size)));
		break;
	case 1:
		//enemies.emplace_back(std::make_unique<Basic>(randomPosition(map_size)));
		break;
	case 2:
		//enemies.emplace_back(std::make_unique<Range>(randomPosition(map_size)));
		break;
	default:
		std::cout << "how did that happed?!\n";
		break;
	}
}

GameControl::GameControl(sf::RenderWindow* window)
	:camera(static_cast<sf::Vector2f>(window->getSize())/2.f, static_cast<sf::Vector2f>(window->getSize()))
{
	this->window = window;
	is_controller_connected = sf::Joystick::isConnected(0);
	is_controller_connected ? std::cout << "controller connected\n" : std::cout << "controller not connected\n";
	enemies_count = 0;
	
}

bool GameControl::setup()
{	
	sf::Vector2f window_size = static_cast<sf::Vector2f>(window->getSize());
	sf::Vector2f middle = window_size / 2.f;
	player.setPosition(middle);
	enemies_count = 10;
	return false;
}

void GameControl::inputs()
{
	frame_time = clock.restart();
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		//zmiany stanu gry pausa etc.
	}

	if (is_controller_connected) {
		controllerMovement();
	}
	else {
		//movement with keyboard
		keyboardMovement();
	}
}

void GameControl::actions()
{
	while (enemies.size() <= enemies_count) {
		randomEnemySpawn();
	}
	sf::Vector2f dm = player_movement * frame_time.asSeconds();
	player.move(dm);
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].get()->moveToPlayer(player,frame_time);
		for (int j = 0; j < i; j++) {
			if (enemies[i].get()->isColliding(*enemies[j].get())) {
				enemies[i].get()->bounceOfEnemy(enemies[j].get(),frame_time);
			}
		}
	}
}

void GameControl::draw(sf::RenderWindow& _window)
{

	window->clear();
	for (const auto& s : enemies) {
		s->animate(frame_time);
		s->draw(&_window);
	}
	player.draw(&_window);
	window->display();
}

sf::Vector2f GameControl::randomPosition(sf::Vector2f map_size)
{
	float x = (float)randomInt(0, (int)map_size.x);
	float y = (float)randomInt(0, (int)map_size.y);
	
	return sf::Vector2f(x,y);
}

int GameControl::randomInt(int min, int max)
{
	static std::default_random_engine e{ static_cast<long unsigned int>(time(0)) };
	std::uniform_int_distribution<int> d{ min, max };
	return d(e);
}
