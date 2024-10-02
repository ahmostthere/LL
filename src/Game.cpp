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
sf::CircleShape circ_mouse;
HUD Game::hud;

ItemFactory Game::If;

#include "Map.hpp"
Map map = Map();
sf::RectangleShape backpack;
sf::View mainView;
sf::Font manaFont;
sf::Text text;
bool toggleCenter = false;

// ============ TEST ==================

void Game::load()
{
    m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Little Leaf");
    m_window.setVerticalSyncEnabled(true);
    mainView = m_window.getView();
// Map testing
    hud.addItem(&map);

    


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
        hud.addItem(If.createItem(sf::Vector2f(itemSz, itemSz), sf::Vector2f(itemPosX, itemPosY), sf::Color(Rx, Gx, Bx)));
    }







    circle = sf::CircleShape(10);
    circle.setFillColor(sf::Color::Green);

    circ_mouse = sf::CircleShape(5);
    circ_mouse.setFillColor(sf::Color::Red);
    circle.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
    DPadMovable::setDPad(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);


    hud.addItem(&circ_mouse);
    hud.addItem(&circle);
    hud.addItem(&text);
    
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
            currentGameState = GameState::Quit;
            break;
        case sf::Event::KeyPressed:
            switch (currentEvent.key.code)
            {
            case (sf::Keyboard::Escape):
                currentGameState = GameState::Quit;
                break;
            case (sf::Keyboard::Space):
                toggleCenter = !toggleCenter;            
                break;
            case (sf::Keyboard::B):
                std::cout << "circle pos: " << circle.getPosition().x << ", " << circle.getPosition().y << std::endl;
                std::cout << "viewcenter pos: " << mainView.getCenter().x << ", " << mainView.getCenter().y << std::endl;
                std::cout << "defaultviewcenter pos: " << m_window.getDefaultView().getCenter().x << ", " << m_window.getDefaultView().getCenter().y << std::endl;
                
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sf::Vector2f dest_pos = sf::Vector2f(sf::Mouse::getPosition(m_window).x + mainView.getCenter().x - m_window.getDefaultView().getCenter().x,
                                                     sf::Mouse::getPosition(m_window).y + mainView.getCenter().y - m_window.getDefaultView().getCenter().y);
                MouseMovable::setMouseMoveDestination(dest_pos);
                circ_mouse.setPosition(dest_pos); // set destination position marker (red dot)
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
    if (dmove != sf::Vector2f(0, 0))
    {
        MouseMovable::unsetMouseMoveDestination();
        circle.move(dmove);
    }
    else 
    {
        circle.move(MouseMovable::MouseMove(circle.getPosition()) * speed);
    }

    if (toggleCenter)
    {
        mainView.setCenter(circle.getPosition());
        m_window.setView(mainView);
    }
}

void Game::render()
{
    m_window.clear();
    // draw map
    // draw objects in order of y axis (billboarding)
    m_window.draw(hud); // this will be last thing to draw
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
