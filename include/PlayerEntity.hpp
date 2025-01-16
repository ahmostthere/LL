#pragma once
#include <Entity.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <DPadMovable.hpp>

class PlayerEntity : public Entity, public DPadMovable {
public:
    PlayerEntity() {
        m_circle.setFillColor(sf::Color::Blue);
        m_circle.setRadius(25);
        m_circle.setOrigin(25, 25);
        setDPad(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
        m_speed = 250;
    }

    void setSpeed(float speed) {
        m_speed = speed;
    }

    float getSpeed() const {
        return m_speed;
    }

    void setPosition(sf::Vector2f position) {
        sf::Transformable::setPosition(position);
        m_circle.setPosition(position);
    }

    sf::Vector2f getPosition() const {
        return sf::Transformable::getPosition();
    }

    float getRadius() const {
        return m_circle.getRadius();
    }

    void update(sf::Time time) {
        sf::Transformable::move(DPadMove() * m_speed * time.asSeconds());
        m_circle.move(DPadMove() * m_speed * time.asSeconds());
    }

private:
    sf::CircleShape m_circle;
    float m_speed;
    sf::Vector2f m_position;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_circle);
    }
};