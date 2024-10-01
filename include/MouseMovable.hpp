#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

class MouseMovable
{
private:
    static sf::Vector2f m_destinationPosition;
    static bool m_isDestSet;

public:
    static void setMouseMoveDestination(const sf::Vector2i &destinationPosition);
    static void unsetMouseMoveDestination();
    static sf::Vector2f MouseMove(const sf::Vector2f &currentPosition, float minDistance = 5);
};