#include "ladder.h"
#include <algorithm>
#include <unordered_set>

void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;

    int diff_count = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            diff_count++;
            if (diff_count > 1) return false;  // More than one character differs
        }
    }
    
    return diff_count == 1;  // Exactly one character must differ
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return {}; // Return empty to signal failure
    }

    queue<vector<string>> ladder_queue;
    unordered_set<string> visited;  // Use unordered_set for faster lookup

    ladder_queue.push({begin_word});
    visited.insert(begin_word); // Mark visited immediately

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();  // Process level-by-level

        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for (const auto& word : word_list) {
                // Check if the word is adjacent and not visited
                if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;  // Found the shortest path
                    }

                    ladder_queue.push(new_ladder);
                    visited.insert(word);  // Mark word as visited as soon as it's added
                }
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
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i < ladder.size() - 1) cout << ", ";  // Add commas between words for clarity
        }
        cout << endl;
    }
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) return false;

    std::vector<int> prev(len2 + 1), curr(len2 + 1);  // Only two rows needed

    for (int j = 0; j <= len2; ++j) prev[j] = j;

    for (int i = 1; i <= len1; ++i) {
        curr[0] = i;
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + std::min({prev[j], curr[j - 1], prev[j - 1]});
            }
        }
        prev = curr;  // Move to the next row
    }

    return curr[len2] <= d;
}


void verify_word_ladder() {
    vector<string> test_ladder = {"hit", "hot", "dot", "dog", "cog"};
    bool valid = true;

    for (size_t i = 1; i < test_ladder.size(); ++i) {
        if (!is_adjacent(test_ladder[i - 1], test_ladder[i])) {
            cout << "Invalid transition between: " << test_ladder[i - 1] << " and " << test_ladder[i] << endl;
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
