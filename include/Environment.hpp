#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <Entity.hpp>
#include <vector>
#include <iostream>
#include <memory>

class Environment : public sf::Drawable
{
public:
    Environment();
    ~Environment();
    static void addEntity(Entity* entity);
    static std::vector<Entity*> Entities;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (int i = 0; i < Entities.size(); i++)
        {
            target.draw(*Entities[i], states);
        }
    }
};