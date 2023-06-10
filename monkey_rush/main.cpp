#include <SFML/Graphics.hpp>
#include <iostream>


#include "GameControl.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Monke Rush");
    GameControl game(&window);

    //mo¿e byæ nie potrzebne
    game.setup();

    while (window.isOpen())
    {
        game.inputs();

        game.actions();
        
        game.draw(window);

    }

    return 0;
}