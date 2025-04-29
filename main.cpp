#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <limits>

using namespace std;

/* ===== Struktura krawędzi ===== */
struct Krawedz {
    int cel;
    explicit Krawedz(int c) : cel(c) {}
};

/* ===== Funkcja DFS (Depth-First Search) ===== */
void DFS(int start, const vector<vector<Krawedz>>& graf, vector<bool>& odw, int id) {
    stack<int> st;
    st.push(start);
    cout << "[Graf " << id << "] Start DFS od wierzcholka " << start << endl;

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        if (odw[v]) continue;
        odw[v] = true;

        cout << "[Graf " << id << "] Odwiedzono wierzcholek: " << v << endl;

        for (auto it = graf[v].rbegin(); it != graf[v].rend(); ++it)
            if (!odw[it->cel])
                st.push(it->cel);
    }

    cout << "[Graf " << id << "] DFS ZAKONCZONE." << endl;
}

/* ===== Funkcja dodająca krawędź do grafu ===== */
bool dodajKrawedz(vector<vector<Krawedz>>& g, int a, int b) {
    if (a == b) {
        cout << "  Krawedz " << a << " -> " << b << " odrzucona (petla)." << endl;
        return false;
    }

    for (const auto& k : g[a])
        if (k.cel == b) {
            cout << "  Krawedz " << a << " - " << b << " juz istnieje. Pomijam." << endl;
            return false;
        }

    g[a].push_back(Krawedz(b));
    g[b].push_back(Krawedz(a));
    return true;
}

/* ===== Funkcja wypisująca listę sąsiedztwa ===== */
void wypisz(const vector<vector<Krawedz>>& g, int id) {
    cout << endl << "[Graf " << id << "] Lista sasiedztwa:" << endl;
    for (size_t i = 0; i < g.size(); ++i) {
        cout << ' ' << i << ": ";
        for (const auto& k : g[i])
            cout << k.cel << ' ';
        cout << endl;
    }
}

/* ===== Funkcja wczytująca graf od użytkownika ===== */
void wczytaj(vector<vector<Krawedz>>& g, int& start, int id) {
    int n, m;
    cout << endl << "[Graf " << id << "] Podaj liczbe wierzcholkow: ";
    cin >> n;
    cout << "[Graf " << id << "] Podaj liczbe krawedzi: ";
    cin >> m;

    g.assign(n, {});

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "[Graf " << id << "] Podaj " << m << " krawedzi (np. 0 1):" << endl;
    int dodane = 0;
    string linia;
    while (dodane < m) {
        cout << "  [" << dodane + 1 << "/" << m << "]> ";
        getline(cin, linia);
        istringstream iss(linia);

        int a, b;
        if (!(iss >> a >> b) || (iss >> ws && !iss.eof())) {
            cout << "  Nieprawidlowy format – wpisz dwie liczby." << endl;
            continue;
        }
        if (a < 0 || b < 0 || a >= n || b >= n) {
            cout << "  Indeksy poza zakresem 0-" << n - 1 << "." << endl;
            continue;
        }
        if (dodajKrawedz(g, a, b)) ++dodane;
    }

    do {
        cout << "[Graf " << id << "] Podaj wierzcholek startowy (0-" << n - 1 << "): ";
        cin >> start;
        if (start < 0 || start >= n)
            cout << "  Nieprawidlowy wierzcholek startowy." << endl;
    } while (start < 0 || start >= n);
}

/* ===== Funkcja główna ===== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<Krawedz>> g1, g2;
    int s1, s2;

    wczytaj(g1, s1, 1);
    wczytaj(g2, s2, 2);

    wypisz(g1, 1);
    wypisz(g2, 2);

    vector<bool> odw1(g1.size(), false), odw2(g2.size(), false);

    cout << endl << "Rozpoczynamy DFS na grafie 1:" << endl;
    DFS(s1, g1, odw1, 1);

    cout << endl << "Rozpoczynamy DFS na grafie 2:" << endl;
    DFS(s2, g2, odw2, 2);

    cout << endl << "Wszystkie watki DFS zakonczone." << endl;
    return 0;
}

