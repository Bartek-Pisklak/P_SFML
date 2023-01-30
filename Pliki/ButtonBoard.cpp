#include "ButtonBoard.h"


ButtonBoard::ButtonBoard()
{
}

ButtonBoard::ButtonBoard(float posX, float posY,float sizeB, float scaleB, short typeBot)
{
	this->typeBot = typeBot;
	enemy = Bot{ linePlayer,this->typeBot };
	float scale;
	float size;

	float x;
	float y;
	y = posY;
	scale = scaleB;
	size = sizeB;

	for (int i = 0;i < MUCHBUTTON;i++)
	{
		x = posX;
		for (int j = 0; j < MUCHBUTTON ;j++)
		{
			buttonBoard[i][j] = ButtonOne(x, y,size,  scale);
			x += 10 * scale + 15;
		}
		y += 10 * scale + 15;
	}

	initText();
}


ButtonBoard::~ButtonBoard()
{
	lineEnemy.clear();
	linePlayer.clear();
	for (int i = 0;i < MUCHBUTTON;i++)
	{
		for (int j = 0; j < MUCHBUTTON;j++)
		{
			buttonBoard[i][j].~ButtonOne();
		}
	}
	winPlayer = false;
	winEnemy = false;
	klik = false;
}



using namespace std;
void ButtonBoard::updateButtonBoard(sf::Vector2f mousePosView)
{
	if (!winEnemy && !winPlayer)
	{
		bool change = false;
		for (int i = 0;i < MUCHBUTTON;i++)
		{
			for (int j = 0;j < MUCHBUTTON;j++)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (buttonBoard[i][j].getButton().getGlobalBounds().contains(mousePosView) && buttonBoard[i][j].getLock() == 0)
					{
						gameRun(change, i, j);
						lineWin();

						break;
					}
				}
			}
		}

		// lockowanie przyciskow
		if (change)
		{
			bool stan = false;
			if (!klik)
			{
				stan = true;
			}
			for (int i = 0;i < MUCHBUTTON;i++)
			{
				for (int j = 0;j < MUCHBUTTON;j++)
				{
					buttonBoard[i][j].setLock(stan);
					if (stan)
						buttonBoard[i][j].setStan(99);
				}
			}
		}
	}
}

void ButtonBoard::setActiveButton(int x, int y, int a, int b) // i, j, gdzie gora, gdzie lewo 
{
	if ((x - a) >= 0 && (x - a) < MUCHBUTTON)
	{
		if ((y - b) >= 0)
		{
			if (buttonBoard[x - a][y - b].getEnemy() == false)
			{
				buttonBoard[x - a][y - b].setStan(4);
			}
		}
		if ((y + b) < MUCHBUTTON)
		{
			if (buttonBoard[x - a][y + b].getEnemy() == false)
			{
				buttonBoard[x - a][y + b].setStan(4);
			}
		}
	}
	return;
}


void ButtonBoard::drawButtonBoard(sf::RenderWindow* window)
{
	using namespace sf;

	for (int i = 0;i < MUCHBUTTON;i++)
	{
		for (int j = 0;j < MUCHBUTTON;j++)
		{
			window->draw(buttonBoard[i][j].getButton());
			buttonBoard[i][j].changeColor();
		}
	}

	lineDraw(window, linePlayer);
	lineDraw(window, lineEnemy);

	if (winPlayer || winEnemy)
	{
		whoWinCreateWin();
		window->draw(textWin);
	}

}



void ButtonBoard::lineWin()
{
	if (typeBot == 1)
	{
		if (lineWin_VertivalHorizontal(linePlayer) || lineWin_TwoWall(linePlayer))
		{
			winPlayer = true;
			return;
		}

		if (lineEnemy.size() > 20)
		{
			if (checkPoint(lineEnemy, 0, 99) && checkPoint(lineEnemy, 23, 99) || checkPoint(lineEnemy, 99, 0) && checkPoint(lineEnemy, 99, 23))
				winEnemy = true;
		}
	}
	else if (typeBot == 2)
	{
		if (lineWin_VertivalHorizontal(linePlayer) || lineWin_TwoWall(linePlayer))
		{

		}
		if (lineWin_VertivalHorizontal(lineEnemy) || lineWin_TwoWall(lineEnemy))
		{

		}
	}
}



void ButtonBoard::lineDraw(sf::RenderWindow* window, std::vector <sf::Vector2i> line)
{
	sf::Color color;
	if(line.size())
		color = buttonBoard[line[0].x][line[0].y].getColor();

	for (int i = 0;i < line.size();i += 2)
	{
		sf::Vector2f A = sf::Vector2f(buttonBoard[line[i].x][line[i].y].getX(),     buttonBoard[line[i].x][line[i].y].getY());
		sf::Vector2f B = sf::Vector2f(buttonBoard[line[i+1].x][line[i+1].y].getX(), buttonBoard[line[i+1].x][line[i+1].y].getY());

		sf::Vertex line[] =
		{
			sf::Vertex(A ,color, A),
			sf::Vertex(B ,color, B)
		};

		window->draw(line, 2, sf::Lines);
	}
}



void ButtonBoard::gameRun(bool& change, int i, int j)
{
	if (buttonBoard[i][j].getStan() != 0 && buttonBoard[i][j].getPress() == false && !klik)
	{
		change = true;
		klik = true;

		buttonBoard[i][j].setStan(2);
		pressButton[0] = i;
		pressButton[1] = j;

		setActiveButton(i, j, 2, 1);
		setActiveButton(i, j, 1, 2);
		setActiveButton(i, j, -2, 1);
		setActiveButton(i, j, -1, 2);
	}
	else if (buttonBoard[i][j].getPress() && klik)
	{
		change = true;
		klik = false;

		buttonBoard[i][j].setStan(99);

	}
	else if (buttonBoard[i][j].getActive() && klik)
	{
		if (checkLine(sf::Vector2i(i, j), sf::Vector2i(pressButton[0], pressButton[1]),linePlayer))
			return;

		change = true;
		klik = false;
		buttonBoard[i][j].setStan(1);
		buttonBoard[pressButton[0]][pressButton[1]].setStan(1);

		createLine(sf::Vector2i(pressButton[0], pressButton[1]), sf::Vector2i(i, j), linePlayer);


		sf::Vector2i beginLineEnemy;
		sf::Vector2i endLineEnemy;

		try
		{
			enemy.updateButtonBoardShadow(this->linePlayer, this->buttonBoard);
			enemy.roadCreate(lineEnemy, beginLineEnemy, endLineEnemy);
			buttonBoard[beginLineEnemy.x][beginLineEnemy.y].setStan(0);
			buttonBoard[endLineEnemy.x][endLineEnemy.y].setStan(0);
			createLine(beginLineEnemy, endLineEnemy, lineEnemy);
		}
		catch (out_of_range www)
		{
			cout << "przeciwnik zachorował poddaje sie (powod algorytm sie wywalil bota)" << endl;
			winPlayer = true;
		}


	}
}



void ButtonBoard::initText()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "nie ma czcionki" << endl;
	}

	textWin.setPosition(150, 350);
	textWin.setCharacterSize(80);
	textWin.setStyle(sf::Text::Bold);
}

void ButtonBoard::whoWinCreateWin()
{
	if (winPlayer)
		textWin.setString("Wygral Gracz");
	if (winEnemy)
		textWin.setString("Wygral Przeciwnik");

	textWin.setFont(font);
	textWin.setFillColor(sf::Color::Yellow);
}


bool ButtonBoard::lineWin_VertivalHorizontal(std::vector <sf::Vector2i> line)
{
	if (checkPoint(line, 0, 99) && checkPoint(line, 23, 99) || checkPoint(line, 99, 0) && checkPoint(line, 99, 23))
	{
		std::vector<sf::Vector2i> start;
		if (checkPoint(line, 0, 99))
		{
			for (int i = 0;i < line.size();i++)
			{
				if (line[i].x == 0)
				{
					start.push_back(line[i]);
				}
			}
		}
		if (checkPoint(line, 99, 0))
		{
			for (int i = 0;i < line.size();i++)
			{
				if (line[i].y == 0)
				{
					start.push_back(line[i]);
				}
			}
		}


		int stepHorse[2][8] = { { 2,2,1,1,-1,-1,-2,-2 },{-1, 1, -2, 2, -2, 2, -1, 1} };
		sf::Vector2i search;
		std::vector<sf::Vector2i> searchBack;
		std::vector<sf::Vector2i> endSearch;
		std::vector<sf::Vector2i> I_WAS_HERE;

		int kh = 0;
		for (int k = 0;k < start.size() || kh < searchBack.size();k++)
		{
			if (k < start.size())
			{
				search = start[k];
			}
			else
			{
				search = searchBack[kh];
				kh++;
			}

			for (int i = 0;i < line.size();i++)
			{
				bool one = false;
				for (int j = 0;j < 8;j++)
				{
					if (search.x + stepHorse[0][j] >= 0 && search.x + stepHorse[0][j] < MUCHBUTTON)
					{
						if (search.y + stepHorse[1][j] >= 0 && search.y + stepHorse[1][j] < MUCHBUTTON)
						{

							if (!checkPoint(line, search.x + stepHorse[0][j], search.y + stepHorse[1][j]))
							{
							}
							else if (!one && !checkPoint(I_WAS_HERE, search.x + stepHorse[0][j], search.y + stepHorse[1][j]))
							{
								I_WAS_HERE.push_back(search);
								search.x += stepHorse[0][j];
								search.y += stepHorse[1][j];
								one = true;

							}
							else if (one && !checkPoint(I_WAS_HERE, search.x + stepHorse[0][j], search.y + stepHorse[1][j]))
							{
								searchBack.push_back(sf::Vector2i(search.x + stepHorse[0][j], search.y + stepHorse[1][j]));
							}
						}
					}
				}
			}
			for (int c = 0;c < searchBack.size();c++)
			{
				if (checkPoint(I_WAS_HERE, searchBack[c].x, searchBack[c].y))
				{
					searchBack.erase(searchBack.begin() + c);
				}
			}
			endSearch.push_back(search);

			for (int e = 0;e < endSearch.size();e++)
			{
				if (endSearch[e].x == MUCHBUTTON - 1 || endSearch[e].y == MUCHBUTTON - 1)
				{
					return true;
				}
				if (endSearch[e].x == 0 && checkPoint(line, 23, 99) || endSearch[e].y == 0 && checkPoint(line, 99, 23)	)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool ButtonBoard::lineWin_TwoWall(std::vector <sf::Vector2i> line)
{
	if (line.size() / 2 < 7)
	{
		return false;
	}
	if ((checkPoint(line, 0, 99) && checkPoint(line, 99, MUCHBUTTON - 1)) || (checkPoint(line, 0, 99) && checkPoint(line,99,0)) || (checkPoint(line, MUCHBUTTON - 1, 99) && checkPoint(line, 99, 0)) || (checkPoint(line, MUCHBUTTON - 1, 99) && checkPoint(line, 99, MUCHBUTTON - 1)))
	{
		std::vector<sf::Vector2i> start;
		if (checkPoint(line, 0, 99))
		{
			for (int i = 0;i < line.size();i++)
			{
				if (line[i].x == 0)
				{
					start.push_back(line[i]);
				}
			}
		}
		if (checkPoint(line, 23, 99))
		{
			for (int i = 0;i < line.size();i++)
			{
				if (line[i].x == MUCHBUTTON-1)
				{
					start.push_back(line[i]);
				}
			}
		}

		int stepHorse[2][8] = { { 2,2,1,1,-1,-1,-2,-2 },{-1, 1, -2, 2, -2, 2, -1, 1} };
		sf::Vector2i search;
		std::vector<sf::Vector2i> searchBack;
		std::vector<sf::Vector2i> endSearch;
		std::vector<sf::Vector2i> I_WAS_HERE;

		int kh = 0;
		for (int k = 0;k < start.size() || kh < searchBack.size();k++)
		{
			if (k < start.size())
			{
				search = start[k];
			}
			else
			{
				search = searchBack[kh];
				kh++;
			}

			for (int i = 0;i < line.size();i++)
			{
				bool one = false;
				for (int j = 0;j < 8;j++)
				{
					if (search.x + stepHorse[0][j] >= 0 && search.x + stepHorse[0][j] < MUCHBUTTON)
					{
						if (search.y + stepHorse[1][j] >= 0 && search.y + stepHorse[1][j] < MUCHBUTTON)
						{

							if (!checkPoint(line, search.x + stepHorse[0][j], search.y + stepHorse[1][j]))
							{
							}
							else if (!one && !checkPoint(I_WAS_HERE, search.x + stepHorse[0][j], search.y + stepHorse[1][j]))
							{
								I_WAS_HERE.push_back(search);
								search.x += stepHorse[0][j];
								search.y += stepHorse[1][j];
								one = true;

							}
							else if (one && !checkPoint(I_WAS_HERE, search.x + stepHorse[0][j], search.y + stepHorse[1][j]))
							{
								searchBack.push_back(sf::Vector2i(search.x + stepHorse[0][j], search.y + stepHorse[1][j]));
							}
						}
					}
				}
			}
			for (int c = 0;c < searchBack.size();c++)
			{
				if (checkPoint(I_WAS_HERE, searchBack[c].x, searchBack[c].y))
				{
					searchBack.erase(searchBack.begin() + c);
				}
			}
			endSearch.push_back(search);

			for (int e = 0;e < endSearch.size();e++)
			{
				int pktEnemy = 0;
				sf::Vector2i cube = endSearch[e];
				bool pageL_R = true;

				if (endSearch[e].y == 0 && checkPoint(line, 0, 99)) //L G
				{
					sf::Vector2i go = cube;
					go.x--;
					while (buttonBoard[0][go.y].getPlayer() == false)
					{
						if (buttonBoard[go.x][go.y].getEnemy() == true)
						{
							pktEnemy++;
						}

						if (go.x == 0  || cube.x == go.x && pageL_R == false)
						{
							pageL_R = !pageL_R;
							go.y++;
						}

						if (pageL_R)
						{
							go.x--;
						}
						else
						{
							go.x++;
						}
					}
				}
				else if (endSearch[e].y == 0 && checkPoint(line, MUCHBUTTON - 1, 99)) // L D
				{
					sf::Vector2i go = cube;
					go.x++;
					pageL_R = false;

					while (buttonBoard[MUCHBUTTON-1][go.y].getPlayer() == false)
					{
						if (buttonBoard[go.x][go.y].getEnemy() == true)
						{
							pktEnemy++;
						}

						if (go.x == MUCHBUTTON-1 || cube.x == go.x && pageL_R == true)
						{
							pageL_R = !pageL_R;
							go.y++;
						}

						if (pageL_R)
						{
							go.x--;
						}
						else
						{
							go.x++;
						}
					}
				}
				else if (endSearch[e].y == MUCHBUTTON - 1 && checkPoint(line, 0, 99)) // G P
				{
					sf::Vector2i go = cube;
					go.x--;

					while (buttonBoard[0][go.y].getPlayer() == false)
					{
						if (buttonBoard[go.x][go.y].getEnemy() == true)
						{
							pktEnemy++;
						}

						if (go.x == 0 || cube.x == go.x && pageL_R == false)
						{
							pageL_R = !pageL_R;
							go.y--;
						}

						if (pageL_R)
						{
							go.x--;
						}
						else
						{
							go.x++;
						}
					}
				}
				else if (endSearch[e].y == MUCHBUTTON - 1 && checkPoint(line, MUCHBUTTON-1, 99)) // D P
				{
					sf::Vector2i go = cube;
					go.x++;
					pageL_R = false;

					while (buttonBoard[MUCHBUTTON - 1][go.y].getPlayer() == false)
					{
						cout << go.x << " " << go.y << endl;
						if (buttonBoard[go.x][go.y].getEnemy() == true)
						{
							pktEnemy++;
						}

						if (go.x == MUCHBUTTON - 1 || cube.x == go.x && pageL_R == true)
						{
							pageL_R = !pageL_R;
							go.y--;
						}

						if (pageL_R)
						{
							go.x--;
						}
						else
						{
							go.x++;
						}
					}
				}

				if (pktEnemy >= lineEnemy.size() / 3)
				{
					return true;
				}
			}
		}


	}
	return false;
}

