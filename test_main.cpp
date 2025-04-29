#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <limits>
#include <cassert>

using namespace std;

struct Krawedz {
    int cel;
    explicit Krawedz(int c) : cel(c) {}
};

void DFS(int start, const vector<vector<Krawedz>>& graf, vector<bool>& odw, int id, ostringstream& output) {
    stack<int> st;
    st.push(start);
    output << "[Graf " << id << "] Start DFS od wierzcholka " << start << '\n';

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        if (odw[v]) continue;
        odw[v] = true;

        output << "[Graf " << id << "] Odwiedzono wierzcholek: " << v << '\n';

        for (auto it = graf[v].rbegin(); it != graf[v].rend(); ++it)
            if (!odw[it->cel])
                st.push(it->cel);
    }

    output << "[Graf " << id << "] DFS ZAKONCZONE.\n";
}

bool dodajKrawedz(vector<vector<Krawedz>>& g, int a, int b) {
    if (a == b) return false;

    for (const auto& k : g[a])
        if (k.cel == b) return false;

    g[a].push_back(Krawedz(b));
    g[b].push_back(Krawedz(a));
    return true;
}

void wypisz(const vector<vector<Krawedz>>& g, int id) {
    cout << "\n[Graf " << id << "] Lista sasiedztwa:\n";
    for (size_t i = 0; i < g.size(); ++i) {
        cout << ' ' << i << ": ";
        for (const auto& k : g[i])
            cout << k.cel << ' ';
        cout << '\n';
    }
}

void wczytaj(vector<vector<Krawedz>>& g, int& start, int id) {
    int n, m;
    n = 5;
    m = 4;

    g.assign(n, {});

    dodajKrawedz(g, 0, 1);
    dodajKrawedz(g, 0, 2);
    dodajKrawedz(g, 1, 3);
    dodajKrawedz(g, 2, 4);

    start = 0;
}

void testDFS() {
    vector<vector<Krawedz>> g1;
    int s1;

    wczytaj(g1, s1, 1);

    ostringstream output;
    vector<bool> odw1(g1.size(), false);

    DFS(s1, g1, odw1, 1, output);

    string expected_output = "[Graf 1] Start DFS od wierzcholka 0\n"
                             "[Graf 1] Odwiedzono wierzcholek: 0\n"
                             "[Graf 1] Odwiedzono wierzcholek: 1\n"
                             "[Graf 1] Odwiedzono wierzcholek: 3\n"
                             "[Graf 1] Odwiedzono wierzcholek: 2\n"
                             "[Graf 1] Odwiedzono wierzcholek: 4\n"
                             "[Graf 1] DFS ZAKONCZONE.\n";

    assert(output.str() == expected_output);

    cout << "? Test DFS przeszedl pomyslnie!" << endl;
}

int main() {
    testDFS();
    return 0;
}
