#include <Component.hpp>

Component::~Component() {
    while (!childComponents.empty()) {
        delete childComponents.back();
        childComponents.pop_back();
    }
}

void Component::update() {}