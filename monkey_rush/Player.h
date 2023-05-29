#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Player :
    public Entity
{
    std::pair<float, float> velocity;

public:
    Player(sf::Texture& entity_texture, sf::Vector2f middle_position);
    
    

    
    
};

