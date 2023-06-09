#include "Basic.h"

Basic::Basic(sf::Vector2f position)
	:Enemy(position)
{
	Enemy::setTexture(path);
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(64, 64));
}
