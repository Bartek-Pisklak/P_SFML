#include "Line.h"

bool Line::checkLine(sf::Vector2i A, sf::Vector2i B)
{

	for (int i = 0;i < linePlayer.size();i += 2)
	{
		sf::Vector2i C = linePlayer[i];
		sf::Vector2i D = linePlayer[1 + i];

		float	v1 = vector_product(C, D, A);
		float	v2 = vector_product(C, D, B);
		float	v3 = vector_product(A, B, C);
		float	v4 = vector_product(A, B, D);

		if (v1 * v2 < 0 && v3 * v4 < 0)
			return true;

		if (A == C && B == D || A == D && B == C)
		{
			return true;
		}
	}

	for (int i = 0;i < lineEnemy.size() && lineEnemy.size() >= 2;i += 2)
	{
		sf::Vector2i C = lineEnemy[i];
		sf::Vector2i D = lineEnemy[1 + i];

		float	v1 = vector_product(C, D, A);
		float	v2 = vector_product(C, D, B);
		float	v3 = vector_product(A, B, C);
		float	v4 = vector_product(A, B, D);

		if (v1 * v2 < 0 && v3 * v4 < 0)
			return true;

		if (A == C && B == D || A == D && B == C)
			return true;
	}
	return false;
}

float Line::vector_product(sf::Vector2i X, sf::Vector2i Y, sf::Vector2i Z)
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