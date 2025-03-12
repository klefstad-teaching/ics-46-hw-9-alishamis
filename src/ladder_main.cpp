#include <iostream>
#include <set>
#include <string>
#include "ladder.h"  

using namespace std;

int main() {
    set<string> word_list; 
    string start_word, end_word;

    load_words(word_list, "words.txt");

    cout << "Enter the start word: ";
    cin >> start_word;
    cout << "Enter the end word: ";
    cin >> end_word;

    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words are the same. Please enter different words.");
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);

    print_word_ladder(ladder);

    return 0;
}
