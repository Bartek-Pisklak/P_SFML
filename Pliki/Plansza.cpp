#include "Plansza.h"


Plansza::Plansza()
{
}

Plansza::Plansza(float posX, float posY,float sizeB, float scaleB, short typeBot)
{
	this->typeBot = typeBot;
	enemy = Bot{ linePlayer, typeBot };


	float x;
	float y;
	y = posY;
	scale = scaleB;
	size = sizeB;

	for (int i = 0;i < rozmiar;i++)
	{
		x = posX;
		for (int j = 0; j < rozmiar ;j++)
		{
			plansza[i][j] = ButtonOne(x, y,size,  scale);
			x += 10 * scale + 15;
		}
		y += 10 * scale + 15;
	}
}


Plansza::~Plansza()
{
	lineEnemy.clear();
	linePlayer.clear();
	for (int i = 0;i < rozmiar;i++)
	{
		for (int j = 0; j < rozmiar;j++)
		{
			plansza[i][j].~ButtonOne();
		}
	}
}



using namespace std;
void Plansza::updatePlansza(sf::Vector2f mousePosView)
{

	bool change = false;
	for (int i = 0;i < rozmiar;i++)
	{
		for (int j = 0;j < rozmiar;j++)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (plansza[i][j].getButton().getGlobalBounds().contains(mousePosView) && plansza[i][j].getLock() == 0)
				{
					if (plansza[i][j].getStan() !=0 && plansza[i][j].getPress() == false && !klik)
					{
						change = true;
						klik = true;

						plansza[i][j].setStan(2);
						pressButton[0] = i;
						pressButton[1] = j;

						setActiveButton(i, j, 2, 1);
						setActiveButton(i, j, 1, 2);
						setActiveButton(i, j, -2, 1);
						setActiveButton(i, j, -1, 2);
					}
					else if (plansza[i][j].getPress() && klik)
					{
						change = true;
						klik = false;

						plansza[i][j].setStan(99);

					}
					else if (plansza[i][j].getActive() && klik)
					{
						if (checkLine(sf::Vector2i(i, j), sf::Vector2i(pressButton[0], pressButton[1])))
							break;

						change = true;
						klik = false;
						plansza[i][j].setStan(1);
						plansza[pressButton[0]][pressButton[1]].setStan(1);

						createLine(sf::Vector2i(pressButton[0], pressButton[1]), sf::Vector2i(i, j), linePlayer);


						sf::Vector2i beginLineEnemy;
						sf::Vector2i endLineEnemy;

						enemy.updatePlanszaShadow(linePlayer, plansza);
						enemy.droga(lineEnemy,beginLineEnemy,endLineEnemy);

						plansza[beginLineEnemy.x][beginLineEnemy.y].setStan(0);
						plansza[endLineEnemy.x][endLineEnemy.y].setStan(0);

						createLine(beginLineEnemy, endLineEnemy, lineEnemy);

						for (int i = 0;i < lineEnemy.size();i += 2)
							cout << lineEnemy[i].x << " " << lineEnemy[i].y << "<>" << lineEnemy[i + 1].x << " " << lineEnemy[i + 1].y << endl;


					}
					break;
				}
			}
		}
	}

//	sprawdzanie stanow
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	cout << "<><>" << change << endl;
	//	for (int i = 0;i < rozmiar;i++)
	//	{
	//		for (int j = 0;j < rozmiar;j++)
	//		{
	//			cout << plansza[i][j].getLock();
	//		}
	//		cout << endl;
	//	}
	//	for (int i = 0;i < rozmiar;i++)
	//	{
	//		for (int j = 0;j < rozmiar;j++)
	//		{
	//			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//			{
	//				if (plansza[i][j].getButton().getGlobalBounds().contains(mousePosView))
	//				{
	//					cout <<">A "<< plansza[i][j].getActive() << ">P " << plansza[i][j].getPlayer() << ">S " << plansza[i][j].getStan() << endl;
	//				}
	//			}
	//		}
	//	}
	//}


	// lockowanie przyciskow
	if (change)
	{
		bool stan = false;
		if (!klik)
		{
			stan = true;
		}
		for (int i = 0;i < rozmiar;i++)
		{
			for (int j = 0;j < rozmiar;j++)
			{
				plansza[i][j].setLock(stan);
				if (stan)
					plansza[i][j].setStan(99);
			}
		}
	}
}

void Plansza::setActiveButton(int x,int y , int a, int b) // i, j, gdzie gora, gdzie lewo 
{
	if ((x - a) >= 0 && (x-a) < rozmiar)
	{
		if ((y - b) >= 0)
		{
			if (plansza[x - a][y - b].getStan() != 1 && plansza[x - a][y - b].getStan() !=0)
				plansza[x - a][y - b].setStan(4);
		}
		if ((y + b) < rozmiar)
		{
			if (plansza[x - a][y - b].getStan() != 1 && plansza[x - a][y - b].getStan() != 0)
				plansza[x - a][y + b].setStan(4);
		}
	}
	return;
}





void Plansza::drawPlansza(sf::RenderWindow* window)
{
	using namespace sf;
	lineDraw(window, linePlayer);
	lineDraw(window, lineEnemy);


		for (int i = 0;i < rozmiar;i++)
		{
			for (int j = 0;j < rozmiar;j++)
			{
				window->draw(plansza[i][j].getButton());
				plansza[i][j].changeColor();
			}
		}

}

void Plansza::lineWin()
{
	bool beginEnemy = false;
	bool lineEnemy = false;
	bool endEnemy;
	//for (int i = 0;i < lineEnemy.size();i++)
	//{


	//}
}

void Plansza::lineDraw(sf::RenderWindow* window, std::vector <sf::Vector2i> linia)
{
	sf::Color color;
	if(linia.size())
		color = plansza[linia[0].x][linia[0].y].getColor();

	for (int i = 0;i < linia.size();i += 2)
	{
		sf::Vector2f A = sf::Vector2f(plansza[linia[i].x][linia[i].y].getX(),     plansza[linia[i].x][linia[i].y].getY());
		sf::Vector2f B = sf::Vector2f(plansza[linia[i+1].x][linia[i+1].y].getX(), plansza[linia[i+1].x][linia[i+1].y].getY());

		sf::Vertex line[] =
		{
			sf::Vertex(A ,color, A),
			sf::Vertex(B ,color, B)
		};

		window->draw(line, 2, sf::Lines);
	}
}

/*
void Plansza::lineDraw(sf::RenderWindow* window, std::vector <sf::Vector2f> linia, sf::Color color)
{
	for (int i = 0;i < linia.size();i += 2)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(linia[i]     ,color, linia[i]),
			sf::Vertex(linia[i + 1] ,color, linia[i + 1])
		};

		window->draw(line, 2, sf::Lines);
	}
}


void Plansza::createLine(ButtonOne first, ButtonOne second)
{
	sf::Vector2f poczatek = (sf::Vector2f(first.getX(), first.getY()));
	sf::Vector2f koniec = (sf::Vector2f(second.getX(), second.getY()));

	linePlayer.push_back(poczatek);
	linePlayer.push_back(koniec);
}

bool Plansza::checkLine(sf::Vector2i first, sf::Vector2i second)
{
	ButtonOne guzik1 = plansza[first.x][first.y];
	ButtonOne guzik2 = plansza[second.x][second.y];
	sf::Vector2f A = (sf::Vector2f(guzik1.getX(), guzik1.getY()));
	sf::Vector2f B = (sf::Vector2f(guzik2.getX(), guzik2.getY()));

	for (int i = 0;i < linePlayer.size();i += 2)
	{
		sf::Vector2f C = linePlayer[i];
		sf::Vector2f D = linePlayer[1 + i];

		float	v1 = iloczyn_wektorowy(C, D, A);
		float	v2 = iloczyn_wektorowy(C, D, B);
		float	v3 = iloczyn_wektorowy(A, B, C);
		float	v4 = iloczyn_wektorowy(A, B, D);

		if (v1 * v2 < 0 && v3 * v4 < 0)
			return true;

		if (A == C && B == D || A == D && B == C)
		{
			return true;
		}
	}

	for (int i = 0;i < lineEnemy.size();i++)
	{
		sf::Vector2f C = lineEnemy[i];
		sf::Vector2f D = lineEnemy[1 + i];

		float	v1 = iloczyn_wektorowy(C, D, A);
		float	v2 = iloczyn_wektorowy(C, D, B);
		float	v3 = iloczyn_wektorowy(A, B, C);
		float	v4 = iloczyn_wektorowy(A, B, D);

		if (v1 * v2 < 0 && v3 * v4 < 0)
			return true;

		if (B == lineEnemy[i])
			return true;
	}

	return false;
}

float Plansza::iloczyn_wektorowy(sf::Vector2f X, sf::Vector2f Y, sf::Vector2f Z)
{
	float x1 = Z.x - X.x;
	float y1 = Z.y - X.y;
	float x2 = Y.x - X.x;
	float y2 = Y.y - X.y;

	return x1 * y2 - x2 * y1;
}
*/