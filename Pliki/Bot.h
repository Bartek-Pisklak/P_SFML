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

	int buttonBoardShadow[MUCHBUTTON][MUCHBUTTON];
	bool whereGo[4] = { 1,0,0,0 };//S N W E

	int stepHorseNS[2][8] = {{ 2,2,1,1,-1,-1,-2,-2 },{-1, 1, -2, 2, -2, 2, -1, 1}};
	int stepHorseWE[2][8] = {{ -1,1,-2,2,-2,2,-1,1 },{2, 2, 1, 1, -1, -1, -2, -2}};

	bool LEFT_WAS  = false;
	bool RIGHT_WAS = false;

	bool isDouble(std::vector <sf::Vector2i> roadCopy, int x, int y);
	void createFastRoad(int x, int y);
	void graf(bool& isInTable, std::vector <sf::Vector2i>& roadCopy, int& x, int& y, int zmiennaX, int zmiennaY);

	void clearWhereGo();
	void S_GO(bool& isInTable, std::vector <sf::Vector2i>& roadCopy, int& x, int& y);
	void N_GO(bool& isInTable, std::vector <sf::Vector2i>& roadCopy, int& x, int& y);
	void W_GO(bool& isInTable, std::vector <sf::Vector2i>& roadCopy, int& x, int& y);
	void E_GO(bool& isInTable, std::vector <sf::Vector2i>& roadCopy, int& x, int& y);
public:

	Bot();
	Bot(std::vector <sf::Vector2i>& linePlayer, int typ);
	~Bot();

	void updateButtonBoardShadow(std::vector <sf::Vector2i>& linePlayer, ButtonOne buttonBoard[][MUCHBUTTON]);
	void roadCreate(std::vector<sf::Vector2i> lineEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end);
};

