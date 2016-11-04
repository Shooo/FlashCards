#ifndef FLASH_CARDS_H
#define FLASH_CARDS_H

#include <iostream>
#include <vector>
#include <string>
#include "deck.h"

using namespace std;

class flash_cards{

public:
    flash_cards(string);
    ~flash_cards();
    void choose_option();


private:
    deck new_deck;
    vector<string> list;
    int get_option(string,int);
    int get_command();
    void random_order();
    void alphabetical_order();
    void in_order();

    void guess_term();
    void guess_definition();

    string capitalize(string);
    void clear_screen();

};

#endif
