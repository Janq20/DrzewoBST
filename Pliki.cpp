/**
 * @file Pliki.cpp
 * @brief Plik implementacyjny dla klasy MenedzerPlikow.
 * @details Zawiera definicje metod odpowiedzialnych za zapis i odczyt
 * drzewa BST do/z plików tekstowych oraz binarnych.
 */

#include "Pliki.h"
#include <fstream>
#include <iostream>
#include <string>

 // Wymagany do dzia³ania, poniewa¿ Pliki.h go zawiera
#include "DrzewoBST.h" 

using namespace std;

/**
 * @brief Wczytuje drzewo z pliku tekstowego.
 * @details Otwiera plik tekstowy, czyta liczby (jedna na liniê lub oddzielone spacj¹)
 * i dodaje je do drzewa.
 * @param nazwaPliku Œcie¿ka do pliku wejœciowego.
 * @param drzewo Referencja do obiektu DrzewoBST, który ma byæ wype³niony danymi.
 */
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
    }
    else if (plik.fail()) {
        cout << "Blad formatu danych w pliku." << endl;
    }

    plik.close();
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do zapisu binarnego.
 * @details Zapisuje drzewo w kolejnoœci Pre-order. Dla ka¿dego wêz³a
 * zapisuje flagê (bool), czy wêze³ istnieje (true) czy jest to nullptr (false).
 * Jeœli istnieje, zapisuje równie¿ jego dane (int).
 * @param plik Referencja do otwartego strumienia pliku binarnego (fstream).
 * @param wezel WskaŸnik na aktualnie przetwarzany wêze³.
 */
void MenedzerPlikow::zapiszWezelBinarnie(fstream& plik, Wezel* wezel) {
    if (wezel == nullptr) {
        // Zapisz 'false', aby zaznaczyæ brak wêz³a (nullptr)
        bool jestWezel = false;
        plik.write(reinterpret_cast<char*>(&jestWezel), sizeof(bool));
    }
    else {
        // Zapisz 'true', aby zaznaczyæ istnienie wêz³a
        bool jestWezel = true;
        plik.write(reinterpret_cast<char*>(&jestWezel), sizeof(bool));

        // Zapisz dane wêz³a
        plik.write(reinterpret_cast<char*>(&wezel->dane), sizeof(int));

        // Kontynuuj rekurencyjnie
        zapiszWezelBinarnie(plik, wezel->lewy);
        zapiszWezelBinarnie(plik, wezel->prawy);
    }
}

/**
 * @brief Publiczna metoda zapisuj¹ca ca³¹ strukturê drzewa do pliku binarnego.
 * @details Wymaga przyjaŸni z klas¹ DrzewoBST, aby uzyskaæ dostêp do korzenia.
 * @param nazwaPliku Œcie¿ka do pliku wyjœciowego.
 * @param drzewo Referencja do obiektu DrzewoBST, który ma byæ zapisany.
 */
void MenedzerPlikow::zapiszBinarnie(const string& nazwaPliku, DrzewoBST& drzewo) {
    fstream plik;
    plik.open(nazwaPliku, ios::out | ios::binary);

    if (!plik.is_open()) {
        cout << "Blad otwarcia pliku do zapisu binarnego: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam zapis binarny do pliku: " << nazwaPliku << "..." << endl;
    
    // U¿ywamy 'drzewo.korzen' dziêki deklaracji 'friend class' w DrzewoBST.h
    zapiszWezelBinarnie(plik, drzewo.korzen);

    plik.close();
    cout << "Drzewo zapisane binarnie do pliku: " << nazwaPliku << endl;
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do odczytu binarnego.
 * @details Odczytuje flagê (bool). Jeœli jest 'true', odczytuje dane (int),
 * tworzy nowy wêze³ i rekurencyjnie odbudowuje jego lewe i prawe poddrzewo.
 * Jeœli jest 'false', zwraca nullptr.
 * @param plik Referencja do otwartego strumienia pliku binarnego (fstream).
 * @return WskaŸnik na nowo utworzony wêze³ lub nullptr.
 */
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
    }
    else {
        // To by³ nullptr
        return nullptr;
    }
}

/**
 * @brief Publiczna metoda wczytuj¹ca strukturê drzewa z pliku binarnego.
 * @details Przed wczytaniem, ta metoda wywo³uje `drzewo.usunWszystko()`,
 * aby wyczyœciæ aktualn¹ zawartoœæ drzewa.
 * @param nazwaPliku Œcie¿ka do pliku binarnego.
 * @param drzewo Referencja do obiektu DrzewoBST, który zostanie nadpisany.
 */
void MenedzerPlikow::wczytajBinarnie(const string& nazwaPliku, DrzewoBST& drzewo) {
    fstream plik;
    plik.open(nazwaPliku, ios::in | ios::binary);

    if (!plik.is_open()) {
        cout << "Blad otwarcia pliku do odczytu binarnego: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam wczytywanie binarne z pliku: " << nazwaPliku << "..." << endl;

    // Wyczyœæ istniej¹ce drzewo przed wczytaniem nowego
    drzewo.usunWszystko();

    // Odbuduj drzewo i ustaw nowy korzeñ (wymaga przyjaŸni)
    drzewo.korzen = wczytajWezelBinarnie(plik);

    // Sprawdzenie, czy plik zosta³ odczytany w ca³oœci
    if (plik.peek() == EOF && plik.eof()) {
        cout << "Wczytano (binarnie) drzewo z pliku: " << nazwaPliku << endl;
    }
    else if (plik.fail()) {
        cout << "Blad formatu danych w pliku binarnym." << endl;
    }
    else if (!plik.eof()) {
        cout << "Ostrzezenie: Plik binarny nie zostal odczytany do konca." << endl;
    }
    else {
        cout << "Wczytano (binarnie) drzewo z pliku: " << nazwaPliku << endl;
    }

    plik.close();
}