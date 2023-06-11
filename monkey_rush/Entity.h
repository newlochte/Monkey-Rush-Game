#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include<iostream>

class Entity: public sf::RectangleShape
{
	
protected:
	Animation animation;
	sf::Texture texture;

	const sf::Vector2f unclipVector(Entity other);

public:
	Entity();

	Entity(sf::Vector2f hitbox_size, sf::Vector2f animation_size);
	Entity(sf::Vector2f size);

	//void draw();

	bool isColliding(sf::RectangleShape check_for_collision);
	void draw(sf::RenderTarget* target);
	//virtual int atack();

	//przeci¹¿enia metod z klasy RectangleShape, bo animacjê te¿ trzeba ruszaæ kiedy postaæ
	void move(sf::Vector2f offset);
	void move(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);
	const sf::Vector2f getPosition();

	void animate(sf::Time time);
	float distance(sf::Vector2f distance_to);
};

