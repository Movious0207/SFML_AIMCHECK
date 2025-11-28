#include "Game.h"
#include "GamePlay.h"

namespace Game
{
    Button PlayButton;
    Button QuitButton;

    static float SCREEN_WIDTH = 1280.0f;
    static float SCREEN_HEIGHT = 720.0f;

    static void Input(Screen& actualScreen);
    static void Update(Screen& actualScreen);
    static void Draw();
    static void CreateButtons();

    static sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "AIMCHECK");
    static sf::Text text(font, "  AIMCHECK", 100);
    static sf::Event* event;

    void Game::Run()
    {
        font.openFromFile("res/comfort.ttf");

        CreateButtons();

        GamePlay::Init();

        Screen actualScreen = Screen::Menu;

        while (window.isOpen())
        {

            switch (actualScreen)
            {
            case Screen::Menu:
                Input(actualScreen);
                Update(actualScreen);
                Draw();
                break;
            case Screen::GamePlay:
                GamePlay::Input(&window, actualScreen);
                GamePlay::Update(&window);
                GamePlay::Draw(&window);
                break;
            default:
                break;
            }

         
        }
    }

    static void Input(Screen& actualScreen)
    {
        sf::Vector2 MousePos = sf::Mouse::getPosition(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left && PlayButton.isHovering)
                {
                    actualScreen = Screen::GamePlay;
                }
                if (mouseButtonPressed->button == sf::Mouse::Button::Left && QuitButton.isHovering)
                {
                    window.close();
                }
            }
        }

        if (MousePos.x > (SCREEN_WIDTH / 8) * 3
            && MousePos.x < (SCREEN_WIDTH / 8) * 3 + (SCREEN_WIDTH / 4)
            && MousePos.y > (SCREEN_HEIGHT / 15) * 10
            && MousePos.y < ((SCREEN_HEIGHT / 15) * 10) + (SCREEN_HEIGHT / 15))
        {
            PlayButton.isHovering = true;
        }
        else
        {
            PlayButton.isHovering = false;
        }
        if (MousePos.x > (SCREEN_WIDTH / 8) * 3
            && MousePos.x < (SCREEN_WIDTH / 8) * 3 + (SCREEN_WIDTH / 4)
            && MousePos.y >(SCREEN_HEIGHT / 15) * 12
            && MousePos.y < ((SCREEN_HEIGHT / 15) * 12) + (SCREEN_HEIGHT / 15))
        {
            QuitButton.isHovering = true;
        }
        else
        {
            QuitButton.isHovering = false;
        }
    }

    static void Update(Screen& actualScreen)
    {

        if (PlayButton.isHovering)
        {
            PlayButton.Rectangle.setFillColor(sf::Color(100, 100, 100));
        }
        else
        {
            PlayButton.Rectangle.setFillColor(sf::Color(255, 255, 255));
        }
        if (QuitButton.isHovering)
        {
            QuitButton.Rectangle.setFillColor(sf::Color(100, 100, 100));
        }
        else
        {
            QuitButton.Rectangle.setFillColor(sf::Color(255, 255, 255));
        }

    }

    static void Draw()
    {
        
        window.clear();

        text.setPosition({ 1280.0f / 4.0f, 720.0f / 11 });
        window.draw(text);

        window.draw(PlayButton.Rectangle);
        window.draw(QuitButton.Rectangle);

        // Update the window
        window.display();
    }

    static void CreateButtons()
    {
        PlayButton.Rectangle.setSize({ SCREEN_WIDTH / 4, SCREEN_HEIGHT / 15 });
        PlayButton.Rectangle.setFillColor(sf::Color(255, 255, 255));
        PlayButton.Rectangle.setPosition({ (SCREEN_WIDTH / 8) * 3 , (SCREEN_HEIGHT / 15) * 10 });

        QuitButton.Rectangle.setSize({ SCREEN_WIDTH / 4, SCREEN_HEIGHT / 15 });
        QuitButton.Rectangle.setFillColor(sf::Color(255, 255, 255));
        QuitButton.Rectangle.setPosition({ (SCREEN_WIDTH / 8) * 3 , (SCREEN_HEIGHT / 15) * 12 });
    }
}