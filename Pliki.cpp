#include "Pliki.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

    if (plik.eof() && !plik.fail()) {
        cout << "Wczytano liczby z pliku: " << nazwaPliku << endl;
    } else if (plik.fail()) {
        cout << "Blad formatu danych w pliku." << endl;
    }

    plik.close();
}

void MenedzerPlikow::zapiszWezelBinarnie(fstream& plik, Wezel* wezel) {
    if (wezel == nullptr) {
        bool jestWezel = false;
        plik.write(reinterpret_cast<char*>(&jestWezel), sizeof(bool));
    } else {
        bool jestWezel = true;
        plik.write(reinterpret_cast<char*>(&jestWezel), sizeof(bool));
        
        plik.write(reinterpret_cast<char*>(&wezel->dane), sizeof(int));
        
        zapiszWezelBinarnie(plik, wezel->lewy);
        zapiszWezelBinarnie(plik, wezel->prawy);
    }
}

void MenedzerPlikow::zapiszBinarnie(const string& nazwaPliku, DrzewoBST& drzewo) {
    fstream plik;
    plik.open(nazwaPliku, ios::out | ios::binary);

    if (!plik.is_open()) {
        cout << "Blad otwarcia pliku do zapisu binarnego: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam zapis binarny do pliku: " << nazwaPliku << "..." << endl;
    
    zapiszWezelBinarnie(plik, drzewo.korzen);
    
    plik.close();
    cout << "Drzewo zapisane binarnie do pliku: " << nazwaPliku << endl;
}

Wezel* MenedzerPlikow::wczytajWezelBinarnie(fstream& plik) {
    bool jestWezel;
    
    plik.read(reinterpret_cast<char*>(&jestWezel), sizeof(bool));

    if (!plik) {
        return nullptr;
    }

    if (jestWezel) {
        int dane;
        plik.read(reinterpret_cast<char*>(&dane), sizeof(int));
        
        Wezel* nowyWezel = new Wezel(dane);
        
        nowyWezel->lewy = wczytajWezelBinarnie(plik);
        nowyWezel->prawy = wczytajWezelBinarnie(plik);
        
        return nowyWezel;
    } else {
        return nullptr;
    }
}

void MenedzerPlikow::wczytajBinarnie(const string& nazwaPliku, DrzewoBST& drzewo) {
    fstream plik;
    plik.open(nazwaPliku, ios::in | ios::binary);

    if (!plik.is_open()) {
        cout << "Blad otwarcia pliku do odczytu binarnego: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam wczytywanie binarne z pliku: " << nazwaPliku << "..." << endl;

    drzewo.usunWszystko();

    drzewo.korzen = wczytajWezelBinarnie(plik);

    if (plik.peek() == EOF && plik.eof()) {
        cout << "Wczytano (binarnie) drzewo z pliku: " << nazwaPliku << endl;
    } else if (plik.fail()) {
        cout << "Blad formatu danych w pliku binarnym." << endl;
    } else if (!plik.eof()) {
        cout << "Ostrzezenie: Plik binarny nie zostal odczytany do konca." << endl;
    } else {
        cout << "Wczytano (binarnie) drzewo z pliku: " << nazwaPliku << endl;
    }

    plik.close();
}