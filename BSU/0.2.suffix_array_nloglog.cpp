#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct suff { 
    size_t pos;
    int c[2];
    bool operator < (suff const& o) const { 
        return (c[0] == o.c[0]) 
            ? (c[1] < o.c[1]) 
            : (c[0] < o.c[0]); 
    }
};
vector<suff> suffs;
void suff_arr_nlognlogn(string s, int n);

int main() {
    string s;
    cin >> s;
    suff_arr_nlognlogn(s, s.size());
    cout << suffs.size() << "\n";
    for(auto & el : suffs) cout << el.pos + 1 << " ";
}


void suff_arr_nlognlogn(string s, int n) {
    suffs.resize(n);
    for (size_t i = 0; i < n; ++i) {
        suffs[i].pos = i;
        suffs[i].c[0] = s[i] - 97;
        suffs[i].c[1] = (i + 1 < n) ? s[i + 1] - 97 : -1;
    }
    sort(suffs.begin(), suffs.end());
    vector<size_t> inds(n);
    for (size_t k = 4; k < 2 * n; k <<= 1) {
        int c = 0, cc = suffs[0].c[0], wc;
        suffs[0].c[0] = 0;
        inds[suffs[0].pos] = 0;
        for (int i = 1; i < n; i++) {
            wc = cc;
            cc = suffs[i].c[0];
            suffs[i].c[0] = suffs[i].c[0] == wc && suffs[i].c[1] == suffs[i-1].c[1] ? c : ++c;
            inds[suffs[i].pos] = i;
        }
        for (int i = 0; i < n; i++) {
            int next = suffs[i].pos + k / 2;
            suffs[i].c[1] = (next < n) ? suffs[inds[next]].c[0]: -1;
        }
        sort(suffs.begin(), suffs.end());
    }
}
