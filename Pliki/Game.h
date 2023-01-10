#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Plansza.h"

class Game
{
private:
	// variable
	// window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	sf::Color colorbackground;

	// Game obcjets	
	Plansza plansza;

	short typeBot;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	void initializeVariebles();
	void initWindow();

public:

	void drawPlansza();

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

