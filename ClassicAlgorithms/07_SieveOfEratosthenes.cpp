/*
================================================================================
                    SIEVE OF ERATOSTHENES
================================================================================

PROBLEM: Find all prime numbers up to n.

KEY INSIGHT: Start with 2, mark all its multiples as non-prime.
             Move to next unmarked number, repeat.

ALGORITHM:
1. Create boolean array isPrime[0..n], all true initially
2. Mark 0 and 1 as non-prime
3. For i from 2 to √n:
   - If isPrime[i]: mark all multiples of i as non-prime
4. Collect all indices where isPrime[i] = true

TIME:  O(n log log n)
SPACE: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// BASIC SIEVE - Find all primes up to n
// ═══════════════════════════════════════════════════════════════════════════

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    // Only need to check up to √n
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // Mark all multiples of i as non-prime
            // Start from i*i because smaller multiples already marked
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    // Collect primes
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// ═══════════════════════════════════════════════════════════════════════════
// COUNT PRIMES (LC 204)
// ═══════════════════════════════════════════════════════════════════════════

int countPrimes(int n) {
    if (n <= 2) return 0;
    
    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i < n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return count(isPrime.begin(), isPrime.end(), true);
}

// ═══════════════════════════════════════════════════════════════════════════
// SEGMENTED SIEVE - For large ranges [L, R]
// ═══════════════════════════════════════════════════════════════════════════

vector<int> segmentedSieve(long long L, long long R) {
    // First, get all primes up to √R
    int limit = sqrt(R) + 1;
    vector<bool> basePrime(limit + 1, true);
    basePrime[0] = basePrime[1] = false;
    
    for (int i = 2; i * i <= limit; i++) {
        if (basePrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                basePrime[j] = false;
            }
        }
    }
    
    vector<int> basePrimes;
    for (int i = 2; i <= limit; i++) {
        if (basePrime[i]) basePrimes.push_back(i);
    }
    
    // Mark composites in range [L, R]
    vector<bool> isPrime(R - L + 1, true);
    
    for (int p : basePrimes) {
        // Find first multiple of p >= L
        long long start = max((long long)p * p, ((L + p - 1) / p) * p);
        
        for (long long j = start; j <= R; j += p) {
            isPrime[j - L] = false;
        }
    }
    
    // Handle special case: L = 1
    if (L == 1) isPrime[0] = false;
    
    // Collect primes
    vector<int> result;
    for (long long i = L; i <= R; i++) {
        if (isPrime[i - L]) {
            result.push_back(i);
        }
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// SMALLEST PRIME FACTOR (SPF) - For prime factorization
// ═══════════════════════════════════════════════════════════════════════════

vector<int> smallestPrimeFactor(int n) {
    vector<int> spf(n + 1);
    
    // Initialize: spf[i] = i
    for (int i = 0; i <= n; i++) {
        spf[i] = i;
    }
    
    // Sieve
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {  // i is prime
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) {  // Not yet marked
                    spf[j] = i;
                }
            }
        }
    }
    
    return spf;
}

// Prime factorization using SPF
vector<int> primeFactorization(int n, vector<int>& spf) {
    vector<int> factors;
    while (n > 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }
    return factors;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Basic sieve
    cout << "Primes up to 50: ";
    for (int p : sieveOfEratosthenes(50)) {
        cout << p << " ";
    }
    cout << "\n\n";
    
    // Count primes
    cout << "Count primes < 100: " << countPrimes(100) << "\n\n";
    
    // Prime factorization using SPF
    int n = 100;
    vector<int> spf = smallestPrimeFactor(n);
    
    cout << "Prime factorizations:\n";
    for (int num : {12, 36, 84, 97}) {
        cout << num << " = ";
        vector<int> factors = primeFactorization(num, spf);
        for (int i = 0; i < factors.size(); i++) {
            cout << factors[i];
            if (i < factors.size() - 1) cout << " × ";
        }
        cout << "\n";
    }
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

BASIC SIEVE:
- Time: O(n log log n) - nearly linear!
- Space: O(n)

WHY O(n log log n)?
- Number n is crossed out by each prime factor
- Average number of prime factors of n is log log n
- So each number is visited O(log log n) times on average

SEGMENTED SIEVE:
- Time: O((R-L+1) log log R + √R)
- Space: O(√R + (R-L))
- Use when range is large but R-L is manageable

RELATED PROBLEMS:
- LC 204: Count Primes
- LC 762: Prime Number of Set Bits in Binary Representation
- LC 866: Prime Palindrome
- LC 1175: Prime Arrangements

================================================================================
*/

