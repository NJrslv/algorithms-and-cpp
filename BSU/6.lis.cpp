#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

size_t LIS(std::vector<int64_t>& in) {
    std::vector<int64_t> dp(in.size() + 1, INT64_MAX);
    dp[0] = INT64_MIN;
    size_t length = 0;
    for(size_t i = 0; i < in.size(); ++i) {
        size_t insert_pos = std::upper_bound(dp.begin(), dp.end(), in[i]) - dp.begin();
        if(in[i] < dp[insert_pos] && dp[insert_pos - 1] < in[i]) {
            dp[insert_pos] = in[i];
            length = std::max(length, insert_pos);
        }
    }
    return length;
}

int main() {
    std::fstream in("input.txt", std::ios_base::in);
    std::fstream out("output.txt", std::ios_base::out);
    size_t n;
    in >> n;
    std::vector<int64_t> input(n);
    for(auto& el: input) in>>el;
    out << LIS(input);
}
