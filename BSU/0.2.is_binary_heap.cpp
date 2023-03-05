#include <fstream>
#include <vector>

bool isHeap(std::vector<int>& in, size_t n) {
    if(n == 1) return true;
    for (size_t i = 0; i <= (n - 2) / 2; ++i) {
        if (in[2*i + 1] < in[i]) return false;
        if (2*i+2 < n && in[2 * i + 2] < in[i]) return false;
    }
    return true;
}

int main() {
    std::fstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t n;
    fin >> n;
    std::vector<int> in(n);
    for(auto& el : in)
        fin >> el;
    isHeap(in, n) ? fout << "Yes" : fout << "No"; 
}