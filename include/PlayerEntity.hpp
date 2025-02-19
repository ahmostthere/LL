#pragma once
#include <Entity.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <RoundedRectShape.hpp>
#include <EllipseShape.hpp>
#include <DPadMovable.hpp>

class PlayerEntity : public Entity, public DPadMovable {
public:
    PlayerEntity();

    void showIndicator();

    void hideIndicator();

    void setSpeed(float speed);

    float getSpeed() const;

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition() const;

    sf::Vector2f getSize() const;

    void update(sf::Time time);

    void printFace();

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