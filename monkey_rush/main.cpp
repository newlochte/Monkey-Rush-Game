#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "GameControl.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    GameControl gc(&window);

    gc.setup();

    while (window.isOpen())
    {
        gc.inputs();

        gc.actions();
        
        gc.draw(window);
        
    }

    return 0;
}