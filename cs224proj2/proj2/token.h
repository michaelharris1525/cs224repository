#pragma once
#include <string>
#include<sstream>  
#include "scanner.h"
using namespace std;


enum TokenType {
  COMMA, 
  UNDEFINED,
  COMMENT,
  COLON,
  COLON_DASH,
  QUERIES,
  PERIOD,
  Q_MARK,
  LEFT_PAREN,
  RIGHT_PAREN,
  MULTIPLY,
  ADD,
  SCHEMES,
  FACTS,
  RULES,
  ID,
  STRING,
  END_OF_FILE,
  UNKNOWN
};

class Token {
    public: 
    Token(TokenType type, string value_s, int num_lines) 
    : type(type), value_s(value_s), num_lines(num_lines) { }

    string toString() const {
      stringstream out;
      out << "(" << typeName(type) << "," << "\"" << value_s << "\"" << "," << num_lines << ")";
      return out.str();
    }
    string getValueS() const {
        return value_s;
    }

    string typeName(TokenType type) const {
    // return the correct string for each TokenType value
      if (type == COMMA) {
        return "COMMA";
      }
      else if(type == COLON){
        return "COLON";
      }
      else if(type == COLON_DASH){
        return "COLON_DASH";
      }
      else if(type == QUERIES) {
        return "QUERIES";
      }
      else if(type == PERIOD) {
        return "PERIOD";
      }
      else if(type == Q_MARK) {
        return "Q_MARK";
      }
      else if(type == LEFT_PAREN) {
        return "LEFT_PAREN";
      }
      else if(type == RIGHT_PAREN) {
        return "RIGHT_PAREN";
      }
      else if(type == MULTIPLY) {
        return "MULTIPLY";
      }
      else if(type == ADD) {
        return "ADD";
      }
      else if(type == SCHEMES) {
        return "SCHEMES";
      }
      else if(type == FACTS) {
        return "FACTS";
      }
      else if(type == RULES) {
        return "RULES";
      }
      else if(type == QUERIES) {
        return "QUERIES";
      }
      else if(type == ID) {
        return "ID";
      }
      else if(type == STRING) {
        return "STRING";
      }
      else if(type == END_OF_FILE) {
        return "EOF";
      }
      else if(type == COMMENT) {
        return "COMMENT";
      }
      else  {
        return "UNDEFINED";
      }
      // else {
      //   return "UNKNOWN";
      // }
    }
    TokenType getType() const {
      return type;
    }
    
    
    
    private:
    TokenType type;
    string value_s = ",";
    int num_lines = 0; 

    


  
};

