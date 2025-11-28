#include "GamePlay.h"

static bool isGameStarted = false;

static bool isPointInCircle(sf::Vector2i& p, const sf::CircleShape& c);

static Target target[5];


void GamePlay::Init()
{

}

void GamePlay::Input(sf::RenderWindow* window)
{
    sf::Vector2 MousePos = sf::Mouse::getPosition(*window);


    
}
void GamePlay::Update(sf::RenderWindow* window, Screen& actualScreen)
{

}
void GamePlay::Draw(sf::RenderWindow* window)
{
    window->clear({0,0,0,0});
    if (isGameStarted)
    {
        for (int i = 0; i < 5; i++)
        {
            if (target[i].isEvil)
            {
                target[i].Circle.setFillColor({ 255, 0, 0 });
            }
            else
            {
                target[i].Circle.setFillColor({ 0, 255, 0 });
            }
            if (target[i].isActive)
            {
                window->draw(target[i].Circle);
            }
        }
    }
    window->draw(target[0].Circle);

    window->display();
}

static bool isPointInCircle( sf::Vector2i& p, const sf::CircleShape& c) 
{
    float dx = p.x - c.getPosition().x;
    float dy = p.y - c.getPosition().y;
    float distanceSquared = (dx * dx) + (dy * dy);

    return distanceSquared <= (c.getRadius() * c.getRadius());
}