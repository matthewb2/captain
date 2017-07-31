#include "Particle.h"

Particle::Particle()
{
	m_mass = 50 ;
	m_position = Vector2f(50,50) ;
	m_speed = Vector2f(0,0) ;
	m_acceleration = Vector2f(0,0) ;
	m_sleep = false ;
}
Particle::Particle(float mass, Vector2f position, Vector2f speed)
{
	m_mass = mass ;
	m_position = position ;
	m_speed = speed ;
	m_acceleration = Vector2f(0,0) ;
	m_sleep = false ;
}

float Particle::getMass() const
{
	return m_mass ;
}
void Particle::setMass(float const& mass)
{
	m_mass=mass ;
}

vector<Vector2f> Particle::getForce() const
{
	return m_force ;
}
Vector2f Particle::getTotalForce() const
{
	Vector2f totalForce(0,0) ;
	for(int i(0) ; i < m_force.size() ; i++)
	{
		totalForce += m_force[i] ;
	}
	return totalForce ;
}
void Particle::addForce(Vector2f const& force)
{
	m_force.push_back(force) ;
}
void Particle::clearForce()
{
	m_force.clear() ;
}

Vector2f Particle::getPosition() const
{
	return m_position ;
}
void Particle::setPosition(Vector2f const& position)
{
	m_position = position ;
}

Vector2f Particle::getSpeed() const
{
	return m_speed ;
}
void Particle::setSpeed(Vector2f const& speed)
{
	m_speed = speed ;
}

Vector2f Particle::getAcceleration() const
{
	return m_acceleration ;
}
void Particle::setAcceleration(Vector2f const& acceleration)
{
	m_acceleration = acceleration ;
}
void Particle::sleep()
{
	m_sleep = true ;
}
void Particle::wake()
{
	m_sleep = false ;
}
bool Particle::isAsleep() const
{
	return m_sleep ;
}

void Particle::updatePosition(float const& dt)
{
	if(m_sleep == false)
	{
		Vector2f previousPosition = m_position ; // if x is the position : we store x(t)
		m_position = m_position + m_speed*dt + 0.5f*getTotalForce()/m_mass*(float)pow(dt,2); // the equation explained above
		m_speed = (m_position-previousPosition)/dt ; //now we need to update the speed by differentiating the position. (now we have the new position and the new speed : the particle moves !)
		clearForce() ;
	}
}