# FlashCards
A very simple flash card program I wrote a while back to help me with studying. 

#### How to compile:
call 'make' in the command line

## How to format a deck:
I tried design it in a way anyone can easily create and edit a deck, so instead of using xml or json this program simply parses a text file based on certain delimiters.
  
### Terms:
Terms are parsed by enclosing with '~'.  
#### Example:  
    ~apple~  
note: terms cannot be more than one line long  
  
### Definitions:
Definitions are parsed by enclosing with '\'. The first '\' of each definition must be the first character of the line.  
#### Example:
    \the usually round, red or yellow, edible fruit of a small tree\  
note: definitions can be more than one line long
#### Example:  
     \the usually round, red  
        or yellow, edible fruit  
        of a small tree\  
        
As terms and definitions are parsed using the characters, '~' and '\', these two characters cannot be used inside the term or definition.  
A template and example deck can be found in the Decks folder.  
  
  
## How to load a deck:
1) Type in the file name when prompted during execution  
#### Example:
    Enter file to load  
    ./Decks/TestDeck.txt  
note: Decks do not have to be in this folder, if its in the local folder simply type the name of the deck file  
  
2) Pass in the file name as the second argument  
#### Example:
    $ ./flash_cards ./Decks/TestDeck.txt

#### Commands:
This program can display cards in random order, alphabetical order, or in the order you created the deck.  
It can display a term to guess the definition, or display a deffinition to guess the term  

##### Commands:
1) Previous/prev: go to previous card  
2) Next: go to next card  
3) Retry: guess the card again  
4) Reenter: puts current card to back of deck  
5) ENTER (command): flip card/ go to next card  
  
All commands are not case sensitive. 
