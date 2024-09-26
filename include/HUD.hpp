#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

class HUD : public sf::Drawable
{
public:
    HUD();
    static std::vector<sf::Drawable *> HUD_items;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (int i = 0; i < HUD_items.size(); i++)
        {
            target.draw(*HUD_items[i], states);
        }
    }
};