/*
Площадка для выгула собак — место, где собираются и общаются люди разных возрастов. На одной из площадок Восточного Бирюлева хозяева собак очень дружны и приглашают друг-друга на день рождения.

Человек x не приглашает на день рождения человека y если выполнено хотя бы одно из условий:

- (Возраст человека y) <= 0.5 * (Возраст человека x) + 7

- (Возраст человека y) > (Возраст человека x)

- (Возраст человека y) > 100 и одновременно с этим (Возраст человека x) < 100

Во всех остальных случаях человек x приглашает человека y на день рождения.

Определите суммарное количество приглашений на день рождения.

Формат ввода
В первой строке вводится число n (1 ≤ n ≤ 100000).

Во второй строке вводится n чисел — возраст людей. Возраст находится в промежутке от 1 до 120.

Формат вывода
Выведите одно число — суммарное количество приглашений.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T> using v = vector<T>;

int n;
v<int> ages;

int64_t countInvitations() {
    sort(begin(ages), end(ages));
    int64_t cnt = 0ll;
    int l = 0, r = 0;
    for(auto age : ages) {
        while(l < n && 0.5 * double(age) + 7. >= double(ages[l])) ++l;
        while(r < n && ages[r] <= age) ++r;
        if(r > l) cnt += r - l - 1;
    }
    return cnt;
}

int main() {
    cin >> n;
    ages.resize(n);
    for(auto& age : ages) cin >> age;
    cout << countInvitations();
    return 0;
}

static const auto speedup = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();