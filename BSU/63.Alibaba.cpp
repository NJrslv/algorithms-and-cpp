#include <vector>
#include <iostream>
#include <numeric>

#define ABS(N) ((N<0)?(-N):(N))

const int64_t MAX64 = std::numeric_limits<int64_t>::max();

struct coin {
    int64_t dist;
    int64_t time;
};

//dp[i][j] - наименьшее время прохождения первый i монет,
//при условии, что последней монетой была j-ая.

int64_t F(std::vector<coin>& in,
          std::vector<std::vector<int64_t>>& dp,
          size_t n,
          size_t count,
          size_t last) {
    if(count == 0) {
        return 0;
    } else if(dp[count][last] == -1) {
        int64_t time_first = in[count].time - in[0].time;
        int64_t time_prev_last = in[count].time - in[count - 1].time; 
        int64_t common_first_dist, common_prev_last_dist;
        int64_t dist_first = in[count].dist - in[0].dist;
        int64_t dist_last = in[count].dist - in[count - 1].dist;

        time_first >= dist_first? common_first_dist = dist_first : common_first_dist = MAX64;
        time_prev_last >= dist_last? common_prev_last_dist = dist_last : common_prev_last_dist = MAX64;

        dp[count][last] = std::min(F(in, dp, n, count - 1, 0) + common_first_dist,//может быть переполнение
                                   F(in, dp, n, count - 1, count - 1) + common_prev_last_dist);
    } else if(dp[count][last] == MAX64) {
        return MAX64;
    } else {
        return dp[count][last];
    }
}

int64_t alibaba(std::vector<coin>& in,
          std::vector<std::vector<int64_t>>& dp,
          size_t n,
          size_t count) {
    return std::min(F(in, dp, n, n - 1, n - 1),
                    F(in, dp, n, n - 1, 0));
}

int main() {
    size_t n;
    std::cin>>n;
    std::vector<coin> in(n);
    for(auto &el : in)
        std::cin>>el.dist>>el.time;
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(n, -1));
    dp[0][0] = 0;
    int64_t res = alibaba(in, dp, n, n - 1);
    std::cout<<res;
}
