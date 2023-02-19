#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

auto LCS_fill(std::vector<uint16_t>& a, std::vector<uint16_t>& b, size_t n) {
    std::vector<std::vector<ssize_t>> dp(n + 1, std::vector<ssize_t>(n + 1, -1));
    for(size_t i = 1; i <= n; ++i) {
        for(size_t j = 1; j <= n; ++j) {
            if(a[i] == b[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    return dp;
}

auto LCS(std::vector<uint16_t>& a, std::vector<uint16_t>& b, size_t n) {
    auto dp = LCS_fill(a, b, n);
    std::vector<std::pair<size_t, size_t>> lcs;
    size_t i = n, j = n;
    while(i && j) { 
        if(a[i] == b[j]) {
            lcs.push_back({i - 1, j - 1});
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    size_t n;
    std::cin>>n;
    std::vector<uint16_t> first(n + 1), second(n + 1);
    for(size_t i = 1; i <= n; ++i) std::cin>>first[i];
    for(size_t i = 1; i <= n; ++i) std::cin>>second[i];
    

    auto lcs = LCS(first, second, n);
    std::cout<<lcs.size()<<"\n";
    for(auto it = lcs.rbegin(); it != lcs.rend(); ++it) std::cout<< (*it).first<< " ";
    std::cout<<"\n";
    for(auto it = lcs.rbegin(); it != lcs.rend(); ++it) std::cout<< (*it).second<< " ";
    return 0; 
}