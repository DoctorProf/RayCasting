#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Wall
{
public:
	Vector2f origin;
	Vector2f end;
	Wall(float x1, float y1, float x2, float y2);
};