#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<vector<int>> g;
array<bool, 301> used;
array<bool, 301> part;
int n;

void read() {
    cin >> n;
    cin.ignore();
    g.resize(n + 1);
    for(size_t v = 1; v <= n; ++v) {
        string ith;
        getline(cin, ith);
        stringstream ss(ith);
        int v_;
        while (ss >> v_) {
            if (v_ == 0) continue;
            g[v].push_back(v_);
        }
    }
}

void dfs(int x, bool& is_bipartite, int& cnt) {
    used[x] = true;
    for(auto u : g[x]) {
        if(used[u] && part[u] == part[x]) {
            is_bipartite = false;
        } else if(!used[u]) {
            part[u] = !part[x];
            dfs(u, is_bipartite, ++cnt);
        }
    }
}

void solve() {
    read();
    int components = 0;
    int power = 0;
    bool isbpte = false;
    for(size_t v = 1; v <= n; ++v) {
        if(bool is_bipartite = true; !used[v]) {
            fill(begin(part) + 1, begin(part) + n + 1, 0);
            ++components;
            part[v] = 1;
            int cnt = 1;
            dfs(v, is_bipartite, cnt);
            if(is_bipartite) {
                isbpte = true;
                int cnt_l = count(begin(part) + 1, begin(part) + n + 1, 1);
                power += max(cnt_l, cnt - cnt_l);
            } else {
                ++power;
            }
        }
    }
    if(components == 1 && !isbpte)
        cout << "YES";
    else
        cout << "NO" << "\n" << power;
}

int main() {
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    solve();
}
