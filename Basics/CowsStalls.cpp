/*
На завод по изготовлению гирлянд пришел срочный заказ: изготовить как можно больше одинаковых гирлянд, состоящих из n лампочек. 
На складе завода есть лампочки k различных цветов, цвета занумерованы от 1 до k. 
Определите, сколько гирлянд сможет изготовить завод и из каких лампочек должна состоять каждая гирлянда.

Формат ввода
В первой строке задаются два числа n (1 ≤ n ≤ 40000) и k (1 ≤ k ≤ 50000).

В следующих k строках задается количество лампочек каждого из k цветов. 
Суммарное количество лампочек на складе не превосходит 2 × 109.

Формат вывода
В первой строке выведите максимальное количество гирлянд. 
В следующих n строках выведите описание гирлянды: в каждой строке выведите номер цвета лампочки, 
находящейся в гирлянде на очередном месте. Если возможных ответов несколько — выведите любой из них.
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