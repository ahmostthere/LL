#include <Map.hpp>
#include <iostream>

Map::Map(int row, int col, int sz, int thickness)
: rows(row), columns(col), tileSize(sz), outlineThickness(thickness) {
    sf::Vector2f size(tileSize - outlineThickness, tileSize - outlineThickness);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            sf::RectangleShape tile(sf::Vector2f(tileSize - outlineThickness,
                                                 tileSize - outlineThickness));
            tile.setPosition(sf::Transformable::getPosition() +
                             sf::Vector2f(c * tileSize, r * tileSize));
            tile.setOutlineThickness(outlineThickness);
            tile.setFillColor(sf::Color(115, 195, 95));
            tile.setOutlineColor(sf::Color(75, 145, 55));
            map.push_back(tile);
        }
    }
}

void Map::update(sf::Time time) {}