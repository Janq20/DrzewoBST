#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

struct Wezel {
    int dane;
    Wezel* lewy;
    Wezel* prawy;

    Wezel(int d) : dane(d), lewy(nullptr), prawy(nullptr) {}
};

class MenedzerPlikow;

class DrzewoBST {
private:
    Wezel* korzen;

    Wezel* dodaj(Wezel* wezel, int wartosc);
    void preorder(Wezel* wezel);
    void inorder(Wezel* wezel);
    void postorder(Wezel* wezel);
    bool znajdzSciezke(Wezel* wezel, int dane, string& sciezka);
    Wezel* znajdzMin(Wezel* wezel);
    Wezel* usun(Wezel* wezel, int wartosc);
    void zapiszDoTekstu(Wezel* wezel, fstream& plik);
    void usunWszystko(Wezel* wezel);
    void zapiszGraficznie(Wezel* wezel, fstream& plik, int poziom, int odstep);

public:
    DrzewoBST();
    ~DrzewoBST();

    void dodaj(int wartosc);
    void wyswietlGraficznie(int tryb);
    void znajdzSciezke(int dane);
    void usun(int wartosc);
    void zapiszDoTekstu(const string& nazwaPliku);
    void usunWszystko();
    void zapiszGraficznieDoTekstu(const string& nazwaPliku);

    friend class MenedzerPlikow;
};

class MenedzerPlikow {
private:
    void zapiszWezelBinarnie(fstream& plik, Wezel* wezel);
    Wezel* wczytajWezelBinarnie(fstream& plik);

public:
    void wczytajZTekstu(const string& nazwaPliku, DrzewoBST& drzewo);
    void zapiszBinarnie(const string& nazwaPliku, DrzewoBST& drzewo);
    void wczytajBinarnie(const string& nazwaPliku, DrzewoBST& drzewo);
};

DrzewoBST::DrzewoBST() {
    korzen = nullptr;
}

DrzewoBST::~DrzewoBST() {
    usunWszystko();
}

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
    return wezel;
}

void DrzewoBST::dodaj(int wartosc) {
    korzen = dodaj(korzen, wartosc);
}

void DrzewoBST::preorder(Wezel* wezel) {
    if (wezel != nullptr) {
        cout << wezel->dane << " ";
        preorder(wezel->lewy);
        preorder(wezel->prawy);
    }
}

void DrzewoBST::inorder(Wezel* wezel) {
    if (wezel != nullptr) {
        inorder(wezel->lewy);
        cout << wezel->dane << " ";
        inorder(wezel->prawy);
    }
}

void DrzewoBST::postorder(Wezel* wezel) {
    if (wezel != nullptr) {
        postorder(wezel->lewy);
        postorder(wezel->prawy);
        cout << wezel->dane << " ";
    }
}

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

    if (!znaleziono) {
        string usunieta_wartosc = to_string(wezel->dane);
        size_t dlugoscDoUsuniecia = usunieta_wartosc.length() + 4;

        if (sciezka.length() >= dlugoscDoUsuniecia && sciezka.substr(sciezka.length() - 4) == " -> ") {
            sciezka.erase(sciezka.length() - dlugoscDoUsuniecia);
        }
        else if (sciezka.length() >= usunieta_wartosc.length()) {
            sciezka.erase(sciezka.length() - usunieta_wartosc.length());
        }
    }

    return znaleziono;
}

void DrzewoBST::znajdzSciezke(int dane) {
    string sciezka = "";

    if (znajdzSciezke(korzen, dane, sciezka)) {
        cout << "\nŚcieżka do danych " << dane << ": " << sciezka << endl;
    }
    else {
        cout << "\nDane " << dane << " nie zostały znalezione w drzewie." << endl;
    }
}

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

        Wezel* nastepnik = znajdzMin(wezel->prawy);
        wezel->dane = nastepnik->dane;
        wezel->prawy = usun(wezel->prawy, nastepnik->dane);
    }

    return wezel;
}

void DrzewoBST::usun(int wartosc) {
    Wezel* stary_korzen = korzen;
    korzen = usun(korzen, wartosc);

    if (stary_korzen == nullptr) {
        cout << "\nNie znaleziono wartości " << wartosc << " do usunięcia (drzewo puste)." << endl;
    }
    else if (korzen == nullptr && stary_korzen != nullptr) {
        cout << "\nWartość " << wartosc << " usunięta pomyśllnie. Drzewo jest teraz puste." << endl;
    }
    else {
        cout << "\nOperacja usuwania dla " << wartosc << " zakończona." << endl;
    }
}
void DrzewoBST::zapiszDoTekstu(Wezel* wezel, fstream& plik) {
    if (wezel != nullptr) {
        plik << wezel->dane << "\n";
        zapiszDoTekstu(wezel->lewy, plik);
        zapiszDoTekstu(wezel->prawy, plik);
    }
}
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
void DrzewoBST::zapiszGraficznie(Wezel* wezel, fstream& plik, int poziom, int odstep) {
    if (wezel == nullptr) {
        return;
    }
    zapiszGraficznie(wezel->prawy, plik, poziom + 1, odstep);
    for (int i = 0; i < poziom * odstep; i++) {
        plik << " ";
    }
    plik << wezel->dane << "\n";
    zapiszGraficznie(wezel->lewy, plik, poziom + 1, odstep);
}
void DrzewoBST::zapiszGraficznieDoTekstu(const string& nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku, ios::out);

    if (!plik.is_open()) {
        cout << "Błąd otwarcia pliku do zapisu graficznego: " << nazwaPliku << endl;
        return;
    }

    cout << "Rozpoczynam zapis graficzny do pliku: " << nazwaPliku << "..." << endl;
    zapiszGraficznie(korzen, plik, 0, 5);

    plik.close();
    cout << "Drzewo zapisane (graficznie) do pliku: " << nazwaPliku << endl;
}
void DrzewoBST::usunWszystko() {
    usunWszystko(korzen);
    korzen = nullptr;
}

void DrzewoBST::usunWszystko(Wezel* wezel) {
    if (wezel != nullptr) {
        usunWszystko(wezel->lewy);
        usunWszystko(wezel->prawy);
        delete wezel;
    }
}

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

void MenedzerPlikow::zapiszWezelBinarnie(fstream& plik, Wezel* wezel) {
    if (wezel == nullptr) {
        bool jestWezel = false;
        plik.write(reinterpret_cast<char*>(&jestWezel), sizeof(bool));
    }
    else {
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
    }
    else {
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

void wyswietlMenu() {
    cout << "\n===== MENU DRZEWA BST =====\n";
    cout << "1. Dodaj element\n";
    cout << "2. Usun element\n";
    cout << "3. Znajdz sciezke\n";
    cout << "4. Wyswietl drzewo (tryby)\n";
    cout << "5. Usun cale drzewo\n";
    cout << "6. Zapisz graficznie do pliku TXT\n"; 
    cout << "7. Wczytaj z pliku TXT\n";
    cout << "8. Zapisz binarnie (BIN)\n";
    cout << "9. Wczytaj binarnie (BIN)\n";
    cout << "0. Wyjscie\n";
    cout << "Wybierz opcje: ";
}

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
        case 1:
            cout << "Podaj wartosc do dodania: ";
            wartosc = pobierzLiczbeCalkowita();
            drzewo.dodaj(wartosc);
            cout << "Dodano " << wartosc << " do drzewa." << endl;
            break;

        case 2:
            cout << "Podaj wartosc do usuniecia: ";
            wartosc = pobierzLiczbeCalkowita();
            drzewo.usun(wartosc);
            break;

        case 3:
            cout << "Podaj wartosc do znalezienia sciezki: ";
            wartosc = pobierzLiczbeCalkowita();
            drzewo.znajdzSciezke(wartosc);
            break;

        case 4:
            cout << "Wybierz tryb wyswietlania:\n";
            cout << " 1. Pre-order (Korzen -> Lewy -> Prawy)\n";
            cout << " 2. In-order (Lewy -> Korzen -> Prawy)\n";
            cout << " 3. Post-order (Lewy -> Prawy -> Korzen)\n";
            cout << "Wybierz (1-3): ";
            wartosc = pobierzLiczbeCalkowita();
            drzewo.wyswietlGraficznie(wartosc);
            break;

        case 5:
            drzewo.usunWszystko();
            cout << "Cale drzewo zostalo usuniete." << endl;
            break;

        case 6:
            cout << "Podaj nazwe pliku do zapisu (np. drzewo.txt): ";
            getline(cin, nazwaPliku);
            drzewo.zapiszGraficznieDoTekstu(nazwaPliku);
            break;

        case 7:
            cout << "Podaj nazwe pliku do wczytania (np. dane.txt): ";
            getline(cin, nazwaPliku);
            menedzer.wczytajZTekstu(nazwaPliku, drzewo);
            break;

        case 8:
            cout << "Podaj nazwe pliku do zapisu binarnego (np. drzewo.bin): ";
            getline(cin, nazwaPliku);
            menedzer.zapiszBinarnie(nazwaPliku, drzewo);
            break;

        case 9:
            cout << "Podaj nazwe pliku do wczytania binarnego (np. drzewo.bin): ";
            getline(cin, nazwaPliku);
            menedzer.wczytajBinarnie(nazwaPliku, drzewo);
            break;

        case 0:
            cout << "Koniec programu." << endl;
            return 0;

        default:
            cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
        }
    }

    return 0;
}