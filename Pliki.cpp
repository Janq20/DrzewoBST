#include "Pliki.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// == Metoda Wczytywania z Tekstu ==
void MenedzerPlikow::wczytajZTekstu(const string& nazwaPliku, DrzewoBST& drzewo) {
    fstream plik;
    plik.open(nazwaPliku, ios::in); 

    if (!plik.is_open()) {
        cout << "Blad otwarcia pliku do odczytu: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam wczytywanie z pliku: " << nazwaPliku << "..." << endl;

    int liczba;
    while (plik >> liczba) {
        drzewo.dodaj(liczba); 
    }

    if (plik.eof()) {
        cout << "Wczytano liczby z pliku: " << nazwaPliku << endl;
    } else if (plik.fail()) {
        cout << "Blad formatu danych w pliku." << endl;
    }

    plik.close();
}