#include "Bullet.h"

Bullet::Bullet()
{
	inMag = 1 ;
	shot = 0 ;
	dead = 0 ;

	setPosition(Vector2f(200,200)) ;
}
void Bullet::shoot(Vector2f speed)
{
	setSpeed(speed) ;
	shot = 1 ;
}

bool Bullet::isInMag() const
{
	return inMag ;
}
bool Bullet::isShot() const
{
	return shot ;
}
bool Bullet::isDead() const
{
	return dead ;
}