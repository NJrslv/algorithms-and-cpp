#include <vector>
#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>

/*
В магазине структур данных вы увидели массив $a_i$ из $n$ целых чисел.
Вы хотите приобрести этот массив, однако сразу весь массив купить нельзя ввиду бюрократических сложностей.
Это, впрочем, можно сделать следующим образом:изначально вы можете бесплатно получить в собственность ровно
один любой элемент массива на ваш выбор;
после этого в любой момент времени вы можете приобрести какой-нибудь ещё не принадлежащий вам элемент массива,
соседний с каким-нибудь принадлежащим вам элементом массива.
Чтобы купить все элементы массива, вам, конечно, следует совершить это действие ровно $n - 1$ раз.
Есть только одна проблема: за покупку всех элементов, кроме первого выбранного вами, нужно платить. 
Если уже принадлежащие вам элементы равны $x_1, x_2, \ldots, x_k$ (в некотором порядке) и вы хотите купить элемент,
равный $y$, то вам придётся заплатить $(21S - 17y - 1) \mod (10^9 + 7)$ монет, где $S = x_1 + x_2 + \ldots + x_k$.
Обратите внимание, что остаток от деления на положительное число всегда является неотрицательным числом.
В каком порядке следует приобретать элементы, чтобы минимизировать суммарное количество потраченных монет?

Input:
Первая строка содержит одно целое число $n$ — длину покупаемого массива ($1 \leqslant n \leqslant 3000$).
Вторая строка содержит $n$ целых чисел $a_1, a_2, \ldots, a_n$ — элементы массива ($0 \leqslant a_i < 10^9 + 7$).

Output:
В первой строке выведите одно число — минимальное количество монет, необходимых для покупки всего массива.
Обратите внимание, что это число может не поместиться в 32-битный целочисленный тип данных.
Во второй строке выведите $n$ чисел $p_1, p_2, \ldots, p_n$ ($1 \leqslant p_i \leqslant n$, $p_i \ne p_j$ для $i \ne j$), 
означающих, что $i$-м по счёту следует приобретать элемент $a_{p_i}$.
Если существует несколько способов минимизировать количество монет, выведите любой из них.
*/

std::array<int64_t, 3000> in, psum;
std::vector<size_t> res;
using vec2D = std::vector<std::vector<int64_t>>;
const int64_t MOD = 1000000007;

template<class T>
inline const T& min(const T& a, const T& b) {
    return (b < a) ? b : a;
}

void fill_psum(size_t size) {
    psum[0] = in[0];
    for(size_t i = 1; i < size; ++i)
        psum[i] = psum[i - 1] + in[i];
}

inline int64_t penalize(size_t i, size_t j, int64_t y) {
    int64_t S = psum[j] - psum[i - 1];
    return ((21 * S - 17 * y - 1) % MOD + MOD) % MOD;
}

int64_t F(vec2D& dp, size_t i, size_t j) {
    if(i == j) {
        dp[i][j] = 0;
    } else if(dp[i][j] == -1) {
        dp[i][j] = min(F(dp, i + 1, j) + penalize(i + 1, j, in[i]), F(dp, i, j - 1) + penalize(i, j - 1, in[j]));
    }
    return dp[i][j];
}

void restore(const vec2D& dp, size_t n) {
    size_t i = 0, j = n - 1;
    while(i < j) {
        int64_t cost1 = dp[i + 1][j] + penalize(i + 1, j, in[i]);
        int64_t cost2 = dp[i][j - 1] + penalize(i, j - 1, in[j]);
        if(cost1 <= cost2) { 
            res.push_back(i + 1);
            ++i;
        } else {
            res.push_back(j + 1); 
            --j;
        }
    }
    res.push_back(++i);
    for(auto it = res.rbegin(); it != res.rend(); ++it)
        std::cout << *it << " ";
}


void solve(vec2D& dp, size_t n) {
    fill_psum(n);
    std::cout << F(dp, 0, n - 1) << "\n";
    restore(dp, n);
}



int main() {
    size_t n;
    std::cin >> n;
    for(size_t i = 0; i < n; ++i)
        std::cin >> in[i];
    if(n == 1) {
        std::cout<<"0\n1";
    } else {
        vec2D dp(n, std::vector<int64_t>(n, -1));
        solve(dp, n);
    }
    return 0;
}