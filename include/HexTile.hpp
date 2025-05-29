#include <HexagonShape.hpp>

class HexTile : public sf::Drawable {
public:
    HexTile();
    enum HexLink {
        NullLink,
        SoftLink,
        HardLink
    };
    void addTile(HexTile &tile, std::size_t index);

private:
    HexTile* surroundingTiles[6] = {nullptr};
    HexLink links[6] = {NullLink};

};