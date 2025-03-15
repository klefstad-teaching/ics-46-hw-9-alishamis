#include "ladder.h"
#include <algorithm>
#include <unordered_set>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

// Optimized version of edit distance check for single character changes
bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1.length() != str2.length()) return false;
    int diff_count = 0;
    for (size_t i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i] && ++diff_count > d) {
            return false;
        }
    }
    return diff_count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return {};
    }

    // Convert to unordered_set for O(1) lookups while keeping original parameter type
    unordered_set<string> dict(word_list.begin(), word_list.end());
    if (!dict.count(end_word)) {
        cout << "Error: End word not in dictionary." << endl;
        return {};
    }

    queue<vector<string>> ladder_queue;
    unordered_set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        auto current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();

        // Generate all possible 1-character mutations
        for (size_t i = 0; i < last_word.size(); ++i) {
            string neighbor = last_word;
            for (char c = 'a'; c <= 'z'; ++c) {
                neighbor[i] = c;
                
                // Skip if word doesn't exist or already visited
                if (!dict.count(neighbor) || visited.count(neighbor)) continue;

                // Found the end word
                if (neighbor == end_word) {
                    current_ladder.push_back(neighbor);
                    return current_ladder;
                }

                // Add to queue and mark visited
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(neighbor);
                ladder_queue.push(new_ladder);
                visited.insert(neighbor);
            }
        }
    }

    return {}; // No ladder found
}

// Keep original load_words implementation
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

// Keep original print implementation
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

// Keep original verification implementation
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
