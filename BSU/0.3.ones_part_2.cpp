#include <iostream>
#include <vector>
#include <cmath>

const int M = 1000000007;
const int N = 1000001;

std::vector<int64_t> inord_factorial(N); // inord_factorial[i] = i! mod M
std::vector<int64_t> preord_factorial(N);// preord_factorial[i] = i!^-1 mod M
int64_t power_mod(int64_t a, int64_t b);// a^b mod m
int64_t Cnk(int64_t n, int64_t k);//C(n,k)
void fill_factorials();// fills factoral's arrays
int64_t mod(int64_t a, int64_t b);// custom mod to avoid overflowing


int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  size_t n, k;
  std::cin >> n >> k;
  fill_factorials();
  std::cout << Cnk(n, k) << std::endl;
  return 0;
}

void fill_factorials() {
  inord_factorial[0] = 1;
  for (int64_t i = 1; i < N; i++) {
    inord_factorial[i] = mod((inord_factorial[i-1] * i), M);
  }
  preord_factorial[N-1] = power_mod(inord_factorial[N-1], M-2);
  for (int64_t i = N-2; i >= 0; i--) {
    preord_factorial[i] = mod((preord_factorial[i+1] * (i+1)), M);
  }
}

int64_t Cnk(int64_t n, int64_t k) {
  return mod(mod(inord_factorial[n] * preord_factorial[k], M) * preord_factorial[n-k], M);
}

int64_t power_mod(int64_t a, int64_t b) {
  int64_t res = 1;
  while (b) {
    if (b & 1) res = mod((res * a), M);
    a = mod((a * a), M);
    b >>= 1;
  }
  return res;
}

int64_t mod(int64_t a, int64_t b) {
    int64_t res = a % b;
    if (res < 0)
        res += b;
    return res;
}


