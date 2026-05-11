#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// Function to prepare the key matrix
void generateKeyMatrix(string key, char keyMatrix[5][5]) {
    string result = "";
    vector<bool> used(26, false);

    // Treat I and J as the same
    for (char &c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (!used[c - 'A'] && isalpha(c)) {
            result += c;
            used[c - 'A'] = true;
            if (c == 'I') used['J' - 'A'] = true;
        }
    }
    // Fill remaining letters
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            result += c;
            used[c - 'A'] = true;
        }
    }
    // Fill keyMatrix
    int idx = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            keyMatrix[i][j] = result[idx++];
}

// Find position of a character in the key matrix
void findPosition(char keyMatrix[5][5], char c, int &row, int &col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (keyMatrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
}

// Prepare plaintext: pairs, insert X, handle odd length
string preparePlaintext(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            result += c;
        }
    }
    string prepared = "";
    for (size_t i = 0; i < result.length(); ++i) {
        prepared += result[i];
        if (i + 1 < result.length()) {
            if (result[i] == result[i + 1]) {
                prepared += 'X';
            }
        }
    }
    if (prepared.length() % 2 != 0)
        prepared += 'X';
    return prepared;
}

// Encrypt a pair
string encryptPair(char a, char b, char keyMatrix[5][5]) {
    int r1, c1, r2, c2;
    findPosition(keyMatrix, a, r1, c1);
    findPosition(keyMatrix, b, r2, c2);
    if (r1 == r2)
        return string(1, keyMatrix[r1][(c1 + 1) % 5]) + keyMatrix[r2][(c2 + 1) % 5];
    else if (c1 == c2)
        return string(1, keyMatrix[(r1 + 1) % 5][c1]) + keyMatrix[(r2 + 1) % 5][c2];
    else
        return string(1, keyMatrix[r1][c2]) + keyMatrix[r2][c1];
}

// Decrypt a pair
string decryptPair(char a, char b, char keyMatrix[5][5]) {
    int r1, c1, r2, c2;
    findPosition(keyMatrix, a, r1, c1);
    findPosition(keyMatrix, b, r2, c2);
    if (r1 == r2)
        return string(1, keyMatrix[r1][(c1 + 4) % 5]) + keyMatrix[r2][(c2 + 4) % 5];
    else if (c1 == c2)
        return string(1, keyMatrix[(r1 + 4) % 5][c1]) + keyMatrix[(r2 + 4) % 5][c2];
    else
        return string(1, keyMatrix[r1][c2]) + keyMatrix[r2][c1];
}

int main() {
    string key, plaintext;
    char keyMatrix[5][5];

    cout << "Enter keyword: ";
    getline(cin, key);

    generateKeyMatrix(key, keyMatrix);

    cout << "\nPlayfair Key Matrix:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            cout << keyMatrix[i][j] << " ";
        cout << endl;
    }

    cout << "\nEnter plaintext: ";
    getline(cin, plaintext);

    string prepared = preparePlaintext(plaintext);
    cout << "\nPrepared plaintext: " << prepared << endl;

    // Encrypt
    string ciphertext = "";
    for (size_t i = 0; i < prepared.length(); i += 2)
        ciphertext += encryptPair(prepared[i], prepared[i + 1], keyMatrix);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decrypt
    string decrypted = "";
    for (size_t i = 0; i < ciphertext.length(); i += 2)
        decrypted += decryptPair(ciphertext[i], ciphertext[i + 1], keyMatrix);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}