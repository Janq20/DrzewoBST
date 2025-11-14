#include <iostream>
#include <string>
#include <limits> 
#include "DrzewoBST.h"
#include "Pliki.h"
using namespace std;

/**
 * @brief Wyświetla główne menu programu.
 */
void wyswietlMenu() {
    cout << "\n===== MENU DRZEWA BST =====\n";
    cout << "1. Dodaj element\n";
    cout << "2. Usun element\n";
    cout << "3. Znajdz sciezke\n";
    cout << "4. Wyswietl drzewo (tryby)\n";
<<<<<<< HEAD
    cout << "5. (Opcja niedostepna)\n"; 
    cout << "6. Zapisz do pliku TXT\n";
    cout << "7. Wczytaj z pliku TXT\n";
=======
    cout << "5. Usun cale drzewo\n"; 
    cout << "6. Zapisz do pliku TXT\n";
    cout << "7. Wczytaj z pliku TXT\n";
    cout << "8. Zapisz binarnie (BIN)\n";
    cout << "9. Wczytaj binarnie (BIN)\n";
>>>>>>> 20bfa62 (Integracja operacji binarnych i czyszczenia drzewa z menu)
    cout << "0. Wyjscie\n";
    cout << "Wybierz opcje: ";
}

/**
 * @brief Pobiera od użytkownika bezpiecznie liczbę całkowitą.
 * @details Funkcja obsługuje błędne dane wejściowe (np. litery) i prosi
 * użytkownika o ponowne wprowadzenie danych. Czyści również bufor wejścia.
 * @return Poprawnie wczytana liczba całkowita.
 */
int pobierzLiczbeCalkowita() {
    int liczba;
    while (!(cin >> liczba)) {
        cout << "Blad: Wprowadz poprawna liczbe calkowita: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return liczba;
}

int main() {
    DrzewoBST drzewo;
    MenedzerPlikow menedzer;
    
    int wybor;
    int wartosc;
    string nazwaPliku;

    while (true) {
        wyswietlMenu();
        wybor = pobierzLiczbeCalkowita();

        switch (wybor) {
            case 1: // Dodaj
                cout << "Podaj wartosc do dodania: ";
                wartosc = pobierzLiczbeCalkowita();
                drzewo.dodaj(wartosc);
                cout << "Dodano " << wartosc << " do drzewa." << endl;
                break;

            case 2: // Usuń
                cout << "Podaj wartosc do usuniecia: ";
                wartosc = pobierzLiczbeCalkowita();
                drzewo.usun(wartosc); 
                break;

            case 3: // Szukaj ścieżki
                cout << "Podaj wartosc do znalezienia sciezki: ";
                wartosc = pobierzLiczbeCalkowita();
                drzewo.znajdzSciezke(wartosc);
                break;

            case 4: // Wyświetl
                cout << "Wybierz tryb wyswietlania:\n";
                cout << " 1. Pre-order (Korzen -> Lewy -> Prawy)\n";
                cout << " 2. In-order (Lewy -> Korzen -> Prawy)\n";
                cout << " 3. Post-order (Lewy -> Prawy -> Korzen)\n";
                cout << "Wybierz (1-3): ";
                wartosc = pobierzLiczbeCalkowita();
                drzewo.wyswietlGraficznie(wartosc);
                break;

<<<<<<< HEAD
            case 6: // Zapis TXT
=======
            case 5: // Usuń całe drzewo
                drzewo.usunWszystko();
                cout << "Cale drzewo zostalo usuniete." << endl;
                break;

            case 6: // Zapisz TXT
>>>>>>> 20bfa62 (Integracja operacji binarnych i czyszczenia drzewa z menu)
                cout << "Podaj nazwe pliku do zapisu (np. drzewo.txt): ";
                getline(cin, nazwaPliku);
                drzewo.zapiszDoTekstu(nazwaPliku);
                break;

            case 7: // Wczytaj TXT
                cout << "Podaj nazwe pliku do wczytania (np. dane.txt): ";
                getline(cin, nazwaPliku);
                menedzer.wczytajZTekstu(nazwaPliku, drzewo);
                break;

<<<<<<< HEAD
=======
            case 8: // Zapisz Binarnie
                cout << "Podaj nazwe pliku do zapisu binarnego (np. drzewo.bin): ";
                getline(cin, nazwaPliku);
                menedzer.zapiszBinarnie(nazwaPliku, drzewo);
                break;

            case 9: // Wczytaj Binarnie
                cout << "Podaj nazwe pliku do wczytania binarnego (np. drzewo.bin): ";
                getline(cin, nazwaPliku);
                menedzer.wczytajBinarnie(nazwaPliku, drzewo);
                break;

>>>>>>> 20bfa62 (Integracja operacji binarnych i czyszczenia drzewa z menu)
            case 0: // Wyjście
                cout << "Koniec programu." << endl;
                return 0;

            default:
                cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
        }
    }

    return 0; 
}