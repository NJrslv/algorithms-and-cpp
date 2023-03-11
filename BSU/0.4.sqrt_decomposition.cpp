#include <vector>
#include <iostream>
#include <cmath>

using vec64 = std::vector<int64_t>;

vec64 fillBlocks(vec64& in, size_t n) {
    const size_t cnt = static_cast<size_t>(std::sqrt(n + .0) + 1);
    vec64 blocks(cnt);
    for(size_t i = 0; i < n; ++i)
        blocks[i / cnt] += in[i];
    return blocks;
}

void add(vec64& blocks, vec64& in, size_t ind, int element) {
    in[ind] += element;
    blocks[ind / blocks.size()] += element;
}

int64_t sum(vec64& blocks, vec64& in, size_t l, size_t r) {
    const size_t cnt = blocks.size();
    const size_t cntl = static_cast<size_t>((1.0 * l) / (double)cnt);
    const size_t cntr = static_cast<size_t>((1.0 * r) / (double)cnt);
    int64_t sum = 0;

    if (cntl == cntr) {
        //one block
        for (size_t i = l; i < r; ++i)
            sum += in[i];
    } else {
        //first block
        for (size_t i = l; i <= (cntl + 1) * cnt - 1; ++i)
            sum += in[i];
        //last block
        for (size_t i = cntr * cnt; i <= r - 1; ++i)
            sum += in[i];
        //middle blocks
        for (size_t i = cntl + 1; i <= cntr - 1; ++i)
            sum += blocks[i];
    }
    return sum;
}

int main() {
    size_t n, times;
    std::cin >> n;
    vec64 in(n);
    for(auto &el: in)
        std::cin >> el;
    std::cin >> times;
    vec64 blocks = fillBlocks(in, n);
    vec64 res;
    for(size_t i = 0; i < times; ++i) {
        std::string op;
        int f, s;
        std::cin >> op >> f >> s;
        if(!op.compare("FindSum"))
            res.push_back(sum(blocks, in, f, s));
        else
            add(blocks, in, f, s);
    }
    for(auto &el: res)
        std::cout << el << "\n";
}