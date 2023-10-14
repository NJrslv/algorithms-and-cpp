#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <iomanip>

// Function to generate a random matrix A of size n x n
auto generateRandomMatrix(int n) {
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = dist(rng);

    return A;
}

// Function to generate vector x = (22, 23, 24, ..., 22 + n - 1)
auto generateVectorX(int n) {
    std::vector<double> x(n);
    std::iota(x.begin(), x.end(), 22.0);
    return x;
}

// Function to calculate b = A * x
auto calculateB(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    int n = A.size();
    std::vector<double> b(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    return b;
}

// Gaussian elimination Ax = b
auto gaussianElimination(const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    auto start = std::chrono::high_resolution_clock::now();

    auto n = A.size();
    std::vector<std::vector<double>> augmentedMatrix(n, std::vector<double>(n + 1));

    // Create the augmented matrix from A and b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A[i][j];
        }
        augmentedMatrix[i][n] = b[i];
    }

    // Forward move
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            double l = augmentedMatrix[k][i] / augmentedMatrix[i][i];
            for (int j = i; j <= n; j++) {
                augmentedMatrix[k][j] -= l * augmentedMatrix[i][j];
            }
        }
    }

    // Back-substitution
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmentedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= augmentedMatrix[i][j] * x[j];
        }
        x[i] /= augmentedMatrix[i][i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return make_pair(x, duration.count());
}

// Gaussian Pivot elimination Ax = b
auto gaussianEliminationPivot(const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    auto start = std::chrono::high_resolution_clock::now();

    auto n = A.size();
    std::vector<std::vector<double>> augmentedMatrix(n, std::vector<double>(n + 1));

    // Create an augmented matrix from A and b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A[i][j];
        }
        augmentedMatrix[i][n] = b[i];
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; i++) {
        // Pivotization
        for (int k = i + 1; k < n; k++) {
            if (std::abs(augmentedMatrix[i][i]) < std::abs(augmentedMatrix[k][i])) {
                for (int j = 0; j <= n; j++) {
                    std::swap(augmentedMatrix[i][j], augmentedMatrix[k][j]);
                }
            }
        }

        // Elimination
        for (int k = i + 1; k < n; k++) {
            double l = augmentedMatrix[k][i] / augmentedMatrix[i][i];
            for (int j = i; j <= n; j++) {
                augmentedMatrix[k][j] -= l * augmentedMatrix[i][j];
            }
        }
    }

    // Back-substitution
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmentedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= augmentedMatrix[i][j] * x[j];
        }
        x[i] /= augmentedMatrix[i][i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return make_pair(x, duration.count());
}

auto calculateNorm(const std::vector<double>& vector) {
    double norm = 0.0;
    for (double value : vector) {
        norm += value * value;
    }
    return std::sqrt(norm);
}


auto calculateResidualNorm(const std::vector<std::vector<double>>& A,
                           const std::vector<double>& x,
                           const std::vector<double>& b) {
    auto n = A.size();
    std::vector<double> residual(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            residual[i] += A[i][j] * x[j];
        }
        residual[i] = b[i] - residual[i];
    }

    return calculateNorm(residual);
}

auto calculateRelativeError(const std::vector<double>& x, const std::vector<double>& xPrecise) {
    double normX = calculateNorm(xPrecise);
    std::vector<double> diff(x.size());
    for(auto i = 0; i < x.size(); ++i)
        diff[i] = x[i] - xPrecise[i];
    double normDiff = calculateNorm(diff);

    if (normX == 0.0) {
        return 0.0;
    }

    return normDiff / normX;
}


void printResults(const std::vector<std::vector<double>>& A,
                  const std::vector<double>& xPrecise,
                  const std::vector<double>& x,
                  const std::vector<double>& b,
                  double time) {
    std::cout << "1) First 5 coordinates:\n\n";
    for (int i = 0; i < 5; i++)
        std::cout << "x[" << i << "] = " << x[i] << "\n";
    std::cout << "\n";

    std::cout << "2) ||f - Ax*||2: " << calculateResidualNorm(A, x, b) << "\n";

    std::cout << "3) ||x - x*||2 / ||x||2: " << calculateRelativeError(x, xPrecise) << "\n";

    std::cout << "4) Execution time: " << time << "\n";
}


int main() {
    int n;
    std::cout << "Input (n): ";
    std::cin >> n;

    auto A = generateRandomMatrix(n);
    auto x = generateVectorX(n);
    auto b = calculateB(A, x);

    auto [result1, time1] = gaussianElimination(A, b);
    auto residualNorm1 = calculateResidualNorm(A, result1, b);
    auto relativeError1 = calculateRelativeError(x, result1);

    auto [result2, time2] = gaussianEliminationPivot(A, b);
    auto residualNorm2 = calculateResidualNorm(A, result2, b);
    auto relativeError2 = calculateRelativeError(x, result2);

    std::cout << std::fixed << std::setprecision(8);

    std::cout << "<--- Gaussian elimination --->\n";
    printResults(A, x, result1, b, time1);

    std::cout << "\n";

    std::cout << "<--- Gaussian Pivot elimination --->\n";
    printResults(A, x, result2, b, time2);

    return 0;
}
