//
//  Question.cpp
//  cppquiz
//
//  Created by Mark Henderson on 8/1/23.
//

#include <string>
#include <unordered_map>

#include "Question.hpp"

std::string Question::format() const
{
    std::string formattedQuestion = question + "\n";
    
    for (size_t i = 0; i < options.size(); ++i) {
        char choice = static_cast<char>('a' + i);
        std::string choiceString(1, choice);
        formattedQuestion += choiceString + ") " + options[i] + "\n";
    }
    
#if DEBUG
    formattedQuestion += "\n\nDebugging Info\n";
    formattedQuestion += "Correct Answer Index: " + std::to_string(answerIndex) + "\n";
    formattedQuestion += "\n****************\n";
#endif
    
    return formattedQuestion;
}

bool Question::checkAnswer(char guess) const
{
    static std::unordered_map<char, int> answerMap
    {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3}
    };
    
    return answerMap[std::tolower(guess)] == answerIndex;
}
