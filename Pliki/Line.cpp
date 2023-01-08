#include "Line.h"

bool Line::checkLine(sf::Vector2i A, sf::Vector2i B)
{

	for (int i = 0;i < liniePlayer.size();i += 2)
	{
		sf::Vector2i C = liniePlayer[i];
		sf::Vector2i D = liniePlayer[1 + i];

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

	for (int i = 0;i < linieEnemy.size() && linieEnemy.size() >= 2;i +=2)
	{
		sf::Vector2i C = linieEnemy[i];
		sf::Vector2i D = linieEnemy[1 + i];

		float	v1 = iloczyn_wektorowy(C, D, A);
		float	v2 = iloczyn_wektorowy(C, D, B);
		float	v3 = iloczyn_wektorowy(A, B, C);
		float	v4 = iloczyn_wektorowy(A, B, D);

		if (v1 * v2 < 0 && v3 * v4 < 0)
			return true;

		if (B == linieEnemy[i])
			return true;
	}
	return false;
}

float Line::iloczyn_wektorowy(sf::Vector2i X, sf::Vector2i Y, sf::Vector2i Z)
{
	float x1 = Z.x - X.x;
	float y1 = Z.y - X.y;
	float x2 = Y.x - X.x;
	float y2 = Y.y - X.y;

	return x1 * y2 - x2 * y1;
}

void Line::createLine(sf::Vector2i A, sf::Vector2i B, std::vector<sf::Vector2i>& linia)
{
	linia.push_back(A);
	linia.push_back(B);
}
