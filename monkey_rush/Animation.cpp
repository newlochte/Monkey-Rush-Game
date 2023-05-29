#include "Animation.h"

bool Animation::animationChange(sf::Time time)
{
	if (switch_time != 0.0f) {
		animation_timer += time;
		if (animation_timer.asSeconds() >= switch_time) {
			animation_timer -= sf::seconds(switch_time);
			return true;
		}
	}
	return false;
}

Animation::Animation()
{
}

Animation::Animation(sf::Vector2f size)
	:sf::RectangleShape(size)
{

}

Animation::Animation(sf::Vector2f size, sf::Texture &texture)
	:sf::RectangleShape(size)
{
	setTexture(&texture);
	Animation::texture_size = { texture.getSize().x,texture.getSize().y };
}

void Animation::animate(sf::Time time)
{
	if (animationChange(time)) {
		if (uvRect.left+uvRect.width >= texture_size.x) {
			uvRect.left = 0;
		}
		else {
			uvRect.left += texture_size.x;
		}
	}
}

void Animation::setAnimationSpeed(float animation_speed_per_second)
{
	switch_time = 1 / animation_speed_per_second;
}

void Animation::setFrameSize(sf::Vector2f frame_size)
{
	Animation::frame_size = frame_size;
}
