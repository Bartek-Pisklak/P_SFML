#pragma once

#include "ButtonOne.h"
#include <vector>
#include <iostream>


# define MUCHBUTTON 24



class Line
{
	protected:

	std::vector <sf::Vector2i> linePlayer;
	std::vector <sf::Vector2i> lineEnemy;

	float vector_product(sf::Vector2i X, sf::Vector2i Y, sf::Vector2i Z);
public:

	void createLine(sf::Vector2i A, sf::Vector2i B, std::vector <sf::Vector2i>& linia);
	bool checkLine(sf::Vector2i first, sf::Vector2i second);

};

