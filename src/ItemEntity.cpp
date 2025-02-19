#include <ItemEntity.hpp>
#include <iostream>

ItemEntity::ItemEntity() {}

ItemEntity::ItemEntity(const sf::Vector2f &size)
: m_rect(sf::RectangleShape(size)) {}

ItemEntity::ItemEntity(const sf::Vector2f &size, sf::Color color)
: m_rect(sf::RectangleShape(size)) {
    m_rect.setFillColor(color);
}

ItemEntity::ItemEntity(const sf::Vector2f &size, sf::Vector2f position,
                       sf::Color color)
: m_rect(sf::RectangleShape(size)) {
    m_rect.setPosition(position);
    m_rect.setFillColor(color);
}

sf::Vector2f ItemEntity::getSize() const {
    return m_rect.getSize();
}

void ItemEntity::setSize(sf::Vector2f size) {
    m_rect.setSize(size);
}

sf::Color ItemEntity::getFillColor() const {
    return m_rect.getFillColor();
}

void ItemEntity::setFillColor(sf::Color color) {
    m_rect.setFillColor(color);
}

sf::Vector2f ItemEntity::getPosition() const {
    return m_rect.getPosition();
}

void ItemEntity::setPosition(sf::Vector2f position) {
    m_rect.setPosition(position);
}

void ItemEntity::update(sf::Time time) {}