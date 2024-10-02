#include "MouseMovable.hpp"
#include <cmath>
#include <iostream>

sf::Vector2f MouseMovable::m_destinationPosition = sf::Vector2f(0, 0);
float move_distance;
float move_theta;
bool MouseMovable::m_isDestSet = false;

float getTheta(const sf::Vector2f &a, const sf::Vector2f &b)
{
    sf::Vector2f c(a.x - b.x, a.y - b.y);
    return std::atan2(c.y, c.x);
}

float getDistance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    sf::Vector2f c(a.x - b.x, a.y - b.y);
    return sqrt((c.x * c.x) + (c.y * c.y));
}

void MouseMovable::setMouseMoveDestination(const sf::Vector2f &destinationPosition)
{
    m_destinationPosition = destinationPosition;
    m_isDestSet = true;
}

void MouseMovable::unsetMouseMoveDestination()
{
    m_isDestSet = false;
}

sf::Vector2f MouseMovable::MouseMove(const sf::Vector2f &currentPosition, float minDistance)
{
    float theta = getTheta(m_destinationPosition, currentPosition);
    float distance = getDistance(m_destinationPosition, currentPosition);
    if (distance > minDistance && m_isDestSet)
    {
        return sf::Vector2f(std::cos(theta), std::sin(theta));
    }
    else
    {
        m_isDestSet = false;
    }
    return sf::Vector2f(0,0);
}
