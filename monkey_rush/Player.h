#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Player :
    public Entity
{
    float velocity = 300;
    void setTexture();
    std::string path = "img\\Explorer_animation.png";

    int health = 1000;
public:
    Player();
    
    void move(sf::Vector2f offset);
    void move(float x, float y);

    void playerMovement(sf::Vector2f movement_vector, sf::Time delta_time);
    void doDamage(int damage_done);
    
    
};