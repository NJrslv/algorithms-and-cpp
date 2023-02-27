#include <iomanip>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#define cdist first
#define ctime second
using coin = std::pair<int64_t, int64_t>;

inline int64_t dist(const coin& cstart, const coin& cend, int64_t prev_time) {
    if(cend.ctime - prev_time - std::abs(cend.cdist - cstart.cdist) >= 0)
        return std::abs(cend.cdist - cstart.cdist);
    else 
        return INT64_MAX;
}

inline int64_t add(int64_t a, int64_t b) {
    if(a == INT64_MAX || b == INT64_MAX)
        return INT64_MAX;
    else 
        return a + b;
}

int64_t F(std::vector<coin>& in,
          std::vector<std::vector<int64_t>>& dp,
          size_t i,
          size_t j) {
    if (i == j) {
        dp[i][j] = 0;
    } else if(dp[i][j] == -1) {
        if(j > i){
            int64_t i_to_j_min_1 = F(in, dp, i, j - 1);
            int64_t j_min_1_to_i = F(in, dp, j - 1, i);
            dp[i][j] = std::min(add(i_to_j_min_1, dist(in[j - 1], in[j], i_to_j_min_1)) , 
                                add(j_min_1_to_i, dist(in[i], in[j], j_min_1_to_i)));
            int64_t i_plus_1_to_j = F(in, dp, i + 1, j);
            int64_t j_to_i_plus_1 = F(in, dp, j, i + 1);
            dp[j][i] = std::min(add(i_plus_1_to_j, dist(in[j], in[i], i_plus_1_to_j)),
                                add(j_to_i_plus_1, dist(in[i + 1], in[i], j_to_i_plus_1)));
        }
    }
    return dp[i][j];
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t n;
    fin>>n;
    std::vector<coin> in(n);
    for(int64_t a, b, i = 0;fin>>a>>b;++i)
        in[i] = std::make_pair(a, b);
    //for(auto &el : in)
       // fin>>el.cdist>>el.ctime;
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(n, -1));
    F(in, dp, 0, n - 1);
    int64_t res = std::min(dp[0][n - 1], dp[n - 1][0]);
    res == INT64_MAX ? fout<<"No solution" : fout<<res;
}