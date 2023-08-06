#include <gtest/gtest.h>
#include "../src/Question.hpp"



// Test the constructor with same values
TEST(QuestionTests, ConstructorOK) {
    const char questionText[] = "What is the capitol of Massachusetts?";
    std::vector<std::string> options = {};
    int answerIndex = 1;
    
    const Question question(questionText, options, answerIndex);
    
    EXPECT_STREQ(question.getQuestion().c_str(), questionText);
    EXPECT_EQ(question.getOptions().size(), 0);
    EXPECT_EQ(question.getAnswerIndex(), 1);
}

// Test the constructor with same values
TEST(QuestionTests, SettersOK) {
    const char questionText[] = "What is the capitol of Massachusetts?";
    std::vector<std::string> options = {};
    int answerIndex = 1;
    
    Question question(questionText, options, answerIndex);
    
    std::vector<std::string> newOptions = {
        "Boston", "Phoenix", "Atlanta", "Providence"};
    question.setOptions(newOptions);
    question.setAnswerIndex(2);
    
    EXPECT_STREQ(question.getQuestion().c_str(), questionText);
    EXPECT_EQ(question.getOptions().size(), 4);
    EXPECT_EQ(question.getAnswerIndex(), 2);
}

TEST(QuestionTests, DisplayOK) {
    const char questionText[] = "What is the capitol of Massachusetts?";
    std::vector<std::string> options = {
        "Boston", "Phoenix", "Atlanta", "Providence"}
    ;
    int answerIndex = 1;
    
    std::string correctFormatting = R"(What is the capitol of Massachusetts?
a) Boston
b) Phoenix
c) Atlanta
d) Providence
)";
    
    Question question(questionText, options, answerIndex);
    std::string formattedQuestion = question.format();
    
    EXPECT_STREQ(formattedQuestion.c_str(), correctFormatting.c_str());
}


TEST(QuestionTests, CheckAnswerOK) {
    const char questionText[] = "What is the capitol of Massachusetts?";
    std::vector<std::string> options = {};
    int answerIndex = 1;
    
    Question question(questionText, options, answerIndex);

    EXPECT_EQ(question.checkAnswer('a'), false);
    EXPECT_EQ(question.checkAnswer('b'), true);
    EXPECT_EQ(question.checkAnswer('c'), false);
    EXPECT_EQ(question.checkAnswer('d'), false);
}
