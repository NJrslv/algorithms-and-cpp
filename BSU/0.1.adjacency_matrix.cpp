#include <iostream>
#include <array>
#include <cstring>

using namespace std;

array<array<bool, 101>, 101> adj;

int main() {
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    size_t n, m, b, e;
    cin >> n >> m;
    for(size_t i = 1; i <= m; ++i) {
        cin >> b >> e;
        adj[b][e] = true;
        adj[e][b] = true;
    }
    for(size_t i = 1; i <= n; ++i) {
        for(size_t j = 1; j <= n; ++j) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
}