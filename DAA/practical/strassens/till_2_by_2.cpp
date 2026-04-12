#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> createMatrix(size_t n) {
    return vector<vector<int>>(n, vector<int>(n, 0));
}

vector<vector<int>> vectorAddition(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    size_t n = A.size();
    vector<vector<int>> result = createMatrix(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

vector<vector<int>> vectorSubtraction(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    size_t n = A.size();
    vector<vector<int>> result = createMatrix(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B, size_t n) {
    if (n == 2) {
        vector<vector<int>> C = createMatrix(2);
        C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
        return C;
    }
    if (n == 1) {
        vector<vector<int>> C = createMatrix(1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    size_t newSize = n / 2;
    auto A11 = createMatrix(newSize), A12 = createMatrix(newSize), A21 = createMatrix(newSize), A22 = createMatrix(newSize);
    auto B11 = createMatrix(newSize), B12 = createMatrix(newSize), B21 = createMatrix(newSize), B22 = createMatrix(newSize);

    for (size_t i = 0; i < newSize; i++) {
        for (size_t j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    auto M1 = strassen(vectorAddition(A11, A22), vectorAddition(B11, B22), newSize);
    auto M2 = strassen(vectorAddition(A21, A22), B11, newSize);
    auto M3 = strassen(A11, vectorSubtraction(B12, B22), newSize);
    auto M4 = strassen(A22, vectorSubtraction(B21, B11), newSize);
    auto M5 = strassen(vectorAddition(A11, A12), B22, newSize);
    auto M6 = strassen(vectorSubtraction(A21, A11), vectorAddition(B11, B12), newSize);
    auto M7 = strassen(vectorSubtraction(A12, A22), vectorAddition(B21, B22), newSize);

    auto C11 = vectorAddition(vectorSubtraction(vectorAddition(M1, M4), M5), M7);
    auto C12 = vectorAddition(M3, M5);
    auto C21 = vectorAddition(M2, M4);
    auto C22 = vectorAddition(vectorSubtraction(vectorAddition(M1, M3), M2), M6);

    vector<vector<int>> C = createMatrix(n);
    for (size_t i = 0; i < newSize; i++) {
        for (size_t j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

int main() {
    vector<vector<int>> a = {{1, 2, 3, 4}, {1, 1, 1, 1}, {2, 2, 3, 4}, {2, 3, 4, 5}};
    vector<vector<int>> b = {{1, 2, 3, 4}, {6, 7, 8, 8}, {3, 3, 4, 7}, {3, 5, 7, 9}};

    vector<vector<int>> c = strassen(a, b, a.size());

    for (size_t i = 0; i < c.size(); i++) {
        for (size_t j = 0; j < c[i].size(); j++) {
            cout << c[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}