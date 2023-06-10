#pragma once
#include "Enemy.h"
class Tank :
    public Enemy
{
    std::string path = "img\\Tank_animation.png";
public:
    Tank(sf::Vector2f position);
};

