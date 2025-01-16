#pragma once
#include <Entity.hpp>
#include <ItemEntity.hpp>
#include <memory>
#include <iostream>

class EntityFactory {
public:
    enum class EntityType {
        Item
    };

    virtual Entity* createEntity(EntityType type) {
        switch (type) {
            case EntityType::Item:
                std::cout << "make item";
                return new ItemEntity();
            default:
                return nullptr;                
        }
    }
};
