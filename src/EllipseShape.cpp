#include <EllipseShape.hpp>
#include <cmath>
#define PI std::acos(-1)

EllipseShape::EllipseShape(sf::Vector2f radii) : m_radii(radii) {
    m_pointCount = 32;
    update();
}

void EllipseShape::setRadii(sf::Vector2f radii) {
    m_radii = radii;
    update();
}

sf::Vector2f EllipseShape::getRadii() const {
    return m_radii;
}

sf::Vector2f EllipseShape::getSize() const {
    return sf::Vector2f(m_radii.x * 2, m_radii.y * 2);
}

void EllipseShape::setPointCount(std::size_t count) {
    m_pointCount = count;
    update();
}

std::size_t EllipseShape::getPointCount() const {
    return m_pointCount;
}

sf::Vector2f EllipseShape::getPoint(std::size_t index) const {
    float theta = index / float(m_pointCount) * PI * 2;
    return m_radii + sf::Vector2f(m_radii.x * std::cos(theta),
                                  m_radii.y * std::sin(theta));
}

sf::Vector2f EllipseShape::getGeometricCenter() const {
    return m_radii;
}
