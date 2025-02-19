#pragma once
#include <Entity.hpp>
#include <ItemEntity.hpp>
#include <iostream>
#include <memory>

class EntityFactory {
public:
    enum class EntityType { Item };

    virtual Entity* createEntity(EntityType type);
};
