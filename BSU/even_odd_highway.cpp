#include <iostream>
#include <stack>
#include <array>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include <sstream>

using namespace std;

vector<vector<int>> g;
array<bool, 301> used;
array<int, 301> part;
int n;

void is_bipartite(int x, uint8_t& is);
void dfs();
void read();

void solve() {
    read();

}

int main() {
    ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}

void read() {
    cin >> n;
    cin.ignore();
    g.resize(n + 1);
    for(size_t v = 1; v <= n; ++v) {
        string ith;
        getline(cin, ith);
        stringstream ss(ith);
        int v_;
        while (ss >> v_) g[v].push_back(v_);
    }
}

void is_bipartite(int x, uint8_t& is) {
    used[x] = true;
    for(auto u : g[x]) {
        if(used[u] && part[u] == part[x]) {
            is = false;
        } else if(!used[u]) {
            part[u] = !part[x];
            is_bipartite(u, is);
        }
    }
}

void dfs() {
    int components = 0;
    for(size_t v = 1; v <= n; ++v) {
        cout << used[v] << "<--\n";
        if(!used[v]) {
            ++components;
            part[v] = true;
            uint8_t is = true;
            is_bipartite(v, is);
            cout << is;
        }
    }
}