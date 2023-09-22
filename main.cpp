#include <iostream>
#include "Player.hpp"

using namespace sf;

void drawMap(RenderWindow& window, Player &player, std::vector<Wall> &walls)
{
    VertexArray line;
    Vertex pos;
    VertexArray wall;
    RectangleShape miniMap(Vector2f(400, 200));
    miniMap.setFillColor(Color::Color(100, 100, 100));
    pos.color = Color::Green;
    line.setPrimitiveType(Lines);
    wall.setPrimitiveType(Lines);
    for (int i = 40; i < miniMap.getSize().x; i += 40)
    {
        pos.position = Vector2f(i, 0);
        line.append(pos);
        pos.position = Vector2f(i, miniMap.getSize().y);
        line.append(pos);
    }
    for (int i = 20; i < miniMap.getSize().y; i += 20)
    {
        pos.position = Vector2f(0, i);
        line.append(pos);
        pos.position = Vector2f(miniMap.getSize().x, i);
        line.append(pos);
    }
    for (int i = 0; i < walls.size(); i++) 
    {
        
        Vertex pos;
        pos.color = Color::Red;
        pos.position = Vector2f(walls[i].origin.x / 3, walls[i].origin.y / 4);
        wall.append(pos);
        pos.position = Vector2f(walls[i].end.x / 3, walls[i].end.y / 4);
        wall.append(pos);
    }
    player.player.setPosition(Vector2f(player.x / 3, player.y / 4));
    window.draw(miniMap);
    window.draw(wall);
    window.draw(player.player);
    //window.draw(line);
}
int main() {
    RenderWindow window(VideoMode(1200, 800), "Ray");
    std::setlocale(LC_ALL, "rus");
    Player player(5, 100, 200);
    std::vector<Wall> walls;
    walls.push_back(Wall(100, 100, 200, 300));
    walls.push_back(Wall(200, 300, 500, 200));
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        player.move();
        window.clear(Color::Black);
        player.distan.clear();
        player.visibility.clear();
        player.lines.clear();
        player.calculateRay(walls);
        player.draw3D(window);
        drawMap(window, player, walls);
        
        window.display();
    }
    return 0;
}