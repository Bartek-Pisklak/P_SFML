#include "Bot.h"

Bot::Bot()
{

}


Bot::Bot(std::vector <sf::Vector2i>& linePlayer, int typ)
{
	//pointBeRoadCopy = new std::vector < std::vector <sf::Vector2i>>  [8];

	srand((unsigned)time(NULL));
	
	if (typ == 1)
	{
		whatBot = 1;
		int where = rand() % MUCHBUTTON;
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
	//delete[] pointBeRoadCopy;
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

	begin = roadPoints[0];
	end   = roadPoints[1];
}

void Bot::createFastRoad(int x,int y)
{
	std::vector < std::vector <sf::Vector2i>> *pointBeRoad;
	pointBeRoad = new std::vector < std::vector <sf::Vector2i>>[8];


	std::vector <sf::Vector2i> road;
	road.push_back(sf::Vector2i(x, y));


	int howMuchImustGoBack = 0;
	int loop = 0;

	while (lineEnemy[0].x == 0 && x != 23 )//|| lineEnemy[0].y == 0 && y != 23
	{
		bool wstawil = false;

		for (int i = 0;i < 8;i++)
		{
			graf(wstawil, road, pointBeRoad[i], x, y, stepHorse[0][i], stepHorse[1][i]);
		}

		//graf(wstawil, road , pointBeRoad, x, y, 2, 1);
		//graf(wstawil, road , pointBeRoad, x, y, 1, -2);
		//graf(wstawil, road , pointBeRoad, x, y, 1, 2);
		//graf(wstawil, road, pointBeRoad, x, y, -1, -2);
		//graf(wstawil, road, pointBeRoad, x, y, -1, 2);
		//graf(wstawil, road, pointBeRoad, x, y, -2, -1);
		//graf(wstawil, road, pointBeRoad, x, y, -2, 1);

		if (!wstawil)
		{
			loop++;
		}

		//if (loop > 4)
		//{
		//	for (int i = 0;i < 8;i++)
		//	{
		//		if (pointBeRoad[i].size() > 0)
		//		{
		//			road = pointBeRoad[i].back();
		//			x = road.back().x;
		//			y = road.back().y;
		//			pointBeRoad[i].pop_back();
		//			loop = 0;
		//		}

		//	}
		//}

		std::cout << "Road"<<wstawil<<" "<< x << "<>" << y << " " << loop << "\n";

		//if (loop > 10 && road.size() - ileMamDoCofania >= 0)
		//{
		//	loop = 0;
		//	std::cout << "musze cofac \n";
		//	ileMamDoCofania++;
		//	x = road[road.size() - ileMamDoCofania].x;
		//	y = road[road.size() - ileMamDoCofania].y;
		//	road.pop_back();
		//}
		//lineEnemy.push_back(sf::Vector2i(x,y));
		//std::cout << road.back().x<<"<>"<< road.back().y << "\n";
		//lineEnemy.push_back(road.back());
	}

	roadPoints = road;

	delete[] pointBeRoad;
}

void Bot::graf(bool& wstawil, std::vector <sf::Vector2i>& roadCopy, std::vector < std::vector <sf::Vector2i>>& pointBeRoad, int& x, int& y, int zmiennaX, int zmiennaY)
{
	if (isDouble(roadCopy, x + zmiennaX, y + zmiennaY) == false)
	{
		if ((x + zmiennaX >= 0 && x + zmiennaX < MUCHBUTTON) && (y + zmiennaY >= 0 && y + zmiennaY < MUCHBUTTON))
		{
			if (buttonBoardShadow[x + zmiennaX][y + zmiennaY] == 0)
			{
				if (checkLine(sf::Vector2i(x, y), sf::Vector2i(x + zmiennaX, y + zmiennaY)) == false)
				{
					if (wstawil == false)
					{
						x += zmiennaX;
						y += zmiennaY;
						roadCopy.push_back(sf::Vector2i(x, y));
						wstawil = true;
					}
					else
					{
						std::vector <sf::Vector2i> helpRoad;
						helpRoad = roadCopy;
						helpRoad.push_back(sf::Vector2i(x + zmiennaX, y + zmiennaY));
						pointBeRoad.push_back(helpRoad);
					}
				}
			}
		}
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