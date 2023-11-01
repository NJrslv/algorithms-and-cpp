#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <iomanip>

// Function to generate a matrix A of size n x n
auto generateA(int n) {
    std::vector<std::vector<float>> A(n, std::vector<float>(n, 0.0));
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> dist(-4, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j) {
                for(int k = 0; k < n; ++k)
                    if(i != k)
                        A[i][j] += A[i][k];
                A[i][j] *= -1;
            } else {
                A[i][j] = static_cast<float>(dist(rng));
                A[j][i] = static_cast<float>(dist(rng));
            }
        }
    }

    A[0][0] += 1;
    return A;
}

// Function to generate vector x = (m, m + 1, m + 2, ..., m + n - 1)
auto generateVectorX(const int n, const int m) {
    std::vector<float> x(n);
    std::iota(x.begin(), x.end(), m);
    return x;
}

// Function to calculate b = A * x
auto calculateB(const std::vector<std::vector<float>>& A,
                const std::vector<float>& x) {
    int n = A.size();
    std::vector<float> b(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    return b;
}

// Function to solve the system Ax=b using the Jacobi method
auto jacobi(const std::vector<std::vector<float>>& A,
            const std::vector<float>& b,
            std::vector<float>& x,
            const float eps,
            const int maxIter) {
    int n = A.size();
    std::vector<float> x_new(n, 0.0);
    int iter = 0;
    float error = eps + 1;

    while (error > eps && iter < maxIter) {
        for (int i = 0; i < n; i++) {
            float sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        error = std::abs(x_new[0] - x[0]);
        for (int i = 0; i < n; i++) {
            if (std::abs(x_new[i] - x[i]) > error) {
                error = std::abs(x_new[i] - x[i]);
            }
            x[i] = x_new[i];
        }
        iter++;
        if (error < eps || iter >= maxIter) {
            break;
        }
    }

    return make_pair(x_new, iter);
}

// Function to solve the system Ax=b using the relaxation method
auto relaxation(const std::vector<std::vector<float>>& A,
                const std::vector<float>& b,
                std::vector<float>& x,
                const float w,
                const float eps,
                const int maxIter) {
    int n = A.size();
    std::vector<float> x_new(n, 0.0);
    float error = eps + 1;
    int iter = 0;

    while (error > eps && iter < maxIter) {
        for (int i = 0; i < n; i++) {
            float sum1 = 0.0;
            float sum2 = 0.0;
            for (int j = 0; j < i; j++) {
                sum1 += A[i][j] * x_new[j];
            }
            for (int j = i + 1; j < n; j++) {
                sum2 += A[i][j] * x[j];
            }
            x_new[i] = (1 - w) * x[i] + (w / A[i][i]) * (b[i] - sum1 - sum2);
        }
        error = std::abs(x_new[0] - x[0]);
        for (int i = 0; i < n; i++) {
            if (std::abs(x_new[i] - x[i]) > error) {
                error = std::abs(x_new[i] - x[i]);
            }
            x[i] = x_new[i];
        }
        iter++;
        if (error < eps || iter >= maxIter) {
            break;
        }
    }

    return std::make_pair(x_new, iter);
}

void printResults(const std::vector<std::vector<float>>& A,
                  const std::vector<float>& xPrecise,
                  const std::vector<float>& x,
                  const std::vector<float>& b,
                  int64_t iters) {
    std::cout << "1) First 5 coordinates:\n\n";
    for (int i = 0; i < 5; i++)
        std::cout << "x[" << i << "] = " << x[i] << "\n";
    
    std::cout << "\n2) Iterations: " << iters << "\n";
}


int main() {
    std::cout << std::fixed << std::setprecision(8);

    constexpr int n = 10, m = 22;
    constexpr float maxIter = 1000., eps = 0.0001;

    const auto A = generateA(n);
    const auto x = generateVectorX(n, m);
    const auto b = calculateB(A, x);
    std::vector<float> startPlan(n, 0.0);

    std::cout << "<--- Jacobi Method --->\n\n";
    auto [xJacobi, iterJacobi] = jacobi(A, b, startPlan, eps, maxIter);
    printResults(A, xJacobi, x, b, iterJacobi);

    std::fill(startPlan.begin(), startPlan.end(), 0.0);
    constexpr float w1 = 0.5;
    auto [xRelax1, iterRelax1] = relaxation(A, b, startPlan, w1, eps, maxIter);

    std::fill(startPlan.begin(), startPlan.end(), 0.0);
    constexpr float w2 = 1;
    auto [xRelax2, iterRelax2] = relaxation(A, b, startPlan, w2, eps, maxIter);

    std::fill(startPlan.begin(), startPlan.end(), 0.0);
    constexpr float w3 = 1.5;
    auto [xRelax3, iterRelax3] = relaxation(A, b, startPlan, w3, eps, maxIter);

    std::cout << "\n<--- Relaxation Method --->\n";
    std::cout << "\n<--- w = 0.5 --->\n\n";
    printResults(A, xRelax1, x, b, iterRelax1);

    std::cout << "\n<--- w = 1 ---> \n\n";
    printResults(A, xRelax2, x, b, iterRelax2);

    std::cout << "\n<--- w = 1.5 ---> \n\n";
    printResults(A, xRelax3, x, b, iterRelax3);

    return 0;
}