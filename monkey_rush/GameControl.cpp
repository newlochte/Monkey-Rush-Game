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
	textures.emplace_back(sf::Texture());
	textures[0].loadFromFile("img\\sprite_0.png");
	/*for (int i = 0; i < texture_path.size(); i++) {
		textures.emplace_back(sf::Texture());
		textures.back().loadFromFile(texture_path[i]);
	}*/
	sf::Vector2f window_size = static_cast<sf::Vector2f>(window->getSize());
	sf::Vector2f middle = window_size / 2.f;
	player.setPosition(middle);
	player.setTexture(&textures[0]);
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
