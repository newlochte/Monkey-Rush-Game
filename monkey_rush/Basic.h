#pragma once
#include "Enemy.h"
class Basic :
    public Enemy
{
    std::string path = "img\\Monke_animation.png";

public:
    Basic(sf::Vector2f position);
};

