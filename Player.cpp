#include "Player.hpp"
#include "Global.hpp"
#include <iostream>

Player::Player(float radius, float x, float y) 
{
	this->radius = radius;
	this->player.setRadius(radius);
    this->player.setFillColor(Color::Blue);
	this->x = x;
	this->y = y;
	this->anglePlayer = radian(0);
	this->speedPlayer = 0.1;
	this->visibility.setPrimitiveType(TriangleFan);
    this->lines.setPrimitiveType(Lines);
}
void Player::move() 
{
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        
        x += std::cos(radian(anglePlayer)) * speedPlayer;
        y += std::sin(radian(anglePlayer)) * speedPlayer;
        player.setPosition(x, y);

    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        x -= std::cos(radian(anglePlayer)) * speedPlayer;
        y -= std::sin(radian(anglePlayer)) * speedPlayer;
        player.setPosition(x, y);

    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        x -= std::cos(radian(anglePlayer) + PI / 2) * speedPlayer;
        y -= std::sin(radian(anglePlayer) + PI / 2) * speedPlayer;
        player.setPosition(x, y);


    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        x += std::cos(radian(anglePlayer) + PI / 2) * speedPlayer;
        y += std::sin(radian(anglePlayer) + PI / 2) * speedPlayer;
        player.setPosition(x, y);

    }
    if (Keyboard::isKeyPressed(Keyboard::Q))
    {


        anglePlayer -= 0.1;

    }
    if (Keyboard::isKeyPressed(Keyboard::E))
    {


        anglePlayer += 0.1;
    }
}
void Player::calculateRay(std::vector<Wall> &walls)
{
    float angleRad = radian(anglePlayer);
    Vector2f rayOrigin(x + radius, y + radius);
    visibility.append(Vertex(rayOrigin));

    for (int i = 0; i < RAY; i++)
    {
        float angleRay = ARAY * i + angleRad - FOV / 2;
        Vertex pos;
        pos.color = Color::White;
        pos.position = Vector2f(std::cos(angleRay) * LENGTHRAY + x, std::sin(angleRay) * LENGTHRAY + y);
        Vertex pos1 = intersection(walls[0].origin, walls[0].end, rayOrigin, pos.position);
        visibility.append(pos1);
        distan.push_back(distance(rayOrigin, Vector2f(pos1.position.x, pos1.position.y)));
    }

}
void Player::drawRay(RenderWindow& window)
{
    window.draw(visibility);
}
void Player::draw3D(RenderWindow& window)
{
    float projectionDistance = 0.5 * WALLHEIGHT / std::tan(FOV / 2);
    for (int i = 0; i < distan.size(); i++)
    {
        //std::cout << distan[i] << "\n";
        float angleRay = FOV * ((0.5 * RAY) - i) / (RAY - 1);
        float rayProgectionPos = 0.5 * std::tan(angleRay) / std::tan(FOV / 2);
        int currentCollumn = (int)(window.getSize().x * (0.5 - rayProgectionPos));
        int height = (int)(window.getSize().y * projectionDistance / (distan[i] * std::cos(angleRay)));
        Vertex pos1;
        Vertex pos2;
        float k = 255 * (1 - (distan[i] / LENGTHRAY));
        pos1.color = Color::Color(k, k, k);
        pos2.color = pos1.color;
        float yHigh = (window.getSize().y - height) / 2;
        float yLow = yHigh + height;
        pos1.position = Vector2f(currentCollumn, yHigh);
        pos2.position = Vector2f(currentCollumn, yLow);
        lines.append(pos1);
        lines.append(pos2);
    }
    window.draw(lines);
}