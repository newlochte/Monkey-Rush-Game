#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Player :
    public Entity
{
    float velocity;
    void setTexture();
    std::string path = "img\\Explorer_animation.png";
public:
    Player();

    Player(sf::Texture& entity_texture, sf::Vector2f middle_position);
    
    void move(sf::Vector2f offset);
    void move(float x, float y);

    void playerMovement(sf::Vector2f movement_vector, sf::Time delta_time);

    
    
};