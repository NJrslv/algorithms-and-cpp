#include <iostream>
#include <vector>

//(a % b + b) % b

int64_t task(const std::vector<int64_t>& in, size_t n) {
    std::vector<std::vector<int64_t>> accumulator(3, std::vector<int64_t>(n, INT64_MIN));
    //
    accumulator[(in[0] % 3 + 3) % 3][0] = in[0];
    //
    for (size_t i = 0; i < n; ++i) {
        if (i + 2 < n) {
            for (int j = 0; j < 3; ++j) {
                if (accumulator[j][i] != INT64_MIN)
                    accumulator[((in[i + 2] + accumulator[j][i]) % 3 + 3) % 3][i + 2] = std::max(in[i + 2] + accumulator[j][i],
                                                            accumulator[((in[i + 2] + accumulator[j][i]) % 3 + 3) % 3][i + 2]);
            }
        }
        if (i + 5 < n) {
            for (int j = 0; j < 3; ++j) {
                if (accumulator[j][i] != INT64_MIN)
                    accumulator[((in[i + 5] + accumulator[j][i]) % 3 + 3) % 3][i + 5] = std::max(in[i + 5] + accumulator[j][i],
                                                             accumulator[((in[i + 5] + accumulator[j][i]) % 3 + 3) % 3][i + 5]);
            }
        }
    }
    //
    int64_t res;
    (accumulator[0][n - 1] == INT64_MIN) ? res = -2023 : res = accumulator[0][n - 1];
    return res;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int64_t> in(n);
    for (int i = 0; i < n; ++i)
        std::cin >> in[i];
    std::cout << task(in, n);
    return 0;
}
