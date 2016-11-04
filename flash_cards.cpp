
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "deck.h"
#include "deck_exception.h"
#include "flash_cards.h"

using namespace std;

int main(int argc, char *argv[]){
    string filename;
    if(argc == 1){
        cout << "Enter file to load" << endl;
        getline(cin,filename);
        //filename = "./Decks/" + filename;
    }
    else if(argc == 2){
        filename = argv[1];
    }
    else{
        exit(1);
    }

    string option;
    try{
        flash_cards flash_card(filename);
        flash_card.choose_option();
    }
    catch(deck_exception excpt){
        cout << "Error: " << excpt.get_message() << endl;
        cout << "Press any key to exit." << endl;
        string finish;
        getline(cin,finish);
    }

    return 0;
}

flash_cards::flash_cards(string file_name):new_deck(file_name){
    clear_screen();
    list = new_deck.get_list();

}
flash_cards::~flash_cards(){
}

void flash_cards::choose_option(){
    string option0;
    bool valid_option;
    do{
        string menu1 = "Select order:\n1) Random\n2) Alphabetical\n3) In order";
        string menu2 = "Select format:\n1) Guess definition\n2) Guess term";
        int option1;
        int option2;
        option1 = get_option(menu1,3);
        if(option1 == 1){
            random_order();
        }
        else if(option1 == 2){
            alphabetical_order();
        }
        else{
            in_order();
        }
        clear_screen();
        option2 = get_option(menu2,2);
        clear_screen();
        if(option2 == 1){
            guess_definition();
        }
        else if(option2 == 2){
            guess_term();
        }
        valid_option = false;
        while(!valid_option){
            cout << "Would you like to try again? (y/n)" << endl;
            getline(cin,option0);
            option0 = capitalize(option0);
            if(option0 == "Y" || option0 == "N"){
                valid_option = true;
            }
            else{
                cout << "Invalid option. " << endl;
            }
        }

    }
    while(option0 == "Y");
}

int flash_cards::get_option(string menu,int num_of_options){
    string option;
    int op;
    bool valid_option = false;
    cout << menu << endl;
    while(!valid_option){
        getline(cin,option);
        int test = option.find_first_not_of("0123456789");
        if(test != -1 || option.empty()){
            cout << "Invalid option, try again" << endl;
            continue;
        }
        istringstream ss(option);
        ss >> op;
        if(op > num_of_options){
            cout << "Invalid option, try again" << endl;
            continue;
        }
        else{
            valid_option = true;
        }
    }
    return op;

}

//Returns 1 if previous, 2 if next, 3 if empty line
int flash_cards::get_command(){
    bool valid_command = false;
    string input;
    while(!valid_command){
        getline(cin,input);
        input = capitalize(input);
        if(input == "PREV" || input == "PREVIOUS"){
            return 1;
        }
        if(input == "NEXT"){
            return 2;
        }
        if(input.empty()){
            return 3;
        }
        else if(input == "RETRY"){
            return 4;
        }
        else if(input == "REENTER"){
            return 5;
        }
        else{
            cout << "Invalid command. Valid commands: previous (prev), next, retry, reenter, ENTER." << endl;
        }
    }

    return 0;
}

void flash_cards::random_order(){
    srand(time(0));
    random_shuffle(list.begin(),list.end());
}

void flash_cards::alphabetical_order(){
    sort(list.begin(),list.end());
}

void flash_cards::in_order(){
    list = new_deck.get_list();
}

void flash_cards::guess_definition(){
    unsigned int i = 0;
    int command;
    bool valid_command;
    bool valid_command2;
    string display;
    string input;
    while(i != list.size()){
        clear_screen();
        valid_command = false;
        valid_command2 = false;
        while(!valid_command){
            display = list[i];
            cout << display << endl;
            command = get_command();
            if(command == 1){
                if(i == 0){
                    cout << "No previous card avaiable. Enter any key to continue." << endl;
                    getline(cin,input);
                    clear_screen();
                    //continue;
                }
                else{
                    i--;
                    valid_command = true;
                }
            }
            else if(command == 2){
                if(i == list.size()-1){
                    cout << "No next card avaiable. Enter any key to continue." << endl;
                    getline(cin,input);
                    clear_screen();
                    //continue;
                }
                else{
                    i++;
                    valid_command = true;
                }
            }
            else if(command == 4){
                clear_screen();
                continue;
            }
            else if(command == 5){
                clear_screen();
                list.push_back(display);
                list.erase(list.begin() + i);
                continue;
            }
            else if(command == 3){
                cout << new_deck.get_definition(list[i]) << endl;
                cout << endl;
                valid_command = true;
            }
        }
        if(command == 1 || command == 2){
            continue;
        }

        while(!valid_command2){
            command = get_command();
            if(command == 1){
                if(i == 0){
                    cout << "No previous card avaiable. Enter any key to continue." << endl;
                    getline(cin,input);
                    clear_screen();
                    continue;
                }
                else{
                    i--;
                    valid_command2 = true;
                }
            }
            else if(command == 2){
                if(i == list.size()-1){
                    cout << "No next card avaiable. Enter any key to continue" << endl;
                    getline(cin,input);
                    clear_screen();
                    continue;
                }
                else{
                    i++;
                    valid_command2 = true;
                }
            }
            else if(command == 4){
                valid_command2 = true;
                continue;
            }
            else if(command == 5){
                clear_screen();
                list.push_back(list[i]);
                list.erase(list.begin() + i);
                valid_command2 = true;
                continue;
            }
            else{
                i++;
                valid_command2 = true;
            }
        }

    }
    if(i == list.size()){
        cout << "Completed deck" << endl;
    }

}

void flash_cards::guess_term(){
    unsigned int i = 0;
    int command;
    bool valid_command;
    bool valid_command2;
    string display;
    string input;
    while(i != list.size()){
        clear_screen();
        valid_command = false;
        valid_command2 = false;
        while(!valid_command){
            display = list[i];
            cout << new_deck.get_definition(display) << endl;
            command = get_command();
            if(command == 1){
                if(i == 0){
                    cout << "No previous card avaiable. Enter any key to continue." << endl;
                    getline(cin,input);
                    clear_screen();
                    //continue;
                }
                else{
                    i--;
                    valid_command = true;
                }
            }
            else if(command == 2){
                if(i == list.size()-1){
                    cout << "No next card avaiable. Enter any key to continue." << endl;
                    getline(cin,input);
                    clear_screen();
                    //continue;
                }
                else{
                    i++;
                    valid_command = true;
                }
            }
            else if(command == 4){
                clear_screen();
                continue;
            }
            else if(command == 5){
                clear_screen();
                list.push_back(display);
                list.erase(list.begin() + i);
                continue;
            }
            else if(command == 3){
                cout << display << endl;
                valid_command = true;
            }
        }
        if(command == 1 || command == 2){
            continue;
        }

        while(!valid_command2){
            command = get_command();
            if(command == 1){
                if(i == 0){
                    cout << "No previous card avaiable. Enter any key to continue." << endl;
                    getline(cin,input);
                    clear_screen();
                    continue;
                }
                else{
                    i--;
                    valid_command2 = true;
                }
            }
            else if(command == 2){
                if(i == list.size()-1){
                    cout << "No next card avaiable. Enter any key to continue" << endl;
                    getline(cin,input);
                    clear_screen();
                    continue;
                }
                else{
                    i++;
                    valid_command2 = true;
                }
            }
            else if(command == 4){
                valid_command2 = true;
                continue;
            }
            else if(command == 5){
                clear_screen();
                list.push_back(list[i]);
                list.erase(list.begin() + i);
                valid_command2 = true;
                continue;
            }
            else{
                i++;
                valid_command2 = true;
            }
        }
        if(i == list.size()){
            cout << "Completed deck" << endl;
        }
    }
}

string flash_cards::capitalize(string s){
    for(unsigned int i = 0; i < s.length(); i++){
        s[i] = toupper(s[i]);
    }
    return s;
}

void flash_cards::clear_screen(){
    cout << string(50, '\n');
}
