#include "Macierz.h"
#include <iostream>
#include <random>
#include <list>
#include "algMacierz.h"
#include "MSTree1.h"
#include <string>
#include <fstream>


using namespace std;



Macierz::Macierz(int wierzcholki, int krawedzie, int start)
{
	wymiar = wierzcholki;
	liczbaKrawedzi = krawedzie;
	startowy = start;
	a = new int *[wymiar];
	for (int i = 0; i < wymiar; i++)
	{
		a[i] = new int[wymiar];
	}

	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			a[i][j] = MAXINT;
		}
	}

}


Macierz::~Macierz()
{
	for (int i = 0; i < wymiar; i++)
		delete[] a[i];
	delete[] a;
}



void Macierz::losowaNieskMacierz()
{

	int v1, v2, waga;

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(0, wymiar-1); // distribute results between
											// 1 and 1000000 inclusive
	a = new int *[wymiar];
	for (int i = 0; i < wymiar; i++)
	
		a[i] = new int[wymiar];


	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		a[i][j] = -1;
	}

	for (int i = 0; i < liczbaKrawedzi; i++)
	{
		do
		{
			v1 = dist(gen);
			v2 = dist(gen);
			waga = dist(gen) + 1;
		} while (a[v1][v2] > 0 || a[v2][v1] > 0 || v1 == v2);
		a[v1][v2] = waga;
		a[v2][v1] = waga;
	}

}

void Macierz::losowaMacierz()
{
	cout << endl << "Podaj liczbe wierzcholkow grafu: ";
	cin >> wymiar;

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(1, 10); // distribute results between
											// 1 and 1000000 inclusive
	a = new int *[wymiar];
	for (int i = 0; i < wymiar; i++)
	{
		a[i] = new int[wymiar];
	}

	// Wype³nienie macierzy wartoœciami MAXINT
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			a[i][j] = MAXINT;
		}
	}

	// Ka¿dy z wierzcho³ków ³¹czy siê z nastêpnikiem, ostatni ³¹czy siê z zerowym. Wszystkie wagi s¹ losowe.
	for (int i = 0; i < wymiar; i++)
	{
		if (i < wymiar - 1)
		{
			a[i][i + 1] = dist(gen);
			liczbaKrawedzi++;
		}
		else if (i == wymiar - 1)
		{
			a[i][0] = dist(gen);
			liczbaKrawedzi++;
		}
	}
}

void Macierz::wyswietlMacierz()
{
	cout << endl << "Graf w postaci macierzy: " << endl << endl;

	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (a[i][j] != MAXINT)
			{
				cout << "          " << i  << " -> " << j << ": " << a[i][j] << endl;
			}
		}
	}

	cout << endl << endl;
}

void Macierz::MSTPrim()
{
	// Tworzymy kopiê grafu, zmieniaj¹c j¹ na graf skierowany i wysy³aj¹c j¹ do funkcji.

	Macierz *G;

	G = new Macierz(wymiar, liczbaKrawedzi, startowy);

	G->a = a;

	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (G->a[i][j] != MAXINT)G->a[j][i] = G->a[i][j];
		}
	}

	algMacierz *mstree;
	mstree = new algMacierz(wymiar, liczbaKrawedzi, startowy);

	mstree -> MSTreePrimMacierz(wymiar, liczbaKrawedzi, G->a);


}

void Macierz::przykladowaMacierzSkierowana()
{
	wymiar = 6;
	liczbaKrawedzi = 9;

	for (int i = 0; i < wymiar; i++)
	{
		a[i] = new int[wymiar];
		for (int j = 0; j < wymiar; j++)
		{
			a[i][j] = MAXINT;
		}
	}


	a[0][1] = 3;

	a[0][4] = 3;

	a[1][2] = 1;

	a[2][3] = 3;

	a[2][5] = 1;

	a[3][1] = 3;

	a[4][5] = 2;

	a[5][0] = 6;

	a[5][3] = 1;

}

void Macierz::Dijkstry()
{
	algMacierz *dijkstry;
	dijkstry = new algMacierz(wymiar, liczbaKrawedzi, startowy);

	dijkstry->Dijkstry(wymiar, liczbaKrawedzi, a);
}

void Macierz::przykladowaMacierzNieskierowana()
{
	wymiar = 5;
	liczbaKrawedzi = 7;

	for (int i = 0; i < wymiar; i++)
	{
		a[i] = new int[wymiar];
		for (int j = 0; j < wymiar; j++)
		{
			a[i][j] = MAXINT;
		}
	}

	a[0][1] = 1;

	a[0][2] = 3;

	a[2][3] = 4;

	a[3][1] = 6;

	a[2][1] = 3;

	a[2][4] = 2;
	
	a[4][3] = 5;

	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (a[i][j] != MAXINT) a[j][i] = a[i][j];
		}
	}
}

void Macierz::losowyGrafgestosc(int wierzcholki, int gestosc)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(0, wierzcholki); // distribute results between
											// 1 and 1000000 inclusive



	int maxK = (wierzcholki*(wierzcholki - 1))/2;
	liczbaKrawedzi = (maxK * gestosc) / 100;
	int licznikKrawedzi = 0, i, j, waga;

	for (int i = 0; i < wierzcholki; i++)
	{
		if (i < wierzcholki - 1)
		{
			a[i][i + 1] = (rand() % 21) + 90;
			licznikKrawedzi++;
		}

		else if (i == wierzcholki - 1)
		{
			a[i][0] = (rand() % 21) + 90;
			licznikKrawedzi++;
		}
	}

	while (licznikKrawedzi < liczbaKrawedzi)
	{
		do 
		{
			i = dist(gen);
			j = dist(gen);
		} while (i == j || a[i][j] != MAXINT);

		waga = (rand() % 1) + 20;

		a[i][j] = waga;
		licznikKrawedzi++;

	}
}