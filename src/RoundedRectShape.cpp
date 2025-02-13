#include <RoundedRectShape.hpp>

RoundedRectShape::RoundedRectShape(sf::Vector2f size, float radius) : m_size(size), m_radius(radius)
{
    auto min = [](float a, float b) { return (a < b) ? a : b; };
    sf::Vector2f halfSize = m_size / 2.f;
    m_radius = (m_radius > min(halfSize.x, halfSize.y)) ? min(halfSize.x, halfSize.y) : radius; 
    m_pointCount = (m_radius == 0) ? 4 : 52;
    update();
}

void RoundedRectShape::setRadius(float radius)
{
    auto min = [](float a, float b) { return (a < b) ? a : b; };
    sf::Vector2f halfSize = m_size / 2.f;
    m_radius = (m_radius > min(halfSize.x, halfSize.y)) ? min(halfSize.x, halfSize.y) : radius; 
    m_pointCount = (m_radius == 0) ? 4 : 52;

    update();
}

float RoundedRectShape::getRadius() const 
{
    return m_radius;
}

void RoundedRectShape::setSize(sf::Vector2f size)
{
    m_size = size;
    update();
}

sf::Vector2f RoundedRectShape::getSize() const 
{
    return m_size;
}

void RoundedRectShape::setPointCount(std::size_t count)
{
    m_pointCount = count;
    update();
}

std::size_t RoundedRectShape::getPointCount() const 
{
    return m_pointCount;
}

sf::Vector2f RoundedRectShape::getPoint(std::size_t index) const
{
    if (m_pointCount == 4) 
    {
        switch (index)
        {
            default:
            case 0:
                return {0, 0};
            case 1:
                return {m_size.x, 0};
            case 2:
                return {m_size.x, m_size.y};
            case 3:
                return {0, m_size.y};
        }
    } 
    else
    {
        std::size_t i = (index) / (m_pointCount / 4);
        float theta = (((index - i) / float(m_pointCount - 4)) * PI * 2) + PI;
        sf::Vector2f ret = sf::Vector2f(m_radius * std::cos(theta), m_radius * std::sin(theta));
        switch (i)
        {
            default:
            case 0: 
                return ret + sf::Vector2f(m_radius, m_radius);
            case 1:
                return ret + sf::Vector2f(m_size.x - m_radius, m_radius);
            case 2:
                return ret + sf::Vector2f(m_size.x - m_radius, m_size.y - m_radius);
            case 3:
                return ret + sf::Vector2f(m_radius, m_size.y - m_radius);;
        }
    }
}

sf::Vector2f RoundedRectShape::getGeometricCenter() const
{
    return m_size / 2.f;
}