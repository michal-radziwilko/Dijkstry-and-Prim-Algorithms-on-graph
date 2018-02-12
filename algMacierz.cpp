#include "algMacierz.h"
#include <iostream>
#include <queue>
#include <limits>
#include "Lista.h"


using namespace std;

struct algMacierz::Krawedz
{
	int v1, v2, waga;               // Wierzcho³ki i waga krawêdzi
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
		//kolejnoœæ - rosn¹co
		if (waga1.waga > waga2.waga) return true;

		if (waga1.waga < waga2.waga) return false;

		return false;
	}
};

algMacierz::algMacierz(int n, int m, int start) //int wierzcho³ki, int krawêdzie
{
	startowy = start;
	int i;
	A = new TNode *[n];            // Tworzymy tablicê dynamiczn¹ (list)
	for (i = 0; i < n; i++) A[i] = NULL; // i wype³niamy j¹ pustymi listami
	Alen = n - 1;                   // Zapamiêtujemy d³ugoœæ tablicy
	waga = 0;                     // Zerujemy wagê drzewa
	kk = new Krawedz[m];		// Tworzymy tablicê krawêdzi w drzewie rozpinaj¹cym (do wyœwietlania drzewa)
	a = 0;
}

// Destruktor - usuwa listy oraz tablicê s¹siedztwa
//-------------------------------------------------
algMacierz::~algMacierz()
{
	TNode *p, *r;

	for (int i = 0; i <= Alen; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;                      // Zapamiêtujemy wskazanie
			p = p->next;                // Przesuwamy siê do nastêpnego elementu listy
			delete r;                   // Usuwamy element
		}
	}

	delete[] A;                    // Usuwamy tablicê list s¹siedztwa
	delete[] kk;
}

// Dodaje krawêdŸ do drzewa
//-------------------------
void algMacierz::dodajKrawedz(Krawedz k)
{
	TNode *p;

	waga += k.waga;             // Do wagi drzewa dodajemy wagê krawêdzi
	p = new TNode;                  // Tworzymy nowy wêze³
	p->v = k.v2;                    // Wierzcho³ek koñcowy
	p->waga = k.waga;           // Waga krawêdzi
	p->next = A[k.v1];              // Dodajemy p do listy wierzcho³ka v1
	A[k.v1] = p;

	p = new TNode;                  // To samo dla krawêdzi odwrotnej
	p->v = k.v1;                    // Wierzcho³ek koñcowy
	p->waga = k.waga;           // Waga krawêdzi
	p->next = A[k.v2];              // Dodajemy p do listy wierzcho³ka v2
	A[k.v2] = p;

	kk[a] = k;
	a++;
}

// Zwraca wskaŸnik pocz¹tku listy s¹siadów wierzcho³ka
//----------------------------------------------------
algMacierz::TNode * algMacierz::getAList(int n)
{
	return A[n];
}

// Wyœwietla zawartoœæ drzewa oraz jego wagê
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



void algMacierz::MSTreePrimMacierz(int n, int m, int **a)           //n liczba wierzcho³ków, m liczba krawêdzi, a graf
{
	Krawedz k;

	int i, v, licznik = 0;



	typedef std::priority_queue < Krawedz, std::vector < Krawedz >, porownajWagi > TKolejkaPriorytetowaKrawedzi;

	TKolejkaPriorytetowaKrawedzi Q;

	algMacierz T(n, m, startowy);                    // Minimalne drzewo rozpinaj¹ce

	bool * odwiedzone = new bool[n];

	bool istnieje = false;

	for (i = 0; i < n; i++)
		odwiedzone[i] = false;           // Inicjujemy tablicê odwiedzin


										 // Tworzymy minimalne drzewo rozpinaj¹ce

	v = 0;                          // Wierzcho³ek startowy
	odwiedzone[v] = true;              // Oznaczamy go jako odwiedzonego

	while (licznik < n - 1)          // Do drzewa dodamy m - 1 krawêdzi grafu
	{

 // Przegl¹damy listê s¹siadów

		for (int j = 0; j < n; j++)
		{

			if (!odwiedzone[j])          // Jeœli s¹siad jest nieodwiedzony,
			{
				if (a[v][j] != MAXINT)
				{
					istnieje = true;
					k.v1 = v;                 // to tworzymy krawêdŸ
					k.v2 = j;
					k.waga = a[v][j];
					Q.push(k);                // Dodajemy j¹ do kolejki priorytetowej
				}
			}
		}

		if (istnieje)
		{
			if (!Q.empty())
				do
				{
					k = Q.top();              // Pobieramy krawêdŸ z kolejki
					Q.pop();
				} while (odwiedzone[k.v2] && !Q.empty());
				// KrawêdŸ prowadzi poza drzewo?


				T.dodajKrawedz(k);   licznik++;              // Dodajemy krawêdŸ do drzewa rozpinaj¹cego
				odwiedzone[k.v2] = true;         // Oznaczamy drugi wierzcho³ek jako odwiedzony

				v = k.v2;
		}
		else if (!istnieje)v++;
	}

	// Wyœwietlamy wyniki

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

	d = new int[wierzcholki];                // Tablica kosztów dojœcia
	p = new int[wierzcholki];                // Tablica poprzedników
	pk = new int[wierzcholki];				 // Kopia tablicy poprzedników (uzywana do wypisywania sciezki)
	przebadany = new bool[wierzcholki];              // Zbiory Q i S

													 // Inicjujemy tablice dynamiczne

	for (int i = 0; i < wierzcholki; i++)
	{
		d[i] = MAXINT;
		p[i] = NULL;
		pk[i] = NULL;
		przebadany[i] = false;
	}

	d[startowy] = 0;                       // Koszt dojœcia v jest zerowy
	p[startowy] = startowy;

	//Szukamy wierzcho³ka o najmniejszym koszcie ze wszystkich nie przebadanych, przy u¿yciu kolejki priorytetowej
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

		// W u znajdzie siê numer wierzcho³ka o najmniejszym koszcie
		k = Q.top();
		while (!Q.empty()) Q.pop();
		u = k.v1;

		// Dla ka¿dego z s¹siadów u jeœli d[s¹siad] > d[u] + waga(u -> s¹siad)
		// to dokonujemy relaksacji wierzcho³ka s¹siad
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

		// Oznaczamy wierzcho³ek u jako przebadany
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
