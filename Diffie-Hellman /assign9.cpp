#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

// Function to calculate GCD
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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

// Function to check if a number is prime
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

// Function to count divisors of (p-1)
vector<long long> getPrimeFactors(long long n) {
    vector<long long> factors;
    
    // Check for 2
    if (n % 2 == 0) {
        factors.push_back(2);
        while (n % 2 == 0)
            n = n / 2;
    }
    
    // Check for odd factors
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0)
                n = n / i;
        }
    }
    
    if (n > 2)
        factors.push_back(n);
    
    return factors;
}

// Function to check if g is a primitive root modulo p
bool isPrimitiveRoot(long long g, long long p) {
    if (modExp(g, p - 1, p) != 1)
        return false;
    
    vector<long long> factors = getPrimeFactors(p - 1);
    
    for (auto factor : factors) {
        if (modExp(g, (p - 1) / factor, p) == 1)
            return false;
    }
    
    return true;
}

// Function to find a primitive root modulo p (brute force for small primes)
long long findPrimitiveRoot(long long p) {
    for (long long g = 2; g < p; g++) {
        if (isPrimitiveRoot(g, p))
            return g;
    }
    return -1;
}

int main() {
    cout << "====== DIFFIE-HELLMAN KEY EXCHANGE ALGORITHM ======\n" << endl;
    
    // ========== STEP 1: INPUT PRIME NUMBER ==========
    cout << "--- STEP 1: INPUT PRIME NUMBER (p) ---\n" << endl;
    
    long long p;
    cout << "Enter a large prime number (p): ";
    cin >> p;
    
    if (!isPrime(p)) {
        cout << "Error: " << p << " is not a prime number!" << endl;
        return 1;
    }
    cout << "✓ " << p << " is prime\n" << endl;
    
    // ========== STEP 2: INPUT OR CHOOSE PRIMITIVE ROOT ==========
    cout << "--- STEP 2: CHOOSE PRIMITIVE ROOT (generator g) ---\n" << endl;
    cout << "A primitive root g satisfies: g^(p-1) ≡ 1 (mod p)\n" << endl;
    
    long long g;
    cout << "Enter a primitive root g (or 0 to find one): ";
    cin >> g;
    
    if (g == 0) {
        cout << "Finding a primitive root..." << endl;
        g = findPrimitiveRoot(p);
        if (g == -1) {
            cout << "Error: Could not find a primitive root!" << endl;
            return 1;
        }
    }
    
    // Verify g is a primitive root
    if (!isPrimitiveRoot(g, p)) {
        cout << "Warning: " << g << " may not be a primitive root modulo " << p << endl;
    }
    
    cout << "✓ Primitive root g = " << g << "\n" << endl;
    
    // ========== STEP 3: INPUT PRIVATE KEYS ==========
    cout << "--- STEP 3: INPUT PRIVATE KEYS ---\n" << endl;
    
    long long xa, xb;
    cout << "Enter Alice's private key (xa): ";
    cin >> xa;
    
    cout << "Enter Bob's private key (xb): ";
    cin >> xb;
    
    if (xa >= p || xb >= p) {
        cout << "Error: Private keys must be less than p!" << endl;
        return 1;
    }
    
    cout << "\nAlice's private key (xa) = " << xa << endl;
    cout << "Bob's private key (xb) = " << xb << "\n" << endl;
    
    // ========== STEP 4: GENERATE ALICE'S PUBLIC KEY ==========
    cout << "--- STEP 4: GENERATE ALICE'S PUBLIC KEY ---\n" << endl;
    cout << "Formula: Ya = g^xa mod p\n" << endl;
    cout << "Ya = " << g << "^" << xa << " mod " << p << endl;
    
    long long Ya = modExp(g, xa, p);
    
    cout << "Alice's public key (Ya) = " << Ya << "\n" << endl;
    
    // ========== STEP 5: GENERATE BOB'S PUBLIC KEY ==========
    cout << "--- STEP 5: GENERATE BOB'S PUBLIC KEY ---\n" << endl;
    cout << "Formula: Yb = g^xb mod p\n" << endl;
    cout << "Yb = " << g << "^" << xb << " mod " << p << endl;
    
    long long Yb = modExp(g, xb, p);
    
    cout << "Bob's public key (Yb) = " << Yb << "\n" << endl;
    
    // ========== STEP 6: PUBLIC KEY EXCHANGE ==========
    cout << "--- STEP 6: PUBLIC KEY EXCHANGE ---\n" << endl;
    cout << "Alice sends Ya to Bob" << endl;
    cout << "Bob sends Yb to Alice\n" << endl;
    
    // ========== STEP 7: ALICE COMPUTES SHARED SECRET ==========
    cout << "--- STEP 7: ALICE COMPUTES SHARED SECRET ---\n" << endl;
    cout << "Formula: K_A = Yb^xa mod p\n" << endl;
    cout << "K_A = " << Yb << "^" << xa << " mod " << p << endl;
    
    long long KA = modExp(Yb, xa, p);
    
    cout << "Alice's shared secret key (K_A) = " << KA << "\n" << endl;
    
    // ========== STEP 8: BOB COMPUTES SHARED SECRET ==========
    cout << "--- STEP 8: BOB COMPUTES SHARED SECRET ---\n" << endl;
    cout << "Formula: K_B = Ya^xb mod p\n" << endl;
    cout << "K_B = " << Ya << "^" << xb << " mod " << p << endl;
    
    long long KB = modExp(Ya, xb, p);
    
    cout << "Bob's shared secret key (K_B) = " << KB << "\n" << endl;
    
    // ========== STEP 9: VERIFICATION ==========
    cout << "--- STEP 9: VERIFICATION ---\n" << endl;
    cout << "Checking if K_A == K_B..." << endl;
    
    if (KA == KB) {
        cout << "✓ SUCCESS! Shared secrets match!" << endl;
        cout << "✓ K_A = K_B = " << KA << "\n" << endl;
    } else {
        cout << "✗ ERROR! Shared secrets do not match!" << endl;
        cout << "✗ K_A = " << KA << " but K_B = " << KB << "\n" << endl;
    }
    
    // ========== MATHEMATICAL VERIFICATION ==========
    cout << "--- MATHEMATICAL VERIFICATION ---\n" << endl;
    cout << "K_A = Yb^xa mod p = (g^xb mod p)^xa mod p = g^(xb*xa) mod p" << endl;
    cout << "K_B = Ya^xb mod p = (g^xa mod p)^xb mod p = g^(xa*xb) mod p" << endl;
    cout << "Since multiplication is commutative: xa*xb = xb*xa" << endl;
    cout << "Therefore: K_A = K_B = g^(xa*xb) mod p\n" << endl;
    
    // ========== SUMMARY ==========
    cout << "========== SUMMARY ==========\n" << endl;
    cout << "Prime number (p):                  " << p << endl;
    cout << "Primitive root (g):                " << g << endl;
    cout << "Alice's private key (xa):          " << xa << endl;
    cout << "Bob's private key (xb):            " << xb << endl;
    cout << "Alice's public key (Ya = g^xa):    " << Ya << endl;
    cout << "Bob's public key (Yb = g^xb):      " << Yb << endl;
    cout << "Alice's shared secret (K_A = Yb^xa): " << KA << endl;
    cout << "Bob's shared secret (K_B = Ya^xb):   " << KB << endl;
    cout << "Shared secret keys equal:          ";
    
    if (KA == KB)
        cout << "YES ✓\n" << endl;
    else
        cout << "NO ✗\n" << endl;
    
    // Computational verification
    long long computed_secret = modExp(g, (xa * xb) % (p - 1), p);
    cout << "Computed g^(xa*xb) mod p:          " << computed_secret << endl;
    cout << "Matches shared secret:             ";
    if (computed_secret == KA)
        cout << "YES ✓\n" << endl;
    else
        cout << "NO ✗\n" << endl;
    
    cout << "====== DIFFIE-HELLMAN COMPLETE ======\n" << endl;
    
    return 0;
}
