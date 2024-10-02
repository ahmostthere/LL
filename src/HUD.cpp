#include "HUD.hpp"


HUD::HUD() 
{
    
}

void HUD::addItem(sf::Drawable* item)
{
    HUD_items.push_back(item);
}

std::vector<sf::Drawable*> HUD::HUD_items;