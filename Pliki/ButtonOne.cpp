#include "ButtonOne.h"
#include <iostream>


ButtonOne::ButtonOne()
{
}

ButtonOne::ButtonOne(float posX, float posY,float sizeB, float scaleB)
{
	// pozycja scala
	centerX = posX;
	centerY = posY;

	size = sizeB;
	scale = scaleB;
	button = sf::CircleShape{ size };

	// kolor przycisku
	defaultColor = sf::Color(128,128,128);
	color = defaultColor;

	playerColor = sf::Color::Blue;
	enemyColor = sf::Color::Red;
	activeColor = sf::Color::Yellow;
	pressColor = sf::Color::Green;

	// tworzenie obiektu
	initObcject();


	// w jakim stanie jest
	active = false;
	press = false;

	// najważniejsze stany
	isPlayer = false;
	isEnemy = false;
	isLock = false;


}


void ButtonOne::initObcject()
{
	this->button.setPosition(this->centerX,this->centerY);
	this->button.setScale(sf::Vector2f(this->scale, this->scale));
	this->button.setFillColor(defaultColor);
	this->button.setOutlineColor(sf::Color::Transparent); // maybe kolor tła
	button.setOutlineThickness(2);
}


ButtonOne::~ButtonOne()
{
	active = false;
	press = false;
	isPlayer = false;
	isEnemy = false;
	isLock = false;
	stan = 99;

}



void ButtonOne::changeColor()
{

	switch (stan)
	{
	case 0:
		isEnemy = true;
		color = enemyColor;
		break;

	case 1:
		isPlayer = true;
		color = playerColor;
		break;

	case 2:
		press = true;
		color = pressColor;
		break;

	case 3:
		isLock = true;
		break;

	case 4:
		active = true;
		color = activeColor;
		break;

	case 99:
		press = false;
		active = false;
		color =  this->defaultColor;
		circleColor = sf::Color::Transparent;
		break;

	default:
		break;
	}
	
	if (isPlayer)
	{
		color = playerColor;
		if (active)
		{
			circleColor = activeColor;
		}
		else if (press)
		{
			circleColor = pressColor;
		}

		this->button.setOutlineColor(circleColor);
	}


	this->button.setFillColor(color);

}

void ButtonOne::updateObcjet()
{
	
}


void ButtonOne::setLock(bool whatLock)
{
	if (whatLock)
	{
		isLock = false;
	}
	else
	{
		if (!active || !press)
		{
			isLock = true;
		}
		if (active || press)
		{
			isLock = false;
		}
	}


	if (isEnemy)
		isLock = true;
}

void ButtonOne::setStan(int nowy)
{
///	0 isEnemy
///	1 isPlayer
///	2 press
///	3 lock
///	4 active
/// 99 defualt


	if (!isLock)
	{
		// breakuje graczy
		if (!press && !active)
		{
			stan = nowy;
		}
		else
		{
			stan = nowy;
		}
	}

	if (nowy == 0)
		stan = nowy;

	changeColor();
}



bool ButtonOne::getPress()
{
	return press;
}

bool ButtonOne::getPlayer()
{
	return isPlayer;
}

bool ButtonOne::getActive()
{
	return active;
}

bool ButtonOne::getEnemy()
{
	return isEnemy;
}



sf::Color ButtonOne::getColor()
{
	return color;
}



short ButtonOne::getStan()
{
	return stan;
}


bool ButtonOne::getLock() const
{
	return isLock;
}

sf::CircleShape ButtonOne::getButton()
{
	return this->button;
}

float ButtonOne::getX() const
{
	return centerX + 2 * size;
}

float ButtonOne::getY() const
{
	return centerY + 2 * size;
}


