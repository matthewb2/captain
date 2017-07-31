#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	particleVA.setPrimitiveType(Points) ;
	color = Color::Red ;
}
ParticleSystem::ParticleSystem(Color _color)
{
	particleVA.setPrimitiveType(Points) ;
	color = _color ;
}

void ParticleSystem::addParticle(Particle const& p)
{
	particle.push_back(p) ;
	particleVA.append(Vertex(p.getPosition(),color)) ;
}
void ParticleSystem::clearParticle() 
{
	particle.clear() ;
	particleVA.clear() ;
}
void ParticleSystem::eraseParticle(int const& i)
{
	particle.erase(particle.begin()+i) ;
	particleVA.resize(particleVA.getVertexCount()-1) ;
}
void ParticleSystem::update(float const& dt, Matrix const& wall)
{
	for(int i(0) ; i < particle.size() ; i++)
	{
		particle[i].updatePosition(dt) ;
		if(wall.get(particle[i].getPosition().x/wall.getScale(), particle[i].getPosition().y/wall.getScale()) == 1)
			eraseParticle(i) ;
		for(int i(0) ; i < particle.size() ; i++)
		{
			particleVA[i].position = particle[i].getPosition() ;
		}
	}
}
VertexArray ParticleSystem::getVA()
{
	return particleVA ;
}
void ParticleSystem::draw(RenderWindow &window)
{
	window.draw(particleVA) ;
}
void ParticleSystem::addForceField(Matrix const& forceX, Matrix const& forceY, float const& dt)
{ 
	for(int i(0) ; i < particle.size() ; i++)
	{
		particle[i].addForce( Vector2f( forceX.get(particle[i].getPosition().x/forceX.getScale(),particle[i].getPosition().y/forceY.getScale() ) ,
										forceY.get(particle[i].getPosition().x/forceX.getScale(),particle[i].getPosition().y/forceY.getScale() ) )/dt  ) ;
	}
}
void ParticleSystem::addSpeedField(Matrix const& speedX, Matrix const& speedY)
{ 
	for(int i(0) ; i < particle.size() ; i++)
	{
		particle[i].setSpeed( Vector2f( speedX.get(particle[i].getPosition().x/speedX.getScale(),particle[i].getPosition().y/speedY.getScale() ) ,
										speedY.get(particle[i].getPosition().x/speedX.getScale(),particle[i].getPosition().y/speedY.getScale() ) )  ) ;
	}
}
void ParticleSystem::addDrag(float drag)
{
	for(int i(0) ; i < particle.size() ; i++)
	{
		particle[i].addForce(-particle[i].getSpeed()*drag) ;
	}	
}
