#include <DPadMovable.hpp>
#include <iostream>
#include <cmath>
#define PI std::acos(-1)

sf::Keyboard::Key DPadMovable::upKey = sf::Keyboard::Up;
sf::Keyboard::Key DPadMovable::downKey = sf::Keyboard::Down;
sf::Keyboard::Key DPadMovable::leftKey = sf::Keyboard::Left;
sf::Keyboard::Key DPadMovable::rightKey = sf::Keyboard::Right;
Compass::Direction DPadMovable::m_direction = Compass::Direction::S;

void DPadMovable::setDPad(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right) {
    upKey = up;
    downKey = down;
    leftKey = left;
    rightKey = right;
}

sf::Vector2f DPadMovable::DPadMove() {
        float theta = PI * 1 / 2;
        int code = 0;
        code = (sf::Keyboard::isKeyPressed(upKey) ? (code | 1) : (code & ~1));
        code = (sf::Keyboard::isKeyPressed(leftKey) ? (code | 2) : (code & ~2));
        code = (sf::Keyboard::isKeyPressed(downKey) ? (code | 4) : (code & ~4));
        code = (sf::Keyboard::isKeyPressed(rightKey) ? (code | 8) : (code & ~8));

        switch (code) {
        case 0b1100: // right down
            theta = PI * 1 / 4;
            m_direction = Compass::Direction::SE;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b0100: // down
        case 0b1110: // down
            theta = PI * 2 / 4;
            m_direction = Compass::Direction::S;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b0110: // down left
            theta = PI * 3 / 4;
            m_direction = Compass::Direction::SW;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b0010: // left
        case 0b0111: // left
            theta = PI * 4 / 4;
            m_direction = Compass::Direction::W;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b0011: // up left
            theta = PI * 5 / 4;
            m_direction = Compass::Direction::NW;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b0001: // up
        case 0b1011: // up
            theta = PI * 6 / 4;
            m_direction = Compass::Direction::N;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b1001: // right up
            theta = PI * 7 / 4;
            m_direction = Compass::Direction::NE;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        case 0b1000: // right
        case 0b1101: // right
            theta = PI * 8 / 4;
            m_direction = Compass::Direction::E;
            return sf::Vector2f(std::cos(theta), std::sin(theta));
        // case 0b1010: // nothing
        // case 0b0101: // nothing
        // case 0b1111: // nothing
        default: // nothing
            return sf::Vector2f(0,0);
        }
}


Compass::Direction DPadMovable::getDirection() {
    return m_direction;
}