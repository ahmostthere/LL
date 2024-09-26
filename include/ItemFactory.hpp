#include "Item.hpp"

class ItemFactory 
{
private:

public:
    ~ItemFactory() 
    {

    }
    Item *createItem(const sf::Vector2f &size, sf::Vector2f position, sf::Color color) 
    {
        return new Item(size, position, color);
    }
};