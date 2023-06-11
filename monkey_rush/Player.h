#pragma once
#include "Entity.h"
#include <SFML/System/Vector2.hpp>
class Player :
    public Entity
{
public:
    friend class Interface;
    Player();

    void move(sf::Vector2f offset);
    void move(float x, float y);

    void playerMovement(sf::Vector2f movement_vector, sf::Time delta_time);
    void doDamage(int damage_done);
    int getAtack();
    int getEfeckt();
    bool atackCooldown(sf::Time delta_time);

    void update_timers(sf::Time delta_time);

    void gunChange();

    enum gun_type {
        mini, ak, bomb
    };
    enum efeckts {
        none = 0, freez = 1 << 0, burn = 1 << 1
    };

private:
    float velocity = 300;
    void setTexture();
    std::string path = "img\\Explorer_animation.png";

    int health = 1000;
    float atack_cooldown = 0.2f;
    float atack_timer = 0.0;

    gun_type gun = ak;
    int gun_efeckt = (int)freez;
};