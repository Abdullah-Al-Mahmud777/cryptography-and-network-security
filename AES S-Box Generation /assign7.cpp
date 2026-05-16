#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

// AES irreducible polynomial: x^8 + x^4 + x^3 + x + 1 = 0x11B
#define IRRED_POLY 0x11B

// Function to multiply two bytes in GF(2^8)
unsigned char gf_multiply(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    unsigned char temp_a = a;
    
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= temp_a;
        }
        
        // Check if MSB is set
        if (temp_a & 0x80) {
            temp_a = (temp_a << 1) ^ IRRED_POLY;
        } else {
            temp_a = temp_a << 1;
        }
        
        b >>= 1;
    }
    
    return result;
}

// Function to find multiplicative inverse in GF(2^8) using Extended Euclidean Algorithm
unsigned char gf_inverse(unsigned char byte) {
    if (byte == 0) return 0; // 0 has no inverse
    
    unsigned char a = byte;
    unsigned char b = IRRED_POLY;
    unsigned char x0 = 0, x1 = 1;
    
    if (b == 1) return x1;
    
    while (a > 1) {
        // q = a / b
        unsigned int q = a / b;
        unsigned int t = b;
        
        // b = a mod b
        b = a % b;
        a = t;
        
        // x0 = x1 - q * x0
        t = x0;
        x0 = x1 ^ ((q & 0xFF) * x0); // Using XOR for modulo 2 arithmetic
        x1 = t;
    }
    
    return x1;
}

// Function to find multiplicative inverse using Fermat's Little Theorem
// In GF(2^8), a^(-1) = a^(254)
unsigned char gf_inverse_fermat(unsigned char byte) {
    if (byte == 0) return 0;
    
    unsigned char result = byte;
    
    // Compute byte^254 = byte^(256-2)
    for (int i = 0; i < 6; i++) { // 254 = 11111110 in binary
        result = gf_multiply(result, result);
        result = gf_multiply(result, byte);
    }
    
    result = gf_multiply(result, result);
    return result;
}

// Apply affine transformation (part of S-Box generation)
unsigned char affine_transform(unsigned char byte) {
    unsigned char result = 0;
    unsigned char c = 0x63; // Constant used in AES (01100011)
    
    // Apply bit rotation and XOR with constant
    for (int i = 0; i < 8; i++) {
        unsigned char bit = 0;
        
        // XOR of byte rotated 4 times with itself and constant
        bit ^= ((byte >> i) & 1);
        bit ^= ((byte >> ((i + 1) % 8)) & 1);
        bit ^= ((byte >> ((i + 2) % 8)) & 1);
        bit ^= ((byte >> ((i + 3) % 8)) & 1);
        bit ^= ((byte >> ((i + 4) % 8)) & 1);
        bit ^= ((c >> i) & 1);
        
        result |= (bit << i);
    }
    
    return result;
}

// Generate AES S-Box value for a single byte
unsigned char aes_sbox_byte(unsigned char input) {
    if (input == 0) return 0x63; // Special case: inverse of 0 is undefined, so S[0] = 0x63
    
    // Step 1: Find multiplicative inverse in GF(2^8)
    unsigned char inverse = gf_inverse_fermat(input);
    
    // Step 2: Apply affine transformation
    unsigned char sbox_value = affine_transform(inverse);
    
    return sbox_value;
}

// Print byte in binary format
void print_binary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        cout << ((byte >> i) & 1);
    }
}

// Generate complete AES S-Box table
void generate_full_sbox() {
    unsigned char sbox[256];
    
    cout << "\n====== FULL AES S-BOX TABLE ======\n" << endl;
    
    for (int i = 0; i < 256; i++) {
        sbox[i] = aes_sbox_byte(i);
    }
    
    // Print in table format (16x16)
    cout << "   ";
    for (int x = 0; x < 16; x++) {
        cout << setw(3) << hex << uppercase << x;
    }
    cout << "\n" << endl;
    
    for (int y = 0; y < 16; y++) {
        cout << hex << uppercase << setw(2) << y << ": ";
        for (int x = 0; x < 16; x++) {
            cout << setw(3) << hex << uppercase << (int)sbox[y * 16 + x];
        }
        cout << "\n";
    }
}

int main() {
    unsigned char input_byte;
    
    cout << "====== AES S-BOX GENERATION FOR ONE BYTE ======\n" << endl;
    cout << "AES Irreducible Polynomial: x^8 + x^4 + x^3 + x + 1 (0x11B)\n" << endl;
    
    // Input handling
    cout << "Enter input byte in hexadecimal (0x00 to 0xFF): ";
    cin >> hex >> (int&)input_byte;
    cin.ignore();
    
    cout << "\n" << string(50, '=') << endl;
    cout << "\nINPUT BYTE: 0x" << hex << uppercase << setw(2) << setfill('0') << (int)input_byte;
    cout << " (Binary: ";
    print_binary(input_byte);
    cout << ")\n" << endl;
    
    // Special case
    if (input_byte == 0) {
        cout << "Input byte is 0x00 (zero)" << endl;
        cout << "Multiplicative inverse: UNDEFINED (0 has no inverse in GF(2^8))" << endl;
        cout << "S-Box value (special case): 0x63\n" << endl;
        cout << "====== PROCESS COMPLETE ======\n" << endl;
        
        generate_full_sbox();
        return 0;
    }
    
    // STEP 1: Multiplicative Inverse in GF(2^8)
    cout << "--- STEP 1: MULTIPLICATIVE INVERSE IN GF(2^8) ---\n" << endl;
    unsigned char inverse = gf_inverse_fermat(input_byte);
    cout << "Multiplicative Inverse: 0x" << hex << uppercase << setw(2) << setfill('0') << (int)inverse;
    cout << " (Binary: ";
    print_binary(inverse);
    cout << ")\n" << endl;
    
    // Verify the inverse
    cout << "Verification: 0x" << hex << uppercase << setw(2) << setfill('0') << (int)input_byte 
         << " × 0x" << hex << uppercase << setw(2) << setfill('0') << (int)inverse 
         << " (mod 0x11B) = 0x" << hex << uppercase << setw(2) << setfill('0') 
         << (int)gf_multiply(input_byte, inverse) << " (should be 0x01)\n" << endl;
    
    // STEP 2: Affine Transformation
    cout << "--- STEP 2: AFFINE TRANSFORMATION ---\n" << endl;
    cout << "Affine transformation matrix:\n";
    cout << "Multiply by binary matrix and XOR with constant 0x63\n";
    cout << "Transformation applies bit rotations and XOR operations.\n" << endl;
    
    unsigned char result = affine_transform(inverse);
    cout << "Affine Transform Result: 0x" << hex << uppercase << setw(2) << setfill('0') << (int)result;
    cout << " (Binary: ";
    print_binary(result);
    cout << ")\n" << endl;
    
    // FINAL RESULT
    cout << "--- FINAL RESULT ---\n" << endl;
    unsigned char sbox_value = aes_sbox_byte(input_byte);
    cout << "S-Box[0x" << hex << uppercase << setw(2) << setfill('0') << (int)input_byte 
         << "] = 0x" << hex << uppercase << setw(2) << setfill('0') << (int)sbox_value << endl;
    cout << "Binary: ";
    print_binary(sbox_value);
    cout << "\nDecimal: " << dec << (int)sbox_value << "\n" << endl;
    
    cout << string(50, '=') << endl;
    
    // Generate full S-Box table
    generate_full_sbox();
    
    return 0;
}
