#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>


class Component : public sf::Drawable, public sf::Transformable {
public:
    Component();
    virtual ~Component();
    virtual void update();
private:
    std::vector<Component *> childComponents;
    float size;
    sf::FloatRect rect;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (size_t i = 0; i < childComponents.size(); i++) {
            target.draw(* childComponents[i]);
        }
    }
};

Component::~Component() {
    while (!childComponents.empty()) {
        delete childComponents.back();
        childComponents.pop_back();
    }
}

void Component::update() {
    
}