#include "Tank.h"

Tank::Tank(sf::Vector2f position)
	:Enemy(position)
{
	Enemy::setTexture(path);
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(64, 64));
}
