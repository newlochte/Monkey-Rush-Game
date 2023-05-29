#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    bool state = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pos = sf::Mouse::getPosition(window);

        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(pos))&& !state) {
            std::cout << "inside\n";
            state = 1;
        }
        if (!shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(pos)) && state) {
            std::cout << "out\n";
            state = 0;
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}