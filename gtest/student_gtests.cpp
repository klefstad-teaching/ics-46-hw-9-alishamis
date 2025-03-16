#include <gtest/gtest.h>
#include <vector>
#include "dijkstras.h"
#include "ladder.h"



class LadderTest : public ::testing::Test {
protected:
    set<string> word_list;

    virtual void SetUp() {
        word_list = {"cat", "cot", "dog", "dot", "cog", "log", "lot"};
    }
};

TEST_F(LadderTest, TestWordLadder) {
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    
    // The expected ladder: cat -> cot -> dot -> dog
    EXPECT_EQ(ladder.size(), 4);
    EXPECT_EQ(ladder[0], "cat");
    EXPECT_EQ(ladder[1], "cot");
    EXPECT_EQ(ladder[2], "cog");
    EXPECT_EQ(ladder[3], "dog");
}

TEST_F(LadderTest, TestNoPath) {
    vector<string> ladder = generate_word_ladder("cat", "fish", word_list);
    
    // No ladder should exist between cat and fish
    EXPECT_TRUE(ladder.empty());
}

TEST_F(LadderTest, TestIdenticalStartAndEnd) {
    vector<string> ladder = generate_word_ladder("cat", "cat", word_list);

    // Should print error, and return empty ladder
    EXPECT_TRUE(ladder.empty());
}

TEST_F(LadderTest, TestEmptyDictionary) {
    set<string> empty_word_list;
    vector<string> ladder = generate_word_ladder("cat", "dog", empty_word_list);
    
    // Should return an empty ladder since no words are in the dictionary
    EXPECT_TRUE(ladder.empty());
}

