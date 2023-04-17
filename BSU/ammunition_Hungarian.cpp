#include <vector>
#include <iostream>
#include <utility>
#include <limits>

using namespace std;

const int inf = 201;
using vvi = vector<vector<int>>;
using vi = vector<int>;

//Hungarian algorithm
int min_weight_perfect_matching(vvi &ws) {
    int n = (int) ws.size();
    vi way(n), p(n), v(n), u(n);

    for (int i = 1; i < n; ++i) {
        vi minv(n, inf);
        vi used(n);
        p[0] = i;
        int j0 = 0;

        while (p[j0] != 0) {
            used[j0] = true;
            int i0 = p[j0];
            int delta = inf;
            int j1 = 0;

            for (int j = 1; j < n; ++j) {
                if (!used[j]) {
                    int d = ws[i0][j] - u[i0] - v[j];
                    if (minv[j] > d) {
                        minv[j] = d;
                        way[j] = j0;
                    }
                    if (delta > minv[j]) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j < n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        }

        while (j0 != 0) {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        }
    }
    return -v[0];
}

bool check(vvi& ws, int n) {
    for(size_t i = 1; i < n + 1; ++i) {
        bool r = 0, c = 0;
        for(size_t j = 1; j < n + 1; ++j) {
            if(ws[i][j] != inf) r = 1;
            if(ws[j][i] != inf) c = 1;
        }
        if(!(r && c)) return 0;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> ws(n + 1, vector<int>(n + 1, inf));
    for(int i = 0; i < n + 1; ++i) ws[i][0] = ws[0][i] = 0;

    for(int lv = 1; lv <= n; ++lv) {
        int k;
        cin >> k;
        for(int cnt = 0; cnt < k; ++cnt) {
            int rv, w;
            cin >> rv >> w;
            ws[lv][rv] = w;
        }
    }

    if(check(ws, n))
        cout << min_weight_perfect_matching(ws);
    else
        cout << "-1";

    return 0;
}