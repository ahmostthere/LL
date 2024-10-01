#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <iostream>

class Map : public sf::Drawable, public sf::Transformable 
{
public:
    std::vector<sf::RectangleShape> map;
    Map() {
        std::cout << "hello map" << std::endl;
        sf::Vector2f pos = sf::Transformable::getPosition();
        std::cout << "pos: " << pos.x << ", " << pos.y << std::endl;
        sf::Vector2f size(49, 49);
        int row = 50;
        int col = 50;
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                sf::RectangleShape tile(size);
                tile.setPosition(pos + sf::Vector2f(c * 50, r * 50));
                tile.setFillColor(sf::Color(115, 195, 95));
                tile.setOutlineColor(sf::Color(75, 145, 55));
                tile.setOutlineThickness(1);
                map.push_back(tile);
            }
        }
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // std::cout << "map size: " << map.size()<< std::endl;
        for (int i = 0; i < map.size(); i++)
        {
            target.draw(map[i]);
        }
    }
};