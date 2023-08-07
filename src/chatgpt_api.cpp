//
//  chatgpt_api.cpp
//  cppquiz
//
//  Created by Mark Henderson on 8/2/23.
//

#include <iostream>
#include <algorithm>
#include <curl/curl.h>

#include "chatgpt_api.hpp"
#include "Question.hpp"

size_t BuildReadBuffer(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string makeCurlRequest(const std::string& quizTopic)
{
    const std::string OPENAI_API_KEY = getenv("OPENAI_API_KEY");
    std::cout << "Calling OpenAI, please wait... ";

    const long CURLOPT_LONG_TRUE = 1L;
    // const long CURLOPT_LONG_FALSE = 0L;
    
    curl_global_init( CURL_GLOBAL_ALL );
    CURL *curl = curl_easy_init();

    if(curl)
    {
        struct curl_slist *headerlist=NULL;
        std::string readBuffer;
        
        headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
        headerlist = curl_slist_append(headerlist, ("Authorization: Bearer " + OPENAI_API_KEY).c_str());
        curl_easy_setopt(curl, CURLOPT_URL, OPENAI_API_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_POST, CURLOPT_LONG_TRUE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, BuildReadBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        std::string sanitizedSystemPrompt = SYSTEM_PROMPT;
        sanitizedSystemPrompt.erase(std::remove(sanitizedSystemPrompt.begin(), sanitizedSystemPrompt.end(), '\n'), sanitizedSystemPrompt.cend());
        std::string data = R"(
        {
        "model": "gpt-3.5-turbo",
        "messages": [
        {
        "role": "system",
        "content": ")" + sanitizedSystemPrompt + R"("
        },
        {
        "role": "user",
        "content": ")" + USER_PROMPT_TEMPLATE + quizTopic + R"(."
      }
    ]
  }
)";
        
#if DEBUG
        std::cout << data << "\n";
#endif
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.5");
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, CURLOPT_LONG_TRUE);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, CURLOPT_LONG_TRUE);
        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(headerlist);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        std::string cURLString = curl_easy_strerror(res);
        if(res != CURLE_OK) {
            throw std::runtime_error(cURLString);
        }
        std::cout << "done.\n";
        return(readBuffer);
    } else {
        curl_global_cleanup();
        throw std::runtime_error("\nError: Could not initialize cURL. Please install cURL.");
    }
}

std::string generateQuizXMLString(const std::string& quizTopic)
{
    static std::string xmlSnippet;
    std::string response = makeCurlRequest(quizTopic);
    
    // Search for "content": "
    size_t startIndex = response.find("\"content\": \"");
    startIndex += 12;

    // Search for the next " and newline after that
    size_t endIndex = response.find("\"\n", startIndex);
            
    // Grab what's in between it and parse it as xml
    xmlSnippet = response.substr(startIndex, (endIndex - startIndex));

#if DEBUG
    std::cout << "xmlString: " << xmlSnippet << "\n";
#endif

    return xmlSnippet;
}
