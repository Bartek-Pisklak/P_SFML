#include "Bot.h"

Bot::Bot()
{

}


Bot::Bot(std::vector <sf::Vector2i>& liniePlayer, int typ)
{
	srand(time(NULL));
	
	if (typ == 1)
	{
		whatBot = 1;
		int where = rand() % rozmiar;
		if(1)//if (rand() % 2 == 0)
		{
			linieEnemy.push_back(sf::Vector2i(0, where));
		}
		else
		{
			linieEnemy.push_back(sf::Vector2i(where, 0));
		}
	}

	this->liniePlayer = liniePlayer;
}

Bot::~Bot()
{
}

void Bot::updatePlanszaShadow(std::vector <sf::Vector2i>& liniePlayer, ButtonOne plansza[][rozmiar])
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

	this->liniePlayer = liniePlayer;
}

void Bot::droga(std::vector<sf::Vector2i> linieEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end)
{
	if(linieEnemy.size()<linieEnemyCurrent.size())
		linieEnemy = linieEnemyCurrent;

	createFastDroga(linieEnemy.back().x, linieEnemy.back().y);

	std::cout << "\n";
	for (int i = 0;i < roadPoints.size();i++)
	{
		std:: cout << roadPoints[i].x <<"<>" << roadPoints[i].y << std::endl;
	}


	begin = roadPoints[0];
	end   = roadPoints[1];
}


void Bot::normalLVL()
{


}


void Bot::createFastDroga(int x,int y)
{

	std::vector <sf::Vector2i> trasa;
	trasa.push_back(sf::Vector2i(x, y));
		
	int ileMamDoCofania = 0;

	while ( x != 23)
	{
		bool wstawil = false;

		graf(wstawil, trasa , x, y, 2, -1);
		graf(wstawil, trasa , x, y, 2, 1);


		graf(wstawil, trasa , x, y, 1, -2);
		graf(wstawil, trasa , x, y, 1, 2);

		graf(wstawil, trasa, x, y, -1, -2);
		graf(wstawil, trasa, x, y, -1, 2);

		graf(wstawil, trasa, x, y, -2, -1);
		graf(wstawil, trasa, x, y, -2, 1);


		std::cout << "droga"<<wstawil<<x<<"<>"<<y<<"\n";

		if (!wstawil && ileMamDoCofania< trasa.size())
		{
			std::cout << "musze cofac \n";
			ileMamDoCofania++;
			x = trasa[trasa.size() - ileMamDoCofania].x;
			y = trasa[trasa.size() - ileMamDoCofania].y;
			trasa.erase(trasa.end());
		}
	}
	std::cout << "mam";
	roadPoints = trasa;
}

void Bot::graf(bool& wstawil, std::vector <sf::Vector2i>& trasaKopia, int& x, int& y, int zmiennaX, int zmiennaY)
{
	if (wstawil == false)
	{
		if ((x + zmiennaX >= 0 && x + zmiennaX < rozmiar) && (y + zmiennaY >= 0 && y + zmiennaY < rozmiar))
		{
			if (planszaShadow[x + zmiennaX][y + zmiennaY] == 0)
			{
				if (checkLine(sf::Vector2i(x, y), sf::Vector2i(x + zmiennaX, y + zmiennaY)) == false)
				{
					x += zmiennaX;
					y += zmiennaY;
					trasaKopia.push_back(sf::Vector2i(x, y));
					wstawil = true;
				}
			}
		}
	}
}
