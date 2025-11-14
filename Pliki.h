#pragma once
#include <iostream>
#include <string>
#include "DrzewoBST.h" 

using namespace std;

class MenedzerPlikow {
private:
    /**
     * @brief Rekurencyjnie zapisuje węzeł i jego dzieci do pliku binarnego.
     * @param plik Strumień pliku otwarty w trybie binarnym.
     * @param wezel Węzeł do zapisu.
     */
    void zapiszWezelBinarnie(fstream& plik, Wezel* wezel);

    /**
     * @brief Rekurencyjnie odczytuje węzeł i jego dzieci z pliku binarnego.
     * @param plik Strumień pliku otwarty w trybie binarnym.
     * @return Wskaźnik na nowo utworzony węzeł (lub nullptr).
     */
    Wezel* wczytajWezelBinarnie(fstream& plik);

public:
    /**
     * @brief Wczytuje dane drzewa z pliku tekstowego.
     * @param nazwaPliku Nazwa pliku do odczytu.
     * @param drzewo Referencja do obiektu drzewa, do którego dane zostaną dodane.
     */
    void wczytajZTekstu(const string& nazwaPliku, DrzewoBST& drzewo);

    /**
     * @brief Zapisuje całą strukturę drzewa do pliku binarnego.
     * @param nazwaPliku Nazwa pliku wyjściowego.
     * @param drzewo Referencja do drzewa, które ma być zapisane.
     */
    void zapiszBinarnie(const string& nazwaPliku, DrzewoBST& drzewo);

    /**
     * @brief Wczytuje całą strukturę drzewa z pliku binarnego.
     * @details UWAGA: Ta funkcja najpierw czyści istniejące drzewo!
     * @param nazwaPliku Nazwa pliku wejściowego.
     * @param drzewo Referencja do drzewa, które zostanie nadpisane.
     */
    void wczytajBinarnie(const string& nazwaPliku, DrzewoBST& drzewo);
};