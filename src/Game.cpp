#include "Game.hpp"
#include "DPadMovable.hpp"
#include "MouseMovable.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

sf::RenderWindow Game::m_window;

sf::Clock Game::m_clock;

sf::Time Game::m_time;

Game::GameState Game::currentGameState;


// ============ TEST ==================
sf::CircleShape Game::circle;
HUD Game::hud;

ItemFactory Game::If;

#include "Map.hpp"
Map map = Map();
sf::RectangleShape backpack;
sf::View mainView;
sf::Font manaFont;
sf::Text text;

// ============ TEST ==================

void Game::load()
{
    m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Little Leaf");
    m_window.setVerticalSyncEnabled(true);
    mainView = m_window.getView();

// Map testing
    hud.HUD_items.push_back(&map);

    


// Text testing
        if (!manaFont.loadFromFile("assets/fonts/retganon.ttf"))
    {
        std::cout << "SUCKS" << std::endl;
    }
    text.setFont(manaFont);
    text.setString("Item");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(36);
    text.setPosition(1500, 350);



// asset file HUD testing
    std::ifstream infile;
    std::string line;
    infile.open("assets/file.txt");
    while (getline(infile, line)) {
        std::istringstream iss(line);
        float itemSz, itemPosX, itemPosY;
        int Rx, Gx, Bx;
        iss >> itemSz >> itemPosX >> itemPosY >> Rx >> Gx >> Bx;
        std::cout << itemSz << " (" << itemPosX << ", " << itemPosY << ") #(" << Rx << Gx << Bx << ")" << std::endl;
        hud.HUD_items.push_back(If.createItem(sf::Vector2f(itemSz, itemSz), sf::Vector2f(itemPosX, itemPosY), sf::Color(Rx, Gx, Bx)));
    }







    circle = sf::CircleShape(10);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
    DPadMovable::setDPad(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);


    hud.HUD_items.push_back(&circle);
    hud.HUD_items.push_back(&text);
    
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
            case (sf::Keyboard::Space):
                mainView.setCenter(circle.getPosition());
                m_window.setView(mainView);

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
    float speed = 250 * m_time.asSeconds();
    sf::Vector2f dmove = DPadMovable::DPadMove() * speed;
    if (dmove != sf::Vector2f(0, 0)) // != sf::Vector2f(0, 0))
    {
        MouseMovable::unsetMouseMoveDestination();
        circle.move(dmove);
    }
    else 
    {
        circle.move(MouseMovable::MouseMove(circle.getPosition()) * speed);
    }
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
