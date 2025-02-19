#pragma once

#include <RoundedRectShape.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>
// #include <EllipseShape.hpp>
#include <Inventory.hpp>
#include <ItemEntity.hpp>
#include <ItemFactory.hpp>

using json = nlohmann::json;

struct GameSettings {
    int width;
    int height;
    std::string title;
    float cameraSpeed;
    std::string playerSettingsFile;
    std::string fontFile;
};

struct PlayerSettings {
    float speed;
    float size;
    sf::Vector2f position;
    sf::Color color;
};

#include <cmath>

auto theta = [](const sf::Vector2f &a, const sf::Vector2f &b) {
    sf::Vector2f c(a.x - b.x, a.y - b.y);
    return std::atan2(c.y, c.x);
};

auto dis = [](const sf::Vector2f &a, const sf::Vector2f &b) {
    sf::Vector2f c(a.x - b.x, a.y - b.y);
    return sqrt((c.x * c.x) + (c.y * c.y));
};

auto min = [](float a, float b) { return (a < b) ? a : b; };

auto max = [](float a, float b) { return (a < b) ? b : a; };

namespace sf {

// ============================= Vector2f =============================
void to_json(json &j, const sf::Vector2f &vec) {
    j = {vec.x, vec.y};
}

void from_json(const json &j, sf::Vector2f &vec) {
    vec.x = j[0];
    vec.y = j[1];
}

// ============================= Color =============================
void to_json(json &j, const sf::Color &c) {
    j = {c.r, c.g, c.b, c.a};
}

void from_json(const json &j, sf::Color &color) {
    color.r = j[0];
    color.g = j[1];
    color.b = j[2];
    color.a = j[3];
}

// ============================= Rectangle =============================
void to_json(json &j, const sf::RectangleShape &r) {
    j["size"] = r.getSize();
    j["position"] = r.getPosition();
    j["color"] = r.getFillColor();
}

void from_json(const json &j, sf::RectangleShape &r) {
    r.setSize(j.at("size").get<sf::Vector2f>());
    r.setPosition(j.at("position").get<sf::Vector2f>());
    r.setFillColor(j.at("color").get<sf::Color>());
}

}  // namespace sf

// ============================= Settings =============================
void to_json(json &j, const GameSettings &gs) {
    j["settings"] = {{"width", gs.width},
                     {"height", gs.height},
                     {"title", gs.title},
                     {"cameraSpeed", gs.cameraSpeed},
                     {"playerSettingsFile", gs.playerSettingsFile},
                     {"fontFile", gs.fontFile}};
}

void from_json(const json &j, GameSettings &gs) {
    j.at("width").get_to(gs.width);
    j.at("height").get_to(gs.height);
    j.at("title").get_to(gs.title);
    j.at("cameraSpeed").get_to(gs.cameraSpeed);
    j.at("playerSettingsFile").get_to(gs.playerSettingsFile);
    j.at("fontFile").get_to(gs.fontFile);
}

void to_json(json &j, const PlayerSettings &ps) {
    j["player"] = {{"speed", ps.speed},
                   {"size", ps.size},
                   {"position", ps.position},
                   {"color", ps.color}};
}

void from_json(const json &j, PlayerSettings &ps) {
    j.at("speed").get_to(ps.speed);
    j.at("size").get_to(ps.size);
    j.at("position").get_to(ps.position);
    j.at("color").get_to(ps.color);
}

// ============================= RoundRectangle =============================
void to_json(json &j, const RoundedRectShape &rr) {
    j["size"] = rr.getSize();
    j["radius"] = rr.getRadius();
    j["position"] = rr.getPosition();
    j["color"] = rr.getFillColor();
}

void from_json(const json &j, RoundedRectShape &rr) {
    rr.setSize(j.at("size").get<sf::Vector2f>());
    rr.setRadius(j.at("radius").get<float>());
    rr.setPosition(j.at("position").get<sf::Vector2f>());
    rr.setFillColor(j.at("color").get<sf::Color>());
}

// ============================= EllipseShape =============================
// void to_json(json &j, const EllipseShape &es) {
//     j["radii"] = es.getRadii();
//     j["size"] = es.getSize();
//     j["position"] = es.getPosition();
//     j["color"] = es.getFillColor();
// }

// void from_json(const json &j, EllipseShape &es) {
//     es.setRadii(j.at("radii").get<sf::Vector2f>());
//     es.setPosition(j.at("position").get<sf::Vector2f>());
//     es.setFillColor(j.at("color").get<sf::Color>());
// }

// ============================= Entity =============================
void to_json(json &j, const Entity &ent) {}

void from_json(const json &j, Entity &ent) {}

// ============================= Map =============================

// ============================= Item =============================
void to_json(json &j, const ItemEntity &i) {
    j["size"] = i.getSize();
    j["position"] = i.getPosition();
    j["color"] = i.getFillColor();
}

void from_json(const json &j, ItemEntity &i) {
    i.setSize(j["size"].get<sf::Vector2f>());
    i.setPosition(j["position"].get<sf::Vector2f>());
    i.setFillColor(j["color"].get<sf::Color>());
}

// ============================= Inventory =============================
void to_json(json &j, const Inventory &in) {
    j["items"] = in.items;
}

void from_json(const json &j, Inventory &in) {
    in.items = j.get<std::vector<ItemEntity>>();
}