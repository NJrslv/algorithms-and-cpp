/*
There are 𝑛 rectangles of the same size: 𝑤 in width and ℎ in length. 
It is required to find a square of the smallest size into which these rectangles can be packed. 
Rectangles cannot be rotated.

Input
The input contains three integers 𝑤, ℎ, 𝑛 (1≤𝑤,ℎ,𝑛≤10^9).

Output
Output the minimum length of a side of a square, into which the given rectangles can be packed.
*/

#include <iostream>

int64_t w, h, n;

int64_t packRectangles() {
    int64_t l = 0, r = std::max(std::max(w, h), n * std::min(h, w));
    while(l < r) {
        int64_t m = l + (r - l) / 2;
        if((m / w) * (m / h) >= n) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main() {
    std::cin >> w >> h >> n;
    std::cout << packRectangles();
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
