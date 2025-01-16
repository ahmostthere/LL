#pragma once
#include <vector>
#include <Entity.hpp>
#include <ItemEntity.hpp>

class Inventory {
public:
    std::vector<ItemEntity> items;
};