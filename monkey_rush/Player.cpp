#include "Player.h"

void Player::setTexture()
{
	texture.loadFromFile(path);
	animation.setTexture(&texture);
	
}

Player::Player()
	:Entity(sf::Vector2f(32, 52), sf::Vector2f(64, 64))
{
	texture.loadFromFile(path);
	animation.setTexture(&texture);
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(64, 64));
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

void Player::doDamage(int damage_done)
{
	health -= damage_done;
	std::cout << health <<"\n";
}

bool Player::atackCooldown(sf::Time delta_time)
{
	if (atack_timer > 0.0) atack_timer -= delta_time.asSeconds();
	if (atack_timer <= 0.0) return true;
	return false;
}

int Player::getAtack()
{
	atack_timer = atack_cooldown;
	return weapon;
}


