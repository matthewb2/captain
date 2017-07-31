#pragma once

#include <SFML/Graphics.hpp>
#include "Matrix.h"

using namespace std;
using namespace sf;

class Isoline
{
public:
	Isoline(float const& _threshold,RenderWindow *_window);
	void marchingSquares(Matrix const& field);
	void draw();

private:

	int sample_size;
	float threshold;

	Matrix threshold_field ;
	Vector2f size;
	float scale;

	VertexArray isolines;
	Image image; //DEBUG
	Texture texture;
	Sprite sprite;
	RenderWindow *window;
};

