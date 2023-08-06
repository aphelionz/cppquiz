//
//  main.cpp
//  cppquiz
//
//  Created by Mark Henderson on 7/31/23.
//

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>

#include "lib/tinyxml.hpp"

#include "Question.hpp"
#include "chatgpt_api.hpp"

const std::string getQuizTopic();
std::vector<Question> parseXMLString(const std::string& xmlString);
void shuffleQuestionsAndOptions(std::vector<Question>& questions);
std::string stripSlashes(const std::string& input);
std::string escapeQuotes(const std::string& input);

int main() {
    int score = 0;
    
    const std::string quizTopic = getQuizTopic();
    const std::string xmlString = generateQuizXMLString(quizTopic);
    
    try {
        std::vector<Question> questions = parseXMLString(xmlString);
        std::vector<std::string> incorrectAnswers;

        // Shuffle then display the questions
        shuffleQuestionsAndOptions(questions);
        for (const Question& question : questions) {
            char guess;
            
            std::cout << question.format() << "\n";
            
            std::cout << "Your answer: ";
            std::cin >> guess;
            if (question.checkAnswer(guess))
            {
                std::cout << "Correct!\n";
                score++;
            } else {
                std::cout << "Wrong!\n";
                incorrectAnswers.push_back(question.getQuestion());
            }
            std::cout << "\n";
        }
        
        // Print final score
        std::cout << "\nYour score: " << score << "/" << questions.size() << "\n";
        
        if (score == questions.size()) return 0;
        
        std::cout << "\nHere's where you went wrong:" << "\n";
        for (const std::string& incorrectAnswer: incorrectAnswers)
        {
            std::cout << "- " << incorrectAnswer << "\n";
        }

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << "\n";
        return 1;
    }
}

void shuffleQuestionsAndOptions(std::vector<Question>& questions)
{
    std::cout << "Shuffling questions...\n\n";
    std::shuffle(questions.begin(), questions.end(), std::default_random_engine());
    
    for (Question& question: questions)
    {
        std::vector<std::string> options = question.getOptions();
        
        std::string originalAnswerText = options[question.getAnswerIndex()];
        std::shuffle(options.begin(), options.end(), std::default_random_engine());
        std::vector<std::string>::iterator newAnswerIterator = std::find(options.begin(), options.end(), originalAnswerText);
        
        question.setAnswerIndex(std::distance(options.begin(), newAnswerIterator));
        question.setOptions(options);
    }
}

std::string escapeQuotes(const std::string& input) {
    std::string escapedInput = input;
    size_t pos = 0;

    // Find and escape quotation marks
    while ((pos = escapedInput.find("\"", pos)) != std::string::npos) {
        escapedInput.replace(pos, 1, "\\\"");
        pos += 2;  // Move to the next character after the escaped quote
    }

    return escapedInput;
}

std::string stripSlashes(const std::string& input) {
     std::string strippedInput = input;
     size_t pos = 0;

     // Find and remove escaped slashes
     while ((pos = strippedInput.find("\\", pos)) != std::string::npos) {
         strippedInput.erase(pos, 1);
     }

     return strippedInput;
 }

// Side effects, stdout, stdin
const std::string getQuizTopic() {
    std::string quizTopic;
    std::cout << "Hello! What would you like to be quizzed about? ";
    
    // Limit input length to 100 characters
    std::getline(std::cin, quizTopic);
    if (quizTopic.length() > 100) {
        std::cerr << "Warning: Input length exceeded the limit.\n";
        quizTopic = "why it's rude to try and break computer systems";
    }
    
    return escapeQuotes(quizTopic);
}

/*
    XML Format:
 
    <quiz>
      <question>
        <text>Quiz question text goes here.</text>
        <options>
            <option>Option A</option>
            <option>Option B</option>
            <option>Option C</option>
            <option>Option D</option>
        </options>
        <correctAnswer>0</correctAnswer>
      </question>
    </quiz>
 */
std::vector<Question> parseXMLString(const std::string& xmlString) {
    using namespace tinyxml2;
    
    XMLDocument quizXml;
    XMLError xmlError = quizXml.Parse(xmlString.c_str());
    if(xmlError != XML_SUCCESS) {
        std::cerr << "tinyxml2 error: " << xmlError <<"\n";
        throw std::runtime_error("Error ingesting XML, please try again");
    }
    
    XMLElement* root = quizXml.RootElement();
    if (root == nullptr) {
        throw std::runtime_error("Error traversing XML, no root element found.");
    }
    
    std::vector<Question> questions;
    for (XMLElement* questionElement = root->FirstChildElement("question"); questionElement != NULL; questionElement = questionElement->NextSiblingElement("question"))
    {
        XMLElement* questionXML = questionElement->FirstChildElement("text");
        
        std::vector<std::string> options;
        XMLElement* optionsXML = questionElement->FirstChildElement("options");
        for (XMLElement* optionElement = optionsXML->FirstChildElement("option"); optionElement != NULL; optionElement = optionElement->NextSiblingElement("option"))
        {
            options.push_back(stripSlashes(optionElement->GetText()));
        }
        
        XMLElement* answerIndexXML = questionElement->FirstChildElement("correctAnswer");
        
        questions.emplace_back(stripSlashes(questionXML->GetText()), options, answerIndexXML->IntText());
    }
    
    return questions;
}
