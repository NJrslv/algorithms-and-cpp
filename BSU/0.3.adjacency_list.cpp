#include <iostream>
#include <unordered_map>
#include <set>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    size_t n, m, b, e;
    unordered_map<size_t, set<size_t>> lst; 
    cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        cin >> b >> e;
        lst[b].insert(e);
        lst[e].insert(b);
    }
    
    for(size_t i = 1; i <= n; ++i) {
        cout << lst[i].size() << " ";
        for(auto & el : lst[i]) {
            cout << el << " ";
        }
        cout << "\n";
    }
}