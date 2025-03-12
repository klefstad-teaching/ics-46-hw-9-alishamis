#include "ladder.h"
#include <algorithm>
void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return true; // Ensure identical words return true

    int len1 = word1.size();
    int len2 = word2.size();
    
    if (abs(len1 - len2) > 1) return false;
    
    int edit_count = 0, i = 0, j = 0;
    
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            edit_count++;
            if (edit_count > 1) return false;

            if (len1 > len2) {
                i++;  // Extra character in word1
            } else if (len1 < len2) {
                j++;  // Extra character in word2
            } else {
                i++; 
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    
    return edit_count + abs(len1 - i) + abs(len2 - j) == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {begin_word}; // Fixing the single-word case
    }

    queue<vector<string>> ladder_queue;
    set<string> visited; // Track visited words

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size(); // Process level-by-level to avoid unnecessary visits
        set<string> words_to_mark;  // Words to mark visited after this level

        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for (const auto& word : word_list) {
                if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder; // Exit immediately upon finding the solution
                    }

                    ladder_queue.push(new_ladder);
                    words_to_mark.insert(word); // Only mark words at the end of this level
                }
            }
        }

        for (const auto& word : words_to_mark) {
            visited.insert(word);
        }
    }

    return {};
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
        cout << "No word ladder found." << endl;  // Fix wording
    } else {
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false;

    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));


    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0)
                dp[i][j] = j;  // Insertions
            else if (j == 0)
                dp[i][j] = i;  // Deletions
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];  // Match
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});  // Edit
        }
    }
    
    return dp[len1][len2] <= d;
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