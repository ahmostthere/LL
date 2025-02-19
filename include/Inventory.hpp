#pragma once

#include <Entity.hpp>
#include <ItemEntity.hpp>
#include <vector>

class Inventory {
public:
    std::vector<ItemEntity> items;
};