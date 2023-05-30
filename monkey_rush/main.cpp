#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "GameControl.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    GameControl gc(&window);

    sf::Texture txtr;
    txtr.loadFromFile("img\\sprite_0.png");
    sf::Vector2f window_size = static_cast<sf::Vector2f>(window.getSize());
    sf::Vector2f middle = window_size / 2.f;

    sf::Clock clock;
    sf::Time time;

    gc.setup();

    while (window.isOpen())
    {
        gc.inputs();

        gc.actions();
        
        gc.draw(window);
        
    }

    return 0;
}