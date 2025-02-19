#pragma once
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class MouseMovable {
private:
    static sf::Vector2f m_destinationPosition;
    static bool m_isDestSet;

public:
    static void setMouseMoveDestination(sf::Vector2f destinationPosition);
    static void unsetMouseMoveDestination();
    static sf::Vector2f MouseMove(sf::Vector2f currentPosition,
                                  float minDistance = 5);
};