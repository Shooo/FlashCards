

#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class deck{

public:
    deck(string);

    ~deck();

    void read_file();

    string get_definition(string);

    vector<string> get_list();





private:
    string file_name;
    vector <string> lines;
    vector <string> insert_order;
    map <string, string> cards;
    unsigned int line_number;
    void parse_file(vector<string>);
    void print_error(string,int);
    bool term_exists(string);
    string remove_char(string,char);
    // struct card{
    //     string term;
    //     string definition;
    // };

};

#endif
