#pragma once

#include "Utility.h"
#include "Fluid.h"
#include "Particle.h"
#include "ParticleSystem.h"

using namespace std ;
using namespace sf ;

class HandGun
{
public:
	HandGun();
	HandGun(int const& _magNumber, int const& _magSize, float const& _muzzleVel, float const& _bulletMass) ;

	RectangleShape getRectangle() const ;
	void setPosition(Vector2f const& pos) ;
	void setRotation(float const& angle) ;
	Vector2f getPosition() const ;

	void shoot(Vector2f const& aimDirection) ;
	void updateBullet(float const& dt, Fluid *fluid) ;
	vector<Particle> getBullet() const ;

	void draw(RenderWindow &window) ;

private:
	RectangleShape rectangle ;
	float size ;

	int magNumber ;
	int magSize ;

	vector<Particle> bullet ;
	CircleShape bulletModel ;
	vector<CircleShape> bulletPic ;
	float bulletMass ;
	
	float muzzleVel ;

	ParticleSystem particle ;
};

