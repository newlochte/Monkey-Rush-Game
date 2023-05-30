#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy :
    public Entity
{
    float velocity = 100;

protected:
    void setTexture(std::string path);

public:
    Enemy(sf::Vector2f position);

    void moveToPlayer(Player player, sf::Time delta_time);
    //void giveEffect();
    //virtual void atack();
    void move(sf::Vector2f& offset);
    void move(float x, float y);
};

