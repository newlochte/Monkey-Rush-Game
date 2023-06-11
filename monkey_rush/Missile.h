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
    int frame_rate;
};

static Missile_info missile_info[5] = {
        {10 ,1  ,1  ,2000 ,{10.f,10.f},"minigun_bullet.png",0},
        {50 ,1  ,3  ,1000 ,{10.f,10.f},"AK_bullet.png",     0},
        {200,150,0.5,150  ,{10.f,6.f} ,"bazooka_bullet.png",0},
        {10 ,1  ,1.5,250  ,{10.f,10.f},"banana.png" ,       4},
        {20 ,1  ,0.5,300  ,{1.f,1.f}  ,"default.png",       0}
};

class Missile :
    public Entity
{
public:
    enum type {
        mini, ak, bomb, //bronie gracza
        banana, mele    //ataki przeciwników
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

