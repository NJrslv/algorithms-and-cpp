#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define sz(a) int((a).size())

using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using ii64 = pair<int64_t, int64_t>;
using vii = vector<ii>;
using i64 = int64_t;

struct DSU {
    DSU(int n) {
        p.resize(n);
        iota(begin(p), end(p), 0);
        sz.resize(n, 1);
    }

    int find(int a) {
        return p[a] == a ? a : p[a] = find(p[a]);
    }

    void merge(int a, int b) {
        a = find(a), b = find(b);
        if(a != b) {
            if(sz[a] > sz[b])
                swap(a, b);
            p[a] = p[b];
            sz[b] += sz[a];
        }
    }
    vi p, sz;
};

struct Edge {
    int b, e, w;
};

i64 kruskal(vector<Edge>& e, int n) {
    sort(begin(e), end(e), [](const auto& l, const auto& r) {
        return l.w < r.w;
    });
    DSU dsu(n);
    i64 W = 0;
    for(const auto& [b, e, w] : e)
        if(dsu.find(b) != dsu.find(e))
           W += w, dsu.merge(b, e);
    return W;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    return 0;
}

