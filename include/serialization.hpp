#pragma once

#include <nlohmann/json.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
// #include <SFML/Graphics/RectangleShape.hpp>
#include <Item.hpp>

using json = nlohmann::json;

struct GameSettings
{
    int width;
    int height;
    std::string title;
};

void to_json(json &j, const sf::Vector2f &v)
{
    j = json { { "x", v.x }, { "y", v.y } };
}

void to_json(json &j, const sf::Color &c)
{
    j = json {
        {"r", c.r},
        {"g", c.g},
        {"b", c.b},
        {"a", c.a}
    };
}

void to_json(json &j, const sf::Transformable &t)
{
    j = json{"position",
             {{"x", t.getPosition().x},
             {"y", t.getPosition().y}}
    };
}

void to_json(json &j, const sf::RectangleShape &r)
{
    j = json {
        {
            "size", //r.getSize()
            { { "x", r.getSize().x }, { "y", r.getSize().y } }
        },
        {
            "position", //r.getPosition()
            { { "x", r.getPosition().x }, { "y", r.getPosition().y } }
        },
        {
            "color", //r.getFillColor()
            { { "r", r.getFillColor().r }, { "g", r.getFillColor().g }, { "b", r.getFillColor().b }, { "a", r.getFillColor().a } }
        }
    };
}



void to_json(json &j, const GameSettings &gs)
{
    j = json {
        {
            "settings", {
                {
                    "width", gs.width
                },
                {
                    "height", gs.height
                },
                {
                    "title", gs.title
                }
            }
        }
    };
}

void from_json(const json &j, GameSettings &gs)
{
    j.at("width").get_to(gs.width);
    j.at("height").get_to(gs.height);
    j.at("title").get_to(gs.title);
}

// void to_json(json &j, const Item &i)
// {
//     j = json {
//         {"size", i.getSize()},
//         {"position", i.getPosition()},
//         {"color", i.getFillColor()}
//     };
// }

void from_json(const json &j, sf::Vector2f &v)
{
    j.at("x").get_to(v.x);
    j.at("y").get_to(v.y);
}

// void from_json(const json &j, Item &i)
// {
//     i.setSize(j.at("size").get<sf::Vector2f&>());
//     i.setPosition(j.at("position").get<sf::Vector2f&>());
// }