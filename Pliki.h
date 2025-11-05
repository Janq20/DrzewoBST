#pragma once
#include <iostream>
#include <string>
#include "DrzewoBST.h" 

using namespace std;

class MenedzerPlikow {
private:

public:
    void wczytajZTekstu(const string& nazwaPliku, DrzewoBST& drzewo);
};