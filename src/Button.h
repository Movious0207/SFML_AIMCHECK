#pragma once

#include <SFML/Graphics.hpp>

struct Button
{
	bool isHovering = false;
	sf::RectangleShape Rectangle;
};

enum class Screen
{
    Menu,
    GamePlay
};
