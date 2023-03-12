#include <iostream>
#include <vector>

/* Analog

class MyHash {
public:
    MyHash(int _m, int _c) : m(_m), c(_c) {}

    std::size_t operator()(int x) const {
        return ((x % m) + c * i) % m;
    }

    void SetI(int _i) {
        i =  _i;
    }

private:
    int m;
    int c;
    int i;
};

MyHash hasher(m, c);
std::unordered_set<int, MyHash> s(m, hasher);

*/

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);

    int m, c, n;
    std::cin >> m >> c >> n;

    std::vector<int> table(m, -1);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        for(int j = 0; j < m; ++j) {
            if(table[((x % m) + c * j) % m] == x) {
                break;
            } else if(table[((x % m) + c * j) % m] == -1) {
                table[((x % m) + c * j) % m] = x;
                break;
            }
        }
    }

    for(auto &el: table)
        std::cout << el << " ";
    return 0;
}