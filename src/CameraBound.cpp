#include <CameraBound.hpp>
#include <iostream>

CameraBound::CameraBound(sf::Vector2f wSz, float spd)
: windowSize(wSz), size(sf::Vector2f(wSz.x / 8, wSz.y / 8)), speed(spd) {
    // this->setPosition(sf::Vector2f((windowSize.x - size.x) / 2, (windowSize.y
    // - size.y) / 2));
    r.setFillColor(sf::Color(100, 100, 255, 100));
    r.setSize(size);
    bound = true;
    isShowBound = false;
    isPanToSubject = false;
}

void CameraBound::unboundSubject() {
    std::cout << "unbound" << std::endl;
    bound = false;
}

void CameraBound::boundSubject() {
    std::cout << "bound" << std::endl;
    m_cameraView->setCenter(m_subject->getPosition());
    bound = true;
}

void CameraBound::showBound() {
    isShowBound = true;
}

void CameraBound::hideBound() {
    isShowBound = false;
}

void CameraBound::setSubject(PlayerEntity *subject) {
    m_subject = subject;
}

void CameraBound::setCameraView(sf::View *view) {
    m_cameraView = view;
    r.setPosition(m_cameraView->getCenter().x - size.x / 2,
                  m_cameraView->getCenter().y - size.y / 2);
}

void CameraBound::boundVertical(sf::Time time) {
    if (m_cameraView->getCenter().y + getSize().y / 2 <=
            m_subject->getPosition().y + m_subject->getSize().y / 2 ||
        m_cameraView->getCenter().y - getSize().y / 2 >=
            m_subject->getPosition().y - m_subject->getSize().y / 2) {
        m_cameraView->move(sf::Vector2f(0, m_subject->DPadMove().y) *
                           m_subject->getSpeed() * time.asSeconds());
    }
}

void CameraBound::boundHorizontal(sf::Time time) {
    if (m_cameraView->getCenter().x + getSize().x / 2 <=
            m_subject->getPosition().x + m_subject->getSize().x / 2 ||
        m_cameraView->getCenter().x - getSize().x / 2 >=
            m_subject->getPosition().x - m_subject->getSize().x / 2) {
        m_cameraView->move(sf::Vector2f(m_subject->DPadMove().x, 0) *
                           m_subject->getSpeed() * time.asSeconds());
    }
}

void CameraBound::panToSubject(sf::Time time) {
    auto theta = [](const sf::Vector2f &a, const sf::Vector2f &b) {
        sf::Vector2f c(a.x - b.x, a.y - b.y);
        return std::atan2(c.y, c.x);
    };

    auto dis = [](const sf::Vector2f &a, const sf::Vector2f &b) {
        sf::Vector2f c(a.x - b.x, a.y - b.y);
        return sqrt((c.x * c.x) + (c.y * c.y));
    };
    if (m_subject->DPadMove() == sf::Vector2f(0, 0) &&
        dis(m_subject->getPosition(), m_cameraView->getCenter()) > 5) {
        float th = theta(m_subject->getPosition(), m_cameraView->getCenter());
        m_cameraView->move(sf::Vector2f(std::cos(th), std::sin(th)) * speed *
                           time.asSeconds());
    }
}

void CameraBound::update(sf::Time time) {
    if (bound) {
        boundHorizontal(time);
        boundVertical(time);
        if (isPanToSubject) {
            panToSubject(time);
        }
    }
}

const sf::Vector2f &CameraBound::getSize() const {
    return size;
}

const sf::Vector2f &CameraBound::getWindowSize() const {
    return windowSize;
}