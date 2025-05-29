#include <HexagonShape.hpp>
#include <cmath>
#include <iostream>
#define PI std::acos(-1)

HexagonShape::HexagonShape(float radius, float cornerRadius)
: m_radius(radius),
  m_cornerRadius(cornerRadius > radius ? radius : cornerRadius),
  m_pointCount(cornerRadius ? 54 : 6) {
    update();
}

void HexagonShape::setRadius(float radius) {
    m_radius = radius;
    update();
}

float HexagonShape::getRadius() const {
    return m_radius;
}

void HexagonShape::setCornerRadius(float cornerRadius) {
    m_cornerRadius = cornerRadius > m_radius ? m_radius : cornerRadius;
    m_pointCount = cornerRadius ? 54 : 6;
    update();
}

float HexagonShape::getCornerRadius() const {
    return m_cornerRadius;
}

std::size_t HexagonShape::getPointCount() const {
    return m_pointCount;
}

sf::Vector2f HexagonShape::getPoint(std::size_t index) const {
    float height = m_radius * sqrt(3) / 2;
    sf::Vector2f offset = sf::Vector2f(m_radius, height);

    if (m_pointCount == 6) {
        float theta = (index / float(m_pointCount) * PI * 2) + PI;
        float dx = m_radius * std::cos(theta);
        float dy = m_radius * std::sin(theta);
        sf::Vector2f ret = sf::Vector2f(dx, dy);
        return ret + offset;

    } else {
        std::size_t i = (index) / (m_pointCount / 6);
        float theta_cr = (((index - i) / float(m_pointCount - 6)) * PI * 2) + PI - PI/6;
        float dx_cr = m_cornerRadius * std::cos(theta_cr);
        float dy_cr = m_cornerRadius * std::sin(theta_cr);
        sf::Vector2f ret = sf::Vector2f(dx_cr, dy_cr);

        float theta_i = (i / float(6) * PI * 2) + PI;
        float dx_i = (m_radius - m_cornerRadius) * std::cos(theta_i);
        float dy_i = (m_radius - m_cornerRadius) * std::sin(theta_i);
        sf::Vector2f offset_i = sf::Vector2f(dx_i, dy_i);
        
        return ret + offset_i + offset;
    }
}

sf::Vector2f HexagonShape::getGeometricCenter() const {
    float height = m_radius * sqrt(3) / 2;
    return sf::Vector2f(m_radius, height);
}