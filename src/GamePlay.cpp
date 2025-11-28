
#include "GamePlay.h"

#include <ctime>
#include <string>
#include <cmath>

static bool isGameStarted = false;

static sf::Clock deltaClock;

static void Reset();
static void moveTargets();
static void drawUi(sf::RenderWindow* window);
static void drawTutorial(sf::RenderWindow* window);
static void drawGameOver(sf::RenderWindow* window);
static bool isPointInCircle(sf::Vector2i& p, const sf::CircleShape& c);

static Target target[5];

static int lives = 5;
static int score = 0;
static float maxTimer = 5.0f;
static float timer = 5.0f;


void GamePlay::Init()
{
    srand(time(nullptr));

    lives = 3;
    score = 0;
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
            {
                actualScreen = Screen::Menu;
                Reset();
                isGameStarted = false;
            }
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (isGameStarted)
            {
                if (lives > 0)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left && isPointInCircle(MousePos, target[i].Circle))
                        {
                            if (target[i].isEvil)
                            {
                                lives--;
                                for (int j = 0; j < 5; j++)
                                {
                                    target[j].isActive = false;
                                }
                            }
                            else
                            {
                                for (int j = 0; j < 5; j++)
                                {
                                    target[j].isActive = false;
                                }
                                score++;
                                maxTimer = fmaxf(maxTimer - 0.2f, 1.5f);
                                timer = maxTimer;
                            }
                        }
                    }
                }
                else if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    Reset();
                    isGameStarted = false;
                }
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Left && !isGameStarted)
            {

                isGameStarted = true;

            }
        }
    }
    
}

void GamePlay::Update(sf::RenderWindow* window)
{
    bool moveTarget = true;
    float dt = deltaClock.restart().asSeconds();
    
    if (isGameStarted)
    {
        timer -= dt;
    }

    if (timer <= 0)
    {
        lives--;
        for (int j = 0; j < 5; j++)
        {
            target[j].isActive = false;
        }
        maxTimer += 0.5f;
        timer = maxTimer;
    }

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
    window->clear({ 100,100,100 });
    if (isGameStarted && lives > 0)
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
        drawUi(window);
    }
    else if (!isGameStarted)
    {
        drawTutorial(window);
    }
    else
    {
        drawGameOver(window);
    }

    window->display();
}

static void Reset()
{
    lives = 3;
    score = 0;

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

    if (score < 5)
    {
        for (int i = 1; i <= score; i++)
        {
            randX = (rand() % (1280 - radius * 2)) + radius;
            randY = (rand() % (720 - radius * 2)) + radius;

            target[i].isActive = true;
            target[i].isEvil = true;

            target[i].Circle.setPosition({ randX ,randY });
        }
    }
    else
    {
        for (int i = 1; i < 5; i++)
        {
            randX = (rand() % (1280 - radius * 2)) + radius;
            randY = (rand() % (720 - radius * 2)) + radius;

            target[i].isActive = true;
            target[i].isEvil = true;

            target[i].Circle.setPosition({ randX ,randY });
        }
    }
}

static void drawUi(sf::RenderWindow* window)
{
    sf::Text ui1(font, std::to_string(score), 20);
    sf::Text ui2(font, "SCORE: ", 20);
    sf::Text ui3(font, std::to_string(lives), 20);
    sf::Text ui4(font, "LIVES: ", 20);
    sf::Text ui5(font, std::to_string(timer), 20);
    sf::Text ui6(font, "COUNT: ", 20);

    ui1.setPosition({ (1280.0f / 5.0f) , 720.0f / 10.0f });
    ui2.setPosition({ (1280.0f / 5.0f) - 80.0f ,720.0f / 10.0f });
    ui3.setPosition({ (1280.0f / 3.0f) , 720.0f / 10.0f });
    ui4.setPosition({ (1280.0f / 3.0f) - 80.0f ,720.0f / 10.0f });
    ui5.setPosition({ (1280.0f / 2.0f) + 20.0f , 720.0f / 10.0f });
    ui6.setPosition({ (1280.0f / 2.0f) - 80.0f ,720.0f / 10.0f });

    window->draw(ui1);
    window->draw(ui2);
    window->draw(ui3);
    window->draw(ui4);
    window->draw(ui5);
    window->draw(ui6);
}

static void drawTutorial(sf::RenderWindow* window)
{
    sf::Text tutorial1(font, "Welcome to AIMCHECK", 70);
    sf::Text tutorial2(font, "Left Click the GREEN circles to earn points, take too long or left Click a RED circle and you lose a life", 20);
    sf::Text tutorial3(font, "Left Click to Start, Press Escape to return to the main menu", 30);
    tutorial1.setPosition({ (1280.0f / 4.0f) - 80.0f ,720.0f / 4.0f });
    tutorial2.setPosition({ (1280.0f / 5.0f) - 80.0f ,720.0f / 2.0f });
    tutorial3.setPosition({ (1280.0f / 5.0f) - 40.0f ,720.0f / 1.5f });

    window->draw(tutorial1);
    window->draw(tutorial2);
    window->draw(tutorial3);
}

static void drawGameOver(sf::RenderWindow* window)
{
    sf::Text GameOver1(font, "GAME OVER", 70);
    sf::Text GameOver2(font, "FINAL SCORE: ", 30);
    sf::Text GameOver3(font, std::to_string(score), 30);
    sf::Text GameOver4(font, "Left Click to Restart, Press Escape to return to the main menu", 30);
    
    GameOver1.setPosition({ (1280.0f / 2.0f) - 200.0f ,720.0f / 4.0f });
    GameOver2.setPosition({ (1280.0f / 2.0f) - 100.0f ,720.0f / 2.0f });
    GameOver3.setPosition({ (1280.0f / 2.0f) + 170.0f ,720.0f / 2.0f });
    GameOver4.setPosition({ (1280.0f / 4.0f) - 130.0f ,720.0f / 1.5f });

    window->draw(GameOver1);
    window->draw(GameOver2);
    window->draw(GameOver3);
    window->draw(GameOver4);
}

static bool isPointInCircle( sf::Vector2i& p, const sf::CircleShape& c)
{
    return (p.x < c.getPosition().x + c.getRadius() * 2
        && p.x > c.getPosition().x
        && p.y < c.getPosition().y + c.getRadius() * 2
        && p.y > c.getPosition().y);
}