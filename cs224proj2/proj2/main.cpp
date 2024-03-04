#include <iostream>
#include "scanner.h"
#include "token.h"
#include "parser.h"
#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
//local testing with custom input
  // Scanner s = Scanner("  :-  ,  \n + \"Jack Black\" :- \n () Schemes \n jakc1 :- ");
  // vector <Token> t = s.scanToken();
  // for (Token &t : t) {
  //   cout << t.toString() << endl;
  // }

   //testing with files
   //Read the contents of the input file into a string
    ifstream inFile(argv[1]);
    /*int number_tokens = 0;*/
    stringstream buffer;
    buffer << inFile.rdbuf();
    string input = buffer.str();

    // Close the input file
    inFile.close();

     // Create a Scanner object and scan the input string
     Scanner scanner(input);
     vector<Token> tokens = scanner.scanToken();
     vector<Token> notTokens;
     for (size_t i = 0; i < tokens.size(); i++) {
         if (tokens.at(i).getType() != COMMENT) {
             notTokens.push_back(tokens[i]);
         }
     }
         

    // // Output the scanned tokens
    // for (const Token& token : tokens) {
    //     cout << token.toString() << endl;
    //     number_tokens++;
    // }
    // cout << "Total Tokens = " << number_tokens << endl;

    //testing sub functions
    // vector<Token> tokens = {
    // Token(ID,"Ned",2),
    // Token(LEFT_PAREN,"(",2),
    // Token(RIGHT_PAREN,")",2),
    // };

    // Parser p = Parser(tokens);
    // cout << p.tokenType() << endl;
    // p.advanceToken();
    // cout << p.tokenType() << endl;
    // p.advanceToken();
    // cout << p.tokenType() << endl;
    // p.throwError();

    //testing match function
    // vector<Token> tokens = {
    // Token(ID,"Ned",2),
    // Token(LEFT_PAREN,"(",2),
    // Token(RIGHT_PAREN,")",2),
    // };

     Parser p = Parser(notTokens);
     p.parse();
          // p.match(ID);
    // p.match(LEFT_PAREN);
    // p.match(ID);  // intentional error
    // p.match(RIGHT_PAREN);
  //   vector<Token> tokens = {
  //   Token(ID,"Ned",2),
  //   //Token(LEFT_PAREN,"(",2),
  //   Token(ID,"Ted",2),
  //   Token(COMMA,",",2),
  //   Token(ID,"Zed",2),
  //   Token(RIGHT_PAREN,")",2),
  // };
     
  //   Parser p = Parser(tokens);
  //   p.scheme();

}