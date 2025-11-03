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
    } else {
   
        znaleziono = znajdzSciezke(wezel->prawy, dane, sciezka);
    }

 
    if (!znaleziono) {
       
        string usunieta_wartosc = to_string(wezel->dane);
        size_t dlugoscDoUsuniecia = usunieta_wartosc.length() + 4; 

        
        if (sciezka.length() >= dlugoscDoUsuniecia && sciezka.substr(sciezka.length() - 4) == " -> ") {
            
             sciezka.erase(sciezka.length() - dlugoscDoUsuniecia);
        } else if (sciezka.length() >= usunieta_wartosc.length()) {
             
             sciezka.erase(sciezka.length() - usunieta_wartosc.length());
        }
    }

    return znaleziono;
}

void DrzewoBST::znajdzSciezke(int dane) {
    string sciezka = "";

   
    if (znajdzSciezke(korzen, dane, sciezka)) {
        cout << "\n✅ Ścieżka do danych " << dane << ": " << sciezka << endl;
    } else {
        cout << "\n❌ Dane " << dane << " nie zostały znalezione w drzewie." << endl;
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
    } else if (wartosc > wezel->dane) {
     
        wezel->prawy = usun(wezel->prawy, wartosc);
    } else {
       

   
        if (wezel->lewy == nullptr) {
            Wezel* temp = wezel->prawy;
            delete wezel;
            return temp;
        } else if (wezel->prawy == nullptr) {
            Wezel* temp = wezel->lewy;
            delete wezel;
            return temp;
        }

    -
        
        Wezel* nastepnik = znajdzMin(wezel->prawy);
        
       
        wezel->dane = nastepnik->dane;
        
      
        wezel->prawy = usun(wezel->prawy, nastepnik->dane);
    }
    
    return wezel; 
}

void DrzewoBST::usun(int wartosc) {
   
    Wezel* nowy_korzen = usun(korzen, wartosc);
    
    if (nowy_korzen != korzen) {
        korzen = nowy_korzen;
        cout << "\n✅ Wartość " << wartosc << " usunięta pomyślnie." << endl;
    } else if (nowy_korzen == nullptr && korzen == nullptr) {
      
        cout << "\n✅ Wartość " << wartosc << " usunięta pomyślnie. Drzewo jest teraz puste." << endl;
    } else {
        cout << "\n Nie znaleziono wartości " << wartosc << " do usunięcia." << endl;
    }
}