

/*/
		if ((v1 > 0 && v2 < 0 || v1 < 0 && v2>0) && (v3 > 0 && v4 < 0 || v3 < 0 && v4>0))
			return true;


if (plansza[i][j].getStan() == 4) // linie
{
	plansza[i][j].setStan(1);

	setActiveButton(pressButton[0], pressButton[1], 2, 1, 99);
	setActiveButton(pressButton[0], pressButton[1], 1, 2, 99);
	setActiveButton(pressButton[0], pressButton[1], -2, 1, 99);
	setActiveButton(pressButton[0], pressButton[1], -1, 2, 99);

	plansza[pressButton[0]][pressButton[1]].setStan(1);
	createLine(plansza[pressButton[0]][pressButton[1]], plansza[i][j]);

	click = true;
}


if (plansza[i][j].getPress() && plansza[i][j].getStan() == 2) // klik i wylaczenie kliku na guzikach
{
	click = true;
	plansza[i][j].setStan(99);
	cout << "wylacza klik" << endl;

	setActiveButton(i, j, 2, 1, 99);
	setActiveButton(i, j, 1, 2, 99);
	setActiveButton(i, j, -2, 1, 99);
	setActiveButton(i, j, -1, 2, 99);
}
else if (plansza[i][j].getStan() != 0 && plansza[i][j].getStan() != 2)
{
	click = true;
	plansza[i][j].setStan(2);
	pressButton[0] = i;
	pressButton[1] = j;

	setActiveButton(i, j, 2, 1, 4);
	setActiveButton(i, j, 1, 2, 4);
	setActiveButton(i, j, -2, 1, 4);
	setActiveButton(i, j, -1, 2, 4);
}
	*/			