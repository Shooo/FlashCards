Deck format:
TERMS:
Terms are parsed by enclosing with '~'.
    ie. ~apple~
NOTE: terms CANNOT be more than one line long

DEFINITIONS:
Definitions are parsed by enclosing with '\'. The first '\' of each definition MUST be the first character.
    ie. \the usually round, red or yellow, edible fruit of a small tree\
NOTE: definitions CAN be more than one line long
    ie. \the usually round, red
        or yellow, edible fruit
        of a small tree\
See ./Decks/Template.txt for an example.

as terms and definitions are parsed using the characters, '~' and '\', these two
characters cannot be used inside the term or definition.



To load deck:
1) type in the file name when prompted during execution
    ie. type when prompted: ./Decks/Template.txt (if file is in Decks folder)
        if txt file is in the same folder as FlashCards directory: simply type name of txt file - ie. Template.txt
2) pass in a file/filename
    type the file name as second argument when executing
    or, simply drag the txt file on the exe



Flash card features:
Can display characters in random order, alphabetical order, or order of deck.
Can display term to guess definition, or display definition to guess term.

Commands:
1) Previous/prev: go to previous card
2) Next: go to next card
3) Retry: guess the card again
4) Reenter: puts current card to back of deck
5) ENTER (command): flip card/ go to next card

All commands are NOT case sensitive.
