#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game {
private:
    enum GameState { Play, Quit };

    static sf::RenderWindow m_window;
    static sf::Clock m_clock;
    static sf::Time m_time;
    static GameState currentGameState;

    static void load();
    static void loop();
    static void handleInputs();
    static void update();
    static void render();

public:
    static void start(int mode = 0);
};