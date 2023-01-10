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
		int where = rand() % rozmiar;
		if(1)//if (rand() % 2 == 0)
		{
			lineEnemy.push_back(sf::Vector2i(0, where));
		}
		else
		{
			lineEnemy.push_back(sf::Vector2i(where, 0));
		}
	}

	this->linePlayer = linePlayer;
}

Bot::~Bot()
{
}

void Bot::updatePlanszaShadow(std::vector <sf::Vector2i>& linePlayer, ButtonOne plansza[][rozmiar])
{
	for (int i = 0;i < rozmiar;i++)
	{
		for (int j = 0; j < rozmiar ; j++)
		{
			if (plansza[i][j].getPlayer())
				planszaShadow[i][j] = 1;
			else
				planszaShadow[i][j] = 0;
		}
	}

	this->linePlayer = linePlayer;
}

void Bot::droga(std::vector<sf::Vector2i> lineEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end)
{
	if(lineEnemy.size()<lineEnemyCurrent.size())
		lineEnemy = lineEnemyCurrent;

	createFastDroga(lineEnemy.back().x, lineEnemy.back().y);

	std::cout << "\n";
	for (int i = 0;i < roadPoints.size();i++)
	{
		std:: cout << roadPoints[i].x <<"<>" << roadPoints[i].y << std::endl;
	}


	begin = roadPoints[0];
	end   = roadPoints[1];
}

void Bot::createFastDroga(int x,int y)
{
	std::vector <sf::Vector2i> pointBeen;

	std::vector <sf::Vector2i> road;
	road.push_back(sf::Vector2i(x, y));


	int ileMamDoCofania = 0;

	int loop = 0;

	while (lineEnemy[0].x == 0 && x != 23 )//|| lineEnemy[0].y == 0 && y != 23
	{
		bool wstawil = false;

		graf(wstawil, road , pointBeen, x, y, 2, -1);
		graf(wstawil, road , pointBeen, x, y, 2, 1);

		graf(wstawil, road , pointBeen, x, y, 1, -2);
		graf(wstawil, road , pointBeen, x, y, 1, 2);



		graf(wstawil, road, pointBeen, x, y, -1, -2);
		graf(wstawil, road, pointBeen, x, y, -1, 2);

		graf(wstawil, road, pointBeen, x, y, -2, -1);
		graf(wstawil, road, pointBeen, x, y, -2, 1);

		if (!wstawil)
		{
			loop++;
		}
		if (loop > 2)
		{
			pointBeen.push_back(road.back());
		}

		std::cout << "droga"<<wstawil<<" "<< x << "<>" << y << " " << loop << "\n";

		if (loop > 10 && road.size() - ileMamDoCofania >= 0)
		{
			loop = 0;
			std::cout << "musze cofac \n";
			ileMamDoCofania++;
			x = road[road.size() - ileMamDoCofania].x;
			y = road[road.size() - ileMamDoCofania].y;

			road.pop_back();
		}

		//lineEnemy.push_back(sf::Vector2i(x,y));
		//std::cout << road.back().x<<"<>"<< road.back().y << "\n";
		//lineEnemy.push_back(road.back());
	}

	roadPoints = road;
}

void Bot::graf(bool& wstawil, std::vector <sf::Vector2i>& roadCopy,  std::vector <sf::Vector2i>& pointBeen, int& x, int& y, int zmiennaX, int zmiennaY)
{
	if (wstawil == false && isDouble(roadCopy, pointBeen, x+zmiennaX,y+zmiennaY) == false)
	{
		if ((x + zmiennaX >= 0 && x + zmiennaX < rozmiar) && (y + zmiennaY >= 0 && y + zmiennaY < rozmiar))
		{
			if (planszaShadow[x + zmiennaX][y + zmiennaY] == 0)
			{
				if (checkLine(  sf::Vector2i(x, y), sf::Vector2i(x + zmiennaX, y + zmiennaY)  ) == false)
				{
					x += zmiennaX;
					y += zmiennaY;
					roadCopy.push_back(sf::Vector2i(x, y));
					wstawil = true;
				}
			}
		}
	}
}

bool Bot::isDouble(std::vector<sf::Vector2i> roadCopy, std::vector <sf::Vector2i>& pointBeen, int x, int y)
{
	bool isDoubleHelp = false;
	for (int i = 0;i < roadCopy.size();i++)
	{
		if (sf::Vector2i(x, y) == roadCopy[i])
			isDoubleHelp = true;
	}

	for (int i = 0;i < pointBeen.size();i++)
	{
		if (sf::Vector2i(x, y) == pointBeen[i])
			isDoubleHelp = true;
	}

	return isDoubleHelp;
}