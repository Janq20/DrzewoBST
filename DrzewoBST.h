#pragma once
#include <iostream>

using namespace std;

struct Wezel {
    int dane;
    Wezel* lewy;
    Wezel* prawy;
    Wezel(int d) : dane(d), lewy(nullptr), prawy(nullptr) {}
};

class DrzewoBST {
private:
    Wezel* korzen;

    // Prywatna, rekurencyjna metoda pomocnicza do dodawania
    Wezel* dodaj(Wezel* wezel, int wartosc);

    // --- NOWE METODY PRYWATNE DLA COMMIT 3 ---
    void preorder(Wezel* wezel);
    void inorder(Wezel* wezel);
    void postorder(Wezel* wezel);
    Wezel* usun(Wezel* wezel, int wartosc);
    Wezel* znajdzMin(Wezel* wezel);.

public:
    DrzewoBST();
    void dodaj(int wartosc);
    void usun (int wartosc);
    // --- NOWA METODA PUBLICZNA DLA COMMIT 3 ---
    void wyswietlGraficznie(int tryb); // tryb: 1-pre, 2-in, 3-post
};