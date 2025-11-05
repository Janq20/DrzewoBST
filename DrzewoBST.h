#pragma once
#include <iostream>
#include <fstream> 
#include <string>  

using namespace std;

struct Wezel {
    int dane;
    Wezel* lewy;
    Wezel* prawy;
    Wezel(int d) : dane(d), lewy(nullptr), prawy(nullptr) {}
};

class MenedzerPlikow; // Deklaracja wyprzedzająca dla 'friend'

class DrzewoBST {
private:
    Wezel* korzen;
    Wezel* dodaj(Wezel* wezel, int wartosc);
    void preorder(Wezel* wezel);
    void inorder(Wezel* wezel);
    void postorder(Wezel* wezel);
    Wezel* usun(Wezel* wezel, int wartosc);
    Wezel* znajdzMin(Wezel* wezel);
    bool znajdzSciezke(Wezel* wezel, int dane, string& sciezka); 
    void zapiszDoTekstu(Wezel* wezel, fstream& plik);

public:
    DrzewoBST();
    void dodaj(int wartosc);
    void usun (int wartosc);
    void wyswietlGraficznie(int tryb);
    void znajdzSciezke(int dane); 
    void zapiszDoTekstu(const string& nazwaPliku);
    friend class MenedzerPlikow; 
};