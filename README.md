# 🌳 DrzewoBST (Binary Search Tree) — C++

Repozytorium **DrzewoBST** zawiera implementację **Drzewa BST (Binary Search Tree / Drzewo Binarnych Poszukiwań)** w języku **C++** wraz z modułem obsługi plików oraz plikami demonstracyjnymi/testowymi. Projekt został przygotowany jako czytelne, edukacyjne rozwiązanie pokazujące klasyczne operacje na BST: wstawianie, wyszukiwanie, przejścia drzewa oraz (w zależności od implementacji) usuwanie elementów.

---

## 💡 Opis Projektu

**BST (Binary Search Tree)** to struktura danych oparta o węzły, w której:

- wszystkie wartości w **lewym poddrzewie** są **mniejsze** od wartości w węźle,
- wszystkie wartości w **prawym poddrzewie** są **większe** (lub zgodnie z logiką implementacji – np. wartości równe mogą trafiać tylko w jedną stronę).

Dzięki temu BST zapewnia szybkie operacje:

- **wyszukiwanie**,
- **wstawianie**,
- **usuwanie**,

które średnio mają złożoność **O(log n)**, natomiast w pesymistycznym przypadku (gdy drzewo staje się „listą”) **O(n)**.

Projekt jest podzielony na moduły:
- logika drzewa BST (`DrzewoBST.h/.cpp`),
- obsługa plików (`Pliki.h/.cpp`),
- program główny (`main.cpp`),
- plik testowy (`test.cpp`).

---

## ✨ Główne Cechy

* **Implementacja BST w C++** (czytelna i modularna).
* **Podział na pliki nagłówkowe i źródłowe** (`.h` / `.cpp`).
* **Obsługa plików** – wczytywanie / zapisywanie danych (moduł `Pliki`).
* **Program demonstracyjny** (`main.cpp`) – uruchomienie i prezentacja działania.
* **Plik testowy** (`test.cpp`) – scenariusze weryfikujące poprawność działania.
* **Dokumentacja w komentarzach** (przydatne pod dalsze rozszerzenie, np. Doxygen).

---

## 📁 Struktura repozytorium

```
DrzewoBST/
├── DrzewoBST.h        # Interfejs BST (definicje klas/struktur i metod)
├── DrzewoBST.cpp      # Implementacja operacji BST
├── Pliki.h            # Interfejs obsługi plików
├── Pliki.cpp          # Implementacja obsługi plików
├── main.cpp           # Program główny (demo / uruchomienie)
└── test.cpp           # Testy / scenariusze sprawdzające działanie
```

---

## 🧠 Jak działa BST w tym projekcie?

W typowej implementacji BST (i w tym projekcie) występują elementy:

### 1) Węzeł drzewa
Każdy węzeł przechowuje:
- wartość (np. liczba),
- wskaźnik do lewego dziecka,
- wskaźnik do prawego dziecka.

### 2) Operacje podstawowe
Najczęściej dostępne są:
- **insert** — dodanie nowej wartości do odpowiedniego miejsca w drzewie,
- **search** — wyszukiwanie wartości (porównania i zejście w lewo/prawo),
- **traversal** — przejścia drzewa:
  - `inorder` (daje wartości w kolejności rosnącej),
  - `preorder`, `postorder` (przydatne np. do zapisu/odtwarzania),
- **remove** — usuwanie węzła:
  - przypadek 0 dzieci (liść),
  - 1 dziecko,
  - 2 dzieci (zastępstwo następnikiem/poprzednikiem).

---

## 🛠 Uruchomienie (kompilacja)

### ✅ Kompilacja w trybie „jeden folder” (g++)
Jeżeli jesteś w katalogu repo i masz wszystkie pliki obok siebie:

```bash
g++ -std=c++17 -O2 main.cpp DrzewoBST.cpp Pliki.cpp -o DrzewoBST
./DrzewoBST
```

### ✅ Kompilacja pliku testowego
```bash
g++ -std=c++17 -O2 test.cpp DrzewoBST.cpp Pliki.cpp -o DrzewoBST_test
./DrzewoBST_test
```

> Jeśli używasz Windows + MinGW:
```bash
g++ -std=c++17 -O2 main.cpp DrzewoBST.cpp Pliki.cpp -o DrzewoBST.exe
DrzewoBST.exe
```

---

## 📖 Użycie

1. Uruchom program (`main.cpp`).
2. W zależności od tego jak jest napisana część „client code”, możesz:
   - dodawać elementy do drzewa,
   - wyszukiwać elementy,
   - wypisywać drzewo (np. inorder),
   - wczytywać dane z pliku / zapisywać wyniki.

Jeżeli w repo jest menu tekstowe — obsługa odbywa się z poziomu konsoli.

---

## 🧪 Testy / weryfikacja

Plik `test.cpp` służy do sprawdzania poprawności operacji BST (np. czy wstawione elementy występują w drzewie, czy inorder zwraca kolejność rosnącą, czy usuwanie działa poprawnie w różnych przypadkach).

---

## 🔥 Co można dodać dalej (pomysły rozwoju)

* balansowanie drzewa (AVL / Red-Black Tree),
* testy jednostkowe w Google Test,
* benchmark wydajności (dla dużych danych),
* eksport drzewa do pliku (np. Graphviz `.dot`),
* obsługa duplikatów w kontrolowany sposób (licznik w węźle).

---

## 👤 Autorzy
**Janq20**  
**Zahinisu**

---
