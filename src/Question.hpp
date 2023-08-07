//
//  Question.h
//  cppquiz
//
//  Created by Mark Henderson on 8/1/23.
//

#pragma once

#include <vector>

#ifndef Question_h
#define Question_h

class Question
{
public:
    Question(const std::string& q, const std::vector<std::string>& opts, size_t answerIndex) :
        question(q), options(opts), answerIndex(answerIndex) {};

    size_t getAnswerIndex() const { return answerIndex; }
    std::vector<std::string> getOptions() const { return options; };
    std::string getQuestion() const { return question; };

    void setAnswerIndex(size_t newAnswerIndex) { answerIndex = newAnswerIndex; };
    void setOptions(std::vector<std::string>& newOptions) { options = newOptions; };

    std::string format() const;
    bool checkAnswer (char guess) const;
private:
    std::string question;
    std::vector<std::string> options;
    size_t answerIndex;
};

#endif /* Question_h */
