#include "ladder.h"


void error(string word1, string word2, string msg){
    cerr << "error between words: " << word1 << " and " << word2 << ". " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.length();
    int len2 = str2.length();

    if(abs(len1 - len2) > d)
        return false;

    int e = 0;
    int i =0, j = 0;

    while(i < len1 && j < len2){
        if(str1[i] != str2[j]){
            e++;
            if(e > d)
                return false;
        }

    if(len1 > len2){i++;} 
    else if(len1 < len2) {j++;}
    else {i++; j++;}

    }

    e += abs(len1- i);
    e += abs(len2 - j);

    return e <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (abs(static_cast<int>(word1.size()) - static_cast<int>(word2.size())) > 1)
        return false;

    int edit_count = 0;
    int i = 0, j = 0;
    
    while (i < word1.size() && j < word2.size()) {
        if (word1[i] != word2[j]) {
            edit_count++;
            if (edit_count > 1) return false;
            if (word1.size() > word2.size()) {
                i++;
            } else if (word1.size() < word2.size()) {
                j++;
            } else {
                i++; j++;
            }
        } else {
            i++;
            j++;
        }
    }
    
    edit_count += abs(static_cast<int>(word1.size()) - static_cast<int>(word2.size()));
    
    return edit_count == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {begin_word};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if(!file.is_open()){
        cerr << "error: unable to open file" << file_name << endl;
        return;
    }

    string word;

    while(file >> word)
        word_list.insert(word);

    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
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
        if (!is_adjacent(test_ladder[i-1], test_ladder[i])) {
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


