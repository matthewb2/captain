#include "Grenade.h"


Grenade::Grenade()
{
	delay = 10 ;
	circle.setFillColor(Color::Green) ;
	circle.setRadius(8) ;
	circle.setOrigin(8,8) ;

	setMass(1) ;

}
CircleShape Grenade::getCircle() const
{
	return circle ;
}
void Grenade::setPosition(Vector2f const& pos)
{
	circle.setPosition(pos) ;
}
Vector2f Grenade::getPosition() const
{
	return circle.getPosition() ;
}

void Grenade::shoot(Vector2f const& pos, Vector2f const& aimDirection)
{
	Particle::setPosition(pos) ;
	setSpeed(aimDirection*600.f) ;
}
void Grenade::update(float const& dt, Fluid *fluid)
{
	if(delay >= 0)
		explode() ;
	addForce(Vector2f(0,1000)) ;
	updatePosition(dt) ;
	circle.setPosition(Particle::getPosition()) ;
	particle.update(dt,fluid->getWall()) ;

	delay -= dt ;
}
void Grenade::explode()
{

}
ParticleSystem Grenade::getParticle() const
{
	return particle ;
}

void Grenade::draw(RenderWindow &window)
{
	window.draw(circle) ;
	particle.draw(window) ;
}