#include "Fluid.h"

Fluid::Fluid()
{
	width = 100 ;
	height = 100 ;
	rho = 20 ; 
	k = rho*30 ;
	L=1 ;
	buoyancyFactor = 0.001 ;
	ambientTemperature = 0 ;
	scale = 1 ;

	u.resize(width, height) ; u.setScale(scale) ;
	v.resize(width, height) ; v.setScale(scale) ;
	u0.resize(width, height) ; u0.setScale(scale) ;
	v0.resize(width, height) ; v0.setScale(scale) ;
	p.resize(width, height) ; p.setScale(scale) ;
	wall.resize(width, height) ; wall.setScale(scale) ;
	T.resize(width, height) ; T.setScale(scale) ;
	T0.resize(width, height) ; T0.setScale(scale) ;
	density.resize(width, height) ; density.setScale(scale) ;
	density0.resize(width, height) ; density0.setScale(scale) ;

	for(int i(0) ; i < width ; i++)
	{
		for(int j(0) ; j < height ; j++)
		{
			u.set(i,j,0);
			v.set(i,j,0);
			u0.set(i,j,0);
			v0.set(i,j,0);
			p.set(i,j,0);
			wall.set(i,j,0);
			T.set(i,j,ambientTemperature);
			T0.set(i,j,ambientTemperature);
			density.set(i,j,0) ;
			density0.set(i,j,0) ;
		}
	}

	image.create(width, height,Color::Black) ;
	texture.loadFromImage(image);
	sprite.setTexture(texture) ;

	posPressureColor.loadFromFile("pressure+.jpg") ;
	negPressureColor.loadFromFile("pressure-.jpg") ;
	temperatureColor.loadFromFile("color.jpg") ;
	speedColor.loadFromFile("speed.jpg") ;
	densityColor.loadFromFile("density.jpg") ;
}
Fluid::Fluid(float const& _width, float const& _height, float const& _rho, float const& _k, float const& _buoyancyFactor, float const& _L, float const& _scale)
{
	width = _width ;
	height = _height ;
	rho = _rho; 
	k = _k ;
	L = 2*_L/(width+height) ;
	buoyancyFactor = _buoyancyFactor ;
	ambientTemperature = 0 ;
	scale = _scale ;

	u.resize(width, height) ; u.setScale(scale) ;
	v.resize(width, height) ; v.setScale(scale) ;
	u0.resize(width, height) ; u0.setScale(scale) ;
	v0.resize(width, height) ; v0.setScale(scale) ;
	p.resize(width, height) ; p.setScale(scale) ;
	wall.resize(width, height) ; wall.setScale(scale) ;
	T.resize(width, height) ; T.setScale(scale) ;
	T0.resize(width, height) ; T0.setScale(scale) ;
	density.resize(width, height) ; density.setScale(scale) ;
	density0.resize(width, height) ; density0.setScale(scale) ;
	
	for(int i(0) ; i <= width ; i++)
	{
		for(int j(0) ; j <= height ; j++)
		{
			u.set(i,j,0);
			v.set(i,j,0);
			u0.set(i,j,0);
			v0.set(i,j,0);
			p.set(i,j,0);
			wall.set(i,j,0); if(i<5) wall.set(i,j,2) ; if(i>width-5) wall.set(i,j,3) ; if(j<5) wall.set(i,j,4) ; if(j>height-5) wall.set(i,j,5) ;
			T.set(i,j,ambientTemperature);
			T0.set(i,j,ambientTemperature);
			density.set(i,j,0) ;
			density0.set(i,j,0) ;
		}
	}
	
	image.create(width, height,Color::Black) ;
	texture.loadFromImage(image);
	sprite.setTexture(texture,true);
	sprite.setScale(scale,scale) ;
	posPressureColor.loadFromFile("pressure+.jpg") ;
	negPressureColor.loadFromFile("pressure-.jpg") ;
	temperatureColor.loadFromFile("color.jpg") ;
	speedColor.loadFromFile("speed.jpg") ;
	densityColor.loadFromFile("density.jpg") ;

	pScale = 3*60000 ;
	vScale = 3*200 ;
	tScale = 3*350 ;
	
	scale = _scale ;
}
void Fluid::Update(float const& dt)
{
	for(int i(2) ; i < width-2 ; i++)
	{
		for(int j(2) ; j < height-2 ; j++)
		{
			u.set(i,j, u.get(i,j) - ( (1/rho)*(p.get(i+1,j)-p.get(i-1,j))/(2.f*L) )*dt);
			v.set(i,j, v.get(i,j) - ( (1/rho)*(p.get(i,j+1)-p.get(i,j-1))/(2.f*L))*dt);
			
			v.set(i,j, v.get(i,j) - buoyancyFactor*(T.get(i,j)-ambientTemperature)*dt);

			if(wall.get(i,j)==1)
			{
				u.set(i,j,0);
				v.set(i,j,0);
				u0.set(i,j,0);
				v0.set(i,j,0);
				//p.set(i,j,0);
				T.set(i,j,ambientTemperature);
				T0.set(i,j,ambientTemperature);
				density.set(i,j,0) ;
				density0.set(i,j,0) ;
			}
			if(wall.get(i,j)==2)
			{
				u.set(i,j,u.get(i+1,j));
				v.set(i,j,v.get(i+1,j));
				u0.set(i,j,u0.get(i+1,j));
				v0.set(i,j,v0.get(i+1,j));
				//p.set(i,j,p.get(i+1,j));
			}
			if(wall.get(i,j)==3)
			{
				u.set(i,j,u.get(i-1,j));
				v.set(i,j,v.get(i-1,j));
				u0.set(i,j,u0.get(i-1,j));
				v0.set(i,j,v0.get(i-1,j));
				//p.set(i,j,p.get(i-1,j));
			}
			if(wall.get(i,j)==4)
			{
				u.set(i,j,u.get(i,j+1));
				v.set(i,j,v.get(i,j+1));
				u0.set(i,j,u0.get(i,j+1));
				v0.set(i,j,v0.get(i,j+1));
				//p.set(i,j,p.get(i,j+1));
			}
			if(wall.get(i,j)==5)
			{
				u.set(i,j,u.get(i,j-1));
				v.set(i,j,v.get(i,j-1));
				u0.set(i,j,u0.get(i,j-1));
				v0.set(i,j,v0.get(i,j-1));
				//p.set(i,j,p.get(i,j-1));
			}
		}
	}

	for(int i(1) ; i < width-1 ; i++)
	{
		for(int j(1) ; j < height-1 ; j++)
		{
			p.set(i,j, p.get(i,j) - k*( (u.get(i+1,j)-u.get(i-1,j))/(2.f*L)  + (v.get(i,j+1)-v.get(i,j-1))/(2.f*L) )*dt );

			if(wall.get(i,j)!=1)
			{
				float x = i-dt*u.get(i,j)/L; 
				float y = j-dt*v.get(i,j)/L; 

				if (x<1) x=1; if (x>width-1) x=width-1; int i0=(int)x; int i1=i0+1;
				if (y<1) y=1; if (y>height-1) y=height-1; int j0=(int)y; int j1=j0+1; 
				float s1 = x-i0; float s0 = 1-s1; float t1 = y-j0; float t0 = 1-t1;
				u0.set(i,j, s0*(t0*u.get(i0,j0)+t1*u.get(i0,j1)) + s1*(t0*u.get(i1,j0)+t1*u.get(i1,j1)));
				v0.set(i,j, s0*(t0*v.get(i0,j0)+t1*v.get(i0,j1)) + s1*(t0*v.get(i1,j0)+t1*v.get(i1,j1))); 
				T0.set(i,j, s0*(t0*T.get(i0,j0)+t1*T.get(i0,j1))+s1*(t0*T.get(i1,j0)+t1*T.get(i1,j1))); 
				density0.set(i,j, s0*(t0*density.get(i0,j0)+t1*density.get(i0,j1))+s1*(t0*density.get(i1,j0)+t1*density.get(i1,j1))); 
			}
		}
	}
	u=u0;
	v=v0; 
	T=T0;
	density = density0 ;
}

Sprite Fluid::getPressureSprite()
{
	for(int i(1) ; i < width-1 ; i++)
		for(int j(1) ; j < height-1 ; j++)
			if(p.get(i,j) > 0 ) image.setPixel(i,j,colorGradient(posPressureColor, p.get(i,j)/pScale)) ;
			else image.setPixel(i,j,colorGradient(negPressureColor, -p.get(i,j)/pScale)) ;
	
	texture.loadFromImage(image) ;
	return sprite ;
}
Sprite Fluid::getTemperatureSprite()
{
	for(int i(1) ; i < width-1 ; i++)
		for(int j(1) ; j < height-1 ; j++)
			image.setPixel(i,j,colorGradient(temperatureColor,T.get(i,j)/tScale)) ;
		
	texture.loadFromImage(image) ;
	return sprite ;
}
Sprite Fluid::getSpeedSprite()
{
	for(int i(1) ; i < width-1 ; i++)
		for(int j(1) ; j < height-1 ; j++)
			image.setPixel(i,j,colorGradient(speedColor,sqrt(pow(u.get(i,j),2)+pow(v.get(i,j),2))/vScale)) ;
		
	texture.loadFromImage(image) ;
	return sprite ;
}
Sprite Fluid::getDensitySprite()
{
	for(int i(1) ; i < width-1 ; i++)
		for(int j(1) ; j < height-1 ; j++)
			image.setPixel(i,j,colorGradient(densityColor,density.get(i,j)*1.f)) ;
		
	texture.loadFromImage(image) ;
	return sprite ;
}
Sprite Fluid::getWallSprite()
{
	for(int i(1) ; i < width-1 ; i++)
		for(int j(1) ; j < height-1 ; j++)
			if(wall.get(i,j)==1)
				image.setPixel(i,j,Color::Color(200, 200, 170)) ;
			else if(wall.get(i,j)>=2)
				image.setPixel(i,j,Color::Color(100, 100, 120)) ;
			else
				image.setPixel(i,j,Color::Transparent) ;
	texture.update(image) ;
	return sprite ;
}
Sprite Fluid::get3DSprite()
{
	for(int i(1) ; i < width-1 ; i++)
		for(int j(1) ; j < height-1 ; j++)
			//image.setPixel(i,j,Color::Color(T.get(i,j)/tScale*127.5+127.5,p.get(i,j)/pScale*127.5+127.5,255.f)) ;
			//image.setPixel(i,j,Color::Color(sqrt(pow(u.get(i,j),2)+pow(v.get(i,j),2))/vScale*1.1*127.5+127.5,1.2*p.get(i,j)/pScale*127.5+127.5,255.f)) ;
			image.setPixel(i,j,Color::Color(u.get(i,j)/vScale*1.4*127.5+127.5,v.get(i,j)/vScale*1.4*127.5+127.5,255.f)) ;

	texture.loadFromImage(image) ;
	return sprite ;
}

void Fluid::Reset()
{
	for(int i(1) ; i < width-1 ; i++)
	{
		for(int j(1) ; j < height-1 ; j++)
		{
			u.set(i,j,0);
			v.set(i,j,0);
			u0.set(i,j,0);
			v0.set(i,j,0);
			p.set(i,j,0);
			if(wall.get(i,j)==1) wall.set(i,j,0);
			T.set(i,j,ambientTemperature);
		}
	}
}

void Fluid::drawSpeedField(RenderWindow &window, float const& size, Color const& color) const
{
	for(int i(1) ; i < width-1 ; i+=5)
	{
		for(int j(2) ; j < height-2 ; j+=5)
		{
			drawLine( Vector2f(scale*i, scale*j), size*Vector2f(u.get(i,j),v.get(i,j))/50.f, window, color) ;
		}
	}
}

int Fluid::getWidth() const
{
	return width ;
}
int Fluid::getHeight() const
{
	return height ;
}
float Fluid::getScale() const
{
	return scale ;
}
Matrix Fluid::getP() const
{
	return p ;
}

void Fluid::setWallZone(Vector2f const& pos, float const& size, int const& on)
{
	for(int i((pos.x-size)/scale) ; i < (pos.x+size)/scale ; i++)
		for(int j((pos.y-size)/scale) ; j < (pos.y+size)/scale ; j++)
			if(Distance(Vector2f(i,j),pos/scale)<size/scale)
				wall.set(i,j,on) ;
}

void Fluid::addPressureZone(Vector2f const& pos, float const& size, float const& _p)
{
	for(int i((pos.x-size)/scale) ; i < (pos.x+size)/scale ; i++)
		for(int j((pos.y-size)/scale) ; j < (pos.y+size)/scale ; j++)
			if(Distance(Vector2f(i,j),pos/scale)<size/scale)
				p.set(i,j,_p) ;
}
void Fluid::addTemperatureZone(Vector2f const& pos, float const& size, float const& _T)
{
	for(int i((pos.x-size)/scale) ; i < (pos.x+size)/scale ; i++)
		for(int j((pos.y-size)/scale) ; j < (pos.y+size)/scale ; j++)
			if(Distance(Vector2f(i,j),pos/scale)<size/scale)
				T.set(i,j,_T) ;
}
void Fluid::addSpeedZone(Vector2f pos, Vector2f size, Vector2f speed)
{
	for(int i(pos.x/scale) ; i < (pos.x+size.x)/scale ; i++)
	{
		for(int j(pos.y/scale) ; j < (pos.y+size.y)/scale ; j++)
		{
			u.set(i,j,u.get(i,j)+speed.x) ;
			v.set(i,j,v.get(i,j)+speed.y) ;
		}
	}
}
void Fluid::addDensityZone(Vector2f pos, float size, float _density)
{
	for(int i((pos.x-size)/scale) ; i < (pos.x+size)/scale ; i++)
		for(int j((pos.y-size)/scale) ; j < (pos.y+size)/scale ; j++)
			if(Distance(Vector2f(i,j),pos/scale)<size/scale)
				density.set(i,j,_density) ;
}
