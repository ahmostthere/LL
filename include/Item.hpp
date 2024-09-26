#pragma once
// #include <SFML/Graphics/RenderTarget.hpp>
// #include <SFML/Graphics/Drawable.hpp>
// #include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

// class Item : public sf::Drawable, public sf::Transformable
class Item : public sf::RectangleShape
{
private:
    // sf::RectangleShape m_item;
    // virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    // {
    //     target.draw(m_item, states);
    //     // target.draw(m_mouseMove, states);
    // }
public:
    Item() : sf::RectangleShape(sf::Vector2f(40, 40))
    {
    }

    Item(const sf::Vector2f &size) : sf::RectangleShape(size)
    {

    }

    Item(const sf::Vector2f &size, sf::Color color) : sf::RectangleShape(size)
    {
        sf::RectangleShape::setFillColor(color);
    }

    Item(const sf::Vector2f &size, sf::Vector2f position, sf::Color color) : sf::RectangleShape(size)
    {
        std::cout << "hello" << std::endl;
        sf::RectangleShape::setPosition(position);
        sf::RectangleShape::setFillColor(color);
    }
};