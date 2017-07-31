#pragma once

#include "Utility.h"

using namespace std ;
using namespace sf ;

class Magazine
{
public:
	Magazine(int _size);

	int getEngagedBulletNumber() const ;
	vector<Bullet>& getBullet()  ;

	void drawBullets(RenderWindow &window) ;

private:
	int size ;
	int engagedBullet ;
	vector<Bullet> bullet ;

	VertexArray bulletVA ;
};

