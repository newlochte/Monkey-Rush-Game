#include "Tank.h"
#include "GameControl.h"


Tank::Tank(sf::Vector2f position)
	:Enemy(position)
{
	Enemy::setTexture(path);
}
