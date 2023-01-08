#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class ButtonOne
{
private:
	// obiekt
	sf::CircleShape button{};

	// srodek obiektu
	float centerX;
	float centerY;


	// rozmiar 
	float scale;
	float size;

	// stany 
	bool active;
	bool press;
	bool isPlayer;
	bool isEnemy;
	bool isLock;

	short stan= 99;

	// kolor
	sf::Color color;
	sf::Color defaultColor;
	sf::Color playerColor;
	sf::Color enemyColor;
	sf::Color activeColor;
	sf::Color pressColor;
	sf::Color circleColor;

public:
	// dla obiektu
	void initObcject();
	void changeColor();
	void updateObcjet();

	sf::CircleShape getButton();

	float getX() const;
	float getY() const;

	//dla dzialania obiektu

	void setLock(bool whatLock=false);
	void setStan(int nowy);

	short getStan();

	bool getLock() const;
	bool getPress();
	bool getPlayer();
	bool getActive();
	bool getEnemy();

	sf::Color getColor();


	ButtonOne();
	ButtonOne(float posX,float posY,float size, float scale);
	~ButtonOne();
};


