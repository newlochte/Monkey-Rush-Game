#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Entity: public sf::RectangleShape
{
	
protected:
	Animation animation;


public:
	Entity();

	Entity(sf::Vector2f size);

	void draw();

	void move(sf::Vector2f &offset);
	bool isColliding(sf::RectangleShape check_for_collision);
	//virtual int atack();

};

