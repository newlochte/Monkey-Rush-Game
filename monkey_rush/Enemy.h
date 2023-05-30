#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy :
    public Entity
{

protected:
    virtual void setTexture(std::string path);

public:
    Enemy(sf::Vector2f position);

    void moveToPlayer(Player player);
    //void giveEffect();
    //virtual void atack();

};

