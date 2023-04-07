#include <iostream>
#include <array>

using namespace std;

array<array<bool, 101>, 101> m;
array<bool, 101> v;
array<int, 101> ans;
int cnt = 1, n;

void read() {
    cin >> n;
    for(size_t i = 1; i <= n; ++i) {
        for(size_t j = 1; j <= n; ++j) {
            int val;
            cin >> val;
            m[i][j] = bool(val);
        }
    }
}

void dfs(size_t x) {
    v[x] = true;
    ans[x] = cnt++;
    for(size_t i = 1; i <= n; ++i) {
        if(m[x][i] && !v[i])
            dfs(i);
    }
}

void solve() {
    read();
    for(size_t i = 1; i <= n; ++i) {
        if(!v[i])
            dfs(i);
    }
    for(size_t i = 1; i <= n; ++i)
        cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    solve();
}