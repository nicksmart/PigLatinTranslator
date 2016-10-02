//
//  main.cpp
//  PigLatinTranslator
//
//  Created by Nick Smart on 8/28/16.
//  Copyright © 2016 Smart Technologies. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const string GetInputString();
bool FindWordInDictionary(string word);
vector<string> ParseString(const string input);
string EnglishToPigLatin(vector<string> EnglishInput, bool useDictionary);
bool isVowel(char c);


int main(int argc, const char * argv[]) {
    char cont = 'Y';
    char validEnglish;
    bool useDictionary = false;
    cout << "Do you want all words in the string to be valid English? (Y/N)" << endl;
    cin >> validEnglish;
    if (validEnglish == 'Y' or validEnglish == 'y') useDictionary = true;
    cout << endl;
    
    while (cont != 'N' and cont != 'n') {
        
        cout << "Enter a string to be translated. (Do not use capital letters)" << endl;
        string translatedOutput;
        const string originalInput = GetInputString();
        vector<string> words = ParseString(originalInput);
        string s = EnglishToPigLatin(words, useDictionary);
        cout << s << endl << endl;
        
        cout << "Continue? (Y/N)" << endl;
        cin >> cont;
    }
    
    
    return 0;
}


//Gets entire input from user and returns input as a string;
const string GetInputString() {
    string str, original;
    while(cin >> str) {
        if (cin.get() != '\n') original += (str + " ");
        else {
            original += str;
            break;
        }
    }
    return original;
}


//Searches through directory of English words and returns true if the input is an
//English word
bool FindWordInDictionary(const string word) {
    ifstream file;
    string search;
    bool found = false;
    file.open("words.txt");
    if(!file.is_open()) {
        cout << "Dictionary file not found...\nProgram exiting now." << endl;
        exit(1);
    }
    while (file >> search) {
        if (search == word)
            found = true;
    }
    file.close();
    
    return found;
}


//Separates the input string into individual strings that are contained in a vector
vector<string> ParseString(string input) {
    vector<string> words;
    int counter = 0;
    string tempWord;
    while (counter < input.length()) {
        if (counter == 0 and words.empty()) {
            while (input.at(counter) == ' ') {
                counter++;
            }
        }
        if (input.at(counter) != ' ') {
            if (!((input.at(counter) >= 'a' and input.at(counter) <= 'z') or
                  (input.at(counter) >= 'A' and input.at(counter) <= 'Z'))) {
                
                //MAY WANT TO TRY INCORPORATING HYPHENS
                /*if (input.at(counter) == '-') {
                    words.push_back(tempWord);
                    tempWord.clear();
                    counter++;
                    continue;
                }*/
                
                
                counter++;
                if (counter == input.length()) {
                    words.push_back(tempWord);
                }
                else if (input.at(counter) == ' ') {
                    words.push_back(tempWord);
                    tempWord.clear();
                }
            }
            else {
                tempWord.push_back(input.at(counter));
            }
        }
        else {
            words.push_back(tempWord);
            tempWord.clear();
        }
        if (counter == input.length() - 1) {
            words.push_back(tempWord);
        }
        counter++;
    }
    return words;
}


//Translates the vector of English words into a Pig Latin string
string EnglishToPigLatin(vector<string> EnglishInput, bool useDictionary) {
    string translated;
    for (string word : EnglishInput) {
        if (useDictionary and !FindWordInDictionary(word)) {
            cout << "The input string contains words not found in the English Dictionary" << endl;
            cout << "Exiting program now..." << endl;
            exit(1);
        }
        
        if (word.length() == 1) {
            if (isVowel(word.at(0))) {
                translated += (word + "way ");
            }
            else {
                translated += (word + "ay ");
            }
        }
        else {
            if (isVowel(word.at(0))) {
                translated += (word + "way ");
            }
            if (!isVowel(word.at(0)) and isVowel(word.at(1))) {
                if (word.at(0) == 'q' and word.at(1) == 'u') {
                    translated += (word.substr(2) + word.substr(0, 2) + "ay ");
                }
                else {
                    translated += (word.substr(1) + word.substr(0, 1) + "ay ");
                }
            }
            if (!isVowel(word.at(0)) and !isVowel(word.at(1))) {
                int numTilVowel = 0;
                while (!(isVowel(word.at(numTilVowel)))) {
                    numTilVowel++;
                }
                translated += (word.substr(numTilVowel) + word.substr(0, numTilVowel) + "ay ");
            }
        }
        
    }
    
    return translated;
}


//Checks if input character is a vowel
bool isVowel(char c) {
    tolower(c);
    
    return (c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u');
}





//STILL TO DO
// * Fix dictionary search to not struggle with capital letters (NOT NEEDED)
// * Add a function to ask the user if they want the dictionary feature (DONE)
// * Finish English to Pig Latin translation function for when multiple consonants start the word (DONE)
// * Add a feature to run the program until the user types 'Q'
// * Do Pig Latin to English translation function
// * Create dictionary option for this portion too
// * Try incorporating hyphens










