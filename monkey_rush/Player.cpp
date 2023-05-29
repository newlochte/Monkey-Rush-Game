#include "Player.h"

Player::Player(sf::Texture& entity_texture, sf::Vector2f middle_position)
	:Entity(entity_texture,sf::Vector2f(64,64))
{
	setPosition(middle_position - sf::Vector2f(64, 64)/2.f);
}


