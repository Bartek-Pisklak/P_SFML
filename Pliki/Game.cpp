#include "Game.h"

using namespace sf;
Game::Game()
{
	typeBot = 1;
	this->initializeVariebles();
	this->initWindow();
	this->initButton();

	buttonBoard = ButtonBoard{ 10.f, 10.f, 5.f, 2.f,typeBot};
}

Game::~Game()
{
	delete this->window;
}

// private
void Game::initializeVariebles()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 850;
	this->videoMode.width = 1200;
	this->colorbackground = Color(25, 0, 51);


	this->window = new RenderWindow(this->videoMode, "Game", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}



void Game::drawButton()
{
	window->draw(buttonRestart);
	window->draw(buttonClose);
	window->draw(textButtonRestart);
	window->draw(textButtonClose);
}

void Game::initButton()
{
	buttonRestart.setPosition(875, 300);
	buttonRestart.setSize(sf::Vector2f(300,50));
	buttonRestart.setFillColor(sf::Color::Cyan);

	buttonClose.setPosition(875, 400);
	buttonClose.setSize(sf::Vector2f(300,50));
	buttonClose.setFillColor(sf::Color::Cyan);

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "nie ma czcionki" << std::endl;
	}

	textButtonRestart.setString("Restart");
	textButtonRestart.setPosition(950, 300);
	textButtonRestart.setCharacterSize(40);
	textButtonRestart.setStyle(sf::Text::Bold);
	textButtonRestart.setFont(font);
	textButtonRestart.setFillColor(sf::Color::Black);

	textButtonClose.setString("Zamknij");
	textButtonClose.setPosition(950, 400);
	textButtonClose.setCharacterSize(40);
	textButtonClose.setStyle(sf::Text::Bold);
	textButtonClose.setFont(font);
	textButtonClose.setFillColor(sf::Color::Black);


}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;

		case Event::MouseButtonPressed:
			buttonBoard.updateButtonBoard(mousePosView);

			break;

		default:
			break;
		}
	}
}

int t = 0;
// public
void Game::update()
{
	this->pollEvents(); 

	this->updateMousePosition();


}

void Game::render()
{
	this->window->clear(colorbackground);
	
	buttonBoard.drawButtonBoard(this->window);
	drawButton();

	// Draw game obcjets
	this->window->display();
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}


// Accessors


const bool Game::running() const
{
	return this->window->isOpen();
}