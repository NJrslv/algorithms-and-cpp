#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#define dist first
#define time second
#define index(i, j, n) ((i) * (n) + (j))
#define add(a, b) ((a == INT_MAX || b == INT_MAX) ? INT_MAX : a + b)


using coin = std::pair<int, int>;

coin in[10000];


inline int dist(const coin& cstart, const coin& cend, int prev_time) {
    int d = std::abs(cend.dist - cstart.dist);
    return prev_time == INT_MAX ? INT_MAX
                           : cend.time - prev_time - d >= 0 ? d
                                                            : INT_MAX;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t n;
    fin >> n;
    for(size_t i = 0; i < n; ++i)
        fin >> in[i].dist >> in[i].time;
    std::vector<int> dp(n * n, 0);
    for (size_t i = n - 2; i != (size_t)-1; --i) {
        for (size_t j = i + 1; j < n; ++j) {
            dp[index(i, j, n)] = std::min(add(dp[index(i, j - 1, n)], dist(in[j - 1], in[j], dp[index(i, j - 1, n)])),
                                      add(dp[index(j - 1, i, n)], dist(in[i], in[j], dp[index(j - 1, i, n)])));
            dp[index(j, i, n)] = std::min(add(dp[index(i + 1, j, n)], dist(in[j], in[i], dp[index(i + 1, j, n)])),
                                      add(dp[index(j, i + 1, n)], dist(in[i + 1], in[i], dp[index(j, i + 1, n)])));
        }
    }
    int res = std::min(dp[index(0, n - 1, n)], dp[index(n - 1, 0, n)]);
    res == INT_MAX ? fout << "No solution" : fout << res;
}