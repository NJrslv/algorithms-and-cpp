#include <iostream>
#include <array>
#include <queue>

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

void bfs(size_t start) {
    queue<size_t> q;
    v[start] = true;
    q.push(start);
    ans[start] = cnt++;
    while(!q.empty()) {
        size_t x = q.front();
        q.pop();
        for(size_t i = 0; i <= n; ++i) {
            if(m[x][i] && !v[i]) {
                ans[i] = cnt++;
                v[i] = true;
                q.push(i);
            }
        }
    }
}

void solve() {
    read();
    for(size_t i = 1; i <= n; ++i) {
        if(!v[i])
            bfs(i);
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