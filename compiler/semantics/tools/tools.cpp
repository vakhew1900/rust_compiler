//
// Created by T0mmy on 27.11.2023.
//
#include "tools.h"

vector<string> split(string &str, char separator) {
    vector<string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            if(temp.size())
            {
                strings.push_back(temp);
            }
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

string Exception::getMessage() {
    return message;
}

Exception::Exception(ExceptionType exceptionType, string message) {
    this->exceptionType = exceptionType;
    this->message = message;
}


