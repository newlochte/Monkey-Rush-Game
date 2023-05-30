#include "Range.h"

Range::Range(sf::Vector2f position)
	:Enemy(position)
{
	Enemy::setTexture("img\\Nosacz_animacja.png");
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(64, 64));
}
