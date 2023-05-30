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
	frame_size = { 0,0 };
	
}

Animation::Animation(sf::Vector2f size)
	:sf::RectangleShape(size)
{

}

Animation::Animation(sf::Vector2f size, sf::Texture &texture)
	:sf::RectangleShape(size)
{
	RectangleShape::setTexture(&texture);
	Animation::texture_size = static_cast<sf::Vector2f>(texture.getSize());
	//uvRect = { 0,0,(int)texture_size.x, (int)texture_size.y };
}

void Animation::animate(sf::Time time)
{
	if (animationChange(time)) {
		std::cout<<uvRect.top<<", " << uvRect.left << ", " << uvRect.width << ", " << uvRect.height << "\n ";
		if (uvRect.left+uvRect.width >= texture_size.x) {
			uvRect.left = 0;
		}
		else {
			uvRect.left += (int)frame_size.x;
		}
		setTextureRect(uvRect);
	}
}

void Animation::setTexture(sf::Texture* texture)
{
	RectangleShape::setTexture(texture);
	Animation::texture_size = static_cast<sf::Vector2f>(texture->getSize());
}

void Animation::setAnimationSpeed(float animation_speed_per_second)
{
	switch_time = 1 / animation_speed_per_second;
}

void Animation::setFrameSize(sf::Vector2f frame_size)
{
	Animation::frame_size = frame_size;
	uvRect = { 0,0,(int)frame_size.x,(int)frame_size.y };
}
