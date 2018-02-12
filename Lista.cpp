#include "Lista.h"
#include <iostream>
#include <random>
#include <queue>


using namespace std;


Lista::Lista(int n, int m, int start) //int wierzcho�ki, int kraw�dzie
{
	startowy = start;
	A = new TNode *[n];            // Tworzymy tablic� dynamiczn� (list)
	for (int i = 0; i < n; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = n - 1;                   // Zapami�tujemy d�ugo�� tablicy
	waga = 0;                     // Zerujemy wag� drzewa
	kk = new Krawedz[m];		// Tworzymy tablic� kraw�dzi w drzewie rozpinaj�cym (do wy�wietlania drzewa)
	a = 0;
	wierzcholki = n;
	krawedzie = m;
}

// Destruktor - usuwa listy oraz tablic� s�siedztwa
//-------------------------------------------------
Lista::~Lista()
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

// Dodaje kraw�d� do grafu 
//-------------------------
void Lista::dodajKrawedzNiesk(Krawedz k)
{
	TNode *p;

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

}

void Lista::dodajKrawedz(Krawedz k)
{
	TNode *p;

	p = new TNode;                  // Tworzymy nowy w�ze�
	p->v = k.v2;                    // Wierzcho�ek ko�cowy
	p->waga = k.waga;           // Waga kraw�dzi
	p->next = A[k.v1];              // Dodajemy p do listy wierzcho�ka v1
	A[k.v1] = p;

}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka
//----------------------------------------------------
Lista::TNode * Lista::getAList(int n)
{
	return A[n];
}

// Wy�wietla zawarto�� drzewa oraz jego wag�
//------------------------------------------
void Lista::wyswietl()
{
	int i;
	TNode *p;

	cout << endl << "          Graf w postaci list: " << endl << endl;
	for (i = 0; i <= Alen; i++)
	{
		cout << "     Wierzcholek [" << i << "]: " << "(sasiad, waga):   ";
		for (p = A[i]; p; p = p->next) cout <<  "(" << p->v << ", " << p->waga << ")  ";
		cout << endl;
	}
}

void Lista::losowaNieskLista()
{
	Krawedz k;
//	Krawedz *wDrzewie;


	A = new TNode *[wierzcholki];            // Tworzymy tablic� dynamiczn� (list)
	for (int i = 0; i < wierzcholki; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = wierzcholki - 1;                   // Zapami�tujemy d�ugo�� tablicy

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(0, wierzcholki-1); // distribute results between
											// 1 and 1000000 inclusive


//	wDrzewie = new Krawedz[wierzcholki];		// Tworzymy tablic� kraw�dzi w drzewie rozpinaj�cym (do wy�wietlania drzewa)


	for (int i = 0; i < krawedzie; i++)
	{
		do
		{
			k.v1 = dist(gen);
			k.v2 = dist(gen);
			k.waga = dist(gen) + 1;
//			wDrzewie[k.v1] = k;
//			wDrzewie[k.v2] = k;
		} while (k.v1 == k.v2);
		dodajKrawedzNiesk(k);
	}
}

void Lista::MSTPrim()
{
	// Tworzymy kopi� grafu, zmieniaj�c j� na graf skierowany i wysy�aj�c j� do funkcji.

	Lista *G;

	G = new Lista(wierzcholki, krawedzie, startowy);

	G->A = A;

	TNode *p;
	Krawedz k;

	//Ka�d� istniej�c� kraw�d� dodajemy do grafu na nowo, jako nieskierowan�.

	for (int i = 0; i < wierzcholki; i++)
	{
		for (p = G->A[i]; p; p = p->next)
		{
			if (p)
			{
				k.v1 = i;
				k.v2 = p->v;
				k.waga = p->waga;
				G->dodajKrawedzNiesk(k);
			}
		}
	}

	MSTreePrimLista(wierzcholki, krawedzie, G->A);
}

void Lista::dodajKrawedzMST(Krawedz k)
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

void Lista::wyswietlMST()
{
	cout << endl << "MST na podstawie listy. Algorytm Prima: " << endl << endl;
	for (int i = 0; i < a; i++)
	{

		cout << "Krawedz " << i + 1 << ": ";

		cout << kk[i].v1 << "<-->" << kk[i].v2 << "   [" << kk[i].waga << "] ";

		cout << endl;
	}
	cout << endl << endl << "Waga minimalnego drzewa rozpinajacego = " << waga << endl << endl;
}

void Lista::MSTreePrimLista(int n, int m, TNode ** G)           //n liczba wierzcho�k�w, m liczba kraw�dzi, a graf
{
	Krawedz k;
	TNode * p;
	int i, v, licznik=0;
	bool istnieje = false;


	typedef std::priority_queue < Krawedz, std::vector < Krawedz >, porownajWagi > TKolejkaPriorytetowaKrawedzi;

	TKolejkaPriorytetowaKrawedzi Q;

	Lista T(n,m, startowy);                    // Minimalne drzewo rozpinaj�ce
	bool * odwiedzone = new bool[n];

	for (i = 0; i < n; i++)
		odwiedzone[i] = false;           // Inicjujemy tablic� odwiedzin



										 // Tworzymy minimalne drzewo rozpinaj�ce

	v = 0;                          // Wierzcho�ek startowy
	odwiedzone[v] = true;              // Oznaczamy go jako odwiedzonego

	while (licznik < n - 1)          // Do drzewa dodamy n - 1 kraw�dzi grafu
	{
		for (p = G[v]; p; p = p->next) // Przegl�damy list� s�siad�w
			if (!odwiedzone[p->v])          // Je�li s�siad jest nieodwiedzony,
			{
				istnieje = true;
				k.v1 = v;                 // to tworzymy kraw�d�
				k.v2 = p->v;
				k.waga = p->waga;
				Q.push(k);                // Dodajemy j� do kolejki priorytetowej
			}


	if (istnieje)
		{
		if (!Q.empty())
			do
			{
				k = Q.top();              // Pobieramy kraw�d� z kolejki
				Q.pop();
			} while (odwiedzone[k.v2] && !Q.empty());				  // Kraw�d� prowadzi poza drzewo?

			T.dodajKrawedzMST(k); licznik++;                 // Dodajemy kraw�d� do drzewa rozpinaj�cego
			odwiedzone[k.v2] = true;         // Oznaczamy drugi wierzcho�ek jako odwiedzony
			v = k.v2;
		}
	else if (!istnieje)
	{
		v++;
		odwiedzone[v] = true;
	}
	}

	// Wy�wietlamy wyniki

	T.wyswietlMST();
}

void Lista::Dijkstry()
{
	bool *przebadany;
	int *d, *p,*pk, u;
	Krawedz k;
	TNode *pw;

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
		for (pw = A[u]; pw; pw = pw->next)
		{
			if (d[pw->v] > d[u] + pw->waga)
			{
				d[pw->v] = d[u] + pw->waga;
				p[pw->v] = u;
			}
		}

		// Oznaczamy wierzcho�ek u jako przebadany
		przebadany[u] = true;
	}

	//Wypiujemy wyniki

	cout << endl << "Algorytm Dijkstry na podstawie listy:" << endl << endl;
		int j=0;

		bool czyStartowy = false;

		for (int i = 0; i < wierzcholki; i++)
		{
			pk[i] = p[i];
		}

		cout << endl << "Start = " << startowy << endl << endl;

		cout << "          " << "End" << "    Dist" << "      Patch" << endl <<endl;


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

void Lista::losowaLista()
{
	Krawedz k;
	//	Krawedz *wDrzewie;


	A = new TNode *[wierzcholki];            // Tworzymy tablic� dynamiczn� (list)
	for (int i = 0; i < wierzcholki; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = wierzcholki - 1;                   // Zapami�tujemy d�ugo�� tablicy

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(0, wierzcholki - 1); // distribute results between
														 // 1 and 1000000 inclusive


														 //	wDrzewie = new Krawedz[wierzcholki];		// Tworzymy tablic� kraw�dzi w drzewie rozpinaj�cym (do wy�wietlania drzewa)


	for (int i = 0; i < krawedzie; i++)
	{
			k.v1 = dist(gen);
			k.v2 = dist(gen);
			k.waga = dist(gen) + 1;
			//			wDrzewie[k.v1] = k;
			//			wDrzewie[k.v2] = k;
		dodajKrawedz(k);
	}
}

void Lista::recznaLista()
{
	Krawedz k;


	A = new TNode *[wierzcholki];            // Tworzymy tablic� dynamiczn� (list)
	for (int i = 0; i < wierzcholki; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = wierzcholki - 1;                   // Zapami�tujemy d�ugo�� tablicy


	for (int i = 0; i < krawedzie; i++)
	{
		cout << endl << "Krawedz " << i << ": ";
		cout << "Wierzcho�ek startowy: ";
			cin >> k.v1;
		cout << "Wierzcho�ek koncowy: ";
			cin >> k.v2;
		cout << "Waga: ";
			cin >> k.waga;

		dodajKrawedz(k);
	}
}

void Lista::przykladowaListaSkierowana()
{
	Krawedz k;
	
	wierzcholki = 6;
	krawedzie = 9;

	A = new TNode *[wierzcholki];            // Tworzymy tablic� dynamiczn� (list)
	for (int i = 0; i < wierzcholki; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = wierzcholki - 1;                   // Zapami�tujemy d�ugo�� tablicy


	k.v1 = 0;
	k.v2 = 1;
	k.waga = 3;
	dodajKrawedz(k);

	k.v1 = 0;
	k.v2 = 4;
	k.waga = 3;
	dodajKrawedz(k);

	k.v1 = 1;
	k.v2 = 2;
	k.waga = 1;
	dodajKrawedz(k);
	
	k.v1 = 2;
	k.v2 = 3;
	k.waga = 3;
	dodajKrawedz(k);

	k.v1 = 2;
	k.v2 = 5;
	k.waga = 1;
	dodajKrawedz(k);

	k.v1 = 3;
	k.v2 = 1;
	k.waga = 3;
	dodajKrawedz(k);

	k.v1 = 4;
	k.v2 = 5;
	k.waga = 2;
	dodajKrawedz(k);

	k.v1 = 5;
	k.v2 = 0;
	k.waga = 6;
	dodajKrawedz(k);

	k.v1 = 5;
	k.v2 = 3;
	k.waga = 1;
	dodajKrawedz(k);
}

void Lista::przykladowaListaNieskierowana()
{
	Krawedz k;

	wierzcholki = 5;
	krawedzie = 7;

	A = new TNode *[wierzcholki];            // Tworzymy tablic� dynamiczn� (list)
	for (int i = 0; i < wierzcholki; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = wierzcholki - 1;                   // Zapami�tujemy d�ugo�� tablicy


	k.v1 = 0;
	k.v2 = 1;
	k.waga = 1;
	dodajKrawedzMST(k);

	k.v1 = 0;
	k.v2 = 2;
	k.waga = 3;
	dodajKrawedzMST(k);

	k.v1 = 2;
	k.v2 = 3;
	k.waga = 4;
	dodajKrawedzMST(k);

	k.v1 = 3;
	k.v2 = 1;
	k.waga = 6;
	dodajKrawedzMST(k);

	k.v1 = 2;
	k.v2 = 1;
	k.waga = 3;
	dodajKrawedzMST(k);

	k.v1 = 2;
	k.v2 = 4;
	k.waga = 2;
	dodajKrawedzMST(k);

	k.v1 = 4;
	k.v2 = 3;
	k.waga = 5;
	dodajKrawedzMST(k);

}

Lista::Krawedz Lista::stworzKrawedz(int v1, int v2, int waga)
{
	Krawedz k;
	k.v1 = v1;
	k.v2 = v2;
	k.waga = waga;

	return k;
}