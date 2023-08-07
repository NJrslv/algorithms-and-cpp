/*
There are 𝑛 ropes, you need to cut 𝑘 pieces of the same length from them. Find the maximum length of pieces you can get.

Input
The first line contains two integers 𝑛 and 𝑘 (1≤𝑛,𝑘≤10000). Next 𝑛 lines contain one number each, 
the length of the rope 𝑎𝑖 (1≤𝑎𝑖≤10^7).

Output
Output one real number, maximum length of pieces you can get. The answer will be considered correct if the relative or absolute error does not exceed 10−6.
*/

#include <iostream>
#include <vector>
#include <iomanip>

std::vector<int> ropes;
int n, k;

double devideRopes() {
    auto isDivisible = [](double x){
        int parts = 0;
        for(auto& ropeLen : ropes)
            parts += ropeLen / x;
        return parts >= k; 
    };

    size_t iterations = 50;
    double l = 0.0, r = 1e7 + 1;
    for(int it = 0; it < iterations; ++it) {
        double m = l + (r - l) / 2;
        if(isDivisible(m)) l = m;
        else r = m;
    }

    return l;
}

int main() {
    std::cin >> n >> k;
    ropes.resize(n);
    for(auto& ropeLen : ropes) std::cin >> ropeLen;
    std::cout << std::setprecision(20) << devideRopes();
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();