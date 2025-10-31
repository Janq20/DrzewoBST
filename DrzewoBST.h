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

public:
    DrzewoBST(); 
    void dodaj(int wartosc); 
};