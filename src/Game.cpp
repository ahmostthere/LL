#include "Game.hpp"

#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <serialization.hpp>

#include <DPadMovable.hpp>
#include <MouseMovable.hpp>
#include <CameraBound.hpp>
#include <HUD.hpp>
#include <Environment.hpp>
#include <ItemFactory.hpp>
#include <Inventory.hpp>
#include <EntityFactory.hpp>
#include <PlayerEntity.hpp>


sf::RenderWindow Game::m_window;

sf::Clock Game::m_clock;

sf::Time Game::m_time;

Game::GameState Game::currentGameState;


// ============ TEST START ==================
ItemFactory If;
EntityFactory entFact;
Inventory inv;

PlayerEntity player;
CameraBound camBound(sf::Vector2f(0, 0));

HUD hud;
Environment environment;

float spd = 0;
float cspd = 0;
Inventory inventory;

#include "Map.hpp"
Map map = Map();
sf::View mainView;
sf::View hudView;
sf::Font manaFont;
sf::Text text;

json j;
json j_ps;

GameSettings gameSettings;

#include "hud/HPBar.hpp"
HPBar hpbar; 

#include "RoundedRectShape.hpp"
RoundedRectShape backpack;

// ============ TEST END ==================

void Game::load() {
// Load json testing
    j = json::parse(std::ifstream("assets/saves/saveFile.json"));
    std::cout << j.dump(4) << std::endl;
    
    gameSettings = j.at("settings");
    j_ps = json::parse(std::ifstream(gameSettings.playerSettingsFile));

    m_window.create(sf::VideoMode(gameSettings.width, gameSettings.height), gameSettings.title);
    m_window.setVerticalSyncEnabled(true);
    
    mainView = m_window.getView();

    hudView = m_window.getView();

// Map testing
    environment.addEntity(&map);

// CameraBounds testing
    camBound = CameraBound(sf::Vector2f(gameSettings.width, gameSettings.height));
    camBound.setCameraView(&mainView);
    camBound.setSubject(&player);
    hud.addComponent(&camBound);

// Inventory testing
    inv = j.at("items");
    for (int s = 0; s < inv.items.size(); s++) {
        environment.addEntity(&inv.items[s]);
    }

// Text testing
    if (!manaFont.loadFromFile(gameSettings.fontFile)) {
        std::cout << "SUCKS" << std::endl;
    }
    text.setFont(manaFont);
    text.setString("Item");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(36);
    text.setPosition(1500, 350);
    hud.addComponent(&text);

    player.setPosition(sf::Vector2f(gameSettings.width / 2, gameSettings.height / 2));
    environment.addEntity(&player);

// HP Bar
    hpbar = HPBar(sf::Vector2f(gameSettings.width / 5, gameSettings.height / 20));
    hpbar.setPosition(sf::Vector2f(50, 50));
    hpbar.setHPColor(sf::Color(0x99, 0x22, 0x22));
    hud.addComponent(&hpbar);

// Round Rectangle 
    backpack = j.at("backpack");
    hud.addComponent(&backpack);

}


void Game::loop() {
    while (currentGameState != GameState::Quit) {
        m_time = m_clock.restart();
        handleInputs();
        update();
        render();
    }
    m_window.close();
}

void Game::handleInputs() {
    sf::Event currentEvent;
    while (m_window.pollEvent(currentEvent)) {
        switch (currentEvent.type) {
        case sf::Event::Closed:
            currentGameState = GameState::Quit;
            break;
        case sf::Event::KeyPressed:
            switch (currentEvent.key.code) {
            case (sf::Keyboard::Escape):
                currentGameState = GameState::Quit;
                break;

            case (sf::Keyboard::Space):
                camBound.setPosition(mainView.getCenter().x - camBound.getSize().x/2, mainView.getCenter().y - camBound.getSize().y/2);
                break;

            case (sf::Keyboard::P): {
                std::cout << "viewcenter pos: " << mainView.getCenter().x << ", " << mainView.getCenter().y << std::endl;
                std::cout << "defaultviewcenter pos: " << m_window.getDefaultView().getCenter().x << ", " << m_window.getDefaultView().getCenter().y << std::endl;
                std::cout << "hudviewcenter pos: " << hudView.getCenter().x << ", " << hudView.getCenter().y << std::endl;
                std::cout << "camBound pos: " << camBound.getPosition().x << ", " << camBound.getPosition().y << std::endl;
                break;
            }

            case (sf::Keyboard::Y):
                if (camBound.isShowBound)
                {
                    camBound.hideBound();
                }
                else
                {
                    camBound.showBound();
                }
                break;
            
            case (sf::Keyboard::T): // toggle boundary lock
                if (camBound.bound) {
                    camBound.unboundSubject();
                } else {
                    camBound.boundSubject();
                }
                break;

            case (sf::Keyboard::F):
                player.printFace();
                break;
 
            case (sf::Keyboard::I):
                hpbar.currentHP += 5;
                break;

            case (sf::Keyboard::K):
                hpbar.currentHP -= 5;
                break;

            case (sf::Keyboard::V): {
                    // std::cout << "already written to file\n";
                    
                    
                    json j2;
                    time_t now = time(0);

                    std::cout << now << std::endl;
                    std::cout << "write to file\n";
                    std::ofstream file("assets/saves/" + std::to_string(now) + "_out.json", std::ios_base::out | std::ios_base::trunc);
                    if (file.is_open()) {
                        j2.update(gameSettings);
                        j2["items"] = json::array();
                        for (auto i = 0; i < inventory.items.size(); i++)
                        {
                            j2["items"].push_back(inventory.items[i]);
                        }
                        file << j2.dump(4);
                        file.close();
                    }
                }
                break;

            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                sf::Vector2f dest_pos = sf::Vector2f(sf::Mouse::getPosition(m_window).x + mainView.getCenter().x - m_window.getDefaultView().getCenter().x,
                                                     sf::Mouse::getPosition(m_window).y + mainView.getCenter().y - m_window.getDefaultView().getCenter().y);
                MouseMovable::setMouseMoveDestination(dest_pos);
            }
        default:
            break;
        }
    }
}

void Game::update() {
    hpbar.update();
    player.update(m_time);
    camBound.update(m_time);
}

void Game::render() {
    m_window.clear();
    
    // draw environment
    m_window.setView(mainView);
    m_window.draw(environment);
    // draw hud
    m_window.setView(hudView);
    m_window.draw(hud); // this will be last thing to draw

    m_window.display();
}

void Game::start(int mode) {
    switch (mode) {
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
