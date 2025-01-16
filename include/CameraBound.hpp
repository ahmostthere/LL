#pragma once
#include <PlayerEntity.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <iostream>

class CameraBound : public sf::Drawable, public sf::Transformable {
public:
    sf::Vector2f windowSize;
    sf::Vector2f size;
    float speed;
    sf::RectangleShape r;


    CameraBound(sf::Vector2f wSz, float spd = 200) : windowSize(wSz), size(sf::Vector2f(wSz.x/8, wSz.y/8)), speed(spd) {
        this->setPosition(sf::Vector2f((windowSize.x - size.x) / 2, (windowSize.y - size.y) / 2));
        r.setFillColor(sf::Color(100, 100, 255, 0));
        r.setOutlineColor(sf::Color(80, 80, 255, 10));
        r.setPosition(this->getPosition());
        r.setSize(size);
    }


    void update(sf::Time time) {
        if (getPosition().x + getSize().x <= m_subject->getPosition().x + m_subject->getRadius() || getPosition().x >= m_subject->getPosition().x - m_subject->getRadius()) {
            move(sf::Vector2f(m_subject->DPadMove().x, 0) * m_subject->getSpeed() * time.asSeconds());
            m_cameraView->move(sf::Vector2f(m_subject->DPadMove().x, 0) * m_subject->getSpeed() * time.asSeconds());
        }

        if (getPosition().y + getSize().y <= m_subject->getPosition().y + m_subject->getRadius() || getPosition().y >= m_subject->getPosition().y - m_subject->getRadius()) {
            move(sf::Vector2f(0, m_subject->DPadMove().y) * m_subject->getSpeed() * time.asSeconds());
            m_cameraView->move(sf::Vector2f(0, m_subject->DPadMove().y) * m_subject->getSpeed() * time.asSeconds());
        }

        centerSubject(time);
    }

    void centerSubject(sf::Time time) {
        auto theta = [](const sf::Vector2f &a, const sf::Vector2f &b) {
            sf::Vector2f c(a.x - b.x, a.y - b.y);
            return std::atan2(c.y, c.x);
        };

        auto dis = [](const sf::Vector2f &a, const sf::Vector2f &b) { 
            sf::Vector2f c(a.x - b.x, a.y - b.y);
            return sqrt((c.x * c.x) + (c.y * c.y));
        };
        if (m_subject->DPadMove() == sf::Vector2f(0, 0) && dis(m_subject->getPosition(), m_cameraView->getCenter()) > 5) {
            float th = theta(m_subject->getPosition(), m_cameraView->getCenter());
            m_cameraView->move(sf::Vector2f(std::cos(th), std::sin(th)) * speed * time.asSeconds());
            move(sf::Vector2f(std::cos(th), std::sin(th)) * speed * time.asSeconds());
        }
    }

    void setCameraView(sf::View* view) {
        m_cameraView = view;
    }

    void setSubject(PlayerEntity* subject) {
        m_subject = subject;
    }

    const sf::Vector2f& getSize() const {
        return size;
    }

    const sf::Vector2f& getWindowSize() const {
        return windowSize;
    }


private:
    sf::View* m_cameraView;
    PlayerEntity* m_subject;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(r);
    }
};