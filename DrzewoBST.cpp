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