#pragma comment(linker, "/STACK:10000000000")
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <numeric>
#include <array>

#define N 200000 

using namespace std;

template<typename T>
class SegmentTree {
public:
    SegmentTree(const vector<T>& a) : n(a.size()) {
        sum_tree.resize(4 * a.size());
        min_tree.resize(4 * a.size());
        max_tree.resize(4 * a.size());
        added.resize(4 * a.size(), 0);
        build(a, 1, 0, a.size() - 1);
    }

    void update(int index, T value) {
        update(1, 0, n - 1, index, index, value);
    }

    void add_range(int a, int b, T value) {
        add_range(1, 0, n - 1, a, b, value);
    }

    T sum_range(int l, int r) {
        return query_sum(1, 0, n - 1, l, r, 0);
    }

    T min_range(int l, int r) {
        return query_min(1, 0, n - 1, l, r);
    }

    T max_range(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }

    //void PrintVectors() {
        //cout << "\n";
        //for(auto& el : min_tree)
            //std::cout << el <<"  ";
        //cout << "\n";
    //}

private:
    int n;
    vector<T> sum_tree;
    vector<T> min_tree;
    vector<T> max_tree;
    vector<T> added;
    
    void build(const vector<T>& a, int node, int l, int r) {
        if (l == r) {
            sum_tree[node] = a[l];
            min_tree[node] = a[l];
            max_tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * node, l, mid);
        build(a, 2 * node + 1, mid + 1, r);
        sum_tree[node] = sum_tree[2 * node] + sum_tree[2 * node + 1];
        min_tree[node] = min(min_tree[2 * node], min_tree[2 * node + 1]);
        max_tree[node] = max(max_tree[2 * node], max_tree[2 * node + 1]);
    }

    //Getter for update operation
    T crutch(int node, int nl, int nr, int i, T tmp) {
        if(nl == i && i == nr) {
            return tmp + added[node] + sum_tree[node];
        }
        int mid = (nl + nr) / 2;
        if (i <= mid) {
            return crutch(2 * node, nl, mid, i, tmp + added[node]);
        } else {
            return crutch(2 * node + 1, mid + 1, nr, i, tmp + added[node]);
        } 
    }
    
    void update(int node, int nl, int nr, int l, int r, T val) {
        T el = crutch(1, nl, nr, r, 0);  // 1.getting el
        el = (-1) * el;                  // 2.setting -el
        add_range(1, nl, nr, l, r, el);  // 3.el - el = 0
        add_range(1, nl, nr, l, r, val); // 4.0 + val = val
    }

    void add_range(int node, int nl, int nr, int l, int r, T val) {
        if (l > r) {
            return;
        }
        if (nl == l && nr == r) {
            added[node] += val;
            min_tree[node] += val;
            max_tree[node] += val;
            return;
        }
        int mid = (nl + nr) / 2;
        add_range(2 * node, nl, mid, l, min(r, mid), val);
        add_range(2 * node + 1, mid + 1, nr, max(l, mid + 1), r, val);
        min_tree[node] = min(min_tree[2 * node], min_tree[2 * node + 1]) + added[node];
        max_tree[node] = max(max_tree[2 * node], max_tree[2 * node + 1]) + added[node];
        sum_tree[node] += (r - l + 1) * val;
    }

    T query_sum(int node, int nl, int nr, int l, int r, int tmp) {
        if(l > r) {
            return 0;
        }
        if (l == nl && r == nr) {
            return (added[node] + tmp) * (r - l + 1) + sum_tree[node];
        }
        int mid = (nl + nr) / 2;
        return (
            query_sum(2 * node, nl, mid, l, min(r, mid), added[node] + tmp) +
            query_sum(2 * node + 1, mid + 1, nr, max(mid + 1, l), r, added[node] + tmp)
        );
    }

    T query_min(int node, int nl, int nr, int l, int r) {
        if (l > r) {
            return numeric_limits<T>::max();
        }
        if (l == nl && r == nr) {
            return min_tree[node];
        }
        int mid = (nl + nr) / 2;
        T min_left = query_min(2 * node, nl, mid, l, min(r, mid));
        T min_right = query_min(2 * node + 1, mid + 1, nr, max(mid + 1, l), r);
        return min(min_left, min_right) + added[node];
    }

    T query_max(int node, int nl, int nr, int l, int r) {
        if (l > r) {
            return numeric_limits<T>::min();
        }
        if (l == nl && r == nr) {
            return max_tree[node];
        }
        int mid = nl + (nr - nl) / 2;
        T max_left = query_max(2 * node, nl, mid, l, min(r, mid));
        T max_right = query_max(2 * node + 1, mid + 1, nr, max(mid + 1, l), r);
        return max(max_left, max_right) + added[node];
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);

    
    int n;
    cin >> n;
    vector<int> in(n, 0);
    SegmentTree<int> segTree(in);

    while(true) {
        int t;
        cin >> t;
        if(t == 0) {
            break;
        } else if(t == 1) {
            int i, val;
            cin >> i >> val;
            segTree.update(i, val);
        } else if(t == 2) {
            int a, b, val;
            cin >> a >> b >> val;
            segTree.add_range(a, b, val);
        } else if(t == 3) {
            int a, b;
            cin >> a >> b;
            cout << segTree.sum_range(a, b) << "\n";
        } else if(t == 4) {
            int a, b;
            cin >> a >> b;
            cout << segTree.min_range(a, b) << "\n";
        } else if(t == 5) {
            int a, b;
            cin >> a >> b;
            cout << segTree.max_range(a, b) << "\n";
        }
    }
    return 0;
}

    
        
               
