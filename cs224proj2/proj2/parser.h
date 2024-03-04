#pragma once
#include "token.h"
#include "scanner.h"
#include<string>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
#include <stdexcept> 
#include <string>

//class c_Predicate;

class c_Parameter {
    public:
        string ID;
};

class c_Predicate {
public:
    string name;
    vector<string> parameters;

    string p_toString() const {
        stringstream out;
        size_t i = 0;
        out << name << "(";
        while (i < parameters.size()) {
            out << parameters[i];
            if (i < parameters.size() - 1) {
                out << ",";
            }
            i++;
        }
        out << ")";
        return out.str();
    }
};

class c_Rules {
    public:
        c_Predicate headPredicate;
        vector<c_Predicate> bodyPredicates;
        string p_toString() const {
            stringstream out;
            size_t i = 0;
            out << headPredicate.p_toString() << " :- ";
            while (i < bodyPredicates.size()) {
                out << bodyPredicates[i].p_toString();
                if (i < bodyPredicates.size() - 1) {
                    out << ",";
                }
                i++;
            }
            
            return out.str();
        }
};



class c_datalogProgram {
    private:
    public:
//container to hold info to vector
    vector<c_Predicate> v_schemes;
    vector<c_Predicate> v_facts;
    vector<c_Rules> v_rules;
    vector<c_Predicate> v_queries;

    set<string> cd_set;
     
    string p_toString() const {
        stringstream out;
        out << "Schemes(" << to_string(v_schemes.size()) << "):\n";
        for (size_t i = 0; i < v_schemes.size(); i++) {
            out << "  " << v_schemes[i].p_toString() << "\n";
        }
        out << "Facts(" << to_string(v_facts.size()) << "):\n";
        for (size_t i = 0; i < v_facts.size(); i++) {
            out << "  " << v_facts[i].p_toString() << ".\n";
        }
        out << "Rules(" << to_string(v_rules.size()) << "):\n";
        for (size_t i = 0; i < v_rules.size(); i++) {
            out << "  " << v_rules[i].p_toString() << ".\n";
        }
        out << "Queries(" << to_string(v_queries.size()) << "):\n";
        for (size_t i = 0; i < v_queries.size(); i++) {
            out << "  " << v_queries[i].p_toString() << "?\n";
        }
        out << "Domain(" << to_string(cd_set.size()) << "):\n";
        for (const auto& item : cd_set) { 
            out << "  " << item << "\n";
        }
        return out.str();

    }
    
};

class Parser {
 private:
     c_datalogProgram program;
     vector<Token> tokens;
     c_Predicate dummy_object; 
     c_Rules dummy_rule; 


 public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }
    TokenType tokenType() const {
        return tokens.at(0).getType();
    }
    

    void parse(){

        try {
            datalogProgram();
            cout << "Success!" << std::endl;
            cout << program.p_toString();
        }

  

        catch(Token& errorToken){
            cout << "Failure!\n  ";
            cout << errorToken.toString() << "\n\n";
        }
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    void throwError() {
        throw tokens.at(0);
    }


    void match(TokenType t) {
        while (tokens.at(0).getType() == COMMENT) {
            advanceToken();
        }
        if (t == tokens.at(0).getType()) {
            //added code to avoid comments
         /*   cout << tokens.at(0).toString();*/
            advanceToken();
        }
        else {
            throwError();
        }
        // add code for matching token type t
    }
    

    void parameter() {
        if(tokenType() == STRING) {
            match(STRING);
        }
        else if(tokenType() == ID) {
            match(ID);
        }
        else {
         
        }
    }

    void scheme() {
    // add code for parsing a 'scheme'
       
        //clear dummy predicate, dummy rule but not in scheme
        c_Predicate my_object;
        my_object.name = tokens.at(0).getValueS();
        match(ID);
        match(LEFT_PAREN);
        //make a parameter, call constructor, construct a parameter, and add it to the dummy predicate and its list
        /*cout << tokens.at(0).toString();*/
        my_object.parameters.push_back(tokens.at(0).getValueS());
        match(ID);
        idList(my_object);
        match(RIGHT_PAREN);
        //add it to Datalog program object or vector schemes. 
        /*c_datalogProgram list_scheme_obj;*/
        program.v_schemes.push_back(my_object);
        
              
    }
       
    
    void schemeList() {
        if(tokenType() == ID) {
            scheme();
            schemeList();
        }
        else {
            
        }
    }

    void fact() {
        if(tokenType() == ID) {
            c_Predicate my_object;
            my_object.name = tokens.at(0).getValueS();
            match(ID);
            match(LEFT_PAREN);
            //Ann is here
            my_object.parameters.push_back(tokens.at(0).getValueS());
            program.cd_set.insert(tokens.at(0).getValueS());
            match(STRING);
            stringList(my_object);
            match(RIGHT_PAREN);
            //add it to Datalog program object or vector schemes.
            match(PERIOD);
            program.v_facts.push_back(my_object);
        }
        else {
            
        }
    }
    void stringList(c_Predicate& my_object) {
        if (tokenType() == COMMA) {
            match(COMMA);
            //make parameter
            //Bob is here
            my_object.parameters.push_back(tokens.at(0).getValueS());
            program.cd_set.insert(tokens.at(0).getValueS());
            match(STRING);
            /*cout << tokens.at(0).toString() << "\n";*/
            stringList(my_object);
            /*return my_object;*/
        }
        else {
            
        }
    }
    
    void factList() {
        if(tokenType() == ID) {
            fact();
            factList();
        }
        else {
            
        }
    }

    void headPredicate(c_Rules& my_object) {
        if (tokenType() == ID) {
            c_Predicate object;
            object.name = tokens.at(0).getValueS();
            match(ID);
            match(LEFT_PAREN);
            object.parameters.push_back(tokens.at(0).getValueS());
            match(ID);
            idList(object);
            match(RIGHT_PAREN);
            my_object.headPredicate = object;
        }
        else {
            
        }
    }

    void rule() {
        if (tokenType() == ID) {
            c_Rules my_object;
            headPredicate(my_object);
            match(COLON_DASH);
            my_object.bodyPredicates.push_back(predicate());
            predicateList(my_object);
           /* cout << tokens.at(0).toString() << "\n";*/
            match(PERIOD);
            program.v_rules.push_back(my_object);

        }
        else {
            
        }
    }

    void ruleList() {
        if(tokenType() == ID) {
            rule();
            ruleList();
        }
        else {

        }
    }

    c_Predicate predicate() {
        if (tokenType() == ID) {
            c_Predicate my_object;
            my_object.name = tokens.at(0).getValueS();
            match(ID);
            match(LEFT_PAREN);
            my_object.parameters.push_back(tokens.at(0).getValueS());
            parameter();
            parameterList(my_object);
            match(RIGHT_PAREN);
            return my_object;
        }
    }

    void query() {
        if(tokenType() == ID) {
            c_Predicate my_object;
            /*my_object.name = tokens.at(0).getValueS();*/
            my_object = predicate();
            /*my_object.parameters.push_back(tokens.at(0).getValueS());*/
            match(Q_MARK);
            
            program.v_queries.push_back(my_object);
        }
        else {
           
        }
    }

    void queryList() {
        if(tokenType() == ID) {
            query();
            queryList();
        }
        else {
            
        }
    }

    void predicateList(c_Rules& my_object) {
        if (tokenType() == COMMA) {
            match(COMMA);
            my_object.bodyPredicates.push_back(predicate());
            predicateList(my_object);
        }
        else {
           
        }
    }

   

    void parameterList(c_Predicate& my_object) {
        if (tokenType() == COMMA) {
            match(COMMA);
            my_object.parameters.push_back(tokens.at(0).getValueS());
            parameter();
            parameterList(my_object);
        }
        else {
          
        }
        
    }

    void idList(c_Predicate& my_object) {
        if (tokenType() == COMMA) {
            match(COMMA);
            //make parameter
            my_object.parameters.push_back(tokens.at(0).getValueS());
            match(ID);
            idList(my_object);
        } 
        else {
           
        }
    }

    

    
    

    void datalogProgram() {
        if(tokenType() == SCHEMES) {
            //parsing grammer
            match(SCHEMES);
            match(COLON);
            scheme();
            schemeList();
            if (program.v_schemes.size() == 0) {
                throwError();
            }
            match(FACTS);
            match(COLON);
            factList();
            match(RULES);
            match(COLON);
            ruleList();
            match(QUERIES);
            match(COLON);
            query();
            queryList();
            if (program.v_queries.size() == 0) {
                throwError();
            }
            match(END_OF_FILE); 
        }
        else {
           
        }
    }
  
    
};

