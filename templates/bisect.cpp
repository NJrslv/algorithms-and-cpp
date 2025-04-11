#include <ios>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>

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

template <typename T>
bool binary_search(const vector<T>& v, const T& t) {
    int l = 0, r = v.size();
    while(l < r) {
        int m = l + ((r - l) >> 1);
        if(v[m] == t) return true;
        else if(v[m] < t) l = m + 1;
        else r = m;
    }
    return false;
}

template <typename T>
int lower_bound(const vector<T>& v, const T& t) {
    int l = 0, r = v.size();
    while(l < r) {
        int m = l + ((r - l) >> 1);
        if(t <= v[m]) r = m;
        else l = m + 1;
    }
    return l;
}

template <typename T>
int upper_bound(const vector<T>& v, const T& t) {
    int l = 0, r = v.size();
    while(l < r) {
        int m = l + ((r - l) >> 1);
        if(t < v[m]) r = m;
        else l = m + 1;
    }
    return l;
}

template <typename T>
double double_lower_bound(const vector<T>& v, double L, double R, double eps, function<bool(double)> good) {
    double l = L, r = R;
    // Usually 100 iters is enough.
    for(int _ = 0; _ < log2((r - l) / eps); ++_) {
        double m = (r + l) * 0.5;
        if(good(m)) r = m;
        else l = m;
    }
    // cout << setprecision(20)
    return r;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;
    vi v(n);
    for(auto& el : v) cin >> el;
    while(k--) {
        int t; cin >> t;
        int i = upper_bound(v, t);
        if(i == n || i == 0) cout << "0\n";
        else cout << i - 1 << '\n';
    }

    return 0;
}

