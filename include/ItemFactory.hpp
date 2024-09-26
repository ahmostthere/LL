#include "Item.hpp"
#include <iostream>
class ItemFactory 
{
private:

public:
    ~ItemFactory() 
    {

    }
    Item *createItem(const sf::Vector2f &size, sf::Vector2f position, sf::Color color) 
    {

        std::cout << "hi" << std::endl;
        return new Item(size, position, color);
    }
};