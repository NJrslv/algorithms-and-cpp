/*
Find a number 𝑥 such that 𝑥^2+sqrt(x,2)=c

Input
The input contains one real number 𝐶 (1.0≤𝑐≤10^10).

Output
Print one number, the required 𝑥. 
The answer will be considered correct if the relative or absolute error is not more than 10^−6.
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

double c;

int main() {
    std::cin >> c;

    double l = 0, r = c;
    const size_t iterations = 100;
    for(auto iters = 0; iters < iterations; ++iters) {
        double x = l + (r - l) / 2;
        if(x * x + sqrt(x) < c) l = x;
        else r = x;
    }

    std::cout << std::setprecision(20) << l;
    return 0;
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();