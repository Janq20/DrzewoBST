#pragma once
#include <iostream>
#include <string>
#include <fstream>

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

    Wezel* dodaj(Wezel* wezel, int wartosc);
    void preorder(Wezel* wezel);
    void inorder(Wezel* wezel);
    void postorder(Wezel* wezel);
    bool znajdzSciezke(Wezel* wezel, int dane, string& sciezka);
    Wezel* znajdzMin(Wezel* wezel);
    Wezel* usun(Wezel* wezel, int wartosc);
    void zapiszDoTekstu(Wezel* wezel, fstream& plik);

    /**
     * @brief Prywatna, rekurencyjna funkcja pomocnicza do usuwania wszystkich węzłów.
     * @param wezel Aktualnie przetwarzany węzeł.
     */
    void usunWszystko(Wezel* wezel);


public:
    /**
     * @brief Konstruktor domyślny.
     */
    DrzewoBST();

    /**
     * @brief Destruktor.
     * @details Automatycznie wywołuje usunWszystko(), aby zwolnić pamięć.
     */
    ~DrzewoBST();

    void dodaj(int wartosc);
    void wyswietlGraficznie(int tryb);
    void znajdzSciezke(int dane);
    void usun (int wartosc);
    void zapiszDoTekstu(const string& nazwaPliku);

    /**
     * @brief Publiczna funkcja do usunięcia wszystkich elementów z drzewa.
     */
    void usunWszystko();

    /**
     * @brief Deklaracja przyjaźni z klasą MenedzerPlikow.
     */
    friend class MenedzerPlikow;
};