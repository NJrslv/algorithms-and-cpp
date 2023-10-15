#include <iostream>
#include <algorithm>

using namespace std;

constexpr int N = 1e6, logn = 20;
int in[N], lg[N], mx[N][logn];

inline int get(int l, int r) {
    int t = lg[r-l+1];
    return max(mx[l][t], mx[r - (1 << t) + 1][t]);
}

void sparse(int n) {
    for (int l = 1; l < logn; l++) {
        for (int i = (1 << l); i < N; i++) {
            lg[i] = l;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        mx[i][0] = in[i];
        for (int l = 0; l < logn - 1; l++) {
            mx[i][l + 1] = max(mx[i][l], mx[i + (1 << l)][l]);
        }
    } 
}

int main() {
    std::ios_base::sync_with_stdio(0);
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    //1. sparse(n)
    //2. get(l, r) where [l, r]
    return 0;
}
