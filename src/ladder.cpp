#include "ladder.h"
#include <algorithm>
#include <unordered_set>


void error(string word1, string word2, string msg) {
    cerr << "Error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

bool edit_distance_within(const string& a, const string& b, int d) {
    const int len_a = a.length();
    const int len_b = b.length();

    if (abs(len_a - len_b) > d) return false;

    if (len_a == len_b) {
        int diff = 0;
        for (int i = 0; i < len_a; ++i)
            if (a[i] != b[i] && ++diff > d) return false;
        return true;
    }
    const string& longer = len_a > len_b ? a : b;
    const string& shorter = len_a > len_b ? b : a;

    size_t i = 0, j = 0;
    int errors = 0;
    while (i < longer.length() && j < shorter.length()) {
        if (longer[i] != shorter[j]) { if (++errors > d) return false; i++;
        } else {i++; j++;}
    }
    return true;
}
  
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return {};
    }

    if (word_list.find(end_word) == word_list.end())
        return {};


    unordered_set<string> dict(word_list.begin(), word_list.end());
    dict.insert(end_word);

    queue<vector<string>> q;
    unordered_set<string> visited;

    q.push({begin_word});
    visited.insert(begin_word);

    while (!q.empty()) {
        vector<string> current_path = q.front();
        q.pop();
        string last_word = current_path.back();

        if (last_word == end_word)
            return current_path;

        vector<string> neighbors;
        for (const auto& word : dict) {
            if (!visited.count(word) && is_adjacent(last_word, word)) {
                if (word_list.count(word) || word == end_word)
                    neighbors.push_back(word);
            }
        }
        sort(neighbors.begin(), neighbors.end());

        for (const auto& word : neighbors) {
            vector<string> new_path = current_path;
            new_path.push_back(word);
            q.push(new_path);
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
    while (file >> word)
        word_list.insert(word);

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

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
