#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

class MouseMovable
{
private:
    static sf::Transformable *m_target;
    static sf::Vector2f m_destinationPosition;
    static bool m_isMoving;
    static bool m_isDestSet;

public:
    static void setTarget(sf::Transformable &target);
    static void setMouseMoveDestination(const sf::Vector2i &destinationPosition);
    static void resetMouseMoveDestination();
    static bool MouseMove(float offset, float minDistance = .1);
    static bool MouseMove(sf::Transformable &target, float offset, float minDistance = .1);
};