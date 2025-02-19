#pragma once

#include <Entity.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <memory>
#include <vector>

class Environment : public sf::Drawable {
public:
    Environment();
    ~Environment();
    static void addEntity(Entity* entity);
    static std::vector<Entity*> Entities;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (int i = 0; i < Entities.size(); i++) {
            target.draw(*Entities[i], states);
        }
    }
};