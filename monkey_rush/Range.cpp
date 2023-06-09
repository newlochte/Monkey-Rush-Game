#include "Range.h"

Range::Range(sf::Vector2f position)
	:Enemy(position)
{
	Enemy::setTexture(path);
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(64, 64));
	distance_to_player = 400.f;
}

void Range::moveToPlayer(Player player, sf::Time delta_time)
{
	sf::Vector2f move_vector;
	if (isColliding(player)) {
		move_vector = unclipVector(player);
	}
	else {
		move_vector = player.getPosition() - getPosition();
	}
	if (vectorLenght(move_vector) > distance_to_player) {
		move_vector /= sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
		move_vector *= delta_time.asSeconds();
	}
	else move_vector = { 0,0 };
	move(move_vector);
}
