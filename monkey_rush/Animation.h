#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

/*
Klasa zajmuj¹ca siê obs³ug¹ animacji
Przechowuje ca³¹ grafikê tekstury i wykonuje animacje opare na klatkach
w niej przechowywanych, obs³ugujê animacje ruchu w ró¿nych kierunkach
*/

//klasa w trakcie budowy
class Animation: public sf::RectangleShape
{
	sf::Vector2f frame_size;
	sf::Vector2f texture_size;
	sf::IntRect uvRect;
	
	float switch_time = 0;
	sf::Time animation_timer;

	bool animationChange(sf::Time time);

public:
	Animation();

	Animation(sf::Vector2f size);

	Animation(sf::Vector2f size, sf::Texture &texture);

	void animate(sf::Time time);

	void setTexture(sf::Texture *texture);

	//void setAnimationType();

	void setAnimationSpeed(float animation_speed_per_second);

	void setFrameSize(sf::Vector2f frame_size);

};

