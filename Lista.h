#pragma once
class Lista
{
public:
	Lista(int n, int m, int startowy);
	~Lista();
	int wierzcholki, krawedzie;
	const int MAXINT = 2147483647;

	struct Krawedz
	{
		int v1, v2, waga;               // Wierzcho�ki i waga kraw�dzi
	};

	struct TNode
	{
		TNode * next;
		int v, waga;
	};

	struct porownajWagi
	{
		bool operator ()(const Krawedz & waga1, const Krawedz & waga2)
		{
			//kolejno�� - rosn�co
			if (waga1.waga > waga2.waga) return true;

			if (waga1.waga < waga2.waga) return false;

			return false;
		}
	};

	void dodajKrawedzNiesk(Krawedz e);
	void dodajKrawedz(Krawedz e);
	void losowaNieskLista();
	void losowaLista();
	void MSTPrim();
	void wyswietlMST();
	void dodajKrawedzMST(Krawedz k);
	void MSTreePrimLista(int n, int m, TNode ** A);
	void Dijkstry();
	void recznaLista();
	void przykladowaListaSkierowana();
	void przykladowaListaNieskierowana();
	Krawedz stworzKrawedz(int v1, int v2, int waga);
	Krawedz k;


	TNode * getAList(int n);
	void wyswietl();

private:
	TNode ** A;                   // Tablica list s�siedztwa
	int Alen;                     // Liczba kom�rek w tablicy
	int waga;                   // Waga ca�ego drzewa MST
	Krawedz *kk;
	int a;
	int startowy;
};