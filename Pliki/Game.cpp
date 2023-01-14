#include "Game.h"

using namespace sf;
Game::Game()
{
	typeBot = 1;
	this->initializeVariebles();
	this->initWindow();

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



void Game::drawbuttonBoard()
{
	
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

			// to jest lepsze mniej zacina klikanie
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

	//	buttonBoard.updatebuttonBoard(mousePosView);

}

void Game::render()
{
	this->window->clear(colorbackground);
	
	buttonBoard.drawButtonBoard(this->window);


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