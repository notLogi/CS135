//Roger Su
//CSCI-135
//Genady Maryash
//Project 1
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <climits> 
#include <stdlib.h>
using namespace std;

const int g_MAX_WORDS = 1000;
int g_word_count = 0;

string g_words[g_MAX_WORDS];
string g_definitions[g_MAX_WORDS];
string g_pos[g_MAX_WORDS];
/*
    @param            :   The string with the `filename`
    @post             :   Reads the words, definitions
                          pos into the global-arrays 
                          and set the value of `g_word_count`
                          to the number of words read
*/
void readWords(string filename){

ifstream fin;
    fin.open(filename);
    if (fin.fail()) {
    cerr << "File cannot be opened for reading." << endl;
    exit(1);}
    string word;
    string pos;
    string definition;
    string junk;
    while(fin >> word >> pos >> junk){
        getline(fin, definition);
        definition = definition.substr(1, definition.length());
        g_words[g_word_count] = word;
        g_pos[g_word_count] = pos;
        g_definitions[g_word_count] = definition;
        g_word_count++;
    }
    fin.close();
}
int getIndex(string word){
    for(int i= 0;i < g_word_count; i++){
        if(g_words[i]== word){
            return i;
        }
    }
    return -1;
}
string getDefinition(string word){
    for(int i=0;i<g_word_count; i++){
        if(g_words[i]== word)
        return g_definitions[i];
    }
    return "NOT_FOUND";
}
string getPOS(string word){
    for(int i=0;i<g_word_count; i++){
        if(g_words[i]== word)
        return g_pos[i];
    }
    return "NOT_FOUND";
}
int countPrefix(string prefix){
    int number = 0;
for (int i = 0; i < g_word_count; i++){
    if(g_words[i].substr(0,prefix.length()) == prefix){
        number++;
    }
}
return number;
}
bool addWord(string word, string definition, string pos) {
    for (int i = 0; i < g_word_count; i++) {
        if (g_words[i] == word) {
            return false;
        }
    }
    
    if (g_word_count == g_MAX_WORDS) {
        return false;
    }

    g_words[g_word_count] = word;
    g_definitions[g_word_count] = definition;
    g_pos[g_word_count] = pos;
    g_word_count++;
    
    return true;
}

bool editWord(string word, string definition, string pos) {
    int numb = -1;
    for (int i = 0; i < g_word_count; i++) {
        if (g_words[i] == word) {
            numb = i;
            break;
        }
    }
    if (numb == -1){
        return false;
    }
    g_definitions[numb] = definition;
    g_pos[numb] = pos;
    cout << word << definition << pos;
    
    return true;
}
bool removeWord(string word){
    int numb = getIndex(word);
    if (numb == -1){
        return false;
    }
    g_words[numb] = g_words[g_word_count - 1];
    g_pos[numb] = g_pos[g_word_count - 1];
    g_definitions[numb] = g_definitions[g_word_count - 1];
    g_word_count--;
    g_words[g_word_count] = "";
    g_definitions[g_word_count] = "";
    g_pos[g_word_count] = "";    
    return true;
}

string getRandomWord() {
    srand((unsigned) time(NULL));
    int index = rand() % g_word_count;
    return g_words[index];
}
string maskWord(string word){
    string underscore = "";
for (int i = 0; i < word.length(); i++){
    underscore += "_";

}     
return underscore;
}
int getTries(int difficulty){
    if (difficulty == 0){
        return 9;
    }
    else if(difficulty == 1){
        return 7;
    }
    else if(difficulty == 2){
        return 5;
    }
}
void printAttempts(int tries, int difficulty){
    int total = getTries(difficulty);
    for(int i = 0; i < tries; i++){
        if(i < total){
            cout << "O";
        }
        else{
            cout << "X";
        }
    }

}
bool revealLetter(string word, char letter, string &current){
}
void gameLoop() {
    int difficulty, tries;
    string word, current;
    char letter;
    while (true) {
        cout << "Welcome to Hangman!" << endl;
        cout <<  "0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
        cin >> difficulty;
        while (difficulty < 0 || difficulty > 3) {
            cout <<  "Enough horseplay >_< !\n0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
            cin >> difficulty;
        }
        if (difficulty == 3) {
            cout << "If you're hangry, go grab a bite! See what I did there?" << endl;
            break;
        }
        word = getRandomWord();
        current = maskWord(word);
        tries = getTries(difficulty);
        while (tries != 0) {
            cout << "Life: ";
            printAttempts(tries, difficulty);
            cout << endl << "Word: "<< current << endl;
            cout << "Enter a letter: ";
            cin >> letter;
            
            if (!revealLetter(word, letter, current)) {
                tries--;
            }
            if (current == word) {
                break;
            }
            if (tries == 2) {
                cout << "The part of speech of the word is "<< getPOS(word) << endl;
            }
            if (tries == 1) {
                cout << "Definition of the word: " << getDefinition(word) << endl;
            }
        }
        if (tries == 0) {
            cout << "The word is \"" << word << "\". Better luck next time! You're getting the ..ahem.. hang of it." << endl;
        }
        else {
            cout << "Congrats!!!" << endl;
        }
    }
}
int main(){
    readWords("dictionary.txt");
    for(int i = 0; i < g_word_count; i++){
        cout<< g_words[i] <<" ("<< g_pos[i] << ") " << g_definitions[i] << endl;
    }
    string word;
    cout <<"Enter word: ";
    cin >>word;
    cout<< getIndex(word)<< endl;
    cout << getDefinition(word)<<endl;
    cout << getPOS(word)<<endl;
    string prefix;
    cout <<"Enter prefix: ";
    cin >>prefix;
    cout << countPrefix(prefix) << endl;
    string newword, newpos, newdefinition;
    cout <<"Enter new word: ";
    cin >> newword;
    cout <<"Enter new pos: ";
    cin >>newpos;
    cout <<"Enter new definition: ";
    cin >> newdefinition;
    if(addWord(newword, newpos, newdefinition) == 1){
        cout << "Sucessfully added" <<endl;
    }

    string editword, editpos, editdefinition;
    cout <<"Enter the word you want to edit: ";
    cin >> editword;
    cout <<"Enter the new definition: ";
    cin >>editdefinition;
    cout <<"Enter the new pos: " ;
    cin >> editpos;
    if(editWord(editword, editdefinition, editpos) == 1){
        cout << "Successfully edited"<<endl;
    }
    string removeword;
    cout <<"Enter the word you want to remove: ";
    cin >> removeword;
    if(removeWord(removeword) == 1){
        cout <<"Successfully removed" << endl;
    }
    string maskword;
    cout << "Enter word for hangman game: ";
    cin >> maskword;
    cout <<maskWord(maskword);
    int tries;
    cout << "Enter difficulty from 0-2: ";
    cin >> tries;
    cout <<getTries(tries) << " tries";
    return 0;
}
