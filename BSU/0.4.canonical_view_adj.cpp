#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    size_t n;
    bool item;
    cin >> n;
    vector<int> v(n + 1, 0);
    for(size_t i = 1; i <= n; ++i) {
        for(size_t j = 1; j <= n; ++j) {
            cin >> item;
            if(item) v[j] = i;
        }
    }
    for(size_t i = 1; i <= n; ++i) cout << v[i] << " ";
}
