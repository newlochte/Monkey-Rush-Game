#include "Enemy.h"

void Enemy::setTexture(std::string path = "img\\default.png")
{
	texture.loadFromFile(path);
	animation.setTexture(&texture);
}

float Enemy::vectorLenght(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Enemy::Enemy(sf::Vector2f position)
	:Entity(sf::Vector2f(64,64))
{
	setPosition(position);
	setTexture();
	atack_timer = 0.0;
}

Enemy::Enemy(sf::Vector2f position, sf::Vector2f size)
	:Entity(size)
{
	setPosition(position);
	setTexture();
	atack_timer = 0.0;
}

void Enemy::moveToPlayer(Player player, sf::Time delta_time)
{
	sf::Vector2f move_vector;
	if (isColliding(player)) {
		move_vector = unclipVector(player);
	}
	else {
		move_vector = player.getPosition() - getPosition();
	}
	move_vector /= sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
	move_vector *= delta_time.asSeconds();
	move(move_vector);
}

int Enemy::getAtackType()
{
	return 4;
}

bool Enemy::canAtack(Player player, sf::Time time_elapsed)
{
	bool state = false;
	if(atack_timer > 0.0) atack_timer -= time_elapsed.asSeconds();
	if (vectorLenght(player.getPosition() - getPosition()) < 66 && atack_timer <= 0.0) {
		state = true;
		atack_timer = atack_cooldown;
	}

	return state;
}

void Enemy::giveDebuff(int debuf)
{
	if (debuf & 0b01) velocity *= 0.5;
	if (debuf & 0b10) DoT = 5;
}

void Enemy::doDoT(sf::Time delta_time)
{
	if (DoT != 0) {
		DoT_timer += delta_time.asSeconds();
		if (DoT_timer >= 1) {
			health -= DoT;
			DoT_timer--;
		}
	}
}

bool Enemy::doDamage(std::pair<int,int> damage)
{
	if (damage.second & 0b01) velocity *= 0.5;
	if (damage.second & 0b10) DoT = 5;
	health -= damage.first;
	return health <= 0;
}

void Enemy::move(sf::Vector2f& offset)
{
	offset *= velocity;
	Entity::move(offset);
}

void Enemy::move(float x, float y)
{
	x *= velocity;
	y *= velocity;

	Entity::move(x, y);
}

void Enemy::bounceOfEnemy(Enemy* other, sf::Time delta_time)
{
	sf::Vector2f move_vector;
	move_vector = unclipVector(*other);
	move_vector /= sqrt(move_vector.x * move_vector.x + move_vector.y * move_vector.y);
	move_vector *= delta_time.asSeconds();
	move(move_vector);
}


