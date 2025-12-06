/*
================================================================================
                    FAST EXPONENTIATION (Binary Exponentiation)
================================================================================

PROBLEM: Compute a^n efficiently.

KEY INSIGHT: Use binary representation of n.
  a^13 = a^(1101₂) = a^8 × a^4 × a^1

ALGORITHM (Iterative):
1. result = 1
2. While n > 0:
   - If n is odd: result *= a
   - a *= a (square the base)
   - n /= 2 (right shift)

TIME:  O(log n)
SPACE: O(1) iterative, O(log n) recursive

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// BASIC: Pow(x, n) - LC 50
// ═══════════════════════════════════════════════════════════════════════════

double myPow(double x, int n) {
    long long N = n;  // Handle INT_MIN overflow
    
    if (N < 0) {
        x = 1 / x;
        N = -N;
    }
    
    double result = 1.0;
    
    while (N > 0) {
        if (N & 1) {  // N is odd
            result *= x;
        }
        x *= x;  // Square the base
        N >>= 1; // Divide N by 2
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// RECURSIVE VERSION
// ═══════════════════════════════════════════════════════════════════════════

double myPowRecursive(double x, long long n) {
    if (n == 0) return 1;
    if (n < 0) return myPowRecursive(1 / x, -n);
    
    double half = myPowRecursive(x, n / 2);
    
    if (n % 2 == 0) {
        return half * half;
    } else {
        return half * half * x;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// MODULAR EXPONENTIATION - (a^n) mod m
// ═══════════════════════════════════════════════════════════════════════════

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// SUPER POW (LC 372) - a^b where b is given as array
// ═══════════════════════════════════════════════════════════════════════════

int MOD = 1337;

int powMod(int a, int k) {
    a %= MOD;
    int result = 1;
    while (k > 0) {
        if (k & 1) result = (result * a) % MOD;
        a = (a * a) % MOD;
        k >>= 1;
    }
    return result;
}

int superPow(int a, vector<int>& b) {
    // a^[1,5,6,4] = (a^[1,5,6])^10 × a^4
    int result = 1;
    
    for (int digit : b) {
        result = powMod(result, 10) * powMod(a, digit) % MOD;
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// MATRIX EXPONENTIATION - For Fibonacci in O(log n)
// ═══════════════════════════════════════════════════════════════════════════

typedef vector<vector<long long>> Matrix;

Matrix multiply(Matrix& A, Matrix& B, long long mod) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    
    return C;
}

Matrix matrixPow(Matrix& M, long long n, long long mod) {
    int size = M.size();
    Matrix result(size, vector<long long>(size, 0));
    
    // Identity matrix
    for (int i = 0; i < size; i++) result[i][i] = 1;
    
    while (n > 0) {
        if (n & 1) {
            result = multiply(result, M, mod);
        }
        M = multiply(M, M, mod);
        n >>= 1;
    }
    
    return result;
}

// Fibonacci using matrix exponentiation
long long fibMatrix(long long n, long long mod = 1e9 + 7) {
    if (n <= 1) return n;
    
    Matrix M = {{1, 1}, {1, 0}};
    Matrix result = matrixPow(M, n - 1, mod);
    
    return result[0][0];
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Basic power
    cout << "2^10 = " << myPow(2.0, 10) << "\n";
    cout << "2^-2 = " << myPow(2.0, -2) << "\n\n";
    
    // Modular exponentiation
    cout << "Modular: 3^5 mod 13 = " << modPow(3, 5, 13) << "\n";
    cout << "Modular: 2^100 mod 1000000007 = " << modPow(2, 100, 1e9 + 7) << "\n\n";
    
    // Super Pow
    vector<int> b = {1, 5, 6, 4};
    cout << "Super Pow: 2^[1564] mod 1337 = " << superPow(2, b) << "\n\n";
    
    // Fibonacci using matrix
    cout << "Fibonacci:\n";
    for (int n : {10, 20, 50}) {
        cout << "  F(" << n << ") = " << fibMatrix(n) << "\n";
    }
    
    return 0;
}

/*
================================================================================
                         WHY IT'S O(log n)
================================================================================

Binary representation of n has O(log n) bits.
Each iteration processes one bit → O(log n) iterations.

EXAMPLE: 2^13 = 2^(1101₂)
  - Start: result=1, base=2, n=13
  - n=13 (odd): result=1×2=2, base=4, n=6
  - n=6 (even): result=2, base=16, n=3
  - n=3 (odd): result=2×16=32, base=256, n=1
  - n=1 (odd): result=32×256=8192, n=0
  - Final: 8192 ✓

APPLICATIONS:
- Pow(x, n) - LC 50
- Modular inverse: a^(-1) ≡ a^(p-2) mod p (when p is prime)
- Matrix exponentiation for linear recurrences
- Cryptography (RSA)

RELATED PROBLEMS:
- LC 50: Pow(x, n)
- LC 372: Super Pow
- LC 509: Fibonacci Number (can be optimized with matrix exp)

================================================================================
*/

