#include <iostream>
#include <vector>

bool binary_search(std::vector<int64_t>& in, int64_t target);
int64_t lower_bound(std::vector<int64_t>& in, int64_t target);
int64_t upper_bound(std::vector<int64_t>& in, int64_t target);

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    size_t n;
    std::cin >> n;
    std::vector<int64_t> in(n);

    for(auto &el: in) 
        std::cin>>el;

    size_t count;
    std::cin>>count;

    std::vector<int64_t> nums(count);

    for(auto &el: nums) 
        std::cin>>el;

    for(auto &el:nums) {
        std::cout<<binary_search(in, el)<<" "
                 <<lower_bound(in, el)<<" "
                 <<upper_bound(in, el)<<"\n";
    }
}


bool binary_search(std::vector<int64_t>& in, int64_t target) {
    size_t l = 0, r = in.size();
    while(l < r) {
        size_t mid = (l + r) >> 1;
        if(target == in[mid]) {
            return true;
        } else if (target < in[mid]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return false; 
}

int64_t lower_bound(std::vector<int64_t>& in, int64_t target) {
    size_t l = 0, r = in.size();
    while(l < r) {
        size_t mid = (l + r) >> 1;
        if(target <= in[mid]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int64_t upper_bound(std::vector<int64_t>& in, int64_t target) {
    size_t l = 0, r = in.size();
    while(l < r) {
        size_t mid = (l + r) >> 1;
        if(target < in[mid]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}
