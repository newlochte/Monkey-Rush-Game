#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Player :
    public Entity
{
public:
    Player();

    void move(sf::Vector2f offset);
    void move(float x, float y);

    void playerMovement(sf::Vector2f movement_vector, sf::Time delta_time);
    void doDamage(int damage_done);
    int getAtack();
    bool atackCooldown(sf::Time delta_time);


    enum gun_type {
        mini, ak, bomb
    };
    enum efeckts {
        none = 0b00, freez = 0b01, burn = 0b10
    };

private:
    float velocity = 300;
    void setTexture();
    std::string path = "img\\Explorer_animation.png";

    int health = 1000;
    int weapon = 1;
    float atack_cooldown = 0.2f;
    float atack_timer = 0.0;

    gun_type gun = ak;
    int gun_efeckt = (int)none;
};