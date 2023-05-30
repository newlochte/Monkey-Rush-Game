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

GameControl::GameControl(sf::RenderWindow* window)
{
	this->window = window;
	is_controller_connected = sf::Joystick::isConnected(0);
	is_controller_connected ? std::cout << "controller connected\n" : std::cout << "controller not connected\n";
	
}

bool GameControl::setup()
{	
	sf::Vector2f window_size = static_cast<sf::Vector2f>(window->getSize());
	sf::Vector2f middle = window_size / 2.f;
	player.setPosition(middle);
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
	sf::Vector2f dm = player_movement * frame_time.asSeconds();
	player.move(dm);
}

void GameControl::draw(sf::RenderWindow& _window)
{
	window->clear();
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
