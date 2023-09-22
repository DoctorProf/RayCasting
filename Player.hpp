#pragma once
#include "SFML/Graphics.hpp"
#include "Wall.hpp"
using namespace sf;
class Player {
public:
	CircleShape player;
    VertexArray visibility;
    std::vector<float> distan;
    float x;
    float y;
    float anglePlayer;
    float speedPlayer;
    float radius;
    VertexArray lines;
	Player(float radius, float x, float y);
    void move();
    void calculateRay(std::vector<Wall> &walls);
    void drawRay(RenderWindow& window);
    void draw3D(RenderWindow &window);
};