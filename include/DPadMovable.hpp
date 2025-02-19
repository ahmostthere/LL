#pragma once

#include <Compass.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class DPadMovable {
private:
    static sf::Keyboard::Key upKey;
    static sf::Keyboard::Key downKey;
    static sf::Keyboard::Key leftKey;
    static sf::Keyboard::Key rightKey;
    static Compass::Direction m_direction;

public:
    static void setDPad(sf::Keyboard::Key up = sf::Keyboard::Up,
                        sf::Keyboard::Key down = sf::Keyboard::Down,
                        sf::Keyboard::Key left = sf::Keyboard::Left,
                        sf::Keyboard::Key right = sf::Keyboard::Right);
    static sf::Vector2f DPadMove();
    static Compass::Direction getDirection();
};
