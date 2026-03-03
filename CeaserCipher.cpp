// The Caesar Cipher also known as the shift cipher is one of the simplest and most widely known encryption technique in which each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet .
#include <iostream> 
#include <string> 
using namespace std; 
 
// Function to encrypt plaintext using Caesar Cipher 
string encrypt(const string& text, int key) { 
    string result = ""; 
    key = key % 26; // Normalize the key to ensure it's within the range [0, 25] 
 
    for (char ch : text) { 
        if (isupper(ch)) { 
            // Encrypt uppercase letters 
            result += char((ch - 'A' + key) % 26 + 'A'); 
        } else if (islower(ch)) { 
            // Encrypt lowercase letters 
            result += char((ch - 'a' + key) % 26 + 'a'); 
        } else { 
            // Leave non-alphabet characters unchanged 
            result += ch; 
        } 
    } 
 
    return result; 
} 
 
// Function to decrypt ciphertext using Caesar Cipher 
string decrypt(const string& text, int key) { 
    return encrypt(text, 26 - (key % 26)); // Reverse the shift for decryption 
} 
 
// Main driver function 
int main() { 
    string plaintext; 
    int key; 
 
    cout << "Enter the plaintext: "; 
    getline(cin, plaintext); 
 
    cout << "Enter the key (shift value): ";  
    cin >> key;

        string cipherText = encrypt(plaintext, key); 
    string decryptedText = decrypt(cipherText, key); 
 
    cout << "\nEncrypted Text: " << cipherText << endl; 
    cout << "Decrypted Text: " << decryptedText << endl; 
 
    return 0; 
} 