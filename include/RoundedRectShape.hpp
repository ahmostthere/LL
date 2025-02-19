#pragma once
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <cstddef>
#include <iostream>
#define PI std::acos(-1)

class RoundedRectShape : public sf::Shape {
public:
    explicit RoundedRectShape(sf::Vector2f size = sf::Vector2f(0, 0),
                              float radius = 0);
    void setRadius(float radius);
    float getRadius() const;
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    void setPointCount(std::size_t count);
    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;
    sf::Vector2f getGeometricCenter() const;

private:
    sf::Vector2f m_size;
    float m_radius;
    std::size_t m_pointCount;
};