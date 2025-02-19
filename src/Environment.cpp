#include "Environment.hpp"

Environment::Environment() {}

Environment::~Environment() {}

void Environment::addEntity(Entity* entity) {
    Entities.push_back(entity);
}

std::vector<Entity*> Environment::Entities;