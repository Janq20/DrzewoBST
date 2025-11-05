#pragma once
#include <iostream>
#include <string>
#include <fstream> // Potrzebne do zapisu do pliku

using namespace std;

/**
 * @struct Wezel
 * @brief Reprezentuje pojedynczy węzeł w drzewie BST.
 */
struct Wezel {
    int dane;       ///< Wartość (klucz) przechowywana w węźle.
    Wezel* lewy;    ///< Wskaźnik na lewe dziecko (poddrzewo).
    Wezel* prawy;   ///< Wskaźnik na prawe dziecko (poddrzewo).

    /**
     * @brief Konstruktor węzła.
     * @param d Wartość do przechowania w węźle.
     */
    Wezel(int d) : dane(d), lewy(nullptr), prawy(nullptr) {}
};

class MenedzerPlikow; // Deklaracja wyprzedzająca

/**
 * @class DrzewoBST
 * @brief Implementuje strukturę danych binarnego drzewa poszukiwań (BST).
 */
class DrzewoBST {
private:
    Wezel* korzen; ///< Wskaźnik na korzeń drzewa.

    // --- Funkcje z poprzednich commitów ---
    Wezel* dodaj(Wezel* wezel, int wartosc);
    void preorder(Wezel* wezel);
    void inorder(Wezel* wezel);
    void postorder(Wezel* wezel);

    // --- Funkcje Pawła (z serwera) ---
    bool znajdzSciezke(Wezel* wezel, int dane, string& sciezka);
    Wezel* znajdzMin(Wezel* wezel);
    Wezel* usun(Wezel* wezel, int wartosc);

    // --- Twoja funkcja (Commit 6) ---
    void zapiszDoTekstu(Wezel* wezel, fstream& plik);


public:
    /**
     * @brief Konstruktor domyślny.
     */
    DrzewoBST();

    // --- Funkcje z poprzednich commitów ---
    void dodaj(int wartosc);
    void wyswietlGraficznie(int tryb);

    // --- Funkcje Pawła (z serwera) ---
    void znajdzSciezke(int dane);
    void usun (int wartosc);

    // --- Twoja funkcja (Commit 6) ---
    void zapiszDoTekstu(const string& nazwaPliku);

    /**
     * @brief Deklaracja przyjaźni z klasą MenedzerPlikow.
     */
    friend class MenedzerPlikow;
};