#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <cstdint>
#include <cmath>

using namespace std;

#define sz(a) int((a).size())
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
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

struct sparse_tbl {
    vvi st;

    sparse_tbl(const vi& arr) {
        st.resize(std::log2(sz(arr)) + 1, vi(sz(arr) + 1));
        st[0] = arr;
        for(int i = 1; i < sz(st); ++i)
            for(int j = 0; j + (1 << i) <= sz(arr); ++j)
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }

    // [l, r]
    int minimum(int l, int r) const {
        int i = std::log2(r - l + 1);
        return min(st[i][l], st[i][r - (1 << i) + 1]);
    }

};

struct SuffArr {
    string s;
    vi p, c, lcp_arr, inv;

    SuffArr(string str, int alphabet = 256) : s(std::move(str)) {
        build_suffix_array(alphabet);
        kasai_lcp();
    }

    void build_suffix_array(int alphabet) {
        int n = sz(s);
        // p - suffix array (arr of indexes), c - class array.
        // cnt - array for counting sort.
        p.resize(n), c.resize(n);
        vi cnt(max(alphabet, n), 0);
        // Do counting sort.
        // 1. Count elements.
        rep(i, 0, n) ++cnt[s[i]];
        // 2. Do prefix sum, so cnt[i] corresponds to how many elements are less the current i.
        rep(i, 1, alphabet) cnt[i] += cnt[i - 1];
        // 3. Use info about how many elements on the left - 1 as an index for the current element i.
        rep(i, 0, n) p[--cnt[s[i]]] = i;
        // Assign for the first in order suffix (currently of len 1) class 0.
        c[p[0]] = 0;
        int classes = 1;
        rep(i, 1, n) {
            // Assign classes, numbers from 0 to n - 1.
            classes += s[p[i - 1]] != s[p[i]];
            c[p[i]] = classes - 1;
        }
        // Now we consider substring of size 2^k, note that info for substrings of size 2^(k - 1)
        // is already calculated. So we have two parts left and right of sizes 2^(k - 1) each.
        // 2^(k-1)...  | i...i+2^(k-1)
        // suffix_left | suffix right
        // pn and cn are p and c for left side, note that p is already sorted (our right side is sorted).
        vi pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            rep(i, 0, n) {
                // p was sorted on prev iteration, so we just need to sort pn later on (left side)
                pn[i] = p[i] - (1 << h);
                // Do it in cyclic order.
                if(pn[i] < 0) pn[i] += n;
            }
            // Counting sort of the left side.
            fill(cnt.begin(), cnt.begin() + classes, 0);
            // 1.
            rep(i, 0, n) ++cnt[c[pn[i]]];
            // 2.
            rep(i, 1, n) cnt[i] += cnt[i - 1];
            // 3. curr = prev ~ p = pn. P corresponds to p of size 2^k now.
            rep(i, n, 0) p[--cnt[c[pn[i]]]] = pn[i];
            // After left side is sorted and now in p, we need to assign classes for it.
            cn[p[0]] = 0;
            classes = 1;
            rep(i, 1, n) {
                // Here we assign classes for the string of size 2^k
                pair prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
                pair cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                classes += cur != prev;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
    }

    void kasai_lcp() {
        int n = sz(s);
        // Populate map between suffix's start (p[i]) and idx in p.
        inv.resize(n), lcp_arr.resize(n - 1);
        rep(i, 0, n) inv[p[i]] = i;
        // k is the current lcp.
        int k = 0;
        // Iterate with start - starting pos of a suffix, from largest to smallest.
        rep(start, 0, n) {
            // Get idx of the current suffix in p.
            int pi = inv[start];
            // No suffix after, as current suffix is the last one.
            if(pi == n - 1) {
                k = 0;
                continue;
            }
            // Get idx of the next suffix in p.
            int si = p[pi + 1];
            // Greedily improve k.
            while(start + k < n && si + k < n && s[start + k] == s[si + k])
                ++k;
            // Save the result.
            lcp_arr[pi] = k;
            // Next suffix will start from start + 1, so decrease k by 1;
            k -= k == 0 ? 0 : 1;
        }
    }

    int slow_lcp(int i, int j) const {
        int start = inv[i], end = inv[j];
        if(start > end) swap(start, end);
        if(start == end)
            return sz(p) - 1 - p[start];
        int res = INT_MAX;
        rep(k, start, end)
            res = min(res, lcp_arr[k]);
        return res;
    }

    // Precondition: st is initialized with this->lcp_array.
    int fast_lcp(int i, int j, const sparse_tbl& st) const {
        if(i == j)
            return sz(s) - i;
        int start = inv[i], end = inv[j];
        if(start > end) swap(start, end);
        return st.minimum(start, end - 1);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;
    int n;
    cin >> n;
    vii strs(n);
    for(auto& [l, r] : strs) {
        cin >> l >> r;
        --l, --r;
    }

    s += ' ';
    SuffArr sa(s);
    sparse_tbl st(sa.lcp_arr);

    auto order = [&sa, &s, &st](const auto& lStr, const auto& rStr) -> bool {
        int l = sa.fast_lcp(lStr.first, rStr.first, st);
        int szL = lStr.second - lStr.first + 1, szR = rStr.second - rStr.first + 1;
        if(l >= min(szL, szR)) {
            if(szL < szR)
                return true;
            if(szL == szR)
                return lStr.first < rStr.first;
            return false;
        }
        return s[lStr.first + l] < s[rStr.first + l];
    };

    sort(begin(strs), end(strs), order);
    for(auto& [l, r] : strs)
        cout << l + 1 << " " << r + 1 << "\n";

    return 0;
}
