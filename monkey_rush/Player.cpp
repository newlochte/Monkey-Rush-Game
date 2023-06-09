#include "Player.h"

void Player::setTexture()
{
	texture.loadFromFile(path);
	animation.setTexture(&texture);
	
}

Player::Player()
	:Entity(sf::Vector2f(64, 64))
{
	setTexture();
	velocity = 300;
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(64, 64));
}

Player::Player(sf::Texture& entity_texture, sf::Vector2f middle_position)
	:Entity(entity_texture,sf::Vector2f(64,64))
{
	velocity = 300;
	setPosition(middle_position);
}

void Player::move(sf::Vector2f offset)
{
	offset *= velocity;
	Entity::move(offset);
}

void Player::move(float x, float y)
{
	x *= velocity;
	y *= velocity;

	Entity::move(x, y);
}

void Player::playerMovement(sf::Vector2f movement_vector, sf::Time delta_time)
{
	if (movement_vector.x == 0 && movement_vector.y == 0) {
		animation.animation_type = Animation::idle;
	}
	else if(movement_vector.x > 0 || movement_vector.y >0) {
		animation.animation_type = Animation::move_right;
	}
	else if (movement_vector.x < 0 || movement_vector.y < 0) {
		animation.animation_type = Animation::move_left;
	}
	move(movement_vector * delta_time.asSeconds());
}


