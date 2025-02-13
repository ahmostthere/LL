#pragma once
#include <PlayerEntity.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>


class CameraBound : public sf::Drawable, public sf::Transformable {
public:
    sf::Vector2f windowSize;
    sf::Vector2f size;
    float speed;
    sf::RectangleShape r;
    bool bound;
    bool isShowBound;


    CameraBound(sf::Vector2f wSz, float spd = 200);

    void unboundSubject();

    void boundSubject();

    void showBound();
    
    void hideBound();

    void setSubject(PlayerEntity* subject);

    void setCameraView(sf::View* view);

    void boundVertical(sf::Time time);

    void boundHorizontal(sf::Time time);

    void panToSubject(sf::Time time);

    void update(sf::Time time);

    const sf::Vector2f& getSize() const;

    const sf::Vector2f& getWindowSize() const;


private:
    sf::View* m_cameraView;
    PlayerEntity* m_subject;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (isShowBound)
        {
            target.draw(r);
        }
    }
};