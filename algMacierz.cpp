#include "algMacierz.h"
#include <iostream>
#include <queue>
#include <limits>
#include "Lista.h"


using namespace std;

struct algMacierz::Krawedz
{
	int v1, v2, waga;               // Wierzcho�ki i waga kraw�dzi
};

struct algMacierz::TNode
{
	TNode * next;
	int v, waga;
};


struct algMacierz::porownajWagi
{
	bool operator ()(const Krawedz & waga1, const Krawedz & waga2)
	{
		//kolejno�� - rosn�co
		if (waga1.waga > waga2.waga) return true;

		if (waga1.waga < waga2.waga) return false;

		return false;
	}
};

algMacierz::algMacierz(int n, int m, int start) //int wierzcho�ki, int kraw�dzie
{
	startowy = start;
	int i;
	A = new TNode *[n];            // Tworzymy tablic� dynamiczn� (list)
	for (i = 0; i < n; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = n - 1;                   // Zapami�tujemy d�ugo�� tablicy
	waga = 0;                     // Zerujemy wag� drzewa
	kk = new Krawedz[m];		// Tworzymy tablic� kraw�dzi w drzewie rozpinaj�cym (do wy�wietlania drzewa)
	a = 0;
}

// Destruktor - usuwa listy oraz tablic� s�siedztwa
//-------------------------------------------------
algMacierz::~algMacierz()
{
	TNode *p, *r;

	for (int i = 0; i <= Alen; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;                      // Zapami�tujemy wskazanie
			p = p->next;                // Przesuwamy si� do nast�pnego elementu listy
			delete r;                   // Usuwamy element
		}
	}

	delete[] A;                    // Usuwamy tablic� list s�siedztwa
	delete[] kk;
}

// Dodaje kraw�d� do drzewa
//-------------------------
void algMacierz::dodajKrawedz(Krawedz k)
{
	TNode *p;

	waga += k.waga;             // Do wagi drzewa dodajemy wag� kraw�dzi
	p = new TNode;                  // Tworzymy nowy w�ze�
	p->v = k.v2;                    // Wierzcho�ek ko�cowy
	p->waga = k.waga;           // Waga kraw�dzi
	p->next = A[k.v1];              // Dodajemy p do listy wierzcho�ka v1
	A[k.v1] = p;

	p = new TNode;                  // To samo dla kraw�dzi odwrotnej
	p->v = k.v1;                    // Wierzcho�ek ko�cowy
	p->waga = k.waga;           // Waga kraw�dzi
	p->next = A[k.v2];              // Dodajemy p do listy wierzcho�ka v2
	A[k.v2] = p;

	kk[a] = k;
	a++;
}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka
//----------------------------------------------------
algMacierz::TNode * algMacierz::getAList(int n)
{
	return A[n];
}

// Wy�wietla zawarto�� drzewa oraz jego wag�
//------------------------------------------
void algMacierz::wyswietl()
{
	cout << endl << "MST na podstawie macierzy. Algorytm Prima:" << endl << endl;

	cout << endl;
	for (int i = 0; i < a; i++)
	{

		cout << "Krawedz " << i + 1 << ": ";

		cout << kk[i].v1 << "<-->" << kk[i].v2 << "   [" << kk[i].waga << "] ";

		cout << endl;
	}
	cout << endl << endl << "Waga minimalnego drzewa rozpinajacego = " << waga << endl << endl;
}



void algMacierz::MSTreePrimMacierz(int n, int m, int **a)           //n liczba wierzcho�k�w, m liczba kraw�dzi, a graf
{
	Krawedz k;

	int i, v, licznik = 0;



	typedef std::priority_queue < Krawedz, std::vector < Krawedz >, porownajWagi > TKolejkaPriorytetowaKrawedzi;

	TKolejkaPriorytetowaKrawedzi Q;

	algMacierz T(n, m, startowy);                    // Minimalne drzewo rozpinaj�ce

	bool * odwiedzone = new bool[n];

	bool istnieje = false;

	for (i = 0; i < n; i++)
		odwiedzone[i] = false;           // Inicjujemy tablic� odwiedzin


										 // Tworzymy minimalne drzewo rozpinaj�ce

	v = 0;                          // Wierzcho�ek startowy
	odwiedzone[v] = true;              // Oznaczamy go jako odwiedzonego

	while (licznik < n - 1)          // Do drzewa dodamy m - 1 kraw�dzi grafu
	{

 // Przegl�damy list� s�siad�w

		for (int j = 0; j < n; j++)
		{

			if (!odwiedzone[j])          // Je�li s�siad jest nieodwiedzony,
			{
				if (a[v][j] != MAXINT)
				{
					istnieje = true;
					k.v1 = v;                 // to tworzymy kraw�d�
					k.v2 = j;
					k.waga = a[v][j];
					Q.push(k);                // Dodajemy j� do kolejki priorytetowej
				}
			}
		}

		if (istnieje)
		{
			if (!Q.empty())
				do
				{
					k = Q.top();              // Pobieramy kraw�d� z kolejki
					Q.pop();
				} while (odwiedzone[k.v2] && !Q.empty());
				// Kraw�d� prowadzi poza drzewo?


				T.dodajKrawedz(k);   licznik++;              // Dodajemy kraw�d� do drzewa rozpinaj�cego
				odwiedzone[k.v2] = true;         // Oznaczamy drugi wierzcho�ek jako odwiedzony

				v = k.v2;
		}
		else if (!istnieje)v++;
	}

	// Wy�wietlamy wyniki

	T.wyswietl();

}

void algMacierz::Dijkstry(int wierzcholki, int krawedzie, int **a)
{
	bool *przebadany;
	int *d, *p, *pk, u;
	Krawedz k;

	typedef std::priority_queue < Krawedz, std::vector < Krawedz >, porownajWagi > TKolejkaPriorytetowaKrawedzi;
	TKolejkaPriorytetowaKrawedzi Q;


	// Tworzymy tablice dynamiczne

	d = new int[wierzcholki];                // Tablica koszt�w doj�cia
	p = new int[wierzcholki];                // Tablica poprzednik�w
	pk = new int[wierzcholki];				 // Kopia tablicy poprzednik�w (uzywana do wypisywania sciezki)
	przebadany = new bool[wierzcholki];              // Zbiory Q i S

													 // Inicjujemy tablice dynamiczne

	for (int i = 0; i < wierzcholki; i++)
	{
		d[i] = MAXINT;
		p[i] = NULL;
		pk[i] = NULL;
		przebadany[i] = false;
	}

	d[startowy] = 0;                       // Koszt doj�cia v jest zerowy
	p[startowy] = startowy;

	//Szukamy wierzcho�ka o najmniejszym koszcie ze wszystkich nie przebadanych, przy u�yciu kolejki priorytetowej
	for (int i = 0; i < wierzcholki; i++)
	{

		for (int i = 0; i < wierzcholki; i++)
		{
			if (!przebadany[i])
			{
				k.v1 = i;
				k.waga = d[i];
				Q.push(k);
			}
		}

		// W u znajdzie si� numer wierzcho�ka o najmniejszym koszcie
		k = Q.top();
		while (!Q.empty()) Q.pop();
		u = k.v1;

		// Dla ka�dego z s�siad�w u je�li d[s�siad] > d[u] + waga(u -> s�siad)
		// to dokonujemy relaksacji wierzcho�ka s�siad
		for (int i = 0; i < wierzcholki; i++)
		{
			for (int j = 0; j < wierzcholki; j++)
			{
				if (a[u][j] != MAXINT)
				{
					if (d[j] > d[u] + a[u][j])
					{
						d[j] = d[u] + a[u][j];
						p[j] = u;
					}
				}
			}
		}

		// Oznaczamy wierzcho�ek u jako przebadany
		przebadany[u] = true;
	}

	//Wypiujemy wyniki

	cout << endl << "Algorytm Dijkstry na podstawie macierzy:" << endl << endl;


		int j = 0;

		bool czyStartowy = false;

		for (int i = 0; i < wierzcholki; i++)
		{
			pk[i] = p[i];
		}

		cout << endl << "Start = " << startowy << endl << endl;

		cout << "          " << "End" << "    Dist" << "      Patch" << endl << endl;


		for (int i = 0; i < wierzcholki; i++)
		{
			czyStartowy = false;

			cout << "          " << i << "   |   " << d[i] << "   |   " << i << " ";

			while (!czyStartowy)
			{
				if (pk[i] == startowy) czyStartowy = true;
				cout << pk[i] << " ";
				j = pk[i];
				pk[i] = pk[j];
			}
			cout << endl << endl;
		}
}
