#include "Magazine.h"

Magazine::Magazine(int _size)
{
	size = _size ;
	engagedBullet = 0 ;
	
	bulletVA.setPrimitiveType(Points) ;
	for(int i(0) ; i < size ; i++)
	{
		bullet.push_back(Bullet()) ;
		bulletVA.append(Vertex(bullet[i].getPosition(), Color::Red)) ;
	}
}

int Magazine::getEngagedBulletNumber() const
{
	return engagedBullet ;
}
vector<Bullet>& Magazine::getBullet() 
{
	return &bullet ;
}


void Magazine::drawBullets(RenderWindow &window)
{
	for(int i(0) ; i < size ; i++)
	{
		bulletVA[i].position = bullet[i].getPosition() ;
	}
	window.draw(bulletVA) ;
}