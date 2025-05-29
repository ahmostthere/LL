#pragma once

#include <Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Map : public Entity {
public:
    std::vector<sf::RectangleShape> map;
    int rows;
    int columns;
    float tileSize;
    float outlineThickness;

    Map(int row = 50, int col = 50, int sz = 50, int thickness = 1);

    void update(sf::Time time);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};