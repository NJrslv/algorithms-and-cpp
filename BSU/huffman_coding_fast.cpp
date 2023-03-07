#include <iostream>
#include <vector>
#include <fstream>

int64_t GetBitLengthEncoded(std::vector<int32_t>& f, size_t n) {
    std::vector<int64_t> s(n, INT32_MAX);
    size_t del_pos_f = 0, del_pos_s = 0, ins_pos_s = 0;
    int64_t res = 0;
    while(ins_pos_s < n - 1) {
        int64_t f_sum, s_sum, b_sum;
        del_pos_f + 1 < n ? f_sum = f[del_pos_f] + f[del_pos_f + 1] : f_sum = INT64_MAX;
        del_pos_s + 1 < n ? s_sum = s[del_pos_s] + s[del_pos_s + 1] : s_sum = INT64_MAX;
        del_pos_f < n && del_pos_s < n ? b_sum = f[del_pos_f] + s[del_pos_s] : b_sum = INT64_MAX;
        if(f_sum <= s_sum && f_sum <= b_sum) {
            s[ins_pos_s] = f_sum;
            res += f_sum;
            del_pos_f += 2;
        } else if(s_sum <= f_sum && s_sum <= b_sum) {
            s[ins_pos_s] = s_sum;
            res += s_sum;
            del_pos_s += 2;
        } else if(b_sum <= f_sum && b_sum <= s_sum) {
            s[ins_pos_s] = b_sum;
            res += b_sum;
            ++del_pos_f;
            ++del_pos_s;
        }
        ++ins_pos_s;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    size_t n;
    std::cin >> n;
    std::vector<int32_t> in(n);
    for(auto& el : in)
        std::cin >> el;
    std::cout<<GetBitLengthEncoded(in, n);
}
