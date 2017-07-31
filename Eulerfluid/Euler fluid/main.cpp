/* Euler fluid simulation codded by Muzkaw : https://www.youtube.com/user/Muzkaw
   Fluid solver following the euler equations (see the beggining of this video) : https://www.youtube.com/watch?v=baMFS4qVnjk
   It's still WIP and unstable in some conditions ( you should try different values for rho and k in the fluid constructor )
   You need to link SFML 2.0 or above to run the program
   Happy coding ! */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Utility.h"
#include "Fluid.h"
#include "ParticleSystem.h"
#include "Isoline.h"

using namespace std ;
using namespace sf ;

int main()
{
	const int width = 400 ;
	const int height = 400 ;
	const int scale = 2 ;

	RenderWindow window(sf::VideoMode(width, height, 32), "Euler fluid");
	//window.setFramerateLimit(60) ;

	Fluid fluid(width/scale,height/scale,1.239,101e3,800,1,scale) ; //rho, k buoyancy, scale
	vector<Isoline> isolines ;
	for(int i(0) ; i < 10 ; i++) isolines.push_back(Isoline(-100000+20001*i,&window)) ;
	
	Clock deltaTime ;
	Clock Time ;
	float dt=0.000003 ;

	Vector2f mousePos, mousePrevPos, mouseSpeed ;
	
	Event event ;
	
	while(window.isOpen())
	{
		while(window.pollEvent(event)){}

		mousePrevPos = mousePos ;
		mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y) ;
		mouseSpeed = (mousePos - mousePrevPos)/(float)dt ;
		
		bool RMB = Mouse::isButtonPressed(Mouse::Right) ;
		bool LMB = Mouse::isButtonPressed(Mouse::Left) ;
		bool MMB = Mouse::isButtonPressed(Mouse::Middle) ;
		bool Lctrl = Keyboard::isKeyPressed(Keyboard::LControl) ;
		bool Q = Keyboard::isKeyPressed(Keyboard::Q) ;
		bool S = Keyboard::isKeyPressed(Keyboard::S) ; 
		bool D = Keyboard::isKeyPressed(Keyboard::D) ;
		bool F = Keyboard::isKeyPressed(Keyboard::F) ;
		bool G = Keyboard::isKeyPressed(Keyboard::G) ;
		bool R = Keyboard::isKeyPressed(Keyboard::R) ;
		
		if(MMB && Lctrl) fluid.setWallZone(mousePos,8,0) ;
		else if(MMB) fluid.setWallZone(mousePos,8,1) ;

		if(LMB) { fluid.addSpeedZone(Vector2f(0,55), Vector2f(width,30), Vector2f(0,5)) ; }
		if(RMB && Q)fluid.addPressureZone(mousePos, 30, 100000) ; 
		else if(RMB && S) fluid.addTemperatureZone(mousePos, 10, 1000) ;
		else if(RMB && G) fluid.addPressureZone(mousePos,30,300000) ;
		else if(RMB) fluid.addDensityZone(mousePos, 20, 1) ;
		if(R) fluid.Reset() ;

		fluid.Update(dt) ;
		//for(int i(0) ; i < 10 ; i++) isolines[i].marchingSquares(fluid.getP());
		
		window.clear(Color::White) ;

		if(S) window.draw(fluid.getTemperatureSprite()) ;
		else if(D) window.draw(fluid.getSpeedSprite()) ;
		else if(Q) window.draw(fluid.getPressureSprite()) ;
		else if(G) window.draw(fluid.get3DSprite()) ;
		else window.draw(fluid.getDensitySprite()) ;
		
		window.draw(fluid.getWallSprite()) ;

		if(F) fluid.drawSpeedField(window, 10, Color::White) ;
		//for(int i(0) ; i < 10 ; i++) isolines[i].draw();

		window.display() ;

		//dt = deltaTime.restart().asSeconds() ;
	}
}