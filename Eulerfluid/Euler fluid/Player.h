#pragma once

#include "Utility.h"
#include "Particle.h"
#include "Fluid.h"
#include "HandGun.h"
#include "Grenade.h"

using namespace std ;
using namespace sf ;

class Player : public Particle
{
public:
	Player(float const& mass, Vector2f const& pos, Fluid *_fluid) ;
	~Player() ;

	void updatePlayer(float const& dt, Vector2f const& mousePos) ;
	void updateHandGun(float const& dt) ;
	void updateGrenade(float const& dt) ;
	void control(float const& dt, Vector2f const& mousePos) ;
	void equipHandGun(HandGun *gun) ;

	void draw(RenderWindow &window) ;

private:
	RectangleShape rectangle ;
	float size ;

	bool jumpKey ;
	bool jumpFlag ;
	bool rightKey ;
	bool leftKey ;
	bool shootKey ;
	bool shootFlag ;
	bool throwGrenadeKey ;
	bool throwGrenadeFlag ;

	float drag ;

	float aimAngle ;
	Vector2f aimDir ;

	HandGun *handGun ;
	Grenade *grenade ;
	Fluid *fluid ;

	vector<Particle> particle ;
	VertexArray particleVA ;
};

