#include "ladder.h"
#include <unordered_set>


void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

// Fixed edit distance check (handles insertions/deletions/substitutions)
bool edit_distance_within(const string& a, const string& b, int d) {
    if (d != 1) return false; // Only handle d=1 per problem requirements
    
    const int len_a = a.length();
    const int len_b = b.length();
    
    // Handle same-length substitution
    if (len_a == len_b) {
        int diff = 0;
        for (int i = 0; i < len_a; ++i) {
            if (a[i] != b[i] && ++diff > 1) return false;
        }
        return diff == 1;
    }
    
    // Handle insertion/deletion (length difference 1)
    if (abs(len_a - len_b) != 1) return false;
    
    const string& longer = len_a > len_b ? a : b;
    const string& shorter = len_a > len_b ? b : a;
    
    int i = 0, j = 0, errors = 0;
    while (i < longer.length() && j < shorter.length()) {
        if (longer[i] != shorter[j]) {
            if (++errors > 1) return false;
            i++; // Skip one character in longer string
        } else {
            i++;
            j++;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return {};
    }

    // Convert to unordered_set for O(1) lookups
    unordered_set<string> dict(word_list.begin(), word_list.end());
    dict.insert(end_word); // Ensure end_word is considered
    
    queue<vector<string>> q;
    unordered_set<string> visited;
    
    q.push({begin_word});
    visited.insert(begin_word);
    
    while (!q.empty()) {
        int level_size = q.size();
        
        for (int i = 0; i < level_size; ++i) {
            vector<string> current_path = q.front();
            q.pop();
            string current_word = current_path.back();
            
            // Generate all possible mutations
            for (int pos = 0; pos <= current_word.length(); ++pos) {
                // Insertions
                for (char c = 'a'; c <= 'z'; ++c) {
                    string inserted = current_word.substr(0, pos) + c + current_word.substr(pos);
                    if (dict.count(inserted) && !visited.count(inserted)) {
                        vector<string> new_path = current_path;
                        new_path.push_back(inserted);
                        if (inserted == end_word) return new_path;
                        q.push(new_path);
                        visited.insert(inserted);
                    }
                }
                
                // Deletions (skip if word becomes empty)
                if (pos < current_word.length()) {
                    string deleted = current_word.substr(0, pos) + current_word.substr(pos + 1);
                    if (!deleted.empty() && dict.count(deleted) && !visited.count(deleted)) {
                        vector<string> new_path = current_path;
                        new_path.push_back(deleted);
                        if (deleted == end_word) return new_path;
                        q.push(new_path);
                        visited.insert(deleted);
                    }
                }
                
                // Substitutions
                if (pos < current_word.length()) {
                    string substituted = current_word;
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == substituted[pos]) continue;
                        substituted[pos] = c;
                        if (dict.count(substituted) && !visited.count(substituted)) {
                            vector<string> new_path = current_path;
                            new_path.push_back(substituted);
                            if (substituted == end_word) return new_path;
                            q.push(new_path);
                            visited.insert(substituted);
                        }
                    }
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
