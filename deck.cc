#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include "deck.h"
#include "deck_exception.h"

using namespace std;

deck::deck(string file){
    file_name = file;
    line_number = 0;
    read_file();
}

deck::~deck(){
}

void deck::read_file(){
    ifstream infile (file_name.c_str());
    string line;
    if(!infile){
        throw deck_exception("Invalid file");
    }
    while(!infile.eof()){
        getline(infile,line);
        lines.push_back(line);
    }
    infile.close();
    parse_file(lines);
}

void deck::parse_file(vector<string> lines){
    //string test = lines.front();
    string tilde = "~";
    string slash = "\\";
    string term;
    string definition;
    int first_tilde;
    int last_tilde;
    int test_tilde;
    int first_slash;
    int last_slash;
    bool slash_found = false;
    for(unsigned int i = 0; i < lines.size(); i++){
        line_number++;
        string temp_line = lines[i];

        //Error if term is found before definition has closed
        if(slash_found){
            test_tilde = temp_line.find_first_of(tilde);
            if(test_tilde != -1){
                string message = " Unclosed definition for term: " + term;
                throw deck_exception(message);
            }
        }
        first_tilde = temp_line.find_first_of(tilde);
        last_tilde = temp_line.find_last_of(tilde);
        if(first_tilde != -1){
            if(last_tilde != -1 && last_tilde != first_tilde){  //if closing tilde is found and it is not the same tilde as first
                //term = temp_line.substr(first_tilde+1,last_tilde - first_tilde - 1);
                term = remove_char(temp_line,'~');
                insert_order.push_back(term);
                continue;
            }
            else{
                print_error("Unclosed label at line: ", line_number);
            }
        }
        if(!temp_line.empty() && temp_line[0] == '\\'){
            last_slash = temp_line.find_last_of(slash);
            first_slash = temp_line.find_first_of(slash);
            if(last_slash != first_slash){
                definition = temp_line;
                definition = remove_char(definition,'\\');
                cards[term] = definition;
            }
            if(last_slash == first_slash){
                definition = temp_line + "\n";
                slash_found = true;
                continue;
            }
        }
        if(slash_found){
            last_slash = temp_line.find_last_of(slash);
            if(last_slash == -1){
                definition = definition + temp_line + "\n";
            }
            else{
                definition = definition + temp_line;
                definition = remove_char(definition,'\\');
                cards[term] = definition;
                slash_found = false;
            }
        }

        //Error if last definition is not closed
        if(i+1 == lines.size() && slash_found){
            string message = " Unclosed definition for term: " + term;
            throw deck_exception(message);
        }
    }
}

string deck::get_definition(string term){
    return cards[term];
}

vector<string> deck::get_list(){
    return insert_order;
}

//Helper functions
void deck::print_error(string s, int line_number){
    stringstream ss;
    ss << line_number;
    string line = ss.str();
    throw deck_exception(s + line + '.');
}

bool deck::term_exists(string term){
    if(cards.find(term) == cards.end()){
        return false;
    }
    return true;
}

string deck::remove_char(string str, char ch){
    str.erase(remove(str.begin(),str.end(),ch ), str.end());
    return str;
}
