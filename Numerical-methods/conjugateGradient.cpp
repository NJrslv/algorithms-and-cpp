#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <chrono>

// Function to generate a random matrix A of size n x n
auto generateRandomSymmetricMatrix(int n) {
    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_real_distribution<double> dist(0.0, 1000.0);

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

    A[0][0] = double(1e-1) - std::accumulate(A[0].begin() + 1, A[0].end(), 0.0);

    return A;
}

// Function to generate vector x = (22, 23, 24, ..., 22 + n - 1)
auto generateVectorX(int n) {
    std::vector<double> x(n);
    std::iota(x.begin(), x.end(), 22.0);
    return x;
}

// Function to calculate b = A * x
auto calculateB(const std::vector<std::vector<double>>& A,
                const std::vector<double>& x) {
    int n = A.size();
    std::vector<double> b(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    return b;
}

void ldltDecomposition(const std::vector<std::vector<double>>& A,
                       std::vector<std::vector<double>>& L,
                       std::vector<double>& D) {
    int n = A.size();
    L.resize(n, std::vector<double>(n, 0.0));
    D.resize(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = A[i][j];
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
auto ldltSolve(const std::vector<std::vector<double>>& A,
               const std::vector<double>& b) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = A.size();
    std::vector<std::vector<double>> L;
    std::vector<double> D;

    // Perform LDLT decomposition
    ldltDecomposition(A, L, D);

    // Solve Ly = b
    std::vector<double> y(n, 0.0);
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Solve Dz = y
    std::vector<double> z(n, 0.0);
    for (int i = 0; i < n; ++i) {
        z[i] = y[i] / D[i];
    }

    // Solve L^Tx = z
    std::vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = z[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= L[j][i] * x[j];
        }
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

auto calculateRelativeError(const std::vector<double>& x,
                            const std::vector<double>& xPrecise) -> double {
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

// Function to calculate dot product
auto dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;

    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

// Function to calculate matrix-vector product
auto matrixVectorProduct(const std::vector<std::vector<double>>& A,
                                             const std::vector<double>& v) {
    std::vector<double> result(v.size(), 0.0);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            result[i] += A[i][j] * v[j];
        }
    }
    return result;
}

// Function to calculate the Conjugate Gradient Method
auto conjugateGradient(const std::vector<std::vector<double>>& A,
                                           const std::vector<double>& f) {
    auto start = std::chrono::high_resolution_clock::now();

    size_t n = f.size();
    std::vector<double> x(n, 0.0);
    std::vector<double> r = f;
    std::vector<double> d = r;
    double rr = dotProduct(r, r);
    int max_iter = 50;

    for (int i = 0; i < max_iter; ++i) {
        std::vector<double> Ad = matrixVectorProduct(A, d);
        double alpha = rr / dotProduct(d, Ad);
        for (size_t j = 0; j < n; ++j) {
            x[j] += alpha * d[j];
        }
        std::vector<double> r_new = r;
        for (size_t j = 0; j < n; ++j) {
            r_new[j] -= alpha * Ad[j];
        }
        double rr_new = dotProduct(r_new, r_new);
        if (sqrt(rr_new) < 1e-10) {
            break;
        }
        for (size_t j = 0; j < n; ++j) {
            d[j] = r_new[j] + (rr_new / rr) * d[j];
        }
        rr = rr_new;
        r = r_new;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return make_pair(x, duration.count());
}

int main() {
    int n;
    std::cout << "Input (n): ";
    std::cin >> n;

    auto A = generateRandomSymmetricMatrix(n);
    auto x = generateVectorX(n);
    auto b = calculateB(A, x);

    auto [result1, time1] = ldltSolve(A, b);
    auto [result2, time2] = conjugateGradient(A, b);

    std::cout << std::fixed << std::setprecision(8);

    std::cout << "\n<--- LDLT Decomposition --->\n";
    printResults(A, x, result1, b, time1);

    std::cout << "\n<--- Conjugate Gradient --->\n";
    printResults(A, x, result2, b, time2);

    return 0;
}
