#pragma once
#include "token.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <set>

class Scanner {
    public:
    Scanner(const string& input) : input(input) { }

    vector <Token> scanToken() {
        // TokenType type = COMMA;
        // string value = ",";
        // int line = 4;
        
        // remove_whitespace();
        int numb_lines= 1;

        //checks if input is not empty
        if(input.empty()){
            tokens.push_back(Token(END_OF_FILE, "", numb_lines));
        }
        for(int i = 0; i < input.length(); i++) {
            if(input.at(i) == '\n') {
                    numb_lines++;
            } 
            if (i == input.length()-1) {
                tokens.push_back(Token(END_OF_FILE, "", numb_lines));
            }
            
            else if(isspace(input.at(i))) {
                continue;
            }
            else if(input.at(i) == ',') {
                tokens.push_back(Token(COMMA, ",", numb_lines));
            }
            //id, facts, queries, schemes, rules, the one you always confuse with strings
            else if(isalpha(input.at(i))) {
                string full_word;
                while(i < input.length() && isalnum(input.at(i))) {
                    full_word += input.at(i);
                    i++;
                }
                i--;
                if(full_word == "Schemes") {
                    tokens.push_back(Token(SCHEMES, full_word, numb_lines));
                }
                else if(full_word == "Queries") {
                    tokens.push_back(Token(QUERIES,"Queries", numb_lines));
                }
                else if(full_word == "Facts") {
                    tokens.push_back(Token(FACTS,"Facts", numb_lines));
                }
                else if(full_word == "Rules") {
                    tokens.push_back(Token(RULES,"Rules", numb_lines));
                }
                else {
                    tokens.push_back(Token(ID, full_word, numb_lines));
                }
            }

            else if (input.at(i) == '.') {
                tokens.push_back(Token(PERIOD, ".", numb_lines));
            }
            else if(input.at(i) == '?') {
                tokens.push_back(Token(Q_MARK, "?", numb_lines));
            }
            else if(input.at(i) == '(') {
                tokens.push_back(Token(LEFT_PAREN, "(", numb_lines));
            }
            else if(input.at(i) == ')') {
                tokens.push_back(Token(RIGHT_PAREN, ")", numb_lines));
            }
            else if(input.at(i) == ':') {
                if(input.at(i+1) == '-') {
                    tokens.push_back(Token(COLON_DASH, ":-", numb_lines));
                    i++;
                }
                else {
                    tokens.push_back(Token(COLON, ":", numb_lines));
                }
            }
            else if(input.at(i) == '*') {
                tokens.push_back(Token(MULTIPLY, "*", numb_lines));
            }
            else if(input.at(i) == '+') {
                tokens.push_back(Token(ADD, "+", numb_lines));
            }
            //comments, commented out to fulfil parser
             else if(input.at(i) == '#') {
                 string full_comment;
                 if(input.at(i+1) == '|'){
                     i+=2;
                     while(input.at(i) < input.length() && input.at(i) != '|'){
                         if(input.at(i) == '\n'){
                             numb_lines++;
                         }
                         full_comment += input.at(i);
                         i++;
                     }
                     tokens.push_back(Token(COMMENT, full_comment, numb_lines));
                 }
                 else{
                     while(i < input.length() && input.at(i) != '\n'){
                         full_comment += input.at(i);
                         i++;
                     }
                     tokens.push_back(Token(COMMENT, full_comment, numb_lines));
                     numb_lines++;
                 }
             }


            //stringname strings 
        
            else if (input.at(i) == '\"' || input.at(i) == '\'') {
                string word_with_qmarks;
                int e_lines = 0;
                char opening_quote = input.at(i);
                word_with_qmarks += opening_quote;

                while (i+1 < input.length() && input.at(i+1) != opening_quote) {
                    i++; // Advance i first to skip the opening quote
                    word_with_qmarks += input.at(i);
                    if(input.at(i) == '\n') {
                        e_lines++;
                    }

                }
                if (i + 1 < input.length() && input.at(i + 1) == opening_quote) {
                    i++; // Advance i to skip the closing quote
                }
                if(i+1 >= input.length()){
                    tokens.push_back(Token(UNDEFINED, word_with_qmarks, numb_lines));
                    tokens.push_back(Token(END_OF_FILE, "", numb_lines + e_lines));
                }
                else{
                    word_with_qmarks += opening_quote;
                    tokens.push_back(Token(STRING, word_with_qmarks, numb_lines));

                }

            }

            else {
                string nonexistent;
                nonexistent = input.at(i);
                tokens.push_back(Token(UNDEFINED,nonexistent, numb_lines));
            }
        }
        //for loop will expand indefinitely and keep track of all tokens. Make a while loop
        return tokens;
    }

    private:
    string input;
    int line = 0;
    // TokenType typeof; 
    void remove_whitespace() {
        while(isspace(input.at(0))) {
            input = input.substr(1);
        }
    }
    vector<Token> tokens;
    size_t total_tokens = tokens.size();
 
};












