#include "Macierz.h"
#include <iostream>
#include "algMacierz.h"
#include "Lista.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
	int wybor;

	Macierz *macierz, *kopiaM;
	Lista *lista, *kopiaL;

etykieta:

	cout << endl << endl << "          MENU" << endl << endl <<
		"          1. Wczytaj graf z pliku." << endl <<
		"          2. Wyswietl graf macierzowo i listowo." << endl <<
		"          3. MST. Algorytm Prima" << endl <<
		"          4. Najkrotsza sciezka. Algorytm Dijkstry." << endl <<
		"          5. Zakoncz dzialanie programu"<< endl << endl <<
		"          Wybierz opcje: ";
	cin >> wybor;

	switch (wybor)
	{
	case 1:
	{
		string nazwa;
		int krawedzie, wierzcholki, startowy, koncowy,i,j,waga;

		cout << endl << "          Podaj nazwe pliku do wczytania grafu: ";
		cin >> nazwa;
		nazwa = nazwa + ".txt";
		ifstream plik(nazwa);
		if (!plik)
		{
			cout << endl << "          Nie mozna otworzyc pliku" << endl;
			goto etykieta;

		}

		else
		{

			{
				plik >> krawedzie >> wierzcholki >> startowy >> koncowy;
				if (!plik || krawedzie < wierzcholki - 1 || wierzcholki <= 1 || krawedzie >(wierzcholki*(wierzcholki - 1)))
				{
					cout << endl << "          Cos nie tak!" << endl << "          Liczba wierzcholkow lub krawedzi nie jest prawidlowa." << endl;

					goto etykieta;
				}

				else
				{
					macierz = new Macierz(wierzcholki, krawedzie, startowy);
					kopiaM = new Macierz(wierzcholki, krawedzie, startowy);


					lista = new Lista(wierzcholki, krawedzie, startowy);
					kopiaL = new Lista(wierzcholki, krawedzie, startowy);


					

					while (!plik.eof())
					{

						plik >> i >> j >> waga;
						if (i >= wierzcholki || j >= wierzcholki || waga < 1)
						{
							cout << endl <<"          Cos nie tak! Zle podane krawedzie!" << endl;
							goto etykieta;
							break;
						}
						else
						{
							macierz->a[i][j] = waga;
							kopiaM->a[i][j] = waga;

							lista->k.v1=i;
							lista->k.v2 = j;
							lista->k.waga = waga;
							lista->dodajKrawedz(lista->k);

							kopiaL->k.v1 = i;
							kopiaL->k.v2 = j;
							kopiaL->k.waga = waga;
							kopiaL->dodajKrawedz(kopiaL->k);
						}

					}

						plik.close();
					}
				}
			}

		cout << endl << "          Wczytano graf." << endl;

	} goto etykieta;

	case 2:
	{
		macierz->wyswietlMacierz();
		lista->wyswietl();
	} goto etykieta;

	case 3:
	{
		
		kopiaM->MSTPrim();
		kopiaL->MSTPrim();

	}goto etykieta;

	case 4:
	{
		macierz->Dijkstry();
		lista->Dijkstry();
	}goto etykieta;

	case 5:
	{}goto koniec;

	}

koniec:
	cout << endl << endl << "          ZAKONCZONO DZIALANIE PROGRAMU." << endl << endl;
	return 0;
}