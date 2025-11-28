#include "GamePlay.h"

static bool isGameStarted = false;

static void Reset();
static bool isPointInCircle(sf::Vector2i& p, const sf::CircleShape& c);

static Target target[5];

static int lives = 3;
static int score = 0;


void GamePlay::Init()
{
    lives = 3;

    for (int i = 0; i < 5; i++)
    {
        target[i].Circle.setRadius(30.0f);
    }
}

void GamePlay::Input(sf::RenderWindow* window, Screen& actualScreen)
{
    sf::Vector2 MousePos = sf::Mouse::getPosition(*window);

    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                actualScreen = Screen::GamePlay;
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            for (int i = 0; i < 5; i++)
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left && isPointInCircle(MousePos, target[i].Circle))
                {
                    if (target[i].isEvil)
                    {
                        actualScreen = Screen::GamePlay;
                    }
                    else
                    {
                        target[i].isActive = false;
                    }
                }
            }
        }
    }
    
}

void GamePlay::Update(sf::RenderWindow* window)
{

}

void GamePlay::Draw(sf::RenderWindow* window)
{
    window->clear();
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
    else
    {

    }

    window->display();
}

static void Reset()
{
    lives = 3;

    for (int i = 0; i < 5; i++)
    {
        target[i].isActive = false;
    }
}

static bool isPointInCircle( sf::Vector2i& p, const sf::CircleShape& c) 
{
    float dx = p.x - c.getPosition().x;
    float dy = p.y - c.getPosition().y;
    float distanceSquared = (dx * dx) + (dy * dy);

    return distanceSquared <= (c.getRadius() * c.getRadius());
}