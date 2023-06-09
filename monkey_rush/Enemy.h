#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy :
    public Entity
{
    int DoT = 0;
    float DoT_timer = 0;
protected:
    int health = 100;
    float velocity = 100;
    float atack_cooldown = 2.f;
    float atack_timer;

    void setTexture(std::string path);
    float vectorLenght(sf::Vector2f v);
public:
    Enemy(sf::Vector2f position);
    Enemy(sf::Vector2f position, sf::Vector2f size);

    virtual void moveToPlayer(Player player, sf::Time delta_time);
    virtual int getAtackType();
    virtual bool canAtack(Player player, sf::Time time_elapsed);

    void giveDebuff(int debuf);
    void doDoT(sf::Time delta_time);
    void move(sf::Vector2f& offset);
    void move(float x, float y);
    void bounceOfEnemy(Enemy* other, sf::Time delta_time);
    bool doDamage(std::pair<int, int> damage);
};

