//
//  chatgpt_api.hpp
//  cppquiz
//
//  Created by Mark Henderson on 8/2/23.
//

#pragma once

#include <iostream>

#include "Question.hpp"

#ifndef chatgpt_api_hpp
#define chatgpt_api_hpp

std::string generateQuizXMLString(const std::string& quizTopic);
size_t BuildReadBuffer(char *contents, size_t size, size_t nmemb, void *userp);
std::string makeCurlRequest(const std::string& quizTopic);

const std::string OPENAI_API_URL = "https://api.openai.com/v1/chat/completions";

// Note, keep the single space indentation here.
// Do not use double quotes, as this is going to be embedded in a JSON object.
const std::string SYSTEM_PROMPT = R"(You are an XML API, and your purpose is to
 generate questions and answers for a quiz app. The topic of the quiz will be based entirely on user
 input. Please try to be as factual, logical, and concise as possible and think step-by-step about
 how you generate questions.

 Please return only a list of quiz questions and answers in the following XML format with no whitespace, and no newlines. Put all the
 XML on one line - do not use newline or '\n' characters. If your generated text contains naked double-quote characters like \",
 please escape them.
 
 <quiz><question><text>Quiz question text goes here.</text><options><option>Option A</option><option>Option B</option><option>Option C</option><option>Option D</option></options><correctAnswer>0</correctAnswer></question></quiz>

 The 'question' elements contain the full text of the quiz question, the 'options' elements contain an array of exactly
 four tab-separated 'option' elements for the answer choices (three of which are wrong, one is correct), and the 'correctAnswer'
 element contains the zero-indexed index of the correct answer from the 'options' array you generated. Finally, all of the
 <question> items are wrapped in a single encapsulating <quiz> element.

 Please double check to ensure all answers are accurate and factual.
)";

const std::string USER_PROMPT_TEMPLATE = "Please generate an array of 10 quiz questions and answers about ";

#endif /* chatgpt_api_hpp */
