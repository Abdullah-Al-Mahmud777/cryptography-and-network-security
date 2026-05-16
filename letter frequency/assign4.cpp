#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    string ciphertext;
    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    vector<int> freq(26, 0);
    int total_letters = 0;

    // Count frequency
    for (char c : ciphertext) {
        if (isalpha(c)) {
            c = toupper(c);
            freq[c - 'A']++;
            total_letters++;
        }
    }

    // Display frequency count and percentage
    cout << "\nLetter\tCount\tPercentage\n";
    for (int i = 0; i < 26; ++i) {
        double percent = total_letters ? (freq[i] * 100.0 / total_letters) : 0;
        cout << char('A' + i) << "\t" << freq[i] << "\t" << fixed << setprecision(2) << percent << "%\n";
    }

    // Find top 5 most frequent letters
    vector<pair<char, int>> freqList;
    for (int i = 0; i < 26; ++i)
        freqList.push_back({char('A' + i), freq[i]});
    sort(freqList.begin(), freqList.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    cout << "\nTop 5 most frequent letters:\n";
    for (int i = 0; i < 5; ++i)
        cout << freqList[i].first << " (" << freqList[i].second << ")\n";

    return 0;
}