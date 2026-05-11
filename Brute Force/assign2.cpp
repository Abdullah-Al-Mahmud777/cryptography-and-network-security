#include <iostream>
#include <string>
using namespace std;

// Function to decrypt the ciphertext with a given key
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
    string ciphertext;
    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    cout << "\nBrute force results:\n";
    for (int key = 1; key <= 25; ++key) {
        string decrypted = decrypt(ciphertext, key);
        cout << "Key " << key << ": " << decrypted << endl;
    }
    return 0;
}