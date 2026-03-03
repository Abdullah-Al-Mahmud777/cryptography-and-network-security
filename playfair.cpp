#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Generate 5x5 matrix
vector<vector<char>> generateMatrix(string key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    vector<bool> used(26, false);

    key.erase(remove(key.begin(), key.end(), ' '), key.end());

    int row = 0, col = 0;

    for (char &c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';

        if (!used[c - 'A']) {
            matrix[row][col++] = c;
            used[c - 'A'] = true;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            matrix[row][col++] = c;
            used[c - 'A'] = true;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    return matrix;
}

// Find position
pair<int, int> findPosition(vector<vector<char>> &matrix, char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c)
                return {i, j};
    return {-1, -1};
}

// Encrypt
string encryptPlayfair(string text, string key) {
    vector<vector<char>> matrix = generateMatrix(key);
    string result = "";

    text.erase(remove(text.begin(), text.end(), ' '), text.end());

    for (int i = 0; i < text.length(); i++) {
        text[i] = toupper(text[i]);
        if (text[i] == 'J') text[i] = 'I';
    }

    for (int i = 0; i < text.length(); i += 2) {
        char a = text[i];
        char b = (i + 1 < text.length()) ? text[i + 1] : 'X';

        if (a == b) {
            b = 'X';
            i--;
        }

        auto pos1 = findPosition(matrix, a);
        auto pos2 = findPosition(matrix, b);

        if (pos1.first == pos2.first) {
            result += matrix[pos1.first][(pos1.second + 1) % 5];
            result += matrix[pos2.first][(pos2.second + 1) % 5];
        }
        else if (pos1.second == pos2.second) {
            result += matrix[(pos1.first + 1) % 5][pos1.second];
            result += matrix[(pos2.first + 1) % 5][pos2.second];
        }
        else {
            result += matrix[pos1.first][pos2.second];
            result += matrix[pos2.first][pos1.second];
        }
    }

    return result;
}

int main() {
    string key, text;

    cout << "Enter Key: ";
    getline(cin, key);

    cout << "Enter Plain Text: ";
    getline(cin, text);

    string encrypted = encryptPlayfair(text, key);

    cout << "Encrypted Text: " << encrypted << endl;

    return 0;
}