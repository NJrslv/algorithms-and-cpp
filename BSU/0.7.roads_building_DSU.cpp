#include <iostream>
#include <fstream>
#include <vector>
#include <array>

std::array<int, 750001> size, parent;
int count = 0;

struct Road {
    int begin, end;
    bool isDel = false;
    friend std::istream& operator >> (std::istream& in, Road& edge) {
        in >> edge.begin >> edge.end;
        return in;
    }
};

void DSU_make(int x) {
	parent[x] = x;
	size[x] = 1;
    ++count;
}

int DSU_find(int x) {
    return parent[x] == x ? x : parent[x] = DSU_find(parent[x]);
}

void DSU_union(Road r) {
	int a = DSU_find(r.begin);
	int b = DSU_find(r.end);
	if (a != b) {
		if(size[a] < size[b])
			std::swap(a, b);
		parent[b] = a;
		size[a] += size[b];
        --count;
	}
}

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, q;
    std::cin >> n >> q;

    for(size_t i = 1; i <= n; ++i)
        DSU_make(i);

    std::vector<Road> roads(q + 1);
    std::vector<int> res(q);
    for(size_t i = 1; i <= q; ++i) {
        std::cin >> roads[i];
        DSU_union(roads[i]);
        res[i - 1] = count;
    }

    for(auto &el: res)
        std::cout << el << "\n";
}