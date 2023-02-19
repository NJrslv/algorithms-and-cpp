#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

const int64_t INF = numeric_limits<int64_t>::min();

vector<int64_t> max_food(vector<int64_t> &in, size_t n) {
    vector<int64_t> out(n, INF);
    out[0] = in[0];
    if(n == 2)
        return {INF};
    for(size_t i = 0; i < n; ++i) {
        if(i + 2 < n)
            out[i + 2] = max(out[i + 2], out[i] + in[i + 2]);
        if(i + 3 < n)
            out[i + 3] = max(out[i + 3], out[i] + in[i + 3]); 
    }
    return out;
}

vector<size_t> restore_way(const vector<int64_t>& out, const vector<int64_t>& in) {
    vector<size_t> path;
    size_t i = out.size() - 1;
    while (i > 0) {
        path.push_back(i);
        if (i >= 3 && out[i - 3] == out[i] - in[i]) {
            i -= 3;
        } else if (i >= 2 && out[i - 2] == out[i] - in[i]) {
            i -= 2;
        }
    }
    path.push_back(0);
    return path;
}

int main() {
    size_t n;
    cin>>n; 
    vector<int64_t> in(n);
    for(auto &el: in)
        std::cin>>el;
    std::vector<int64_t> prices = max_food(in, n);
    if(prices.back() == INF) {
        std::cout<<"-1";
    } else {
        std::vector<size_t> way = restore_way(prices, in);
        std::cout<<prices.back()<<'\n';
        for(auto it = way.rbegin(); it != way.rend(); ++it) 
            std::cout<< *it + 1 << " ";
    }
    return 0;
}