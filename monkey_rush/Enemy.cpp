#include "Enemy.h"

void Enemy::setTexture(std::string path = "default.png")
{
	texture.loadFromFile(path);
	animation.setTexture(&texture);
}

Enemy::Enemy(sf::Vector2f position)
	:Entity(sf::Vector2f(64,64))
{
	setPosition(position);
	setTexture();
}

void Enemy::moveToPlayer(Player player)
{
	sf::Vector2f move_vector;
	if (isColliding(player)) {
		move_vector = unclipVector(player);
	}
	else {
		move_vector = player.getPosition() - getPosition();
	}

}
