#pragma once
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cmath>
#include <iostream>
#define PI std::acos(-1)

class EllipseShape : public sf::Shape {
public:
    explicit EllipseShape(sf::Vector2f radii = sf::Vector2f(0,0));
    void setRadii(sf::Vector2f radii);
    sf::Vector2f getRadii() const;
    sf::Vector2f getSize() const;
    void setPointCount(std::size_t count);
    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;
    sf::Vector2f getGeometricCenter() const;

private:
    sf::Vector2f m_radii;
    std::size_t m_pointCount;
};

