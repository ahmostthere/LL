#include "HUD.hpp"

HUD::HUD() {}

void HUD::addComponent(sf::Drawable* component) {
    HUD_items.push_back(component);
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < HUD_items.size(); i++) {
        target.draw(*HUD_items[i], states);
    }
}

std::vector<sf::Drawable*> HUD::HUD_items;