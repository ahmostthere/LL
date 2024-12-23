#pragma once

#include <SFML/Graphics.hpp>

struct HPBar : public sf::Drawable
{
    HPBar(sf::Vector2f _size = sf::Vector2f(100, 10), float _totalHP = 100, float _currentHP = 100) : totalHP(_totalHP), currentHP(_currentHP), containerSize(_size) {
        init();
    }

    void init() {
        containerBar.setSize(containerSize);
        containerBar.setPosition(position);
        containerBar.setFillColor(sf::Color(0xbb, 0xbb, 0xbb));
        containerBar.setOutlineColor(sf::Color(0xee, 0xee, 0xee));
        containerBar.setOutlineThickness(3);

        currentHPBar.setPosition(position);
        currentHPBar.setFillColor(color);
        update();
    }

    void update() {
        if (currentHP < 0) currentHP = 0;
        if (currentHP > totalHP) currentHP = totalHP;
        float percentHP = currentHP / totalHP;
        currentHPBar.setSize(sf::Vector2f(containerSize.x * percentHP, containerSize.y));
    }

    void setPosition(const sf::Vector2f &_position) {
        position = _position;
        containerBar.setPosition(_position);
        currentHPBar.setPosition(_position);
    }

    void setHPColor(const sf::Color &_color) {
        color = _color;
        currentHPBar.setFillColor(_color);
    }

    float totalHP;
    float currentHP;
    sf::Vector2f position;
    sf::Vector2f containerSize;
    sf::Color color;
    sf::RectangleShape containerBar;
    sf::RectangleShape currentHPBar;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(containerBar);
        target.draw(currentHPBar);
    }
};
