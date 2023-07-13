/*
Дана последовательность чисел и запросы вида "определите сколько положительных чисел на отрезке с индексами от L до R".

Формат ввода
В первой строке вводится число n (1 ≤ n ≤ 100000) — длина последовательности.

Во второй строке вводится последовательность из n целых чисел, все числа по модулю не превосходят 100000. Нумерация в последовательности начинается с единицы.

В первой строке вводится число q (1 ≤ q ≤ 100000) — количество запросов.

В каждой из следующих q строк вводятся запросы — два индекса l и r (1 ≤ l ≤ r ≤ n)

Формат вывода
Для каждого запроса выведите количество положительных на отрезке.
*/

#include <iostream>
#include <vector>
#include <array>
#include <utility>
using namespace std;

template<typename T> using v = vector<T>;
template<typename T, typename U> using p = pair<T, U>;
#define l first
#define r second

v<int> in, out, pref_cnt;
v<p<size_t, size_t>> gaps;

void solve() {
    pref_cnt[0] = in[0] > 0 ? 1 : 0;
    for(auto i = 1; i < in.size(); ++i) 
        pref_cnt[i] = in[i] > 0 ? pref_cnt[i - 1] + 1 : pref_cnt[i - 1];

    auto out_it = out.begin();
    for(auto& [l, r] : gaps) {
        *out_it = pref_cnt[r - 1] - (l > 1 ? pref_cnt[l - 2] : 0);
        ++out_it;
    }
}

int main() {
    int n;
    cin >> n;
    in.resize(n);
    pref_cnt.resize(n);
    for (int i = 0; i < n; i++) cin >> in[i];
    
    int q;
    cin >> q;
    gaps.resize(q);
    out.resize(q);
    for (int i = 0; i < q; i++) cin >> gaps[i].l >> gaps[i].r;

    solve();

    for(int el : out) cout << el << "\n";
    return 0;
}

static const auto speedup = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
