#include "EntityFactory.hpp"

Entity* EntityFactory::createEntity(EntityType type) {
    switch (type) {
        case EntityType::Item:
            std::cout << "make item";
            return new ItemEntity();
        default:
            return nullptr;
    }
}