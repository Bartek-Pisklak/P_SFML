#include "Bot.h"

Bot::Bot()
{

}


Bot::Bot(std::vector <sf::Vector2i>& linePlayer, int typ)
{

	srand((unsigned)time(NULL));
	
	if (typ == 1)
	{
		whatBot = 1;
		int where = rand() % MUCHBUTTON;
		while (checkPoint(linePlayer, 0, where))
		{
			where = rand() % MUCHBUTTON;
			if (!checkPoint(linePlayer, 0, where))
			{
				
				break;
			}
		}
		lineEnemy.push_back(sf::Vector2i(0, where));
	}

	this->linePlayer = linePlayer;
}

Bot::~Bot()
{
}

void Bot::updateButtonBoardShadow(std::vector <sf::Vector2i>& linePlayer, ButtonOne buttonBoard[][MUCHBUTTON])
{
	for (int i = 0;i < MUCHBUTTON;i++)
	{
		for (int j = 0; j < MUCHBUTTON ; j++)
		{
			if (buttonBoard[i][j].getPlayer())
				buttonBoardShadow[i][j] = 1;
			else
				buttonBoardShadow[i][j] = 0;
		}
	}

	this->linePlayer = linePlayer;
}

void Bot::roadCreate(std::vector<sf::Vector2i> lineEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end)
{
	if(lineEnemy.size()<lineEnemyCurrent.size())
		lineEnemy = lineEnemyCurrent;

	createFastRoad(lineEnemy.back().x, lineEnemy.back().y);

	begin = roadPoints.at(0);
	end   = roadPoints.at(1);
}

void Bot::createFastRoad(int x,int y)
{

	std::vector <sf::Vector2i> road;
	road.push_back(sf::Vector2i(x, y));

	sf::Vector2i start;
	int loop = 0;
	bool WhatNOW = false;


	while (lineEnemy[0].x == 0 && x != 23 || lineEnemy[0].y == 0 && y != 23 )
	{
		bool isInTable = false;

		//std::cout << "Road" << isInTable << " " << x << "<>" << y << " " << loop <<"pierwsze"<< "\n";

		if (whereGo[0])
		{
			S_GO(isInTable,road,x,y);
		}
		else if (whereGo[1])
		{
			N_GO(isInTable, road, x, y);
		}
		else if (whereGo[2])
		{
			W_GO(isInTable, road, x, y);
		}
		else if (whereGo[3])
		{
			E_GO(isInTable, road, x, y);
		}


		if (y == 0)
		{
			LEFT_WAS = true;
		}
		if (y == MUCHBUTTON - 1)
		{
			RIGHT_WAS = true;
		}

		if (!isInTable )
		{
			loop++;
		}

		if (loop > 10)
		{
			WhatNOW = true;
			break;
		}
		//std::cout << "Road"<<isInTable<<" "<< x << "<>" << y << " " << loop << "\n";

	}


	sf::Vector2i helpL = left_or_right(true);
	sf::Vector2i helpR = left_or_right(false);

	if (WhatNOW)
	{
		bool x = false;
		//std::cout << "tutaj"<<LEFT_WAS<<" "<<RIGHT_WAS;

		if (LEFT_WAS && !checkPoint(lineEnemy,99, 0))
		{
			//std::cout << "tutaj111";
			start = left_or_right(true);
			road.clear();
			road.push_back(start);
			W_GO(x, road, start.x, start.y);
		}
		else if (RIGHT_WAS && !checkPoint(lineEnemy,99, 23))
		{
			//std::cout << "tutaj111222";
			start = left_or_right(false);
			road.clear();
			road.push_back(start);
			E_GO(x, road, start.x, start.y);
		}
		else
		{
			road.clear();

			if (!LEFT_WAS)
			{
			//	std::cout << "tutaj22";
				start = left_or_right(true);
				road.push_back(start);
				W_GO(x, road, start.x, start.y);
			}
			else if (!RIGHT_WAS)
			{
			//	std::cout << "tutaj23";
				start = left_or_right(false);
				road.push_back(start);
				E_GO(x, road, start.x, start.y);
			}
		}
	}

	roadPoints = road;
}

void Bot::graf(bool& isInTable, std::vector <sf::Vector2i>& roadCopy, int& x, int& y, int zmiennaX, int zmiennaY)
{
	if (isDouble(roadCopy, x + zmiennaX, y + zmiennaY) == false)
	{
		if ((x + zmiennaX >= 0 && x + zmiennaX < MUCHBUTTON) && (y + zmiennaY >= 0 && y + zmiennaY < MUCHBUTTON))
		{
			if (buttonBoardShadow[x + zmiennaX][y + zmiennaY] == 0)
			{
				if (checkLine(sf::Vector2i(x, y), sf::Vector2i(x + zmiennaX, y + zmiennaY)) == false)
				{
					if (isInTable == false)
					{
						x += zmiennaX;
						y += zmiennaY;
						roadCopy.push_back(sf::Vector2i(x, y));
						isInTable = true;
					}
				}
			}
		}
	}
}

void Bot::clearWhereGo()
{
}


void Bot::S_GO(bool& isInTable, std::vector<sf::Vector2i>& roadCopy, int& x, int& y)
{
	for (int i = 0;i < 8;i++)
	{
		graf(isInTable, roadCopy, x, y, stepHorseNS[0][i], stepHorseNS[1][i]);
	}
}

void Bot::N_GO(bool& isInTable, std::vector<sf::Vector2i>& roadCopy, int& x, int& y)
{
	for (int i = 7;i >= 0;i--)
	{
		graf(isInTable, roadCopy, x, y, stepHorseNS[0][i], stepHorseNS[1][i]);
	}
}

void Bot::W_GO(bool& isInTable, std::vector<sf::Vector2i>& roadCopy, int& x, int& y)
{
	for (int i = 0;i < 8;i++)
	{
		graf(isInTable, roadCopy, x, y, stepHorseWE[0][i], stepHorseWE[1][i]);
	}
}

void Bot::E_GO(bool& isInTable, std::vector<sf::Vector2i>& roadCopy, int& x, int& y)
{
	for (int i = 7;i >= 0;i--)
	{
		graf(isInTable, roadCopy, x, y, stepHorseWE[0][i], stepHorseWE[1][i]);
	}
}


bool Bot::isDouble(std::vector<sf::Vector2i> roadCopy, int x, int y)
{
	bool isDoubleHelp = false;
	for (int i = 0;i < roadCopy.size();i++)
	{
		if (sf::Vector2i(x, y) == roadCopy[i])
			isDoubleHelp = true;
	}

	return isDoubleHelp;
}