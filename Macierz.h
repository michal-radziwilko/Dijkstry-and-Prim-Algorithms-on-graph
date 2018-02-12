#pragma once
#include <fstream>
class Macierz
{
private:
	int startowy;

public:
	Macierz(int wierzcholki, int krawedzie, int startowy);
	~Macierz();
	int wymiar, liczbaKrawedzi;
	const int MAXINT = 2147483647;
	void losowaMacierz();
	void wyswietlMacierz();
	void MSTPrim();
	void losowaNieskMacierz();
	void przykladowaMacierzSkierowana();
	void przykladowaMacierzNieskierowana();
	void Dijkstry();
	int **a;
	void losowyGrafgestosc(int wierzcholki, int gestosc);

};

