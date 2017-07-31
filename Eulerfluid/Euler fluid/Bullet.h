#pragma once

#include "Utility.h"
#include "Particle.h"

using namespace std ;
using namespace sf ;

class Bullet : public Particle
{
public:
	Bullet();

	void shoot(Vector2f speed) ;

	bool isInMag() const ;
	bool isShot() const ;
	bool isDead() const ;
private:
	bool inMag ;
	bool shot ;
	bool dead ;
};

