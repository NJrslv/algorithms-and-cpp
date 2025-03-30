#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <functional>

using namespace std;

#define sz(a) int((a).size())
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using ii64 = pair<int64_t, int64_t>;
using vii = vector<ii>;
using i64 = int64_t;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T> >;

template<class T>
using max_heap = priority_queue<T, vector<T> >;

template<class T, class Comparator>
using comp_heap = priority_queue<T, std::vector<T>, Comparator>;

uint32_t next_pow2(uint32_t n) {
    if (n <= 1) return 1;
    return 1 << (32 - __builtin_clz(n - 1));
}

template <typename T>
class SGTree {
public:
    // Starting index is 1.
    SGTree(const vector<T>& v, function<T(T, T)> combinator, T neutral)
    : n_in(sz(v)), n(next_pow2(sz(v))), zero(neutral), arr(2 * n, zero), f(combinator) {
        copy(begin(v), end(v), begin(arr) + n);
        for(int node = n - 1; node > 0; --node)
            arr[node] = f(arr[node << 1], arr[node << 1 | 1]);
    }

    void set(int node, const T& val) {
        node += n;
        arr[node] = val;
        for(node = node >> 1; node > 0; node >>= 1)
            arr[node] = f(arr[node << 1], arr[node << 1 | 1]);
    }

    // [l, r)
    // If l is odd, then it is the right child. So we don't want to include our parent.
    // That is because the left border is l; if we include the parent node, it means that
    // we also include its left child, but the left child has an index of l - 1, and we start from l.
    // The same logic applies to the r index in case it is even (left child), note that r is not
    // included so we are checking that r is odd => r - 1 is even.
    T op(int l, int r) {
        T res{};
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = f(res, arr[l++]);
            // r is not included, so prefix decrement.
            if(r & 1) res = f(res, arr[--r]);
        }
        return res;
    }
    
    // Segtree on sum, ai in {0, 1}, find kth one.
    T kthOne(int k) {
        int start = 1;
        while(start < n) {
            int l = start << 1, r = l | 1;
            bool goLeft = arr[l] > k;
            k -= goLeft ? 0 : arr[l];
            start = goLeft ? l : r;
        }
        return start - n;
    }

    // Initially segtree on max.
    int first_greater(int l, int r, T val, int invalid) {
        function<int(int, int, int)> go
            = [this, l, r, val, invalid, &go](int x, int lx, int rx) {
            if (rx <= l || lx >= r)
                return invalid;
            if (rx - lx == 1)
                return (lx < n_in && arr[x] >= val) ? lx : invalid;

            int lChild = x << 1, rChild = x << 1 | 1, mid = (lx + rx) >> 1;
            int res = arr[lChild] >= val ? go(lChild, lx, mid) : invalid;
            if(res != invalid)
                return res;
            return arr[rChild] >= val ? go(rChild, mid, rx) : invalid;
        };
        return go(1, 0, n);
    }

private:
    int n_in;
    int n;
    T zero;
    vector<T> arr;
    function<T(T, T)> f;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<i64> v(n);
    for(i64& el : v)
        cin >> el;

    SGTree<i64> sgt(v, [](i64 a, i64 b) { return a + b; }, 0);
    while(m--) {
        int op, a, b;
        cin >> op >> a >> b;
        if(op == 1) sgt.set(a, b);
        else cout << sgt.op(a, b) << '\n';
    }

    return 0;
}
