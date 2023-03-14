#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_set>

std::array<int, 750001> size, parent;
int count = 0;

struct Road {
    int begin, end;
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

std::vector<int> find_missing_numbers(int n, std::vector<int> &arr) {
    std::unordered_set<int> unique_elements(arr.begin(), arr.end());
    std::vector<int> missing_numbers;
    for (int i = 1; i <= n; i++) {
        if (unique_elements.find(i) == unique_elements.end())
            missing_numbers.push_back(i);
    }
    return missing_numbers;
}

void fill_DSU_not_removed(std::vector<int> &not_removed_ind, std::vector<Road> &roads) {
    for(auto &ind: not_removed_ind)
        DSU_union(roads[ind]);
}

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m, q;
    std::cin >> n >> m >> q;

    for(size_t i = 1; i <= n; ++i)
        DSU_make(i);

    std::vector<Road> roads(m + 1);
    for(size_t i = 1; i <= m; ++i)
        std::cin >> roads[i];

    std::vector<int> removed(q);
    for(auto &el : removed)
        std::cin >> el;

    std::vector<int> not_removed = find_missing_numbers(m, removed);
    fill_DSU_not_removed(not_removed, roads);

    int zeroes = 0, ones = 0;
    for(auto it = removed.rbegin(); it != removed.rend(); ++it) {
        if(count > 1)
            ++zeroes;
        else 
            ++ones;
        DSU_union(roads[*it]);
    }
    while(ones > 0) {
        std::cout << "1";
        --ones;
    }
    while (zeroes > 0) {
        std::cout<<"0";
        --zeroes;
    }
    
}