#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Player :
    public Entity
{
    float velocity;
    void setTexture();
public:
    Player();

    Player(sf::Texture& entity_texture, sf::Vector2f middle_position);
    
    void move(sf::Vector2f& offset);
    void move(float x, float y);

    
    
};