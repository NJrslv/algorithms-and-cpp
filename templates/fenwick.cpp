#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

class Fenwick {
public:
    Fenwick (int _n) {
        n = _n;
        t.resize(n, 0);
    }

    int sum (int r) {
        int ans = 0;
        while (r >= 0) {
            ans += t[r];
            r = (r & (r + 1)) - 1;
        }
        return ans;
    }

    int sum (int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add (int k, int x) {
        while (k < n) {
            t[k] += x;
            k = k | (k + 1);
        }
    }
private:
    int n;
    vector<int> t;
};

int main() {
    std::ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    //maybe check stack constexpr
    int n, x;
    cin >> n;
    Fenwick ft(n);
    for(int i = 0; i < n; ++i) {
        cin >> x;
        ft.add(i, x);
    }

    cout << ft.sum(0, n - 1) << "\n";
    cout << ft.sum(0, 0) << "\n";
    cout << ft.sum(4, 6) << "\n";    
}