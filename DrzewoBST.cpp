// --- Metody Wyświetlania (Prywatne) ---

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

// --- Metoda Wyświetlania (Publiczna) ---

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
    // 1. Warunek bazowy: Wartości nie ma w tej poddrzewie
    if (wezel == nullptr) {
        return false;
    }

    // Dodaj aktualne dane węzła do ścieżki
    sciezka += to_string(wezel->dane);

    // 2. Warunek sukcesu: Znaleziono wartość
    if (wezel->dane == dane) {
        return true;
    }

    // Dodaj strzałkę przed przejściem dalej
    sciezka += " -> ";

    // 3. Rekurencyjne przejście (w lewo lub w prawo)
    bool znaleziono;
    
    if (dane < wezel->dane) {
        // Idź w lewo
        znaleziono = znajdzSciezke(wezel->lewy, dane, sciezka);
    } else {
        // Idź w prawo (dane > wezel->dane)
        znaleziono = znajdzSciezke(wezel->prawy, dane, sciezka);
    }

    // 4. Backtracking (Wycofanie) - jeśli nie znaleziono na tej gałęzi
    if (!znaleziono) {
        // Oblicz długość, którą trzeba usunąć: Długość danych + długość " -> "
        string usunieta_wartosc = to_string(wezel->dane);
        size_t dlugoscDoUsuniecia = usunieta_wartosc.length() + 4; // 4 to długość " -> "

        // Usuń ostatnio dodany fragment (" -> X" lub samo "X")
        if (sciezka.length() >= dlugoscDoUsuniecia && sciezka.substr(sciezka.length() - 4) == " -> ") {
             // Usuń " -> " i wartość
             sciezka.erase(sciezka.length() - dlugoscDoUsuniecia);
        } else if (sciezka.length() >= usunieta_wartosc.length()) {
             // Usuń samą wartość (np. jeśli była to wartość docelowa, ale nie pasuje)
             sciezka.erase(sciezka.length() - usunieta_wartosc.length());
        }
    }

    return znaleziono;
}

void DrzewoBST::znajdzSciezke(int dane) {
    string sciezka = "";

    // Wywołanie prywatnej funkcji, przekazując korzeń drzewa
    if (znajdzSciezke(korzen, dane, sciezka)) {
        cout << "\n✅ Ścieżka do danych " << dane << ": " << sciezka << endl;
    } else {
        cout << "\n❌ Dane " << dane << " nie zostały znalezione w drzewie." << endl;
    }
}

// Dodana kolejna kluczowa funkcja drzewa

Wezel* DrzewoBST::znajdzMin(Wezel* wezel) {
    if (wezel == nullptr) {
        return nullptr;
    }
    // Najmniejszy element jest w najbardziej lewym węźle
    Wezel* aktualny = wezel;
    while (aktualny->lewy != nullptr) {
        aktualny = aktualny->lewy;
    }
    return aktualny;
}

Wezel* DrzewoBST::usun(Wezel* wezel, int wartosc) {
    // 1. Warunek bazowy: Wartość nie została znaleziona
    if (wezel == nullptr) {
        return nullptr;
    }

    // Rekurencyjne poszukiwanie węzła do usunięcia
    if (wartosc < wezel->dane) {
        // Idź w lewo
        wezel->lewy = usun(wezel->lewy, wartosc);
    } else if (wartosc > wezel->dane) {
        // Idź w prawo
        wezel->prawy = usun(wezel->prawy, wartosc);
    } else {
        // *** Węzeł do usunięcia został znaleziony (wezel->dane == wartosc) ***

        // --- Przypadek 1: Brak dzieci LUB tylko jedno dziecko ---
        if (wezel->lewy == nullptr) {
            Wezel* temp = wezel->prawy;
            delete wezel;
            return temp; // Zwróć prawe dziecko (może być nullptr)
        } else if (wezel->prawy == nullptr) {
            Wezel* temp = wezel->lewy;
            delete wezel;
            return temp; // Zwróć lewe dziecko
        }

        // --- Przypadek 3: Dwoje dzieci ---
        
        // a) Znajdź następnika (najmniejszy element w prawym poddrzewie)
        Wezel* nastepnik = znajdzMin(wezel->prawy);
        
        // b) Skopiuj dane następnika do bieżącego węzła
        wezel->dane = nastepnik->dane;
        
        // c) Usuń faktyczny następnik (który ma teraz maksymalnie jedno dziecko, 
        // co jest obsługiwane przez rekurencyjne wywołanie 'usun')
        wezel->prawy = usun(wezel->prawy, nastepnik->dane);
    }
    
    return wezel; // Zwróć niezmieniony wskaźnik, jeśli nic nie usuwaliśmy
}

void DrzewoBST::usun(int wartosc) {
    // Wywołaj prywatną funkcję usuwania, aktualizując wskaźnik korzenia drzewa
    Wezel* nowy_korzen = usun(korzen, wartosc);
    
    if (nowy_korzen != korzen) {
        korzen = nowy_korzen;
        cout << "\n✅ Wartość " << wartosc << " usunięta pomyślnie." << endl;
    } else if (nowy_korzen == nullptr && korzen == nullptr) {
        // Specjalny przypadek: Usunięto ostatni węzeł (korzeń)
        cout << "\n✅ Wartość " << wartosc << " usunięta pomyślnie. Drzewo jest teraz puste." << endl;
    } else {
        // Wartość nie została znaleziona lub węzeł był liściem i korzeń się nie zmienił
        // (Węzły liści i węzły z jednym dzieckiem zmieniają wskaźniki wewnątrz drzewa, 
        // ale nie korzeń, chyba że korzeń jest usuwany)
        // Możemy tu dodać dodatkowe sprawdzenie, czy wartość istniała.
        cout << "\n❌ Nie znaleziono wartości " << wartosc << " do usunięcia." << endl;
    }
}