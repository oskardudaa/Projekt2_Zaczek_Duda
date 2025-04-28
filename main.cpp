#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <limits>

using namespace std;

/* ===== Struktura krawędzi ===== */
struct Krawedz {
    int cel;  // Zmienna przechowująca numer wierzchołka, do którego prowadzi krawędź
    explicit Krawedz(int c) : cel(c) {}  // Konstruktor, który ustawia cel krawędzi
};

/* ===== Funkcja DFS (Depth-First Search) ===== */
void DFS(int start, const vector<vector<Krawedz>>& graf, vector<bool>& odw, int id) {
    // Tworzymy stos, który będzie przechowywał wierzchołki do odwiedzenia
    stack<int> st;
    st.push(start);  // Dodajemy wierzchołek startowy na stos
    cout << "[Graf " << id << "] Start DFS od wierzcholka " << start << '\n';

    // Dopóki stos nie jest pusty, będziemy przetwarzać kolejne wierzchołki
    while (!st.empty()) {
        int v = st.top();  // Pobieramy wierzchołek z góry stosu
        st.pop();  // Usuwamy ten wierzchołek ze stosu

        if (odw[v]) continue;  // Jeśli wierzchołek już odwiedziliśmy, pomijamy go
        odw[v] = true;  // Oznaczamy wierzchołek jako odwiedzony

        cout << "[Graf " << id << "] Odwiedzono wierzcholek: " << v << '\n';

        // Przechodzimy przez sąsiadów wierzchołka (w odwrotnej kolejności)
        for (auto it = graf[v].rbegin(); it != graf[v].rend(); ++it)
            if (!odw[it->cel])  // Jeśli sąsiad nie był jeszcze odwiedzony
                st.push(it->cel);  // Dodajemy go do stosu
    }

    cout << "[Graf " << id << "] DFS ZAKONCZONE.\n";
}

/* ===== Funkcja dodająca krawędź do grafu ===== */
bool dodajKrawedz(vector<vector<Krawedz>>& g, int a, int b) {
    if (a == b) {  // Zapobieganie pętli (krawędź prowadząca do samego siebie)
        cout << "  Krawedz " << a << " -> " << b << " odrzucona (petla).\n";
        return false;
    }
   
    // Sprawdzamy, czy krawędź już istnieje w grafie
    for (const auto& k : g[a])
        if (k.cel == b) {
            cout << "  Krawedz " << a << " - " << b << " juz istnieje. Pomijam.\n";
            return false;
        }

    // Dodajemy krawędź do grafu (dodajemy ją w obie strony, ponieważ graf jest nieskierowany)
    g[a].push_back(Krawedz(b));  
    g[b].push_back(Krawedz(a));
    return true;
}

/* ===== Funkcja wypisująca listę sąsiedztwa ===== */
void wypisz(const vector<vector<Krawedz>>& g, int id) {
    cout << "\n[Graf " << id << "] Lista sasiedztwa:\n";
    for (size_t i = 0; i < g.size(); ++i) {  // Przechodzimy po wszystkich wierzchołkach
        cout << ' ' << i << ": ";  // Wypisujemy numer wierzchołka
        for (const auto& k : g[i])  // Dla każdego sąsiada wierzchołka
            cout << k.cel << ' ';  // Wypisujemy numer sąsiada
        cout << '\n';
    }
}

/* ===== Funkcja wczytująca graf od użytkownika ===== */
void wczytaj(vector<vector<Krawedz>>& g, int& start, int id) {
    int n, m;
    cout << "\n[Graf " << id << "] Podaj liczbe wierzcholkow: ";
    cin >> n;  // Liczba wierzchołków
    cout << "[Graf " << id << "] Podaj liczbe krawedzi: ";
    cin >> m;  // Liczba krawędzi

    g.assign(n, {});  // Inicjalizujemy graf jako pusty (graf o n wierzchołkach)

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "[Graf " << id << "] Podaj " << m << " krawedzi (np. 0 1):\n";
    int dodane = 0;
    string linia;
    while (dodane < m) {  // Dopóki nie dodamy wszystkich krawędzi
        cout << "  [" << dodane + 1 << "/" << m << "]> ";
        getline(cin, linia);  // Wczytujemy linię z danymi krawędzi
        istringstream iss(linia);  // Tworzymy strumień wejściowy z tej linii

        int a, b;
        if (!(iss >> a >> b) || (iss >> ws && !iss.eof())) {  // Sprawdzamy poprawność formatu
            cout << "  Nieprawidlowy format – wpisz dwie liczby.\n";
            continue;
        }
        if (a < 0 || b < 0 || a >= n || b >= n) {  // Sprawdzamy, czy indeksy są w dozwolonym zakresie
            cout << "  Indeksy poza zakresem 0-" << n - 1 << ".\n";
            continue;
        }
        if (dodajKrawedz(g, a, b)) ++dodane;  // Dodajemy krawędź do grafu
    }

    // Wczytujemy wierzchołek startowy dla DFS
    do {
        cout << "[Graf " << id << "] Podaj wierzcholek startowy (0-" << n - 1 << "): ";
        cin >> start;
        if (start < 0 || start >= n)
            cout << "  Nieprawidlowy wierzcholek startowy.\n";
    } while (start < 0 || start >= n);
}

/* ===== Funkcja główna ===== */
int main() {
    ios::sync_with_stdio(false);  // Wyłączamy synchronizację I/O (dla szybszego działania)
    cin.tie(nullptr);  // Zrywamy powiązanie między cin i cout, co poprawia wydajność

    vector<vector<Krawedz>> g1, g2;  // Dwa grafy
    int s1, s2;  // Wierzchołki startowe dla dwóch grafów

    wczytaj(g1, s1, 1);  // Wczytanie pierwszego grafu
    wczytaj(g2, s2, 2);  // Wczytanie drugiego grafu

    wypisz(g1, 1);  // Wypisanie listy sąsiedztwa pierwszego grafu
    wypisz(g2, 2);  // Wypisanie listy sąsiedztwa drugiego grafu

    vector<bool> odw1(g1.size(), false), odw2(g2.size(), false);  // Wektory odwiedzin dla dwóch grafów

    // Przeszukiwanie DFS dla obu grafów
    cout << "\nRozpoczynamy DFS na grafie 1:\n";
    DFS(s1, g1, odw1, 1);

    cout << "\nRozpoczynamy DFS na grafie 2:\n";
    DFS(s2, g2, odw2, 2);

    cout << "\nWszystkie wątki DFS zakończone.\n";
    return 0;
}
