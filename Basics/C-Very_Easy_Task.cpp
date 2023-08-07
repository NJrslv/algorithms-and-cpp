/*
This morning the jury decided to add one more, Very Easy Problem to the problemset of the olympiad. 
The executive secretary of the Organizing Committee has printed its statement in one copy, and now they need to make 𝑛
more copies before the start of the olympiad. They have two copiers at his disposal, one of which copies a sheet in 𝑥 seconds, 
and the other in 𝑦 seconds. 
(It is allowed to use one copier or both at the same time. You can copy not only from the original, but also from the copy.) 
Help them find out what is the minimum time they need to make 𝑛 copies of the statement.

Input
The program receives three integers 𝑛, 𝑥, and 𝑦 (1≤𝑛≤2⋅10^8, 1≤𝑥,𝑦≤10).

Output
Print one integer, the minimum time in seconds required to get 𝑛 copies.
*/
#include <iostream>
#include <vector>
#include <iomanip>

int n, x, y;

int calcMinTime() {
    auto isGood = [](int time){
        return time / x + time / y >= n - 1;
    };

    int l = 0, r = n * std::max(x, y);
    while(l < r) {
        int m = l + (r - l) / 2;
        if(isGood(m)) r = m;
        else l = m + 1;
    }

    return l + std::min(x, y);
}

int main() {
    std::cin >> n >> x >> y;
    std::cout << calcMinTime();
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();