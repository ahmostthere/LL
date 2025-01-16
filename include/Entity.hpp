#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

class Entity: public sf::Drawable, public sf::Transformable {
public:
    virtual ~Entity() = default;
    virtual void update(sf::Time time) = 0;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};