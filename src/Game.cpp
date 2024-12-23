#include "Game.hpp"

#include "DPadMovable.hpp"
#include "MouseMovable.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <serialization.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

sf::RenderWindow Game::m_window;

sf::Clock Game::m_clock;

sf::Time Game::m_time;

Game::GameState Game::currentGameState;


// ============ TEST START ==================
sf::CircleShape Game::circle;

sf::RectangleShape rect_bound;
HUD Game::hud;

float spd, cspd = 0;
sf::CircleShape circ_mouse;
Inventory inventory;

ItemFactory Game::If;

#include "Map.hpp"
Map map = Map();
sf::RectangleShape backpack;
sf::View mainView;
sf::Font manaFont;
sf::Text text;
short move_mode = 0;

json j;


GameSettings gameSettings;

#include "hud/HPBar.hpp"
HPBar hpbar; 
// ============ TEST END ==================

void Game::load()
{
    gameSettings.height = WIN_HEIGHT;
    gameSettings.width = WIN_WIDTH;
    gameSettings.title = "Little Leaf";
    m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Little Leaf");
    m_window.setVerticalSyncEnabled(true);
    mainView = m_window.getView();
// Map testing
    hud.addItem(&map);

    rect_bound.setSize(sf::Vector2f(WIN_WIDTH / 5, WIN_HEIGHT / 5));
    rect_bound.setOrigin(WIN_WIDTH / 10, WIN_HEIGHT / 10);
    rect_bound.setFillColor(sf::Color(100, 100, 255, 40));
    rect_bound.setOutlineColor(sf::Color(80, 80, 255, 60));
    rect_bound.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
    hud.addItem(&rect_bound);

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
    std::cout << text.getLocalBounds().width << ", h: " << text.getLocalBounds().height << std::endl;

// asset file HUD testing
    std::ifstream infile;
    std::string line;
    infile.open("assets/file.txt");
    getline(infile, line);
    std::istringstream ss(line);
    ss >> spd >> cspd;


// parses file.txt
    while (getline(infile, line)) {
        std::istringstream iss(line);
        float itemSz, itemPosX, itemPosY;
        int Rx, Gx, Bx;
        iss >> itemSz >> itemPosX >> itemPosY >> Rx >> Gx >> Bx;
        std::cout << itemSz << " (" << itemPosX << ", " << itemPosY << ") #(" << Rx << Gx << Bx << ")" << std::endl;
        Item* i = If.createItem(sf::Vector2f(itemSz, itemSz), sf::Vector2f(itemPosX, itemPosY), sf::Color(Rx, Gx, Bx));
        hud.addItem(i);
        inventory.items.push_back(*i);
    }
    infile.close();






    circle = sf::CircleShape(25);
    circle.setOrigin(25, 25);
    circle.setFillColor(sf::Color::Blue);

    circ_mouse = sf::CircleShape(5);
    circ_mouse.setOrigin(5, 5);
    circ_mouse.setFillColor(sf::Color::Red);
    circle.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
    DPadMovable::setDPad(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);


    hud.addItem(&circ_mouse);
    hud.addItem(&circle);



    hpbar = HPBar(sf::Vector2f(WIN_WIDTH / 5, WIN_HEIGHT / 20));
    hpbar.setPosition(sf::Vector2f(50, 50));
    hpbar.setHPColor(sf::Color(0x99, 0x22, 0x22));
    hud.addItem(&hpbar);
    // hud.addItem(&text);
    
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
                mainView.setCenter(circle.getPosition());
                m_window.setView(mainView);

                move_mode++;
                if (move_mode > 1)
                    move_mode = 0;
                switch (move_mode)
                {
                case 0:
                    std::cout << "Mouse Move Mode" << std::endl;
                    rect_bound.setFillColor(sf::Color(100, 100, 255, 0));
                    rect_bound.setOutlineColor(sf::Color(80, 80, 255, 0));

                    break;
                case 1:
                    std::cout << "Keyboard Move Mode" << std::endl;

                    rect_bound.setPosition(circle.getPosition());
                    break;
                }
                break;

            case (sf::Keyboard::B):
            {
                
                std::cout << "circle pos: " << circle.getPosition().x << ", " << circle.getPosition().y << std::endl;
                std::cout << "viewcenter pos: " << mainView.getCenter().x << ", " << mainView.getCenter().y << std::endl;
                std::cout << "defaultviewcenter pos: " << m_window.getDefaultView().getCenter().x << ", " << m_window.getDefaultView().getCenter().y << std::endl;

                
                break;
            }

            case (sf::Keyboard::I):
                hpbar.currentHP += 5;
                break;

            case (sf::Keyboard::K):
                hpbar.currentHP -= 5;
                break;

            case (sf::Keyboard::V):
                if (j.empty())
                {
                    time_t now = time(0);

                    std::cout << now << std::endl;
                    std::cout << "write to file\n";
                    std::ofstream file("assets/saves/out_" + std::to_string(now) + ".json", std::ios_base::out | std::ios_base::trunc);
                    if (file.is_open())
                    {
                        j.push_back(gameSettings);
                        for (auto i = 0; i < inventory.items.size(); i++)
                        {
                            j.push_back(inventory.items[i]);
                        }
                        file << j.dump(4);
                        file.close();
                    }
                }
                else
                {
                    std::cout << "already written to file\n";
                }
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
    hpbar.update();
    float speed = spd * m_time.asSeconds();
    float cam_speed = cspd * m_time.asSeconds();
    auto dis = [](const sf::Vector2f &a, const sf::Vector2f &b)
    { 
        sf::Vector2f c(a.x - b.x, a.y - b.y);
        return sqrt((c.x * c.x) + (c.y * c.y));
    };

    auto theta = [](const sf::Vector2f &a, const sf::Vector2f &b)
    {
        sf::Vector2f c(a.x - b.x, a.y - b.y);
        return std::atan2(c.y, c.x);
    };

    auto min = [](float a, float b)
    { return (a < b) ? a : b; };

    auto max = [](float a, float b)
    { return (a < b) ? b : a; };

    switch (move_mode) 
    {
    case 0:
        circle.move(MouseMovable::MouseMove(circle.getPosition()) * speed);
        break;
    case 1:
        circle.move(DPadMovable::DPadMove() * speed);
        if (rect_bound.getPosition().x + rect_bound.getSize().x / 2 <= circle.getPosition().x + circle.getRadius() || rect_bound.getPosition().x - rect_bound.getSize().x / 2 >= circle.getPosition().x - circle.getRadius())
        {
            rect_bound.move(sf::Vector2f(DPadMovable::DPadMove().x, 0) * speed);
            mainView.move(sf::Vector2f(DPadMovable::DPadMove().x, 0) * speed);
        }
        if (rect_bound.getPosition().y + rect_bound.getSize().y / 2 <= circle.getPosition().y + circle.getRadius() || rect_bound.getPosition().y - rect_bound.getSize().y / 2 >= circle.getPosition().y - circle.getRadius())
        {
            rect_bound.move(sf::Vector2f(0, DPadMovable::DPadMove().y) * speed);
            mainView.move(sf::Vector2f(0, DPadMovable::DPadMove().y) * speed);
        }

        if (DPadMovable::DPadMove() == sf::Vector2f(0, 0) && dis(circle.getPosition(), rect_bound.getPosition()) > 5)
        {
            float th = theta(circle.getPosition(), rect_bound.getPosition());
            rect_bound.move(sf::Vector2f(std::cos(th), std::sin(th)) * cam_speed);
            mainView.move(sf::Vector2f(std::cos(th), std::sin(th)) * cam_speed);
        }
        m_window.setView(mainView);
        break;
    default:
        break;
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
