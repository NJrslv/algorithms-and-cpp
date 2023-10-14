#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <iomanip>

// Function to generate a random matrix A of size n x n
auto generateRandomSymmetricMatrix(int n) {
    std::vector<std::vector<float>> A(n, std::vector<float>(n, 0.0));
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_real_distribution<float> dist(0.0, 1000.0);

    // Generate random values for the upper triangular part
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j) {
                for(int k = 0; k < n; ++k)
                    if(i != k)
                        A[i][j] += A[i][k];
                A[i][j] *= -1;
            } else {
                A[i][j] = dist(rng);
                A[j][i] = A[i][j];
            }
        }
    }

    A[0][0] = float(1e-1) - std::accumulate(A[0].begin() + 1, A[0].end(), 0.0);

    return A;
}

// Function to generate vector x = (22, 23, 24, ..., 22 + n - 1)
auto generateVectorX(int n) {
    std::vector<float> x(n);
    std::iota(x.begin(), x.end(), 22.0);
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

// Gaussian elimination Ax = b
auto gaussianElimination(const std::vector<std::vector<float>>& A,
                         const std::vector<float>& b) {
    auto start = std::chrono::high_resolution_clock::now();

    auto n = A.size();
    std::vector<std::vector<float>> augmentedMatrix(n, std::vector<float>(n + 1));

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
            float l = augmentedMatrix[k][i] / augmentedMatrix[i][i];
            for (int j = i; j <= n; j++) {
                augmentedMatrix[k][j] -= l * augmentedMatrix[i][j];
            }
        }
    }

    // Back-substitution
    std::vector<float> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmentedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= augmentedMatrix[i][j] * x[j];
        }
        x[i] /= augmentedMatrix[i][i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return make_pair(x, duration.count());
}

// Gaussian Pivot elimination Ax = b
auto gaussianEliminationPivot(const std::vector<std::vector<float>>& A,
                              const std::vector<float>& b) {
    auto start = std::chrono::high_resolution_clock::now();

    auto n = A.size();
    std::vector<std::vector<float>> augmentedMatrix(n, std::vector<float>(n + 1));

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
            float l = augmentedMatrix[k][i] / augmentedMatrix[i][i];
            for (int j = i; j <= n; j++) {
                augmentedMatrix[k][j] -= l * augmentedMatrix[i][j];
            }
        }
    }

    // Back-substitution
    std::vector<float> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmentedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= augmentedMatrix[i][j] * x[j];
        }
        x[i] /= augmentedMatrix[i][i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return make_pair(x, duration.count());
}

auto calculateNorm(const std::vector<float>& vector) {
    float norm = 0.0;
    for (float value : vector) {
        norm += value * value;
    }
    return std::sqrt(norm);
}


auto calculateResidualNorm(const std::vector<std::vector<float>>& A,
                           const std::vector<float>& x,
                           const std::vector<float>& b) {
    auto n = A.size();
    std::vector<float> residual(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            residual[i] += A[i][j] * x[j];
        }
        residual[i] = b[i] - residual[i];
    }

    return calculateNorm(residual);
}

auto calculateRelativeError(const std::vector<float>& x,
                            const std::vector<float>& xPrecise) -> float {
    float normX = calculateNorm(xPrecise);
    std::vector<float> diff(x.size());
    for(auto i = 0; i < x.size(); ++i)
        diff[i] = x[i] - xPrecise[i];
    float normDiff = calculateNorm(diff);

    if (normX == 0.0) {
        return 0.0;
    }

    return normDiff / normX;
}

void ldltDecomposition(const std::vector<std::vector<float>>& A,
                       std::vector<std::vector<float>>& L,
                       std::vector<float>& D) {
    int n = A.size();
    L.resize(n, std::vector<float>(n, 0.0));
    D.resize(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            float sum = A[i][j];
            for (int k = 0; k < i; ++k) {
                sum -= L[i][k] * D[k] * L[j][k];
            }

            if (i == j) {
                D[i] = sum;
                L[i][i] = 1.0;
            } else {
                L[i][j] = sum / D[j];
            }
        }
    }
}

// Function to solve the system of linear equations Ax = b using LDLT decomposition
auto ldltSolve(const std::vector<std::vector<float>>& A,
                             const std::vector<float>& b) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = A.size();
    std::vector<std::vector<float>> L;
    std::vector<float> D;

    // Perform LDLT decomposition
    ldltDecomposition(A, L, D);

    // Solve Ly = b
    std::vector<float> y(n, 0.0);
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Solve Dz = y
    std::vector<float> z(n, 0.0);
    for (int i = 0; i < n; ++i) {
        z[i] = y[i] / D[i];
    }

    // Solve L^Tx = z
    std::vector<float> x(n, 0.0);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = z[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= L[j][i] * x[j];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return make_pair(x, duration.count());
}


void printResults(const std::vector<std::vector<float>>& A,
                  const std::vector<float>& xPrecise,
                  const std::vector<float>& x,
                  const std::vector<float>& b,
                  double time,
                  bool isLDLT) {
    std::cout << "1) First 5 coordinates:\n\n";
    for (int i = 0; i < 5; i++)
        std::cout << "x[" << i << "] = " << x[i] << "\n";
    std::cout << "\n";

    if(!isLDLT)
        std::cout << "2) ||f - Ax*||2: " << calculateResidualNorm(A, x, b) << "\n";

    std::cout << "3) ||x - x*||2 / ||x||2: " << calculateRelativeError(x, xPrecise) << "\n";

    std::cout << "4) Execution time: " << time << "\n";
}


int main() {
    int n;
    std::cout << "Input (n): ";
    std::cin >> n;

    auto A = generateRandomSymmetricMatrix(n);
    auto x = generateVectorX(n);
    auto b = calculateB(A, x);

    auto [result1, time1] = gaussianElimination(A, b);
    auto [result2, time2] = gaussianEliminationPivot(A, b);
    auto [result3, time3] = ldltSolve(A, b);

    std::cout << std::fixed << std::setprecision(8);

    std::cout << "<--- Gaussian elimination --->\n";
    printResults(A, x, result1, b, time1, false);

    std::cout << "\n<--- Gaussian Pivot elimination --->\n";
    printResults(A, x, result2, b, time2, false);

    std::cout << "\n<--- LDLT Decomposition --->\n";
    printResults(A, x, result3, b, time3, true);

    return 0;
}
