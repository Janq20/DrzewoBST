/**
 * @file DrzewoBST.cpp
 * @brief Plik implementacyjny dla klasy DrzewoBST.
 * @details Zawiera definicje metod klasy DrzewoBST, odpowiedzialnych za
 * zarządzanie binarnym drzewem poszukiwań.
 */

#include "DrzewoBST.h"
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Konstruktor domyślny klasy DrzewoBST.
 * @details Inicjalizuje korzeń drzewa jako nullptr.
 */
DrzewoBST::DrzewoBST() {
    korzen = nullptr;
}

<<<<<<< HEAD
=======
/**
 * @brief Destruktor klasy DrzewoBST.
 * @details Automatycznie wywołuje metodę usunWszystko(), aby zwolnić pamięć
 * przydzieloną na wszystkie węzły drzewa.
 */
>>>>>>> 91fc26d (Dodanie dokumentacji Doxygen do Pliki.cpp i DrzewoBST.cpp)
DrzewoBST::~DrzewoBST() {
    usunWszystko();
}

<<<<<<< HEAD
=======
/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do dodawania węzła.
 * @param wezel Wskaźnik na aktualny węzeł (lub poddrzewo).
 * @param wartosc Wartość (klucz) do dodania do drzewa.
 * @return Wskaźnik na węzeł po operacji dodania.
 */
>>>>>>> 91fc26d (Dodanie dokumentacji Doxygen do Pliki.cpp i DrzewoBST.cpp)
Wezel* DrzewoBST::dodaj(Wezel* wezel, int wartosc) {
    if (wezel == nullptr) {
        return new Wezel(wartosc);
    }
    if (wartosc < wezel->dane) {
        wezel->lewy = dodaj(wezel->lewy, wartosc);
    }
    else if (wartosc > wezel->dane) {
        wezel->prawy = dodaj(wezel->prawy, wartosc);
    }
    // Jeśli wartosc == wezel->dane, nic nie robimy (nie pozwalamy na duplikaty)
    return wezel;
}

/**
 * @brief Publiczna metoda dodająca nową wartość do drzewa BST.
 * @param wartosc Wartość (klucz) do dodania.
 */
void DrzewoBST::dodaj(int wartosc) {
    korzen = dodaj(korzen, wartosc);
}

/**
 * @brief Prywatna funkcja pomocnicza do przechodzenia drzewa metodą Pre-order.
 * @details (Korzeń -> Lewy -> Prawy)
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 */
void DrzewoBST::preorder(Wezel* wezel) {
    if (wezel != nullptr) {
        cout << wezel->dane << " ";
        preorder(wezel->lewy);
        preorder(wezel->prawy);
    }
}

/**
 * @brief Prywatna funkcja pomocnicza do przechodzenia drzewa metodą In-order.
 * @details (Lewy -> Korzeń -> Prawy). Wyświetla elementy posortowane.
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 */
void DrzewoBST::inorder(Wezel* wezel) {
    if (wezel != nullptr) {
        inorder(wezel->lewy);
        cout << wezel->dane << " ";
        inorder(wezel->prawy);
    }
}

/**
 * @brief Prywatna funkcja pomocnicza do przechodzenia drzewa metodą Post-order.
 * @details (Lewy -> Prawy -> Korzeń)
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 */
void DrzewoBST::postorder(Wezel* wezel) {
    if (wezel != nullptr) {
        postorder(wezel->lewy);
        postorder(wezel->prawy);
        cout << wezel->dane << " ";
    }
}

/**
 * @brief Publiczna metoda do wyświetlania drzewa na konsoli w wybranym trybie.
 * @param tryb Liczba całkowita określająca tryb wyświetlania:
 * 1: Pre-order, 2: In-order, 3: Post-order.
 */
void DrzewoBST::wyswietlGraficznie(int tryb) {
    if (korzen == nullptr) {
        cout << "Drzewo jest puste." << endl;
        return;
    }

    switch (tryb) {
    case 1:
        cout << "Pre-order: ";
        preorder(korzen);
        break;
    case 2:
        cout << "In-order (posortowane): ";
        inorder(korzen);
        break;
    case 3:
        cout << "Post-order: ";
        postorder(korzen);
        break;
    default:
        cout << "Nieznany tryb wyświetlania." << endl;
    }
    cout << endl;
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do znajdowania ścieżki do węzła.
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 * @param dane Wartość (klucz) szukanego węzła.
 * @param sciezka Referencja do obiektu string, w którym budowana jest ścieżka.
 * @return true jeśli węzeł został znaleziony, false w przeciwnym razie.
 */
bool DrzewoBST::znajdzSciezke(Wezel* wezel, int dane, string& sciezka) {
    if (wezel == nullptr) {
        return false;
    }

    sciezka += to_string(wezel->dane);

    if (wezel->dane == dane) {
        return true;
    }

    sciezka += " -> ";

    bool znaleziono;

    if (dane < wezel->dane) {
        znaleziono = znajdzSciezke(wezel->lewy, dane, sciezka);
    }
    else {
        znaleziono = znajdzSciezke(wezel->prawy, dane, sciezka);
    }

    // Jeśli nie znaleziono w poddrzewie, usuń ostatni dodany element i strzałkę
    if (!znaleziono) {
        string usunieta_wartosc = to_string(wezel->dane);
        size_t dlugoscDoUsuniecia = usunieta_wartosc.length() + 4; // " -> " ma 4 znaki

        if (sciezka.length() >= dlugoscDoUsuniecia && sciezka.substr(sciezka.length() - 4) == " -> ") {
            sciezka.erase(sciezka.length() - dlugoscDoUsuniecia);
        }
        else if (sciezka.length() >= usunieta_wartosc.length()) {
            // Ostatni element (bez strzałki)
            sciezka.erase(sciezka.length() - usunieta_wartosc.length());
        }
    }

    return znaleziono;
}

/**
 * @brief Publiczna metoda inicjująca szukanie ścieżki i wyświetlająca wynik.
 * @param dane Wartość (klucz) węzła, do którego szukamy ścieżki.
 */
void DrzewoBST::znajdzSciezke(int dane) {
    string sciezka = "";

    if (znajdzSciezke(korzen, dane, sciezka)) {
        cout << "\nŚcieżka do danych " << dane << ": " << sciezka << endl;
    }
    else {
        cout << "\nDane " << dane << " nie zostały znalezione w drzewie." << endl;
    }
}

/**
 * @brief Prywatna funkcja pomocnicza do znajdowania węzła o minimalnej wartości.
 * @details Przechodzi w lewo aż do końca poddrzewa.
 * @param wezel Wskaźnik na korzeń poddrzewa, w którym szukamy minimum.
 * @return Wskaźnik na węzeł o minimalnej wartości w danym poddrzewie.
 */
Wezel* DrzewoBST::znajdzMin(Wezel* wezel) {
    if (wezel == nullptr) {
        return nullptr;
    }

    Wezel* aktualny = wezel;
    while (aktualny->lewy != nullptr) {
        aktualny = aktualny->lewy;
    }
    return aktualny;
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do usuwania węzła.
 * @details Obsługuje trzy przypadki: brak dzieci, jedno dziecko, dwoje dzieci.
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 * @param wartosc Wartość (klucz) do usunięcia.
 * @return Wskaźnik na węzeł (lub jego następcę) po operacji usunięcia.
 */
Wezel* DrzewoBST::usun(Wezel* wezel, int wartosc) {
    if (wezel == nullptr) {
        return nullptr;
    }

    if (wartosc < wezel->dane) {
        wezel->lewy = usun(wezel->lewy, wartosc);
    }
    else if (wartosc > wezel->dane) {
        wezel->prawy = usun(wezel->prawy, wartosc);
    }
    else {
        // Znaleziono węzeł do usunięcia
        // Przypadek 1: Brak lub jedno dziecko
        if (wezel->lewy == nullptr) {
            Wezel* temp = wezel->prawy;
            delete wezel;
            return temp;
        }
        else if (wezel->prawy == nullptr) {
            Wezel* temp = wezel->lewy;
            delete wezel;
            return temp;
        }

        // Przypadek 2: Dwoje dzieci
        // Znajdź następnika (najmniejszy w prawym poddrzewie)
        Wezel* nastepnik = znajdzMin(wezel->prawy);
        // Skopiuj dane następnika do tego węzła
        wezel->dane = nastepnik->dane;
        // Usuń następnika (rekurencyjnie)
        wezel->prawy = usun(wezel->prawy, nastepnik->dane);
    }

    return wezel;
}

/**
 * @brief Publiczna metoda usuwająca węzeł o podanej wartości z drzewa.
 * @param wartosc Wartość (klucz) do usunięcia.
 */
void DrzewoBST::usun(int wartosc) {
    Wezel* stary_korzen = korzen;
    korzen = usun(korzen, wartosc);

    // Komunikaty dla użytkownika
    if (stary_korzen == nullptr) {
<<<<<<< HEAD
         cout << "\nNie znaleziono wartości " << wartosc << " do usunięcia (drzewo puste)." << endl;
    } else if (korzen == nullptr && stary_korzen != nullptr) {
         cout << "\nWartość " << wartosc << " usunięta pomyśllnie. Drzewo jest teraz puste." << endl;
    } else {
         cout << "\nOperacja usuwania dla " << wartosc << " zakończona." << endl;
=======
        cout << "\nNie znaleziono wartości " << wartosc << " do usunięcia (drzewo puste)." << endl;
    }
    else if (korzen == nullptr && stary_korzen != nullptr) {
        cout << "\nWartość " << wartosc << " usunięta pomyśllnie. Drzewo jest teraz puste." << endl;
    }
    else {
        cout << "\nOperacja usuwania dla " << wartosc << " zakończona." << endl;
>>>>>>> 91fc26d (Dodanie dokumentacji Doxygen do Pliki.cpp i DrzewoBST.cpp)
    }
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do zapisu drzewa do pliku tekstowego.
 * @details Używa kolejności Pre-order, aby ułatwić odtworzenie tej samej struktury.
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 * @param plik Referencja do otwartego strumienia pliku (fstream).
 */
void DrzewoBST::zapiszDoTekstu(Wezel* wezel, fstream& plik) {
    if (wezel != nullptr) {
        plik << wezel->dane << "\n";
        zapiszDoTekstu(wezel->lewy, plik);
        zapiszDoTekstu(wezel->prawy, plik);
    }
}

/**
 * @brief Publiczna metoda zapisująca zawartość drzewa do pliku tekstowego.
 * @param nazwaPliku Nazwa pliku (ścieżka), do którego drzewo ma być zapisane.
 */
void DrzewoBST::zapiszDoTekstu(const string& nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku, ios::out);

    if (!plik.is_open()) {
        cout << "Błąd otwarcia pliku do zapisu: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam zapis do pliku: " << nazwaPliku << "..." << endl;
    zapiszDoTekstu(korzen, plik);
    plik.close();
    cout << "Drzewo zapisane (tekstowo) do pliku: " << nazwaPliku << endl;
}

<<<<<<< HEAD
void DrzewoBST::usunWszystko() {
    usunWszystko(korzen); 
    korzen = nullptr;     
}

=======
/**
 * @brief Publiczna metoda usuwająca wszystkie węzły z drzewa.
 * @details Ustawia korzeń na nullptr po zwolnieniu pamięci.
 */
void DrzewoBST::usunWszystko() {
    usunWszystko(korzen);
    korzen = nullptr;
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do usuwania wszystkich węzłów.
 * @details Używa kolejności Post-order, aby poprawnie zwolnić pamięć
 * (najpierw dzieci, potem rodzic).
 * @param wezel Wskaźnik na aktualnie przetwarzany węzeł.
 */
>>>>>>> 91fc26d (Dodanie dokumentacji Doxygen do Pliki.cpp i DrzewoBST.cpp)
void DrzewoBST::usunWszystko(Wezel* wezel) {
    if (wezel != nullptr) {
        usunWszystko(wezel->lewy);
        usunWszystko(wezel->prawy);
        delete wezel;
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> 91fc26d (Dodanie dokumentacji Doxygen do Pliki.cpp i DrzewoBST.cpp)
