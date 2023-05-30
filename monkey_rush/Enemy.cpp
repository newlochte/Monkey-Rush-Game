#include "Enemy.h"

void Enemy::setTexture(std::string path = "img\\default.png")
{
	texture.loadFromFile(path);
	animation.setTexture(&texture);
}

Enemy::Enemy(sf::Vector2f position)
	:Entity(sf::Vector2f(64,64))
{
	velocity = 100;
	setPosition(position);
	setTexture();
}

void Enemy::moveToPlayer(Player player, sf::Time delta_time)
{
	sf::Vector2f move_vector;
	if (isColliding(player)) {
		move_vector = unclipVector(player);
	}
	else {
		move_vector = player.getPosition() - getPosition();
	}
	move_vector /= sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
	move_vector *= delta_time.asSeconds();
	move(move_vector);
}

void Enemy::move(sf::Vector2f& offset)
{
	offset *= velocity;
	Entity::move(offset);
}

void Enemy::move(float x, float y)
{
	x *= velocity;
	y *= velocity;

	Entity::move(x, y);
}

void Enemy::bounceOfEnemy(Enemy* other, sf::Time delta_time)
{
	sf::Vector2f move_vector;
	move_vector = unclipVector(*other);
	move_vector /= sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
	move_vector *= delta_time.asSeconds();
	move(move_vector);
}
