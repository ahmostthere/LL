#pragma once
#include <Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <iostream>

class Map : public Entity {
public:
    std::vector<sf::RectangleShape> map;
    int rows; 
    int columns;
    float tileSize;
    float outlineThickness;
    
    Map(int row = 50, int col = 50, int sz = 50, int thickness = 1) : rows(row), columns(col), tileSize(sz), outlineThickness(thickness) {
        sf::Vector2f size(tileSize - outlineThickness, tileSize - outlineThickness);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                sf::RectangleShape tile(sf::Vector2f(tileSize - outlineThickness, tileSize - outlineThickness));
                tile.setPosition(sf::Transformable::getPosition() + sf::Vector2f(c * tileSize, r * tileSize));
                tile.setOutlineThickness(outlineThickness);
                tile.setFillColor(sf::Color(115, 195, 95));
                tile.setOutlineColor(sf::Color(75, 145, 55));
                map.push_back(tile);
            }
        }
    }

    void update(sf::Time time) {
        
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (int i = 0; i < map.size(); i++) {
            target.draw(map[i]);
        }
    }
};