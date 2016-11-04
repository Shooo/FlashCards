

#ifndef DECK_EXCEPTION_H
#define DECK_EXCEPTION_H
#include <string>
#include <vector>

using namespace std;

class deck_exception {

public:
        deck_exception(string s){
            message = s;
        }
        deck_exception(){
            message = "An error has occured";
        }
        string get_message(){
            return message;
        }

private:
    string message;

};

#endif
