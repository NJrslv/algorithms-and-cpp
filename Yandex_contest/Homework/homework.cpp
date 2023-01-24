#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <set>
#include <algorithm>


using pair = std::pair<uint64_t, uint64_t>;
std::multiset<uint64_t> prime_factors(int n);
uint64_t get_max_unused_prime(std::multiset<uint64_t> l, 
                              std::multiset<uint64_t> r);
std::vector<uint64_t> solve(std::vector<pair>& pairs);


int main(){
   size_t t;
   std::cin>>t;
   std::vector<pair> in(t);
   for(pair& el: in) std::cin>>el.first>>el.second;
   std::vector<uint64_t> result = solve(in);
   for(auto& el: result) std::cout<<el<<'\n';
}


std::vector<uint64_t> solve(std::vector<pair>& pairs){
   std::vector<uint64_t> answer(pairs.size());
   int index = 0;
   for(pair& p: pairs){
      std::multiset<uint64_t> left = prime_factors(std::max(p.first, p.second));
      std::multiset<uint64_t> right = prime_factors(std::min(p.first, p.second));
      uint64_t prime = get_max_unused_prime(left, right);
      answer[index] = std::gcd(std::min(p.first, p.second) * prime, 
                               std::max(p.first, p.second));
      ++index;
   }
   return answer;
}


uint64_t get_max_unused_prime(std::multiset<uint64_t> l,
                              std::multiset<uint64_t> r){
   std::vector<uint64_t> diff(l.size());
   std::set_difference(l.begin(), l.end(), r.begin(), r.end(),diff.begin());
   return *std::max_element(diff.begin(), diff.end());
}


std::multiset<uint64_t> prime_factors(int n) {
    std::multiset<uint64_t> factors;
    while (n % 2 == 0) {
        factors.insert(2);
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            factors.insert(i);
            n = n / i;
        }
    }
    if (n > 2)
        factors.insert(n);
    return factors;
}


