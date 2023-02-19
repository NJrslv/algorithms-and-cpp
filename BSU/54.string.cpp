#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

std::vector<std::vector<int>> dp(512, std::vector<int>(512, -1));

int cut(std::string& in, int i, int j) {
    if (i > j) {
        return 0;
    }
    if (dp[i][j] == -1) {
        dp[i][j] = 1 + cut(in, i + 1, j);
        for (int k = i + 1; k <= j; ++k) {
            if (in[k] == in[i]) {
                dp[i][j] = std::min(dp[i][j], cut(in, i, k - 1) + cut(in, k + 1, j));
            }
        }
    }
    return dp[i][j];
}

int main() { 
    std::fstream in("input.txt", std::ios_base::in);
    std::fstream out("output.txt", std::ios_base::out);
    std::string input;
    in >> input;
    out << cut(input, 0, input.size() - 1);
    return 0;
}

