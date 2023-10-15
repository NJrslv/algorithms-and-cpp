#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<class T> 
using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;

template<class T>
using max_heap = priority_queue<T, std::vector<T>>;

template<class T, class Comparator>
using comp_heap = priority_queue<T, std::vector<T>, Comparator>;

struct two {
    int a, b;
};

struct comp { //min-heap
    bool operator () (two lhs, two rhs) {
        return lhs.b > rhs.b;
    }
};


int main() {
    std::ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);

    comp_heap<two, comp> ch;
    ch.push({0, 4});
    ch.push({0, 3});
    ch.push({0, 1});
}

