#pragma once

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cstddef>

class HexagonShape : public sf::Shape {
public:
    explicit HexagonShape(float radius = 0, float cornerRadius = 0); 
    void setRadius(float radius);
    float getRadius() const;
    void setCornerRadius(float cornerRadius);
    float getCornerRadius() const;
    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;
    sf::Vector2f getGeometricCenter() const;

private:
    float m_radius;
    float m_cornerRadius;
    std::size_t m_pointCount;
};