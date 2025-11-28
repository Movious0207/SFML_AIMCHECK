#pragma once

#include "Game.h"


namespace GamePlay
{
	void Init();
	void Input(sf::RenderWindow* window, Screen& actualScreen);
	void Update();
	void Draw(sf::RenderWindow* window);
}

struct Target
{
	bool isActive;
	bool isEvil;
	sf::CircleShape Circle;
};
