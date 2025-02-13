#pragma once
#include <Entity.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <RoundedRectShape.hpp>
#include <EllipseShape.hpp>
#include <DPadMovable.hpp>

class PlayerEntity : public Entity, public DPadMovable {
public:
    PlayerEntity() {
        m_range = 100;
        m_indicator.setRadius(m_range);
        m_indicator.setFillColor(sf::Color(75, 200, 230));
        m_indicator.setOrigin(100, 100);
        m_indicator.setOutlineColor(sf::Color(150, 235, 255));
        m_indicator.setOutlineThickness(5);
        m_showIndicator = false;

        m_face.setRadius(5);
        m_face.setFillColor(sf::Color::Red);
        m_face.setOrigin(5, 80);

        m_rect.setSize(sf::Vector2f(50, 80));
        m_rect.setRadius(15);
        m_rect.setFillColor(sf::Color(15, 115, 225));
        m_rect.setOrigin(50/2, 80);

        m_ellipse.setFillColor(sf::Color(0, 0, 0, 255 * .3));
        m_ellipse.setRadii(sf::Vector2f(25, 18));
        m_ellipse.setOrigin(m_ellipse.getGeometricCenter());

        setDPad(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
        m_speed = 250;
    }

    void showIndicator() {
        m_showIndicator = true;
    }

    void hideIndicator() {
        m_showIndicator = false;
    }

    void setSpeed(float speed) {
        m_speed = speed;
    }

    float getSpeed() const {
        return m_speed;
    }

    void setPosition(sf::Vector2f position) {
        sf::Transformable::setPosition(position);
        m_rect.setPosition(position);
        m_ellipse.setPosition(position);
        m_face.setPosition(position);
    }

    sf::Vector2f getPosition() const {
        return sf::Transformable::getPosition();
    }

    sf::Vector2f getSize() const {
        return m_ellipse.getSize();
    }

    void update(sf::Time time) {
        sf::Vector2f spd = DPadMove() * m_speed * time.asSeconds();
        sf::Transformable::move(spd);
        m_rect.move(spd);
        m_ellipse.move(spd);
        m_face.move(spd);


        Compass::Direction facing = DPadMovable::getDirection();
        m_face.setOrigin(5 - std::cos(Compass::toRadian(facing)) * 25, 72 - std::sin(Compass::toRadian(facing)) * 18);
    }

    void printFace() {
        Compass::Direction facing = DPadMovable::getDirection();
        switch (facing) {
            case Compass::Direction::E:
                std::cout << "Facing East" << std::endl;
                break;
            case Compass::Direction::SE:
                std::cout << "Facing Southeast" << std::endl;
                break;
            case Compass::Direction::S:
                std::cout << "Facing South" << std::endl;
                break;
            case Compass::Direction::SW:
                std::cout << "Facing Southwest" << std::endl;
                break;
            case Compass::Direction::W:
                std::cout << "Facing West" << std::endl;
                break;
            case Compass::Direction::NW:
                std::cout << "Facing Northwest" << std::endl;
                break;
            case Compass::Direction::N:
                std::cout << "Facing North" << std::endl;
                break;
            case Compass::Direction::NE:
                std::cout << "Facing Northeast" << std::endl;
                break;
        }
    }

private:
    sf::CircleShape m_face;
    sf::CircleShape m_indicator;
    RoundedRectShape m_rect;
    EllipseShape m_ellipse;
    sf::Vector2f m_position;
    bool m_showIndicator;
    float m_speed;
    float m_range;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        if (m_showIndicator) {
            target.draw(m_indicator);
        }
        target.draw(m_ellipse);
        target.draw(m_rect);
        target.draw(m_face);
    }
};