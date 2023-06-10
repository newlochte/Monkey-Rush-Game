#include "Basic.h"

Basic::Basic(sf::Vector2f position)
	:Enemy(position,sf::Vector2f(58,38))
{
	Enemy::setTexture(path);
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(58, 38));
}
