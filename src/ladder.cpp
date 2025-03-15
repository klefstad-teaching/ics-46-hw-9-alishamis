#include "ladder.h"
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

// Check if two words are neighbors (differ by exactly one substitution, insertion, or deletion)
bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.length();
    int len2 = word2.length();

    // Handle substitutions (same length)
    if (len1 == len2) {
        int diff_count = 0;
        for (size_t i = 0; i < len1; ++i) {
            if (word1[i] != word2[i]) {
                if (++diff_count > 1) return false;
            }
        }
        return diff_count == 1;
    }

    // Handle insertions/deletions (length difference = 1)
    if (abs(len1 - len2) == 1) {
        const string& longer = len1 > len2 ? word1 : word2;
        const string& shorter = len1 > len2 ? word2 : word1;

        size_t i = 0, j = 0;
        bool diff_found = false;
        while (i < longer.length() && j < shorter.length()) {
            if (longer[i] != shorter[j]) {
                if (diff_found) return false;
                diff_found = true;
                i++; // Skip one character in longer string
            } else {
                i++;
                j++;
            }
        }
        return true; // Valid insertion/deletion
    }

    return false; // Length difference > 1
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return {};
    }

    unordered_set<string> dict(word_list.begin(), word_list.end());
    dict.insert(end_word); // Ensure end_word is considered

    queue<vector<string>> ladder_queue; // Queue of ladders
    unordered_set<string> visited;      // Track visited words

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();

        // Explore neighbors of last_word
        for (const auto& word : dict) {
            if (!visited.count(word) && is_adjacent(last_word, word)) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);

                if (word == end_word) return new_ladder;

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }

    return {}; // No ladder found
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }

    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert to lowercase
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    vector<string> test_ladder = {"hit", "hot", "dot", "dog", "cog"};
    bool valid = true;

    for (size_t i = 1; i < test_ladder.size(); ++i) {
        if (!is_adjacent(test_ladder[i - 1], test_ladder[i])) {
            valid = false;
            break;
        }
    }

    if (valid) {
        cout << "The word ladder is valid." << endl;
    } else {
        cout << "The word ladder is not valid." << endl;
    }
}
