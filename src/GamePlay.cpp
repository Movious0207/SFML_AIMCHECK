
#include "GamePlay.h"

#include <ctime>

static bool isGameStarted = false;

static void Reset();
static void moveTargets();
static bool isPointInCircle(sf::Vector2i& p, const sf::CircleShape& c);

static Target target[5];

static int lives = 3;
static int score = 0;


void GamePlay::Init()
{
    srand(time(nullptr));

    lives = 3;
    isGameStarted = false;

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
            if (isGameStarted)
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
                            for (int j = 0; j < 5; j++)
                            {
                                target[j].isActive = false;
                                score++;
                            }
                        }
                    }
                }
            }
            else
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    isGameStarted = true;
                }
            }
        }
    }
    
}

void GamePlay::Update(sf::RenderWindow* window)
{
    bool moveTarget = true;

    for (int i = 0; i <= score && i < 5; i++)
    {
        if (target[i].isActive)
        {
            moveTarget = false;
        }
    }

    if (moveTarget)
    {
        moveTargets();
    }
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

static void moveTargets()
{
    int radius = target[0].Circle.getRadius();

    float randX = (rand() % (1280 - radius * 4)) + radius;
    float randY = (rand() % (720 - radius * 4)) + radius;

    target[0].isActive = true;
    target[0].isEvil = false;
    target[0].Circle.setPosition({ randX ,randY });

    for (int i = 1; i <= score && i < 5; i++)
    {
        randX = (rand() % (1280 - radius * 2)) + radius;
        randY = (rand() % (720 - radius * 2)) + radius;

        target[i].isActive = true;
        target[i].isEvil = true;

        target[i].Circle.setPosition({ randX ,randY });
    }
}

static bool isPointInCircle( sf::Vector2i& p, const sf::CircleShape& c)
{
    return (p.x < c.getPosition().x + c.getRadius() * 2
        && p.x > c.getPosition().x
        && p.y < c.getPosition().y + c.getRadius() * 2
        && p.y > c.getPosition().y);
}