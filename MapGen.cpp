#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
int RndNum(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
int main()
{
	setlocale(0, "");

	using namespace std;

	int large = 20;
	string level[30][30];

	for (int i = 0; i < large; i++)
	{
		for (int j = 0; j < large; j++)
		{
			level[i][j] = "o";
		}
	}

	srand(time(NULL));
	int pointX = RndNum(1, large - 9);
	int pointy = RndNum(1, large - 9);
	int Vertical;
	int Horizontal;

	int ran = RndNum(4, 8);

	int ran1 = RndNum(4, 8);

	do
	{


		
		Vertical = pointy + ran;
		Horizontal = pointX + ran1;
	} while (Vertical > large && Horizontal > large);


	for (int i = pointy; i < Vertical; i++)
	{
		for (int j = pointX; j < Horizontal; j++)
		{
			level[i][j] = "Ш";
		}


		for (int i = pointy + 1; i < Vertical - 1; i++)
		{
			for (int j = pointX + 1; j < Horizontal - 1; j++)
			{
				level[i][j] = " ";
			}
		}
	}


		//счетчик пространства за пределами комнаты !!!!!!!(k=pointy, k2=pontX (потом нужно будет это говно поменять))!!!!!!!!
		int k = 0, l = 0, k2 = 0, l2 = 0;
		for (int i = 0; i < pointy; i++)
		{
			if (level[i][1] == "o") {
				k++;// кол-во символов c верху до середины
			}
		}
		for (int i = (Vertical); i < large; i++)
		{
			if (level[i][1] == "o") {
				l++;// кол-во символов с середины до низа
			}
		}
		for (int j = 0; j < pointX; j++)
		{
			if (level[1][j] == "o") {
				k2++;// кол-во символов cлева до середины
			}
		}
		for (int j = (Horizontal); j < large; j++)
		{
			if (level[1][j] == "o") {
				l2++;// кол-во символов с середины до правой стороны
			}
		}



		//Рандомный выбор выхода из комнаты сверху по вертикали
		srand(time(0));
		int Vertica = Vertical - 2;
		int ran3 = RndNum(pointy + 1, (Vertica));
		//Рандомный выбор выхода из комнаты слева по горизонтали
		srand(time(0));
		int Horizonta = Horizontal - 2;
		int ran4 = RndNum(pointX + 1, (Horizonta));
		//рандомный выбор выхода из комнаты справа по вертикали

		if (k >= k2 && k >= l && k >= l2)
		{

			level[pointy][ran4] = "К";
		}
		else if (k2 >= k && k2 >= l && k2 >= l2)
		{

			level[ran3][pointX] = "К";
		}
		else if (l >= k && l >= l2 && l >= k2)
		{
			level[Vertical - 1][ran4] = "К";

		}
		else if (l2 >= k && l2 >= l && l2 >= k2)
		{

			level[ran3][Horizontal - 1] = "К";
		}



		for (int i = 0; i < large; i++)
		{
			for (int j = 0; j < large; j++)
			{
				cout << (level[i][j]);
			}
			cout << endl;
		}

		cout << endl;
		cout << "H= " << Horizontal;

		cout << endl;
		cout << "V= " << Vertical;

		cout << endl;
		cout << "X=" << pointX;

		cout << endl;
		cout << "Y=" << pointy;

		cout << endl;
		cout << "сверху до середины " << k;

		cout << endl;
		cout << "слева до середины " << k2;


		cout << endl;
		cout << "с середины до низу " << l;


		cout << endl;
		cout << "с середины до права " << l2;

		cout << endl;
		cout << "ran3 " << ran3;
		cout << endl;
		cout << "ran4 " << ran4;
		cout << endl;
		cout << "ran " << ran;
		cout << endl;
		cout << "ran1 " << ran1;

		
		return 0;
	
}