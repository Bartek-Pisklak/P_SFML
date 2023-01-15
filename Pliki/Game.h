#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "ButtonBoard.h"

class Game
{
private:

	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Color colorbackground;

	short typeBot;
	// Game obcjets	
	ButtonBoard buttonBoard{};

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	sf::Font font;
	sf::RectangleShape buttonRestart;
	sf::RectangleShape buttonClose;
	sf::Text textButtonRestart;
	sf::Text textButtonClose;

	void initializeVariebles();
	void initWindow();

	void initButton();
	void drawButton();
	void clickButtonMenu();

public:

	void pollEvents();
	void update();
	void render();
	void updateMousePosition();

	// Accessors
	const bool running() const;

	// konstruktor i destruktor
	Game();
	~Game();
};

