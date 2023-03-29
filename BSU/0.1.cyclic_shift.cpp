#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solve(string f, string s, int n);
vector<int> pfn(string s, int n);

int main() {
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    string f, s;
    cin >> n >> f >> s;
    cout << solve(f, s, n);
    return 0;
}

int solve(string f, string s, int n) {
    vector<int> pfv = pfn(s + "!" + f + f, 3 * n + 1);
    for(size_t i = n + 1; i < 3 * n + 1; ++i)
        if(pfv[i] == n) return i % n;
    return -1;
}

vector<int> pfn(string s, int n) {
    vector<int> pfv(n, 0);
    int k = 0;
    for(size_t i = 1; i < n; ++i) {
        k = pfv[i - 1];
        while(k > 0 && s[k] != s[i]) k = pfv[k - 1];
        if(s[k] == s[i]) pfv[i] = k + 1;
        else pfv[i] = k;
    }
    return pfv;
}
