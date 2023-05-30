#include "Player.h"

void Player::setTexture()
{
	texture.loadFromFile("img\\sprite_0.png");
	animation.setTexture(&texture);
}

Player::Player()
	:Entity(sf::Vector2f(64, 64))
{
	setTexture();
	velocity = 300;
}

Player::Player(sf::Texture& entity_texture, sf::Vector2f middle_position)
	:Entity(entity_texture,sf::Vector2f(64,64))
{
	velocity = 300;
	setPosition(middle_position);
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


