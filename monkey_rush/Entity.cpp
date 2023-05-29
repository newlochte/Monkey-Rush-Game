#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f size)
	:animation(size, texture)
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

void Entity::draw(sf::RenderTarget &target)
{
	target.draw(animation);
	target.draw(*this);
}

void Entity::setPosition(const sf::Vector2f& position)
{
	RectangleShape::setPosition(position);
	animation.setPosition(position);
}

void Entity::setPosition(float x, float y)
{
	animation.setPosition(x, y);
	RectangleShape::setPosition(x, y);
}

