#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


int f(std::vector<std::vector<int>>& dp,
         const std::string& in, size_t i, size_t j) {
    if(i == j) {
        dp[i][j] = 1;
    } else if(i > j){
        dp[i][j] = 0;
    } else if(dp[i][j] == -1) {
        if(in[i] == in[j]) {
            dp[i][j] = f(dp, in, i + 1, j - 1) + 2;
        } else {
            dp[i][j] = std::max(f(dp, in, i + 1, j), f(dp, in, i, j - 1));
        }
    }
    return dp[i][j];
}

std::string recalc_palindrome(std::vector<std::vector<int>>& dp,
                               const std::string& in, int i, int j) {
    if (i > j) {
        return "";
    } else if (i == j) {
        return std::string(1, in[i]);
    } else if (in[i] == in[j]) {
        return in[i] + recalc_palindrome(dp, in, i + 1, j - 1) + in[j];
    } else if (dp[i + 1][j] > dp[i][j - 1]) {
        return recalc_palindrome(dp, in, i + 1, j);
    }
    return recalc_palindrome(dp, in, i, j - 1);
}


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    std::string in;
    fin>>in;
    std::vector<std::vector<int>> dp(in.size(), std::vector<int>(in.size(), -1));
    fout<<f(dp, in, 0, in.size() - 1)<<"\n";
    fout<<recalc_palindrome(dp, in, 0, in.size() - 1);
}
