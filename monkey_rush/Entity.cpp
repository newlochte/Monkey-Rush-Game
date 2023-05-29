#include "Entity.h"

void Entity::move(sf::Vector2f& offset)
{
	animation.move(offset);
	move(offset);
}

bool Entity::isColliding(sf::RectangleShape check_for_collision)
{
	return getGlobalBounds().intersects(check_for_collision.getGlobalBounds());
}
