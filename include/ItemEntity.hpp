#pragma once
#include <EllipseShape.hpp>
#include <Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class ItemEntity : public Entity {
public:
    ItemEntity();

    ItemEntity(const sf::Vector2f &size);

    ItemEntity(const sf::Vector2f &size, sf::Color color);

    ItemEntity(const sf::Vector2f &size, sf::Vector2f position, sf::Color color);

    sf::Vector2f getSize() const;

    void setSize(sf::Vector2f size);

    sf::Color getFillColor() const;

    void setFillColor(sf::Color color);

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    void update(sf::Time time);

private:
    sf::RectangleShape m_rect;
    EllipseShape m_ellipse;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_rect, states);
    }
};
