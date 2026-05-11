#include <iostream>
#include <string>
using namespace std;

// Function to encrypt the plaintext
string encrypt(string text, int key) {
    string result = "";
    for (char c : text) {
        if (isupper(c))
            result += char(int('A') + (int(c) - int('A') + key) % 26);
        else if (islower(c))
            result += char(int('a') + (int(c) - int('a') + key) % 26);
        else
            result += c; // Non-alphabetic characters unchanged
    }
    return result;
}

// Function to decrypt the ciphertext
string decrypt(string text, int key) {
    string result = "";
    for (char c : text) {
        if (isupper(c))
            result += char(int('A') + (int(c) - int('A') - key + 26) % 26);
        else if (islower(c))
            result += char(int('a') + (int(c) - int('a') - key + 26) % 26);
        else
            result += c;
    }
    return result;
}

int main() {
    string plaintext;
    int key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key (1-25): ";
    cin >> key;

    if (key < 1 || key > 25) {
        cout << "Invalid key! Key must be between 1 and 25." << endl;
        return 1;
    }

    string ciphertext = encrypt(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}