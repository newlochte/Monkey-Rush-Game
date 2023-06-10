#include "Missile.h"

Missile::Missile(sf::Vector2f position, sf::Vector2f destination, type amo)
	:Entity(sf::Vector2f(missile_info[amo].hit_box))
{
	

	//entity
	setPosition(position);
	
	//missile
	amo_type = amo;
	destination_vector = destination - getPosition();
	destination_vector /= vectorLenght(destination_vector);
	//std::cout << destination_vector.x << " " << destination_vector.y << std::endl;
	path = "img\\" + missile_info[amo].path;
	velocity = missile_info[amo].velocity;
	life_time = missile_info[amo].time;

	//animacja
	texture.loadFromFile(path);
	animation.setTexture(&texture);
	animation.setAnimationSpeed(4);
	animation.setFrameSize(sf::Vector2f(10, 10));
}

void Missile::update(sf::Time time_elasped)
{
	if (life_time <= 0.f) return;
	move(destination_vector * (time_elasped.asSeconds() * velocity));
	life_time -= time_elasped.asSeconds();
}

void Missile::hit()
{
	life_time = 0.f;
}

bool Missile::expired()
{
	if (life_time <= 0.f) return true;
	return false;
}

std::pair<int, float> Missile::getDamageInfo() {
	return std::make_pair(missile_info[amo_type].damage, missile_info[amo_type].radius);
}

float Missile::vectorLenght(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

