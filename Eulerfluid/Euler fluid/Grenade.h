#pragma once

#include "Utility.h"
#include "Fluid.h"
#include "Particle.h"
#include "ParticleSystem.h"

using namespace std ;
using namespace sf ;

class Grenade : public Particle
{
public:
	Grenade();
	
	CircleShape getCircle() const ;
	void setPosition(Vector2f const& pos) ;
	Vector2f getPosition() const ;

	void shoot(Vector2f const& pos, Vector2f const& aimDirection) ;
	void update(float const& dt, Fluid *fluid) ;
	void explode() ;
	ParticleSystem getParticle() const ;

	void draw(RenderWindow &window) ;

private:
	float delay ;

	CircleShape circle ;
	ParticleSystem particle ;

};

