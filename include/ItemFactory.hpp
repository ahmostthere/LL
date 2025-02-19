#pragma once

#include <EntityFactory.hpp>
#include <ItemEntity.hpp>
#include <memory>

class ItemFactory : public EntityFactory {
public:
    // static Item* createEntity(const sf::Vector2f &size, sf::Vector2f
    // position, sf::Color color)
    // {
    // return std::unique_ptr<Item>( new Item(size, position, color));
    // }
};