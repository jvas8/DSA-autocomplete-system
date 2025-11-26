Autocomplete Trie in C++
Overview

This project implements a live autocomplete system using a Trie (prefix tree) data structure in C++.
As the user types, the program suggests words from a dictionary of the 500 most common English words. Words are suggested based on frequency, so more common words appear first.

Features:

Live suggestions while typing (no need to press Enter for each character)

Autocompletion is frequency-aware

Works on Linux/macOS terminals

Dictionary is loaded from a text file (dictionary.txt)

Requirements:

Linux or macOS terminal (uses termios.h for live input, it does not function on windows)

A dictionary.txt file in the project directory

How to Run:

Compile the program:

g++ -std=c++11 autocomplete.cpp -o autocomplete


Make sure dictionary.txt is in the same directory as the compiled program.

Run the program:

./autocomplete


Start typing, and suggestions will appear as you type.

Press Backspace to delete characters

Press Enter to exit

Example Usage:
Start typing (Press ENTER to exit):
You typed: t

Suggestions:
 - the
 - to
 - that
 - this
 - time

Keep typing...

Notes:

The program uses system("clear") to refresh the terminal for suggestions.

Frequencies in dictionary.txt determine the order of suggestions.