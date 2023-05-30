#include "Entity.h"
#include<iostream>


const sf::Vector2f Entity::unclipVector(Entity other)
{
	sf::Vector2f change;
	change = other.getPosition() - getPosition();
	return sf::Vector2f(-change.x,-change.y);
}

Entity::Entity()
{
}

Entity::Entity(sf::Vector2f size)
	:animation(size), RectangleShape(size)
{

}

Entity::Entity(sf::Texture& texture, sf::Vector2f size)
	:animation(size, texture), RectangleShape(size)
{

}

void Entity::move(sf::Vector2f& offset)
{
	animation.move(offset);
	RectangleShape::move(offset);
}

void Entity::move(float x, float y)
{
	animation.move(x, y);
	RectangleShape::move(x, y);
}

bool Entity::isColliding(sf::RectangleShape check_for_collision)
{
	return getGlobalBounds().intersects(check_for_collision.getGlobalBounds());
}

void Entity::draw(sf::RenderTarget* target)
{
	target->draw(animation);
}

void Entity::setPosition(const sf::Vector2f& position)
{
	RectangleShape::setPosition(position - (getSize() / 2.f));
	animation.setPosition(position - (getSize() / 2.f));
}

void Entity::setPosition(float x, float y)
{
	x -= getSize().x / 2.f;
	y -= getSize().y / 2.f;

	animation.setPosition(x, y);
	RectangleShape::setPosition(x, y);
}

const sf::Vector2f Entity::getPosition()
{
	return sf::Vector2f(sf::RectangleShape::getPosition()-(getSize()/2.f));
}

