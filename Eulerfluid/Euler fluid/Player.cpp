#include "Player.h"

Player::Player(float const& mass, Vector2f const& pos, Fluid *_fluid)
{
	size = 20 ;
	setMass(mass) ;
	setPosition(pos) ;

	rectangle.setFillColor(Color::Blue) ;
	rectangle.setSize(Vector2f(size/2,size)) ;

	drag = 10 ;
	jumpKey = 0 ;
	rightKey = 0 ; 
	leftKey = 0 ;
	shootKey = 0 ;

	aimAngle = 0 ;
	aimDir = Vector2f(0,-1) ;

	handGun = 0 ;
	handGun = new HandGun() ;

	fluid = 0 ;
	fluid = _fluid ;

	grenade = 0 ;
	grenade = new Grenade() ;
}
Player::~Player()
{
	delete handGun ;
	delete fluid ;
	delete grenade ;
}

void Player::updatePlayer(float const& dt, Vector2f const& mousePos)
{
	jumpKey = keyPushedOnce(Keyboard::Space,jumpFlag) ;
	rightKey = Keyboard::isKeyPressed(Keyboard::D) ;
	leftKey = Keyboard::isKeyPressed(Keyboard::Q) ;
	shootKey = mouseClickedOnce(Mouse::Left,shootFlag) ;
	throwGrenadeKey = mouseClickedOnce(Mouse::Right,throwGrenadeFlag) ;

	if(jumpKey) setSpeed(Vector2f(getSpeed().x,-1000)) ;
	if(rightKey) addForce(Vector2f(2000,0)) ;
	if(leftKey) addForce(Vector2f(-2000,0)) ;
	
	addForce( -getSpeed()*drag ) ;
	addForce(Vector2f(0,5000)) ;
	
	updatePosition(dt) ;
	fluid->addSpeedZone(getPosition(),rectangle.getSize(),getSpeed()*0.5f) ;
	rectangle.setPosition(getPosition()-Vector2f(size/4,size/2)) ;

	if(fluid->getWall().get(getPosition().x/fluid->getWall().getScale(), (getPosition().y+size/2)/fluid->getWall().getScale()) == 1 ) //bottom collision
	{
		setPosition(getPosition() - (Vector2f(0,getPosition().y-fluid->getWall().getScale()*quo((int)getPosition().y,(int)fluid->getWall().getScale())))) ; // place on a tile
		while(fluid->getWall().get(getPosition().x/fluid->getWall().getScale(), (getPosition().y+size/2)/fluid->getWall().getScale()) == 1 ) // move up until no more tile
		{
			setPosition(getPosition()+Vector2f(0,-fluid->getWall().getScale())) ;
		}
		setPosition(getPosition()+Vector2f(0,fluid->getWall().getScale())) ; // move down 1 tile
		setSpeed(Vector2f(getSpeed().x,0)) ;
	}
	if(fluid->getWall().get((getPosition().x+size/4)/fluid->getWall().getScale(), (getPosition().y+size/2-3.5*fluid->getWall().getScale())/fluid->getWall().getScale()) == 1 && getSpeed().x>=0) //right collision
	{
		setPosition(getPosition() - (Vector2f(getPosition().x-fluid->getWall().getScale()*quo((int)getPosition().x,(int)fluid->getWall().getScale()),0))) ; 
		while(fluid->getWall().get((getPosition().x+size/4)/fluid->getWall().getScale(), (getPosition().y+size/2-3.5*fluid->getWall().getScale())/fluid->getWall().getScale()) == 1) 
		{
			setPosition(getPosition()+Vector2f(-fluid->getWall().getScale(),0)) ;
		}
		setPosition(getPosition()+Vector2f(fluid->getWall().getScale(),0)) ; 
	}
	if(fluid->getWall().get((getPosition().x-size/4)/fluid->getWall().getScale(), (getPosition().y+size/2-3.5*fluid->getWall().getScale())/fluid->getWall().getScale()) == 1 && getSpeed().x<=0) //left collision
	{
		setPosition(getPosition() - (Vector2f(getPosition().x-fluid->getWall().getScale()*quo((int)getPosition().x,(int)fluid->getWall().getScale()),0))) ; 
		while(fluid->getWall().get((getPosition().x-size/4)/fluid->getWall().getScale(), (getPosition().y+size/2-3.5*fluid->getWall().getScale())/fluid->getWall().getScale()) == 1) 
		{
			setPosition(getPosition()-Vector2f(-fluid->getWall().getScale(),0)) ;
		}
		setPosition(getPosition()-Vector2f(fluid->getWall().getScale(),0)) ; 
	}

	angleInterpolation(aimAngle,-Angle(getPosition()-mousePos,Vector2f(0,1)),getMass()/5,dt) ;
	aimDir = rotatePoint(getPosition()+Vector2f(0,-1),getPosition(),aimAngle)-getPosition() ; 
}
void Player::updateHandGun(float const& dt)
{
	handGun->setPosition(rotatePoint(getPosition()+Vector2f(0,-15),getPosition(),aimAngle)) ;
	handGun->setRotation(aimAngle) ;

	if(shootKey)
	{
		handGun->shoot(aimDir) ;
	}
	handGun->updateBullet(dt,fluid) ;

	for(int i(0) ; i < handGun->getBullet().size() ; i++)
		fluid->addSpeedZone(handGun->getBullet()[i].getPosition(), Vector2f(2,2), handGun->getBullet()[i].getSpeed()) ;
}
void Player::updateGrenade(float const& dt)
{
	if(throwGrenadeKey) grenade->shoot(getPosition(), aimDir) ;
	grenade->update(dt, fluid) ;
}
void Player::control(float const& dt, Vector2f const& mousePos)
{
	updatePlayer(dt, mousePos) ;
	updateHandGun(dt) ;
	updateGrenade(dt) ;
}
void Player::equipHandGun(HandGun *gun)
{
	handGun = gun ;
}

void Player::draw(RenderWindow &window)
{
	window.draw(rectangle) ;
	//drawLine(getPosition(), aimDir*1000.f, window, Color::Blue) ;
	handGun->draw(window) ;
	grenade->draw(window) ;
}