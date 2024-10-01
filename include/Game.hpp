#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "HUD.hpp"
#include "ItemFactory.hpp"

class Game
{
private:
    enum GameState
    {
        Play,
        Quit
    };

    static sf::RenderWindow m_window;
    static sf::Clock m_clock;
    static sf::Time m_time;
    static GameState currentGameState;

    static sf::CircleShape circle;
    static HUD hud;
    static ItemFactory If;

    static void load();
    static void loop();
    static void handleInputs();
    static void update();
    static void render();

public:
    static void start(int mode = 0);
};
