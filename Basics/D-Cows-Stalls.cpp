/*
На прямой расположены стойла, в которые необходимо расставить коров так, чтобы минимальное расcтояние между коровами было как можно больше.

Формат ввода
В первой строке вводятся числа N (2 < N < 10001) – количество стойл и K (1 < K < N) – количество коров. Во второй строке задаются N натуральных чисел в порядке возрастания – координаты стойл (координаты не превосходят 109)

Формат вывода
Выведите одно число – наибольшее возможное допустимое расстояние.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template<typename T> using v = vector<T>;

int n, k;
v<int> xs;

bool check(int dist) {
    int cows = 1, last_cow = xs.front();
    for(auto x : xs) {
        if(x - last_cow >= dist) {
            ++cows;
            last_cow = x;
        }
    }
    return cows >= k;
}

int maxMinDistance() {
    int l = 0;
    for(int r = xs.back() - xs.front() + 1; r - l > 1;) {
        int dist = l + (r - l) / 2;
        if(check(dist)) l = dist;
        else r = dist;
    }
    return l;
}

int main() {
    cin >> n >> k;
    xs.resize(n);
    for(auto& x : xs) cin >> x;
    cout << maxMinDistance();
}

static const auto speedup = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
