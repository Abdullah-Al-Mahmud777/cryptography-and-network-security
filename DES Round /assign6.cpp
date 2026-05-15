#include <iostream>
#include <bitset>
#include <string>
#include <iomanip>
using namespace std;

// Initial Permutation Table (IP)
int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Expansion Permutation Table (E)
int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// S-box tables
int S1[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 0, 5},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

int S2[4][16] = {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 15, 3, 12, 0},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
};

int S3[4][16] = {
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
};

int S4[4][16] = {
    {7, 13, 14, 3, 4, 15, 2, 8, 1, 6, 11, 5, 0, 12, 10, 9},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
};

int S5[4][16] = {
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 2, 10, 1, 7, 6, 4, 10, 13, 15, 3, 12, 0, 5}
};

int S6[4][16] = {
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
};

int S7[4][16] = {
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 5, 12, 1, 2, 15, 3, 10, 14, 4, 7, 6, 9, 8},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    {6, 11, 13, 8, 1, 4, 10, 7, 4, 2, 14, 15, 12, 3, 8, 0}
};

int S8[4][16] = {
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 6, 11, 13, 0, 5, 3, 4, 9, 15, 10, 8, 12}
};

// P-box Permutation
int P[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Function to perform permutation
bitset<64> permute(bitset<64> input, int* table, int size) {
    bitset<64> output;
    for (int i = 0; i < size; i++) {
        output[size - 1 - i] = input[64 - table[i]];
    }
    return output;
}

// Function for expansion permutation
bitset<48> expandPermute(bitset<32> input) {
    bitset<48> output;
    for (int i = 0; i < 48; i++) {
        output[47 - i] = input[32 - E[i]];
    }
    return output;
}

// Function for S-box substitution
bitset<32> sBoxSubstitution(bitset<48> input) {
    bitset<32> output;
    int S_tables[8][4][16];
    
    // Copy all S-boxes
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 16; j++) {
            S_tables[0][i][j] = S1[i][j];
            S_tables[1][i][j] = S2[i][j];
            S_tables[2][i][j] = S3[i][j];
            S_tables[3][i][j] = S4[i][j];
            S_tables[4][i][j] = S5[i][j];
            S_tables[5][i][j] = S6[i][j];
            S_tables[6][i][j] = S7[i][j];
            S_tables[7][i][j] = S8[i][j];
        }
    }
    
    // Process each 6-bit block
    for (int i = 0; i < 8; i++) {
        // Extract 6 bits from input
        int bit_pos = 47 - (i * 6);
        int row = (input[bit_pos] << 1) | input[bit_pos - 5];
        int col = (input[bit_pos - 1] << 3) | (input[bit_pos - 2] << 2) | 
                  (input[bit_pos - 3] << 1) | input[bit_pos - 4];
        
        // Get 4-bit output from S-box
        int s_output = S_tables[i][row][col];
        
        // Place 4-bit output in result
        for (int j = 0; j < 4; j++) {
            output[31 - (i * 4 + j)] = (s_output >> (3 - j)) & 1;
        }
    }
    
    return output;
}

// Function for P-box permutation
bitset<32> pBoxPermute(bitset<32> input) {
    bitset<32> output;
    for (int i = 0; i < 32; i++) {
        output[31 - i] = input[32 - P[i]];
    }
    return output;
}

// Print bitset in groups for readability
void printBits(bitset<64> bits, string label) {
    cout << label << ": ";
    for (int i = 0; i < 64; i++) {
        cout << bits[63 - i];
        if ((i + 1) % 8 == 0 && i != 63) cout << " ";
    }
    cout << endl;
}

void printBits32(bitset<32> bits, string label) {
    cout << label << ": ";
    for (int i = 0; i < 32; i++) {
        cout << bits[31 - i];
        if ((i + 1) % 8 == 0 && i != 31) cout << " ";
    }
    cout << endl;
}

void printBits48(bitset<48> bits, string label) {
    cout << label << ": ";
    for (int i = 0; i < 48; i++) {
        cout << bits[47 - i];
        if ((i + 1) % 8 == 0 && i != 47) cout << " ";
    }
    cout << endl;
}

int main() {
    cout << "====== DES ENCRYPTION - SINGLE ROUND DEMONSTRATION ======\n" << endl;
    
    // Sample 64-bit plaintext block (8 bytes)
    bitset<64> plaintext(0x0123456789ABCDEFULL);
    cout << "Plaintext (hex): 0123456789ABCDEF\n" << endl;
    
    printBits(plaintext, "Plaintext (binary)");
    
    // ============================================================
    // STEP 1: INITIAL PERMUTATION (IP)
    // ============================================================
    cout << "\n--- STEP 1: INITIAL PERMUTATION (IP) ---\n" << endl;
    bitset<64> ip_output = permute(plaintext, IP, 64);
    printBits(ip_output, "After IP");
    
    // ============================================================
    // STEP 2: SPLIT INTO LEFT AND RIGHT HALVES
    // ============================================================
    cout << "\n--- STEP 2: SPLIT INTO LEFT AND RIGHT HALVES ---\n" << endl;
    
    bitset<32> L0, R0;
    for (int i = 0; i < 32; i++) {
        L0[i] = ip_output[i + 32];
        R0[i] = ip_output[i];
    }
    
    printBits32(L0, "Left Half  (L0)");
    printBits32(R0, "Right Half (R0)");
    
    // ============================================================
    // STEP 3: EXPANSION PERMUTATION ON RIGHT HALF
    // ============================================================
    cout << "\n--- STEP 3: EXPANSION PERMUTATION (E-BOX) ---\n" << endl;
    bitset<48> expanded = expandPermute(R0);
    printBits48(expanded, "Expanded Right Half");
    
    // ============================================================
    // STEP 4: XOR WITH ROUND KEY
    // ============================================================
    cout << "\n--- STEP 4: XOR WITH ROUND KEY ---\n" << endl;
    
    // Sample 48-bit round key
    bitset<48> roundKey(0xAABBCCDDEE00ULL);
    cout << "Round Key (hex): AABBCCDDEE00FF11\n";
    printBits48(roundKey, "Round Key (binary)");
    
    bitset<48> xor_result = expanded ^ roundKey;
    printBits48(xor_result, "After XOR");
    
    // ============================================================
    // STEP 5: S-BOX SUBSTITUTION
    // ============================================================
    cout << "\n--- STEP 5: S-BOX SUBSTITUTION ---\n" << endl;
    bitset<32> sbox_output = sBoxSubstitution(xor_result);
    printBits32(sbox_output, "After S-box Substitution");
    
    // ============================================================
    // STEP 6: P-BOX PERMUTATION
    // ============================================================
    cout << "\n--- STEP 6: P-BOX PERMUTATION ---\n" << endl;
    bitset<32> pbox_output = pBoxPermute(sbox_output);
    printBits32(pbox_output, "After P-box Permutation");
    
    // ============================================================
    // FINAL XOR WITH LEFT HALF
    // ============================================================
    cout << "\n--- FINAL: XOR WITH LEFT HALF ---\n" << endl;
    bitset<32> R1 = L0 ^ pbox_output;
    bitset<32> L1 = R0;  // L becomes the previous R
    
    printBits32(L1, "L1 (previous R0)");
    printBits32(R1, "R1 (L0 XOR F(R0, K))");
    
    // Combine for final output
    bitset<64> final_output;
    for (int i = 0; i < 32; i++) {
        final_output[i] = R1[i];
        final_output[i + 32] = L1[i];
    }
    
    cout << "\n--- FINAL OUTPUT ---\n";
    printBits(final_output, "After One Round");
    
    cout << "\n====== DES ROUND COMPLETE ======\n" << endl;
    
    return 0;
}
