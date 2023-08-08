/*
Petya has the word 𝑡, he wants to make the word 𝑝 from it.
Petya begins to delete the letters in a certain order, which is described as a permutation of indices of the letters of the word 𝑡: 𝑎1…𝑎|𝑡|. 
Note that after deleting a letter, the numbering does not change.

His brother Vasya is afraid that Petya may delete too many letters, so he will not get the word 𝑝 in the end. 
Vasya's task is to stop his brother at some point and finish deleting himself in such a way, that the resulting word will be 𝑝. 
Since Petya likes this activity, Vasya wants to stop him as late as possible. 
Your task is to tell how many letters Petya can delete out before Vasya stops him.

It is guaranteed that the word 𝑝 can be obtained by deleting letters from 𝑡
.

Input
The first and second lines of the input file contain the words 𝑡 and 𝑝, respectively. 
Words consist of lowercase letters of the Latin alphabet (1≤|𝑝|<|𝑡|≤200000).

The next line contains the permutation 𝑎1…𝑎|𝑡| of letter indices, 
which specifies the order in which Petya deletes the letters of the word 𝑡 (1≤𝑎𝑖≤|𝑡|, all 𝑎𝑖 are different).
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string t, p;
vector<size_t> order;

size_t maxCntToDelete() {
     auto isPossibleDeleteTo = [](size_t end) {
        vector<bool> deleted(t.size(), false);
        for (auto i = 0; i < end; ++i)
            deleted[order[i] - 1] = true;

        for (size_t i = 0, pi = 0; i < t.size(); ++i) {
            if (!deleted[i] && t[i] == p[pi]) {
                ++pi;
                if (pi == p.size())
                    return true; 
            }
        }

        return false;
    };

    size_t l = 0, r = order.size();
    while(l + 1 < r) {
        size_t m = l + (r - l) / 2;
        if(isPossibleDeleteTo(m)) l = m;
        else r = m;
    }

    return l;
}

int main() {
    cin >> t >> p;
    order.resize(t.size());
    for(auto& index : order) cin >> index;
    cout << maxCntToDelete();
}

static const auto speedup = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();