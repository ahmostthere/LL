#pragma once
#include <Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <EllipseShape.hpp>
#include <iostream>


class ItemEntity : public Entity {
private:
    sf::RectangleShape m_rect;
    EllipseShape m_ellipse;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_rect, states);
    }
public:
    ItemEntity() { }

    ItemEntity(const sf::Vector2f &size) : m_rect(sf::RectangleShape(size)) { }

    ItemEntity(const sf::Vector2f &size, sf::Color color) : m_rect(sf::RectangleShape(size)) {
        m_rect.setFillColor(color);
    }

    ItemEntity(const sf::Vector2f &size, sf::Vector2f position, sf::Color color) : m_rect(sf::RectangleShape(size)) {
        m_rect.setPosition(position);
        m_rect.setFillColor(color);
    }

    sf::Vector2f getSize() const {
        return m_rect.getSize();
    }

    void setSize(sf::Vector2f size) {
        m_rect.setSize(size);
    }

    sf::Color getFillColor() const {
        return m_rect.getFillColor();
    }

    void setFillColor(sf::Color color) {
        m_rect.setFillColor(color);
    }

    sf::Vector2f getPosition() const {
        return m_rect.getPosition();
    }

    void setPosition(sf::Vector2f position) {
        m_rect.setPosition(position);
    }

    void update(sf::Time time) {

    }

};
