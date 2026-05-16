#include <bitset>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Function to calculate GCD using Euclidean algorithm
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Extended Euclidean Algorithm to find modular inverse
// Returns x such that (a * x) % m = 1
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    
    long long x1, y1;
    long long gcd_val = extendedGCD(b % a, a, x1, y1);
    
    x = y1 - (b / a) * x1;
    y = x1;
    
    return gcd_val;
}

// Function to find modular multiplicative inverse
// Find d such that (e * d) % phi = 1
long long modularInverse(long long e, long long phi) {
    long long x, y;
    long long g = extendedGCD(e, phi, x, y);
    
    if (g != 1) {
        cout << "Modular inverse does not exist!" << endl;
        return -1;
    }
    
    // Make sure x is positive
    return (x % phi + phi) % phi;
}

// Function to perform modular exponentiation: (base^exp) % mod
// Using binary exponentiation for efficiency
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}

// Function to check if a number is prime (simple primality test)
bool isPrime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to display binary representation
void printBinary(long long num) {
    if (num == 0) {
        cout << "0";
        return;
    }
    
    cout << bitset<64>(num);
}

int main() {
    cout << "====== RSA CRYPTOGRAPHY ALGORITHM ======\n" << endl;
    
    // ========== STEP 1: INPUT PRIME NUMBERS ==========
    cout << "--- STEP 1: INPUT TWO PRIME NUMBERS ---\n" << endl;
    
    long long p, q;
    
    cout << "Enter first prime number (p): ";
    cin >> p;
    
    if (!isPrime(p)) {
        cout << "Error: " << p << " is not a prime number!" << endl;
        return 1;
    }
    cout << "✓ " << p << " is prime" << endl;
    
    cout << "Enter second prime number (q): ";
    cin >> q;
    
    if (!isPrime(q)) {
        cout << "Error: " << q << " is not a prime number!" << endl;
        return 1;
    }
    cout << "✓ " << q << " is prime" << endl;
    
    if (p == q) {
        cout << "Error: p and q must be different!" << endl;
        return 1;
    }
    
    cout << "\np = " << p << endl;
    cout << "q = " << q << "\n" << endl;
    
    // ========== STEP 2: CALCULATE n ==========
    cout << "--- STEP 2: CALCULATE n (n = p × q) ---\n" << endl;
    long long n = p * q;
    cout << "n = p × q = " << p << " × " << q << " = " << n << "\n" << endl;
    
    // ========== STEP 3: CALCULATE EULER'S TOTIENT ==========
    cout << "--- STEP 3: CALCULATE EULER'S TOTIENT φ(n) ---\n" << endl;
    long long phi = (p - 1) * (q - 1);
    cout << "φ(n) = (p - 1) × (q - 1)" << endl;
    cout << "φ(n) = (" << p << " - 1) × (" << q << " - 1)" << endl;
    cout << "φ(n) = " << (p - 1) << " × " << (q - 1) << " = " << phi << "\n" << endl;
    
    // ========== STEP 4: CHOOSE PUBLIC KEY e ==========
    cout << "--- STEP 4: CHOOSE PUBLIC KEY e ---\n" << endl;
    cout << "Condition: gcd(e, φ(n)) = 1\n" << endl;
    
    long long e;
    cout << "Enter public exponent e (or 0 to use default 65537): ";
    cin >> e;
    
    if (e == 0) {
        e = 65537; // Common choice
    }
    
    // Check if gcd(e, phi) = 1
    if (gcd(e, phi) != 1) {
        cout << "Error: gcd(e, φ(n)) ≠ 1. Choose a different e." << endl;
        return 1;
    }
    
    cout << "✓ gcd(" << e << ", " << phi << ") = 1\n" << endl;
    
    // ========== STEP 5: CALCULATE PRIVATE KEY d ==========
    cout << "--- STEP 5: CALCULATE PRIVATE KEY d ---\n" << endl;
    cout << "d such that (e × d) mod φ(n) = 1\n" << endl;
    
    long long d = modularInverse(e, phi);
    
    if (d == -1) {
        cout << "Error: Could not find private key!" << endl;
        return 1;
    }
    
    cout << "Private key d = " << d << endl;
    cout << "Verification: (" << e << " × " << d << ") mod " << phi 
         << " = " << (e * d) % phi << " (should be 1)\n" << endl;
    
    // ========== STEP 6: DISPLAY PUBLIC AND PRIVATE KEYS ==========
    cout << "========== KEY PAIRS ==========\n" << endl;
    cout << "PUBLIC KEY (e, n): (" << e << ", " << n << ")" << endl;
    cout << "PRIVATE KEY (d, n): (" << d << ", " << n << ")\n" << endl;
    
    // ========== STEP 7: INPUT PLAINTEXT MESSAGE ==========
    cout << "--- STEP 7: INPUT PLAINTEXT MESSAGE ---\n" << endl;
    
    long long M;
    cout << "Enter plaintext message M (must be < " << n << "): ";
    cin >> M;
    
    if (M >= n) {
        cout << "Error: Plaintext M must be less than n!" << endl;
        return 1;
    }
    
    cout << "Plaintext message M = " << M << "\n" << endl;
    
    // ========== STEP 8: ENCRYPTION ==========
    cout << "--- STEP 8: ENCRYPTION ---\n" << endl;
    cout << "Formula: C = M^e mod n\n" << endl;
    cout << "C = " << M << "^" << e << " mod " << n << endl;
    
    long long C = modExp(M, e, n);
    
    cout << "Ciphertext C = " << C << "\n" << endl;
    
    // ========== STEP 9: DECRYPTION ==========
    cout << "--- STEP 9: DECRYPTION ---\n" << endl;
    cout << "Formula: M = C^d mod n\n" << endl;
    cout << "M = " << C << "^" << d << " mod " << n << endl;
    
    long long M_decrypted = modExp(C, d, n);
    
    cout << "Decrypted plaintext M' = " << M_decrypted << "\n" << endl;
    
    // ========== VERIFICATION ==========
    cout << "--- VERIFICATION ---\n" << endl;
    if (M == M_decrypted) {
        cout << "✓ Encryption and Decryption successful!" << endl;
        cout << "✓ Original plaintext: " << M << endl;
        cout << "✓ Decrypted plaintext: " << M_decrypted << endl;
    } else {
        cout << "✗ Error in encryption/decryption!" << endl;
    }
    
    // ========== SUMMARY ==========
    cout << "\n========== SUMMARY ==========\n" << endl;
    cout << "Prime numbers (p, q):              (" << p << ", " << q << ")" << endl;
    cout << "n = p × q:                         " << n << endl;
    cout << "φ(n) = (p-1)(q-1):                 " << phi << endl;
    cout << "Public key (e, n):                 (" << e << ", " << n << ")" << endl;
    cout << "Private key (d, n):                (" << d << ", " << n << ")" << endl;
    cout << "Plaintext message (M):             " << M << endl;
    cout << "Encrypted ciphertext (C = M^e):    " << C << endl;
    cout << "Decrypted message (M' = C^d):      " << M_decrypted << endl;
    cout << "\n====== RSA COMPLETE ======\n" << endl;
    
    return 0;
}
