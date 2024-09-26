#include "Game.hpp"
#include "DPadMovable.hpp"
#include "MouseMovable.hpp"

#include <iostream>

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

sf::RenderWindow Game::m_window;

sf::Clock Game::m_clock;

sf::Time Game::m_time;

Game::GameState Game::currentGameState;

HUD Game::hud;

// ============ TEST ==================
sf::CircleShape Game::circle;

Item item;
Item item2(sf::Vector2f(50, 50), sf::Color(0x33, 0x99, 0xaa));

sf::RectangleShape backpack;

sf::Font manaFont;
sf::Text text;

// ============ TEST ==================

void Game::load()
{
    m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Little Leaf");
    m_window.setVerticalSyncEnabled(true);
    if (!manaFont.loadFromFile("assets/fonts/retganon.ttf"))
    {
        std::cout << "SUCKS" << std::endl;
    }
    text.setFont(manaFont);
    text.setString("Item");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(36);
    text.setPosition(1500, 350);

    item.setFillColor(sf::Color::Yellow);
    item.setPosition(250, 250);
    item2.setPosition(1500, 300);






    circle = sf::CircleShape(10);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
    MouseMovable::setTarget(circle);
    DPadMovable::setTarget(circle);
    DPadMovable::setDPad(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);


    hud.HUD_items.push_back(&circle);
    hud.HUD_items.push_back(&text);
    hud.HUD_items.push_back(&item);
    hud.HUD_items.push_back(&item2);
}


void Game::loop()
{
    while (currentGameState != GameState::Quit)
    {
        m_time = m_clock.restart();
        handleInputs();
        update();
        render();
    }
    m_window.close();
}

void Game::handleInputs()
{
    sf::Event currentEvent;
    while (m_window.pollEvent(currentEvent))
    {
        switch (currentEvent.type)
        {
        case sf::Event::Closed:
            std::cout << "closing" << std::endl;
            currentGameState = GameState::Quit;
            break;
        case sf::Event::KeyPressed:
            // std::cout << "key pressed" << std::endl;
            switch (currentEvent.key.code)
            {
            case (sf::Keyboard::Escape):
                currentGameState = GameState::Quit;
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                MouseMovable::setMouseMoveDestination(sf::Mouse::getPosition(m_window));
            }
        default:
            break;
        }
    }
}

void Game::update()
{
    float offset = 250 * m_time.asSeconds();
    if (DPadMovable::DPadMove(offset)) 
    {
        MouseMovable::resetMouseMoveDestination();
    }
    else if (MouseMovable::MouseMove(offset)) {;}
}

void Game::render()
{
    m_window.clear();
    // m_window.draw(item);
    // m_window.draw(circle);
    // m_window.draw(item2);
    // m_window.draw(text);
    m_window.draw(hud);
    m_window.display();
}

void Game::start(int mode)
{
    switch (mode)
    {
    case 0:
        currentGameState = GameState::Play;
        load();
        loop();
        break;
    case 1:
        // menu?
        break;
    default:
        break;
    }
}
