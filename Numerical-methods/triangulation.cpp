#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void fillA(vector<vector<float>>& A, int m, int k, int N) {
    for (int i = 0; i < N; ++i) {
        A[i][i] = m + k + i - 1;
        if (i > 0) {
            A[i][i - 1] = -k;
        }
        if (i + 1 < N) {
            A[i][i + 1] = m - 1 + i;
        }
    }
    A[0][0] = m;
}

auto solveTridiagonalSystem(const vector<vector<float>>& A, const vector<float>& f) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = A.size();

    // Initialize vectors for the tridiagonal matrix and the result
    vector<float> a(n);  // lower diagonal
    vector<float> b(n);  // main diagonal
    vector<float> c(n);  // upper diagonal
    vector<float> res(n); // result vector

    // Fill vectors a, b, and c with the lower, main, and upper diagonals of matrix A
    for (int i = 0; i < n; ++i) {
        b[i] = A[i][i]; // main diagonal
        res[i] = f[i];  // right-hand side vector

        // Check if there are elements in the lower and upper diagonals
        if (i > 0) {
            a[i] = A[i][i - 1]; // lower diagonal
        }
        if (i + 1 < n) {
            c[i] = A[i][i + 1]; // upper diagonal
        }
    }

    float temp;
    // Forward elimination: transform the matrix into an upper triangular form
    for (int i = 1; i < n; i++) {
        temp = a[i] / b[i - 1];
        b[i] = b[i] - temp * c[i - 1];
        res[i] = res[i] - temp * res[i - 1];
    }

    // Backward substitution: solve for the unknowns starting from the last row
    res[n - 1] = res[n - 1] / b[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        res[i] = (res[i] - c[i] * res[i + 1]) / b[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return make_pair(res, duration.count());
}


// Function to calculate f = A * x
auto calculateF(const std::vector<std::vector<float>>& A,
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

auto generateVectorY(int n) {
    std::vector<float> x(n);
    std::iota(x.begin(), x.end(), 1);
    return x;
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

auto calculateNorm(const std::vector<float>& vector) {
    float norm = 0.0;
    for (float value : vector) {
        norm += value * value;
    }
    return std::sqrt(norm);
}

auto calculateRelativeError(const std::vector<float>& x,
                            const std::vector<float>& xPrecise) -> double {
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


void printResults(const std::vector<std::vector<float>>& A,
                  const std::vector<float>& xPrecise,
                  const std::vector<float>& x,
                  double time) {
    std::cout << "1) First 5 coordinates:\n\n";
    for (int i = 0; i < 5; i++)
        std::cout << "x[" << i << "] = " << x[i] << "\n";
    std::cout << "\n";

    std::cout << "3) ||x - x*||2 / ||x||2: " << calculateRelativeError(x, xPrecise) << "\n";

    std::cout << "4) Execution time: " << time << "\n";
}

int main() {
    const int m = 22;
    const int k = 3;
    int N;
    cout << "Input N: ";
    cin >> N;

    vector<vector<float>> A(N, vector<float>(N));
    fillA(A, m, k, N);

    auto y = generateVectorY(N);
    vector<float> f = calculateF(A, y);
    auto [res1, t1] = solveTridiagonalSystem(A, f);
    auto [res2, t2] = gaussianElimination(A, f);

    cout << "<--- Method of Triangularization --->\n";
    printResults(A, y, res1, t1); 
    cout << "<--- Gaussian Elimination Method --->\n";
    printResults(A, y, res2, t2);

    return 0;
}