#include <vector>
#include <iostream>

const unsigned int M = 1000000007;

int main() {
    size_t n,k;
    std::cin>>n>>k;
    std::vector<std::vector<int64_t>> dp(n + 1, std::vector<int64_t>(n + 1));
    
    for(size_t i = 0;i <= n; ++i) dp[i][i] = 1;
    for(size_t i = 1; i <= n; ++i) dp[i][0] = 1;

    for(size_t i = 1; i <= n; ++i) {
        for(size_t j = 1; j <= i - 1; ++j) {
            dp[i][j] = (dp[i - 1][j - 1] % M + dp[i - 1][j] % M) % M;
        }
    }
    std::cout<<dp[n][k];
}