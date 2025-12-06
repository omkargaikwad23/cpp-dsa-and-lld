/*
================================================================================
                    EUCLIDEAN ALGORITHM (GCD/LCM)
================================================================================

PROBLEM: Find Greatest Common Divisor of two numbers.

KEY INSIGHT: gcd(a, b) = gcd(b, a % b) until b becomes 0.

ALGORITHM:
1. If b == 0, return a
2. Otherwise, return gcd(b, a % b)

TIME:  O(log min(a, b))
SPACE: O(1) iterative, O(log min(a,b)) recursive

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// BASIC GCD - Recursive and Iterative
// ═══════════════════════════════════════════════════════════════════════════

int gcdRecursive(int a, int b) {
    if (b == 0) return a;
    return gcdRecursive(b, a % b);
}

int gcdIterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// C++17 has std::gcd in <numeric>
// int g = __gcd(a, b);  // GCC built-in

// ═══════════════════════════════════════════════════════════════════════════
// LCM - Least Common Multiple
// ═══════════════════════════════════════════════════════════════════════════

long long lcm(long long a, long long b) {
    return (a / gcdIterative(a, b)) * b;  // Divide first to avoid overflow
}

// ═══════════════════════════════════════════════════════════════════════════
// EXTENDED EUCLIDEAN - Find x, y such that ax + by = gcd(a, b)
// ═══════════════════════════════════════════════════════════════════════════

// Returns gcd and sets x, y such that ax + by = gcd(a, b)
int extendedGcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd = extendedGcd(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}

// ═══════════════════════════════════════════════════════════════════════════
// MODULAR INVERSE using Extended Euclidean
// ═══════════════════════════════════════════════════════════════════════════

// Find x such that (a * x) % m = 1
// Only exists if gcd(a, m) = 1
int modInverse(int a, int m) {
    int x, y;
    int g = extendedGcd(a, m, x, y);
    
    if (g != 1) {
        return -1;  // Inverse doesn't exist
    }
    
    return (x % m + m) % m;  // Ensure positive result
}

// Alternative: Using Fermat's Little Theorem (when m is prime)
// a^(-1) ≡ a^(m-2) mod m
long long modInverseFermat(long long a, long long m) {
    // Assumes m is prime
    auto power = [](long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    };
    
    return power(a, m - 2, m);
}

// ═══════════════════════════════════════════════════════════════════════════
// GCD OF ARRAY
// ═══════════════════════════════════════════════════════════════════════════

int gcdArray(vector<int>& nums) {
    int result = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        result = gcdIterative(result, nums[i]);
        if (result == 1) return 1;  // Early exit
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// WATER JUG PROBLEM (LC 365) - GCD application
// Can we measure exactly z liters using jugs of x and z liters?
// ═══════════════════════════════════════════════════════════════════════════

bool canMeasureWater(int x, int y, int z) {
    if (x + y < z) return false;
    if (z == 0) return true;
    if (x == 0) return z == y;
    if (y == 0) return z == x;
    
    // z must be multiple of gcd(x, y)
    return z % gcdIterative(x, y) == 0;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Basic GCD
    cout << "GCD(48, 18) = " << gcdIterative(48, 18) << "\n";
    cout << "GCD(100, 35) = " << gcdIterative(100, 35) << "\n";
    
    // LCM
    cout << "\nLCM(12, 18) = " << lcm(12, 18) << "\n";
    cout << "LCM(15, 20) = " << lcm(15, 20) << "\n";
    
    // Extended Euclidean
    int x, y;
    int a = 35, b = 15;
    int g = extendedGcd(a, b, x, y);
    cout << "\nExtended GCD: " << a << "*" << x << " + " << b << "*" << y 
         << " = " << g << "\n";
    cout << "Verification: " << a*x + b*y << "\n";
    
    // Modular Inverse
    cout << "\nModular Inverse of 3 mod 11 = " << modInverse(3, 11) << "\n";
    cout << "Verification: 3 * " << modInverse(3, 11) << " mod 11 = " 
         << (3 * modInverse(3, 11)) % 11 << "\n";
    
    // Water Jug
    cout << "\nWater Jug (3, 5, 4): " << (canMeasureWater(3, 5, 4) ? "Yes" : "No") << "\n";
    cout << "Water Jug (2, 6, 5): " << (canMeasureWater(2, 6, 5) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                         WHY EUCLIDEAN WORKS
================================================================================

Claim: gcd(a, b) = gcd(b, a % b)

Proof:
- Let d = gcd(a, b)
- Then d | a and d | b
- a = q*b + r where r = a % b
- So r = a - q*b, and d | r (since d | a and d | b)
- Therefore d | gcd(b, r)
- Similarly, any divisor of b and r also divides a
- So gcd(a, b) = gcd(b, r) = gcd(b, a % b)

WHY O(log min(a, b))?
- After two iterations, the smaller number is reduced by at least half
- So at most 2*log(min(a,b)) iterations

BÉZOUT'S IDENTITY:
For any integers a, b: ∃ x, y such that ax + by = gcd(a, b)
Extended Euclidean finds these x, y.

RELATED PROBLEMS:
- LC 365: Water and Jug Problem
- LC 1979: Find Greatest Common Divisor of Array
- LC 1250: Check If It Is a Good Array
- LC 878: Nth Magical Number

================================================================================
*/

