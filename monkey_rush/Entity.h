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

	Entity(sf::Texture& texture, sf::Vector2f size);

	void draw();

	bool isColliding(sf::RectangleShape check_for_collision);
	void draw(sf::RenderTarget* target);
	//virtual int atack();

	//przeci¹¿enia metod z klasy RectangleShape, bo animacjê te¿ trzeba ruszaæ kiedy postaæ
	void move(sf::Vector2f &offset);
	void move(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);
};

