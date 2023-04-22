#include <bits/stdc++.h>
////////////////////////////////////////////
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define tr(container, it)\
 for (typeof (container.begin()) it = container.begin(); it != container.end(); it++)
typedef vector < int > vi;
typedef vector < vi > vvi;
typedef pair < int, int > ii;
typedef pair < int64_t, int64_t > ii64;
typedef vector < ii > vii;
#define sz(a) int((a).size())
#define pb push_back

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
using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;

template<class T>
using max_heap = priority_queue<T, std::vector<T>>;

template<class T, class Comparator>
using comp_heap = priority_queue<T, std::vector<T>, Comparator>;

struct two {
    int a, b;
};

struct comp { //min-heap
    bool operator () (two lhs, two rhs) {
        return lhs.b > rhs.b;
    }
};
////////////////////////////////////////////

int main() {
    return 0;
}
