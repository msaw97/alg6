//Wydzia� Fizyki Technicznej i Matematyki Stosowanej
//Matematyka Stosowana
//Algorytmy i struktury danych
//Laboratorium 8: Minimalne drzewa rozpinaj�ce i grafy sp�jne
//Miłosz Sawicki
//15.06.2019

#include <fstream>
#include <iostream>
#include <cstdlib>
#include<cstdio>
#include<vector>
#include<set>
#include <math.h>
#include <conio.h>
#include <curses.h>
#include <stack>
using namespace std;
const int infty = 1000000000;
int w,k; //w - l. wierzcholkow, k - l. krawedzi
vector< vector< pair<int,int> > > adj; //zbior krawedzi w grafie
vector<bool> vis; //tablica odwiedzin (czy wierzcholek zostal odwiedzony)
vector<int> waga, d; //tablica wag, d - drzewo
struct compare //porownanie wag
{	// czy a < b
	bool operator() (const int &a, const int &b)
	{
		if (waga[a] < waga[b]) return true;
		if (waga[a] > waga[b]) return false;
		return a<b;
	}
};
set<int, compare> kopiec;
//Algorytm Prima
void prim(int s)
{
	int v, u, c;
	waga.clear(); waga.resize(w, infty);  //czyszczenie tablicy wag
	vis.clear(); vis.resize(w,false); //czyszczenie tablicy odwiedzin
	d.resize(w);
	waga[s] = 0; //waga poczatkowego wierzcholka = 0
	d[s]=s;
	kopiec.clear(); //czyszczenie kopca
	for (int i=0; i<w; i++) kopiec.insert(i); //dodanie do kopca wszystkich wierzcholkow
	while( !kopiec.empty() )
	{
		u = *(kopiec.begin());  //najmniejszy element kopca
		kopiec.erase(kopiec.begin()); //usuwamy najmniejszy element z kopca
		vis[u]=true;
		for (int i=0; i<adj[u].size(); i++)
		{
			v = adj[u][i].first; //v- wierzcholek polaczony z u
			if (!vis[v]) //jesli v nie jest odwiedzony
			{
				c = adj[u][i].second; //waga krawedzi u,v
				if (c < waga[v])
				{
					kopiec.erase(kopiec.find(v));
					waga[v] = c; //uaktualnienei wagi wierzcholka v
					kopiec.insert(v);
					d[v] = u; //dodanie krawedzi uv do drzewa
				}
			}
		}
	}
}

int main(void)
{
	int a,b,c;
	int menu;
	int menu1;
		do{
			system("CLS");
			printf("1. Minimalne drzewo rozpinajace\n");
			printf("2. Grafy spojne\n");
			printf("3. Wyjscie\n");
			scanf("%d",&menu1);
			switch(menu1){
				case 1:{
				do{
				system("CLS");
				printf("Algoytm tworzenia minimalnego drzewa rozpinajacego:\n");
				printf("1. Podanie danych przez uzytkownika \n");
				printf("2. Graf o 5 wierzcholkach\n");
				printf("3. Graf o 8 wierzcholkach\n");
				printf("4. Graf o 12 wierzcholkach\n");
				printf("5. Graf o 16 wierzcholkach\n");
				printf("6. Graf o 20 wierzcholkach\n");
				printf("7. Powrot\n");
				scanf("%d",&menu);
				switch(menu){
					case 1:{
					//Sprawdzenie spojnosci grafu
					bool visited[10000];   //tablica odwiedzin
					vector <int> V[10000];
		    		int i, suma=0;
		    		stack<int>S;
			 		printf("Podaj liczbe wierzcholkow oraz liczbe krawedzi: ");
					scanf("%d %d", &w, &k);
					adj.resize(w);
					printf("Podaj numery polaczonych wierzcholkow oraz wage krawedzi laczacej: ");
					for (int i=0; i<k; i++){
						scanf("%d %d %d", &a, &b, &c);
						V[a].push_back(b);  //do wektora A[a] dodajemy wierzcho�ek b
		    			V[b].push_back(a);	//do wektora A[b] dodajemy wierzcho�ek a
						a--; b--;
						adj[a].push_back( make_pair(b,c) );
						adj[b].push_back( make_pair(a,c) );
					}
					//DFS
					S.push(1);    // Na stos wierzcho�ek startowy: 1
					while(!S.empty()){
			    		a = S.top();    //pobieramy wierzcho�ek ze szczytu stosu
						S.pop();	//usuwamy pobrany wierzcho�ek ze szczytu stosu
			    		if(!visited[a]){           //je�li a nie by� odwiedzony, to
			        		visited[a] = true;
			   				for(int i=0 ; i < V[a].size() ; i++)   //sprawdzamy sasiadow
			 					if(!visited[V[a][i]]){
			       					S.push(V[a][i]);}		//dodajemy na stos nieodwiedzonego sasiada
			    		}
					}
					for(i = 1; i <= w; i++)
						suma += visited[i]; //visited ma wartosci 1 dla odwiedzonych, 0 dla nieodwiedzonych
					cout<<"Suma: "<<suma<<endl;
					if (w == suma){ //suma = liczba wszystkich odwiedzonych wierzcholkow
						cout << "Graf jest spojny" << endl;
						//Wywo�anie algorytmu Prima dla wybranego grafu
						prim(0);
						printf("Minimalne drzewo rozpinajace:\n");
						for (int i=1; i<w; i++)
							printf("%d -- %d\n", i+1, d[i]+1);
					}
					else
						cout << "Graf nie jest spojny" << endl; //Nie mozna zastostosowac algorytmu Prima
		 			}
					getch();
					break;

					case 2:{ //Otwieranie i czytanie danych z pliku da grafu o 5 wierzcholkach
					fstream plik1;
		 			plik1.open("5w.txt", ios::in); //otwieramy plik: 5w.txt
		  			if (plik1.good() == false){
		  				cout<< "Blad"; //jesli plik nie istnieje - komunikat o bledzie
		  				exit(0);
			  		}
				 	plik1 >> w >> k; //wczytanie liczby wierzcholkow i krawedzi z pliku
		    		adj.resize(w);
					for (int i=0; i<k; i++){
						plik1 >> a >> b >> c; //wczytanie numeru wierzcholkow i wag
						a--; b--;
						adj[a].push_back( make_pair(b,c) );
						adj[b].push_back( make_pair(a,c) );
					}
		 			plik1.close();
					prim(0);
					printf("Minimalne drzewo rozpinajace:\n");
					for (int i=1; i<w; i++)
					printf("%d -- %d\n", i+1, d[i]+1);
					}
					getch();
					break;

					case 3:{//Otwieranie i czytanie danych z pliku da grafu o 8 wierzcholkach
					fstream plik2;
		 			plik2.open("w8.txt", ios::in);
		  			if (plik2.good() == false){
		  				cout<< "Blad";
		  				exit(0);
			  		}
				 	plik2 >> w >> k;
		    		adj.resize(w);
					for (int i=0; i<k; i++){
						plik2 >> a >> b >> c;
						a--; b--;
						adj[a].push_back( make_pair(b,c) );
						adj[b].push_back( make_pair(a,c) );
						}
		 			plik2.close();
					prim(0);
					printf("Minimalne drzewo rozpinajace:\n");
					for (int i=1; i<w; i++)
					printf("%d -- %d\n", i+1, d[i]+1);
		    		}
		    		getch();
					break;

					case 4:{//Otwieranie i czytanie danych z pliku da grafu o 12 wierzcholkach
					fstream plik3;
		 			plik3.open("w12.txt", ios::in);
		  			if (plik3.good() == false){
		  				cout<< "Blad";
		  				exit(0);
			  		}

				 	plik3 >> w >> k;
		    		adj.resize(w);
					for (int i=0; i<k; i++){
						plik3 >> a >> b >> c;
						a--; b--;
						adj[a].push_back( make_pair(b,c) );
						adj[b].push_back( make_pair(a,c) );
						}
		 			plik3.close();
					prim(0);
					printf("Minimalne drzewo rozpinajace:\n");
					for (int i=1; i<w; i++)
					printf("%d -- %d\n", i+1, d[i]+1);
					}
					getch();
					break;

					case 5:{//Otwieranie i czytanie danych z pliku da grafu o 16 wierzcholkach
					{
					fstream plik4;
		 			plik4.open("16w.txt", ios::in);
		  			if (plik4.good() == false){
		  				cout<< "Blad";
		  				exit(0);
			  		}

				 	plik4 >> w >> k;
		    		adj.resize(w);
					for (int i=0; i<k; i++){
						plik4 >> a >> b >> c;
						a--; b--;
						adj[a].push_back( make_pair(b,c) );
						adj[b].push_back( make_pair(a,c) );
						}
		 			plik4.close();
					prim(0);
					printf("Minimalne drzewo rozpinajace:\n");
					for (int i=1; i<w; i++)
					printf("%d -- %d\n", i+1, d[i]+1);
		    		}
					}
					getch();
					break;

					case 6:{//Otwieranie i czytanie danych z pliku da grafu o 20 wierzcholkach
					fstream plik5;
		 			plik5.open("20w.txt", ios::in);
		  			if (plik5.good() == false){
		  				cout<< "Blad";
		  				exit(0);
			  		}

				 	plik5 >> w >> k;
		    		adj.resize(w);
					for (int i=0; i<k; i++){
						plik5 >> a >> b >> c;
						a--; b--;
						adj[a].push_back( make_pair(b,c) );
						adj[b].push_back( make_pair(a,c) );
						}
		 			plik5.close();
					prim(0);
					printf("Minimalne drzewo rozpinajace:\n");
					for (int i=1; i<k; i++)
					printf("%d -- %d\n", i+1, d[i]+1);
		    		}
		    		getch();
					break;
					}
				} while (menu < 7);
				}
				break;
				case 2:{
					bool visited[10000];   //tablica odwiedzin
					vector <int> V[10000];
				    int i, suma=0;
				    stack<int>S;
				    printf("Podaj liczbe wierzcholkow oraz liczbe krawedzi: \n");
				 	cin >> w >> k;  //w - l. wierzcholkow, k - l. krawedzi
					// wczytanie krawedzi jako wierzcholkow
					printf("Podaj numery polaczonych wierzcholkow oraz wage krawedzi laczacych: \n");
				  	for(i = 0; i < k; i++){
				    	cin >> a>> b >>c;
				    	V[a].push_back(b); //do wektora A[a] dodajemy wierzcho�ek b
				    	V[b].push_back(a); //do wektora A[b] dodajemy wierzcho�ek a
				  	}
					//DFS
					S.push(1);    //na stos wierzcho�ek startowy: 1
					while(!S.empty()){
					    a = S.top();    //pobieramy wierzcho�ek ze szczytu stosu
						S.pop();	//usuwamy pobrany wierzcho�ek ze szczytu stosu
					    if(!visited[a]){           //je�li a nie by� odwiedzony, to
					        visited[a] = true;

					        for(int i=0 ; i < V[a].size() ; i++)   //sprawdzamy sasiadow
					 			if(!visited[V[a][i]]){
					       		S.push(V[a][i]);}		//dodajemy na stos nieodwiedzonego sasiada
					    }
					}

					for(i = 1; i <= w; i++)
						suma += visited[i]; //visited ma wartosci 1 dla odwiedzonych, 0 dla nieodwiedzonych
						cout<<"Suma: "<<suma<<endl;

					if (w == suma){ //suma - liczba wszystkich odwiedzonych wierzcholkow
						cout << "Graf jest spojny" << endl;}
					else
						cout << "Graf nie jest spojny" << endl;
					}
					getch();
					break;
			}
		} while (menu1 < 3);
	return 0;
}
