#include "DrzewoBST.h"

// --- Konstruktor ---
DrzewoBST::DrzewoBST() {
    korzen = nullptr; 
}

// --- Metody publiczne ---

void DrzewoBST::dodaj(int wartosc) {
    korzen = dodaj(korzen, wartosc);
}

// --- Metody prywatne ---

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