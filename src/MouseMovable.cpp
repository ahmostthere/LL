#include "MouseMovable.hpp"
#include <cmath>
#include <iostream>

sf::Transformable *MouseMovable::m_target = nullptr;
sf::Vector2f MouseMovable::m_destinationPosition = sf::Vector2f(0, 0);
bool MouseMovable::m_isMoving = false;
bool MouseMovable::m_isDestSet = false;

void MouseMovable::setTarget(sf::Transformable &target)
{
    m_target = &target;
    m_destinationPosition = m_target->getPosition();
}

void MouseMovable::setMouseMoveDestination(const sf::Vector2i &destinationPosition)
{
    m_destinationPosition = sf::Vector2f(destinationPosition);
    m_isDestSet = true;
}

void MouseMovable::resetMouseMoveDestination()
{
    m_isDestSet = false;
    if (m_target != nullptr) 
    {
        m_destinationPosition = m_target->getPosition();
    } 
    else 
    {
        m_destinationPosition = sf::Vector2f(0, 0);
    }
}

bool MouseMovable::MouseMove(float offset, float minDistance)
{
    if (m_target != nullptr)
    {
        sf::Vector2f posDif = m_destinationPosition - m_target->getPosition();
        float theta = std::atan2(posDif.y, posDif.x);
        float distance = sqrt((posDif.x * posDif.x) + (posDif.y * posDif.y));
        if (distance > minDistance)
        {
            m_isMoving = true;
        }
        else
        {
            m_isMoving = false;
            m_isDestSet = false;
            m_destinationPosition = m_target->getPosition();
        }

        if (m_isDestSet && m_isMoving)
        {
            std::cout << "moving now" << std::endl;
            m_target->move(std::cos(theta) * offset, std::sin(theta) * offset);
            return true;
        }
        return false;
    }
    return false;
}

bool MouseMovable::MouseMove(sf::Transformable &target, float offset, float minDistance)
{
    sf::Vector2f posDif = m_destinationPosition - target.getPosition();
    float theta = std::atan2(posDif.y, posDif.x);
    float distance = sqrt((posDif.x * posDif.x) + (posDif.y * posDif.y));
    if (distance > minDistance)
    {
        m_isMoving = true;
    }
    else
    {
        m_isMoving = false;
        m_destinationPosition = target.getPosition();
    }

    if (m_isMoving)
    {
        std::cout << "moving now" << std::endl;
        target.move(std::cos(theta) * offset, std::sin(theta) * offset);
        return true;
    }
    return false;
}
