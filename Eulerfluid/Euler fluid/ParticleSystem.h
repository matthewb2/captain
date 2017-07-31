#pragma once

#include "Utility.h"
#include "Particle.h"

using namespace std ;
using namespace sf ;

class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(Color _color);

	void addParticle(Particle const& p) ;
	void clearParticle() ;
	void eraseParticle(int const& i) ;
	void update(float const& dt, Matrix const& wall) ;
	VertexArray getVA() ;
	void draw(RenderWindow &window) ;

	void addForceField(Matrix const& forceX, Matrix const& forceY, float const& dt) ;
	void addSpeedField(Matrix const& speedX, Matrix const& speedY) ;
	void addDrag(float drag) ;

private:
	vector<Particle> particle ;
	VertexArray particleVA ;
	Color color ;
};

