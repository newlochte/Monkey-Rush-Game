#include "GameControl.h"
#include <iostream>

sf::Vector2f GameControl::controllerMovement()
{
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	if (abs(x) > controller_drift) {
		x /= 100;
	}
	else {
		x = 0;
	}
	if (abs(y) > controller_drift) {
		y /= 100;
	}
	else {
		y = 0;
	}
	return sf::Vector2f(x, y);
}

sf::Vector2f GameControl::keyboardMovement()
{
	float x = 0;
	float y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		x -= 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		x += 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		y -= 1;
	}
	return sf::Vector2f(x, y);
}

void GameControl::randomEnemySpawn()
{
	int type = randomInt(0, 2);
	switch (type)
	{
	case 0:
		enemies.emplace_back(std::make_unique<Tank>(randomPosition(map_size)));
		break;
	case 1:
		enemies.emplace_back(std::make_unique<Basic>(randomPosition(map_size)));
		break;
	case 2:
		enemies.emplace_back(std::make_unique<Range>(randomPosition(map_size)));
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
	sf::Vector2f movement_vector;
	if (is_controller_connected && play_with_controller) {
		movement_vector = controllerMovement();
	}
	else {
		//movement with keyboard
		movement_vector = keyboardMovement();
	}
	player.playerMovement(movement_vector,frame_time);
}

void GameControl::actions()
{
	while (enemies.size() <= enemies_count) {
		randomEnemySpawn();
	}
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
	camera.setCenter(player.getPosition());
	_window.setView(camera);
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
