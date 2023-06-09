#pragma once
#include "Entity.h"
#include<iostream>

struct Missile_info
{
    int damage;
    float radius;
    float time;
    float velocity;
    sf::Vector2f hit_box;
    std::string path;
};

static Missile_info missile_info[5] = {
        {1,1,5,10000,{10.f,10.f},"mini.png"},
        {50,1,5,1000,{10.f,10.f},"mini.png"},
        {200,1,5,150,{10.f,6.f},"bazzooka.png"},
        {10,1,1.5,250,{10.f,10.f},"banana.png"},
        {20,1,0.1,10,{1.f,1.f},"default.png"}
};

class Missile :
    public Entity
{
public:
    enum type {
        mini, ak, bomb, banana, mele
    };

    Missile(sf::Vector2f position, sf::Vector2f destination, type amo);

    void update(sf::Time time_elasped);
    void hit();

    bool expired();

    std::pair<int,float> getDamageInfo();

private:
    float life_time;
    type amo_type;
    sf::Vector2f destination_vector;
    float velocity;
    std::string path;

    float vectorLenght(sf::Vector2f v);
    
};

