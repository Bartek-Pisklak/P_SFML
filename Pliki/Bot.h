#pragma once
#include"ButtonOne.h"
#include"Line.h"


#include <iostream>
#include <vector>
#include <ctime>


class Bot : Line
{
private:
	int whatBot;
	std::vector <sf::Vector2i> roadPoints;
	std::vector < std::vector <sf::Vector2i>> *pointBeRoadCopy;

	int buttonBoardShadow[MUCHBUTTON][MUCHBUTTON];

	int stepHorseNS[2][8] = {{ 2,2,1,1,-1,-1,-2,-2 },{-1, 1, -2, 2, -2, 2, -1, 1}};
	int stepHorseWE[2][8] = {{ -1,1,-2,2,-2,2,-1,1 },{2, 2, 1, 1, -1, -1, -2, -2}};

	bool isDouble(std::vector <sf::Vector2i> roadCopy, int x, int y);
	void createFastRoad(int x, int y);
	void graf(bool& wstawil, std::vector <sf::Vector2i>& roadCopy, std::vector < std::vector <sf::Vector2i>>& pointBeRoad, int& x, int& y, int zmiennaX, int zmiennaY);

public:

	Bot();
	Bot(std::vector <sf::Vector2i>& linePlayer, int typ);
	~Bot();

	void updateButtonBoardShadow(std::vector <sf::Vector2i>& linePlayer, ButtonOne buttonBoard[][MUCHBUTTON]);
	void roadCreate(std::vector<sf::Vector2i> lineEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end);
};

