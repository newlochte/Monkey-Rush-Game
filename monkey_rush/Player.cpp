#include "Player.h"

Player::Player()
	:Entity(sf::Vector2f(64, 64))
{
	velocity = 300;
}

Player::Player(sf::Texture& entity_texture, sf::Vector2f middle_position)
	:Entity(entity_texture,sf::Vector2f(64,64))
{
	setPosition(middle_position - sf::Vector2f(64, 64)/2.f);
}

void Player::move(sf::Vector2f& offset)
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


