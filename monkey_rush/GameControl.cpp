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
		y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x -= 1;
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

void GameControl::printV(sf::Vector2f v)
{
	std::cout << v.x << " " << v.y << std::endl;
}

void GameControl::playerAtack()
{
	if (player.atackCooldown(frame_time)) {
		sf::Vector2f mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		player_missiles.emplace_back(std::make_unique<Missile>(
			player.getPosition(), 
			mouse_pos,
			(Missile::type)player.getAtack(),
			player.getEfeckt()));
	}	
}

GameControl::GameControl(sf::RenderWindow* window)
	:camera(static_cast<sf::Vector2f>(window->getSize()) / 2.f, static_cast<sf::Vector2f>(window->getSize())),
	map(map_size),
	GUI(*window, player)
{
	//pi�kny celownik
	sf::Image target;
	target.loadFromFile("img\\Target.png");
	sf::Vector2u hotspot = {10,10};
	cursor.loadFromPixels(target.getPixelsPtr(),target.getSize(),hotspot);
	window->setMouseCursor(cursor);

	//zmienne klasy
	this->window = window;
	enemies_count = 0;

	//controller check, czasem sprawia �e d�ugo si� w��cza gra
	is_controller_connected = sf::Joystick::isConnected(0);
	is_controller_connected ? std::cout << "controller connected\n" : std::cout << "controller not connected\n";
}

bool GameControl::setup()
{	
	sf::Vector2f window_size = static_cast<sf::Vector2f>(window->getSize());
	sf::Vector2f middle = window_size / 2.f;
	player.setPosition(middle);
	enemies_count = 15;
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
		if (event.type == sf::Event::KeyPressed) {
			//zmiany stanu gry pausa etc.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) 
			{
				player.gunChange();
				GUI.update();
			}
		}

	}
	
	//strzelanie
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 7)) playerAtack();

	sf::Vector2f movement_vector;
	if (is_controller_connected && play_with_controller) {
		movement_vector = controllerMovement();
	}
	else {
		//movement with keyboard
		movement_vector = keyboardMovement();
	}
	//kolizja z kra�cem mapy (do poprawy)
	if (player.getPosition().x + movement_vector.x > map_size.x) {
		movement_vector.x = 0;
	}
	if (player.getPosition().x + movement_vector.x < 0 ) {
		movement_vector.x = 0;
	}
	if (player.getPosition().y + movement_vector.y > map_size.y) {
		movement_vector.y = 0;
	}
	if (player.getPosition().y + movement_vector.y < 0) {
		movement_vector.y = 0;
	}

	player.playerMovement(movement_vector,frame_time);
}

void GameControl::actions()
{
	while (enemies.size() < enemies_count) {
		//spawn przeciwnik�w
		randomEnemySpawn();
	}
	//enemies movement
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].get()->moveToPlayer(player, frame_time);
		enemies[i].get()->doDoT(frame_time);
		//atak przeciwnik�w
		if (enemies[i].get()->canAtack(player, frame_time)) {
			//std::cout << "atakc sent\n";
			enemy_missiles.emplace_back(
				std::make_unique<Missile>(
					enemies[i].get()->RectangleShape::getPosition(), 
					player.getPosition(), 
					(Missile::type)enemies[i].get()->getAtackType()
				)
			);
		}
		for (int j = 0; j < i; j++) {
			if (enemies[i].get()->isColliding(*enemies[j].get())) {
				enemies[i].get()->bounceOfEnemy(enemies[j].get(),frame_time);
			}
		}
	}
	//ataki przeciwnik�w
	for (auto it = enemy_missiles.begin(); it != enemy_missiles.end();) {
		(*it)->update(frame_time);
		if ((*it)->expired() ) { 
			it = enemy_missiles.erase(it);
		}
		else if ((*it)->isColliding(player)) {
			(*it)->hit();
			player.doDamage((*it)->getDamageInfo().first);
			GUI.update();
			it = enemy_missiles.erase(it);
		}
		else {
			it++;
		}
	}
	//ataki gracza (syf totalny przyda�by si� redesign metod to obs�ugi tego)
	for (auto it = player_missiles.begin(); it != player_missiles.end();) {
		(*it)->update(frame_time);
		bool to_delete = false;
		float radius = (*it)->getDamageRadius();
		if ((*it)->expired()) {
			to_delete = true;
			//strza�y z rakiety
			if (radius >= 1.1) {
				for (auto enemy = enemies.begin(); enemy != enemies.end();) {
					if ( (*enemy)->distance( (*it)->getPosition() ) <= radius ) {
						if ((*enemy)->doDamage((*it)->getDamageInfo())) {
							enemy = enemies.erase((enemy));
							points++;
							GUI.updateScore(points);
						}
					}
					else { enemy++; }
				}
			}
		}
		if (radius < 1.1) {
			for (auto enemy = enemies.begin(); enemy != enemies.end();) {
				if ((*it)->isColliding(*(*enemy)) && 
					(*enemy)->doDamage((*it)->getDamageInfo())) {
						enemy = enemies.erase(enemy);
						points++;
						GUI.updateScore(points);
						to_delete = true;
				}
				else enemy++;
			}
		}
		if(!to_delete) {
			it++;
		}
		else {
			it = player_missiles.erase(it);
		}
	}
	player.update_timers(frame_time);
}

void GameControl::draw(sf::RenderWindow& _window)
{
	camera.setCenter(player.getPosition());
	_window.setView(camera);
	_window.clear();
	map.draw(&_window);
	for (const auto& enemy : enemies) {
		enemy->animate(frame_time);
		enemy->draw(&_window);
	}
	player.animate(frame_time);
	player.draw(&_window);
	//debug
	//std::cout << enemy_missiles.size() << std::endl;
	for (const auto& missile : enemy_missiles) {
		missile->animate(frame_time);
		missile->draw(&_window);
	}
	for (const auto& missile : player_missiles) {
		missile->animate(frame_time);
		missile->draw(&_window);
	}
	_window.setView(_window.getDefaultView());
	//interface
	GUI.draw(&_window);


	_window.setView(camera);
	_window.display();
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
