#include "Wall.hpp"

Wall::Wall(float x1, float y1, float x2, float y2) {
	
	
	this->origin = Vector2f(x1, y1);
	this->end = Vector2f(x2, y2);
}