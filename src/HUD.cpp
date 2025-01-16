#include "HUD.hpp"


HUD::HUD() 
{
    
}

void HUD::addComponent(sf::Drawable* component)
{
    HUD_items.push_back(component);
}

std::vector<sf::Drawable*> HUD::HUD_items;