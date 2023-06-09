#pragma once
#include "Enemy.h"
class Range :
    public Enemy
{
    float distance_to_player;

public:
    Range(sf::Vector2f position);

    void moveToPlayer(Player player, sf::Time delta_time);
    
};

