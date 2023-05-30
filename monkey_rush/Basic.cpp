#include "Basic.h"

Basic::Basic(sf::Vector2f position)
	:Enemy(position)
{
	Enemy::setTexture("img\\Monke.png");
}
