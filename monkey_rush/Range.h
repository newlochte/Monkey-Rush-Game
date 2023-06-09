#pragma once
#include "Enemy.h"
class Range :
    public Enemy
{
    float distance_to_player = 200;
    std::string path = "img\\Nosacz_animacja.png";
public:
    Range(sf::Vector2f position);

    void moveToPlayer(Player player, sf::Time delta_time);
    int getAtackType();
    bool canAtack(Player player, sf::Time delta_time);
};

