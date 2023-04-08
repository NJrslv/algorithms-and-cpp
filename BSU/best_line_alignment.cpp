#include <iostream>
#include <string>
#include <complex>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;
using cd = complex<double>;

const double PI = acos(-1);
void fft(vector<cd> & a, bool invert);
vector<int> multiply(vector<int> const& a, vector<int> const& b);

void solve(string s1, string s2, size_t n) {
    s1 += s1;
    vector<int> a(n, 0);
    for(char c : {'A', 'B', 'C', 'D'}) {
        vector<int> p1(2 * n, 0), p2(2 * n, 0);
        for(size_t i = 0; i < 2 * n; ++i) p1[i] = s1[i] == c ? 1 : 0;
        for(size_t i = 0; i < n; ++i) p2[n - i - 1] = s2[i] == c ? 1 : 0;
        auto res = multiply(p1, p2);
        for(size_t i = n - 1; i < 2 * n - 1; ++i) a[i - n + 1] += res[i];
    }
    auto mit = max_element(a.begin(), a.end());
    cout << *mit << " " << distance(a.begin(), mit);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    solve(s1, s2, n);
    return 0;
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while ((size_t) n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = static_cast<int>(round(fa[i].real()));
    return result;
}

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}