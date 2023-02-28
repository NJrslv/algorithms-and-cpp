#include <fstream>
#include <tuple>
#include <vector>
#include <iostream>

#define key std::get<0>
#define parent std::get<1>
#define side std::get<2>
#define lBound std::get<3>
#define rBound std::get<4>

using node = std::tuple<int64_t, size_t, char, int64_t, int64_t>;

bool is_bst(std::vector<node>& bst) {
    //starting from the second node
    for(size_t i = 2; i < bst.size(); ++i) {
        if(side(bst[i]) == 'L') {
            rBound(bst[i]) = key(bst[parent(bst[i])]);
            lBound(bst[i]) = lBound(bst[parent(bst[i])]);
        } else {
            lBound(bst[i]) = key(bst[parent(bst[i])]);
            rBound(bst[i]) = rBound(bst[parent(bst[i])]);
        }
        if(!(key(bst[i]) >= lBound(bst[i]) && key(bst[i]) < rBound(bst[i])))
            return false;
    }
    return true;
}

int main() {
    std::fstream fin("bst.in");
    std::ofstream fout("bst.out");

    size_t n;
    fin>>n;
    std::vector<node> bst(n + 1);
    //root
    int64_t root_key;
    fin>>root_key;
    bst[1] = {root_key, 0, '-', INT64_MIN, INT64_MAX};
    //others
    for(size_t i = 2; i <= n; ++i) {
        int64_t bstkey;
        size_t par;
        char s;
        fin >> bstkey >> par >> s;
        bst[i] = {bstkey, par, s, INT64_MIN, INT64_MAX};
    }
    is_bst(bst) ? fout<<"YES" : fout<<"NO";
    return 0;
}