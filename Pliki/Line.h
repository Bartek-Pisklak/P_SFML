#pragma once

#include "ButtonOne.h"
#include <vector>
#include <iostream>
class Line
{
	protected:

	std::vector <sf::Vector2i> liniePlayer;
	std::vector <sf::Vector2i> linieEnemy;

public:

	void createLine(sf::Vector2i A, sf::Vector2i B, std::vector <sf::Vector2i>& linia);
	bool checkLine(sf::Vector2i first, sf::Vector2i second);
	float iloczyn_wektorowy(sf::Vector2i X, sf::Vector2i Y, sf::Vector2i Z);
};

