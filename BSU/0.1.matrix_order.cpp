#include <vector>
#include <iostream>
#include <utility>
#include <limits>
#include <fstream>

using dim = std::pair<uint64_t,uint64_t>;
const uint64_t SUP = std::numeric_limits<uint64_t>::max();

uint64_t matrix_chain_order(std::vector<dim> dims, size_t n) {
    std::vector<std::vector<uint64_t>> m(n + 1, std::vector<uint64_t>(n + 1));
    for(size_t i = 1; i <= n; ++i) 
        m[i][i] = 0;
    for(size_t l = 2; l <= n; ++l) {
        for(size_t i = 1; i <= n - l + 1; ++i) {
            size_t j = i + l - 1;
            m[i][j] = SUP;
            for(size_t k = i; k <= j - 1; ++k) {
                //indexes in array dims arranged from 0 to n - 1
                //idexes in array m arranged from 1 to n
                uint64_t q = m[i][k] + m[k + 1][j] + dims[i - 1].first * dims[k - 1].second * dims[j - 1].second;
                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    return m[1][n];
}

int main() {
    std::fstream in("input.txt", std::ios_base::in);
    std::fstream out("output.txt", std::ios_base::out);
    size_t n;
    in>>n;
    std::vector<dim> m(n);
    for(auto &el: m)
        in>>el.first>>el.second;
    out<<matrix_chain_order(m, n);
}