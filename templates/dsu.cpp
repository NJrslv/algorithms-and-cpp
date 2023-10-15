#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

constexpr int N = 1e5;
int _size[N], _parent[N];

void DSU_make(int x) {
	_parent[x] = x;
	_size[x] = 1;
}

int DSU_find(int x) {
    return _parent[x] == x ? x : _parent[x] = DSU_find(_parent[x]);
}

void DSU_union(int a, int b) {
	a = DSU_find(a);
	b = DSU_find(b);
	if (a != b) {
		if(_size[a] < _size[b])
			std::swap(a, b);
		_parent[b] = a;
		_size[a] += _size[b];
	}
}

int main() {
    std::ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
     
}