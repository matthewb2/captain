#include "HandGun.h"

HandGun::HandGun()
{
	size = 5 ;
	rectangle.setSize(Vector2f(size,size*2)) ;
	rectangle.setFillColor(Color::Green);
	rectangle.setOrigin(size/2,size) ;
	magNumber = 1 ;
	magSize = 15 ;

	muzzleVel = 500 ;

	bulletModel.setRadius(2) ;
	bulletModel.setOrigin(2,2) ;
	bulletModel.setFillColor(Color::Red) ;

	bulletMass = 5 ;

	particle = ParticleSystem(Color::Black) ;
}
HandGun::HandGun(int const& _magNumber, int const& _magSize, float const& _muzzleVel, float const& _bulletMass)
{
	size = 10 ;
	rectangle.setSize(Vector2f(size,size*2)) ;
	rectangle.setFillColor(Color::Green);
	rectangle.setOrigin(size/2,size) ;
	magNumber = _magNumber ;
	magSize = _magSize ;
	
	muzzleVel = _muzzleVel ;

	bulletModel.setRadius(5) ;
	bulletModel.setOrigin(5,5) ;
	bulletModel.setFillColor(Color::Red) ;

	bulletMass = _bulletMass ;

	particle = ParticleSystem(Color::Black) ;
}

RectangleShape HandGun::getRectangle() const
{
	return rectangle ;
}
void HandGun::setPosition(Vector2f const& pos)
{
	rectangle.setPosition(pos) ;
}
void HandGun::setRotation(float const& angle)
{
	rectangle.setRotation(angle) ;
}
Vector2f HandGun::getPosition() const
{
	return rectangle.getPosition() ;
}

void HandGun::shoot(Vector2f const& aimDirection)
{
	bullet.push_back(Particle(bulletMass,rectangle.getPosition(),Vector2f(0,0)) ) ;
	bullet[bullet.size()-1].setSpeed(aimDirection*muzzleVel) ;
	bulletPic.push_back(CircleShape(bulletModel)) ;

	for(int i(0) ; i < 50 ; i++)
		particle.addParticle(Particle(0.5, getPosition(), aimDirection*muzzleVel + Vector2f(rand()%500-250,rand()%500-250))) ;
}
void HandGun::updateBullet(float const& dt, Fluid *fluid)
{
	Matrix u = fluid->getU() ;
	Matrix v = fluid->getV() ;
	Matrix wall = fluid->getWall() ;
	for(int i(0) ; i < bullet.size() ; i++)
	{
		bullet[i].addForce(Vector2f(u.get(bullet[i].getPosition().x/u.getScale() , bullet[i].getPosition().y/v.getScale()),
									v.get(bullet[i].getPosition().x/u.getScale() , bullet[i].getPosition().y/v.getScale()))/dt) ;
		bullet[i].addForce(Vector2f(0,1000)*bulletMass) ;
		bullet[i].updatePosition(dt) ;
		bulletPic[i].setPosition(bullet[i].getPosition()) ;
	}
	particle.addForceField(u,v,dt) ; 
	particle.addDrag(10) ;
	particle.update(dt,wall) ;
}

vector<Particle> HandGun::getBullet() const
{
	return bullet ;
}

void HandGun::draw(RenderWindow &window)
{
	window.draw(rectangle) ;
	for(int i(0) ; i < bullet.size() ; i++)
	{
		window.draw(bulletPic[i]) ;
	}
	window.draw(particle.getVA()) ;
}