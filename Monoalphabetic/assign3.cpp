#include <iostream>
#include <string>
#include <map>
using namespace std;

// Fixed substitution key (A-Z mapped to a shuffled alphabet)
const string key = "QWERTYUIOPASDFGHJKLZXCVBNM";

// Function to create the substitution table
map<char, char> createSubstitutionTable() {
    map<char, char> table;
    for (int i = 0; i < 26; ++i) {
        table['A' + i] = key[i];
        table['a' + i] = tolower(key[i]);
    }
    return table;
}

// Function to create the inverse substitution table
map<char, char> createInverseTable() {
    map<char, char> table;
    for (int i = 0; i < 26; ++i) {
        table[key[i]] = 'A' + i;
        table[tolower(key[i])] = 'a' + i;
    }
    return table;
}

// Encrypt function
string encrypt(const string& plaintext, const map<char, char>& table) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c))
            ciphertext += table.at(c);
        else
            ciphertext += c;
    }
    return ciphertext;
}

// Decrypt function
string decrypt(const string& ciphertext, const map<char, char>& invTable) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c))
            plaintext += invTable.at(c);
        else
            plaintext += c;
    }
    return plaintext;
}

int main() {
    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    // Create tables
    auto subTable = createSubstitutionTable();
    auto invTable = createInverseTable();

    // Show substitution table
    cout << "\nSubstitution Table:\n";
    for (int i = 0; i < 26; ++i)
        cout << char('A' + i) << " -> " << key[i] << "   ";
    cout << endl;

    // Encrypt
    string ciphertext = encrypt(plaintext, subTable);
    cout << "\nEncrypted text: " << ciphertext << endl;

    // Decrypt
    string decrypted = decrypt(ciphertext, invTable);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}