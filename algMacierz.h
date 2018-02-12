#pragma once
class algMacierz
{
public:
	algMacierz(int n, int m,int startowy);
	~algMacierz();
	struct Krawedz;
	struct TNode;
	struct porownajWagi;
	void dodajKrawedz(Krawedz e);
	TNode * getAList(int n);
	void wyswietl();
	void MSTreePrimMacierz(int n, int m, int **a);
	void Dijkstry(int wierzcholki, int krawedzie, int **a);

private:
	TNode ** A;                   // Tablica list s�siedztwa
	int Alen;                     // Liczba kom�rek w tablicy
	int waga;                   // Waga ca�ego drzewa
	Krawedz *kk;
	int a;
	const int MAXINT = 2147483647;
	int startowy;
};