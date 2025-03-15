#include "ladder.h"
#include <algorithm>
#include <unordered_set>


void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

bool edit_distance_within(const string& a, const string& b, int d) {
    const int len_a = a.length();
    const int len_b = b.length();

    // Early exit for large length differences
    if (abs(len_a - len_b) > d) return false;

    // Handle same-length substitution or identical words
    if (len_a == len_b) {
        int diff = 0;
        for (int i = 0; i < len_a; ++i) {
            if (a[i] != b[i] && ++diff > d) return false;
        }
        return true; // Identical words or within substitution distance
    }

    // Handle insertion/deletion (length difference 1)
    const string& longer = len_a > len_b ? a : b;
    const string& shorter = len_a > len_b ? b : a;

    int i = 0, j = 0, errors = 0;
    while (i < longer.length() && j < shorter.length()) {
        if (longer[i] != shorter[j]) {
            if (++errors > d) return false;
            i++; // Skip one character in longer string
        } else {
            i++;
            j++;
        }
    }
    return true;
}
  

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;
    int diff = 0;
    for (size_t i = 0; i < word1.length(); i++) {
        if (word1[i] != word2[i] && ++diff > 1) return false;
    }
    return diff == 1;
}



vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return {};
    }

    unordered_set<string> dict(word_list.begin(), word_list.end());
    dict.insert(end_word); // Ensure end_word is considered

    queue<vector<string>> q;
    unordered_set<string> visited;

    q.push({begin_word});
    visited.insert(begin_word);

    while (!q.empty()) {
        vector<string> current_path = q.front();
        q.pop();
        string current_word = current_path.back();

        // Only allow single-letter substitutions
        for (int i = 0; i < current_word.length(); i++) {
            string new_word = current_word;
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == current_word[i]) continue;
                new_word[i] = c;
                if (dict.count(new_word) && !visited.count(new_word)) {
                    vector<string> new_path = current_path;
                    new_path.push_back(new_word);
                    if (new_word == end_word) return new_path;
                    q.push(new_path);
                    visited.insert(new_word);
                }
            }
        }
    }

    return {}; // No ladder found
}


// Keep original implementations below (unchanged)
void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }

    string word;
    while (file >> word) {
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
