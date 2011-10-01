//======================================================================
//  main.cpp
//  Memorizer_0
//
//  Created by Yuduo Zhang on 11-06-19.
//  Copyright 2011 The University of Waterloo. All rights reserved.
//======================================================================

#ifndef MEMORIZER_H
#define MEMORIZER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

//======================================================================
//  Review Cycle Declarations (mins)
//======================================================================

const int FirstCycle = 5;
const int SecondCycle = 30;
const int ThirdCycle = 60*24*0.5; // 12 hours
const int FourthCycle = 60*24; // 1 day
const int FifthCycle = 60*24*2; // 2 days
const int SixthCycle = 60*24*4; // 4 days
const int SeventhCycle = 60*24*7; // 7 days
const int EighthCycle = 60*24*15; // 15 days

//======================================================================
//  Helper: currentTime(): return current time in minutes
//          split(): tokenize a string
//======================================================================

//======================================================================
//  
int currentTime(){
    time_t seconds = time (NULL);
    return seconds/60;
}

//======================================================================
//  
vector<string> split(string s){
    vector<string> tokenVector;
    stringstream inputString(s);
    string token;

    while (getline(inputString, token, '\t')){
        tokenVector.push_back(token);
    }

    return tokenVector;
}

//======================================================================
//  Word Class
//======================================================================

class Word {
public:

    /*----- member functions  -----*/

//======================================================================
//  
    const string& getKey() const {
        return key;
    }

//======================================================================
//  
    const string& getContent() const {
        return content;
    }

//======================================================================
//  
    const int getReviewCycle() const {
        return ReviewCycle;
    }

//======================================================================
//  
    const int getNextReviewTime() const {
        return NextReviewTime;
    }

//======================================================================
//  
    const int getReviewCycleTime () const {
        switch (ReviewCycle) {
            case 1:
                return FirstCycle;
            case 2:
                return SecondCycle;
            case 3:
                return ThirdCycle;
            case 4:
                return FourthCycle;
            case 5:
                return FifthCycle;
            case 6:
                return SixthCycle;
            case 7:
                return SeventhCycle;
            case 8:
                return EighthCycle;
            default:
                cout << "Review cycle not defined" << endl;
                return 1;
        }
    }

//======================================================================
//  
    const int CheckExisting() const {
        return InReviewBook;
    }

//======================================================================
//  
    void setKey(string k){
        key = k;
    }

//======================================================================
//  
    void setContent(string c){
        content = c;
    }

//======================================================================
//  
    void setReviewCycle(int rc){
        ReviewCycle = rc;
    }

//======================================================================
//  
    void resetReviewCycle(){
        ReviewCycle = 1;
    }

//======================================================================
//  
    void increaseReviewCycle(){
        ReviewCycle++;
    }

//======================================================================
//  
    void setNextReviewTime(int nrt){
        NextReviewTime = nrt;
    }

//======================================================================
//  
    void resetNextReviewTime(){
        NextReviewTime = ComputeNextReviewTime();
    }

//======================================================================
//  
    void setInReviewBook(int e){
        InReviewBook = e;
    }

//======================================================================
//  
    int ComputeNextReviewTime () {
        int NextReviewTime = currentTime() + getReviewCycleTime();
        return  NextReviewTime;
    }

//======================================================================
//  
    Word () {
        key = "";
        content = "";
        ReviewCycle = 1;
        NextReviewTime = ComputeNextReviewTime();
        InReviewBook = 0;
    }

private:

    /*----- data members -----*/

    string key;
    string content;
    int ReviewCycle;
    int NextReviewTime;
    int InReviewBook;
};

//======================================================================
//  Dictionary Class
//======================================================================

class Dictionary {

public:

    /*----- member functions -----*/

//======================================================================
//  
    void save(){
        ofstream DicName;
        DicName.open(name.c_str());

        // Save all the info of WordS to a name.txt file
        // in the format:
        // key content ReviewCycle NextReviewTime

        map<string,Word>::iterator it;
        for ( it=dictionary.begin(); it != dictionary.end(); it++) {
            Word temp = it->second;
            string key = temp.getKey();
            string content = temp.getContent();
            int ReviewCycle = temp.getReviewCycle();
            int NextReviewTime = temp.getNextReviewTime();
            int InReviewBook = temp.CheckExisting();

            DicName << key
                    << "\t"
                    << content
                    << "\t"
                    << ReviewCycle
                    << "\t"
                    << NextReviewTime
                    << "\t"
                    << InReviewBook
                    << endl;
        }

        DicName.close();
    }

//======================================================================
//  
    void open(){
        ifstream DicName;
        DicName.open(name.c_str());

        // Read all info from the name.txt file into the dictionary

        for ( ;; ) {
            string temp;
            getline (DicName, temp);

            if (DicName.fail()) break;

            vector<string> wordInfo;
            wordInfo = split(temp);

            // Word variables declaration
            Word NewWord;
            string key = wordInfo[0];
            string content = wordInfo[1];
            string reviewCycle = wordInfo[2];
            string nextReviewTime = wordInfo[3];
            string inReviewBook = wordInfo[4];
            int ReviewCycle = atoi(reviewCycle.c_str());
            int NextReviewTime = atoi(nextReviewTime.c_str());
            int InReviewBook = atoi(inReviewBook.c_str());

            NewWord.setKey(key);
            NewWord.setContent(content);
            NewWord.setReviewCycle(ReviewCycle);
            NewWord.setNextReviewTime(NextReviewTime);
            NewWord.setInReviewBook(InReviewBook);

            // If the current time is greater or equal then the review
            // time, put the Word to the RivewBook.

            if (currentTime() >= NewWord.getNextReviewTime()) {
                NewWord.setInReviewBook(1);
                reviewBook.push_back(NewWord);
            }

            // Add the newword
            dictionary[key]=NewWord;

        }
    }

//======================================================================
//  
    /* void MainMenu(){

        for ( ;; ){

            // for debuggin, remove later
            // printDictionary();

            UpdateReviewBook();

            cout << getReviewBookSize()
                 << " words needed to review"
                 << endl;

            cout << "What do you want to do ? \n"
                 << "1. Add a word "
                 << "   "
                 << "2. Review "
                 << "   "
                 << "3. Update ReviewBook"
                 << "   "
                 << "4. Quit"
                 << endl;

            string WhatToDo;
            cin >> WhatToDo;
            cin.ignore(1000, '\n');

            if (WhatToDo == "1"){
                cout << endl << endl;
                AddWord();
                cout << endl << endl;
                continue;
            }

            if (WhatToDo == "2"){
                cout << endl << endl;
                Review();
                cout << endl << endl;
                continue;
            }

            if (WhatToDo == "3"){
                cout << endl << endl;
                UpdateReviewBook();
                MainMenu();
            }

            if (WhatToDo == "4"){
                cout << "\nGood bye! Please remember "
                     << "to review regularly!\n";
                save();
                exit(0);
            }
        }
    } */

//======================================================================
//  
    // insert() is only used to add a new word
    void insert(Word& w){
        map<string,Word>::iterator it;

        string k = w.getKey();
        it = dictionary.find(k);
        if (it == dictionary.end()) {
            dictionary[k]=w;
        }
    }

//======================================================================
//  
    void Delete(Word& w){
        string k = w.getKey();
        dictionary.erase (k);
    }

//======================================================================
//  
    void AddWord(string key, string content) {
        Word newWord;

        newWord.setKey(key);
        newWord.setContent(content);

        insert(newWord);
    }

//======================================================================
//  
    void ManageDic(){}

//======================================================================
//  
    void UpdateReviewBook(){
        reviewBook.clear();
        map<string,Word>::iterator it;
        for (it=dictionary.begin(); it != dictionary.end(); it++) {
            Word temp = it->second;
            if (temp.CheckExisting()){
                reviewBook.push_back(temp);
            }
            else if (currentTime() >= temp.getNextReviewTime()){
                string key = temp.getKey();
                temp.setInReviewBook(1);
                dictionary[key]=temp;
                reviewBook.push_back(temp);
            }
        }
    }

//======================================================================
//  
    void Review(){
        // Add feature to display how long since last reviewed
        UpdateReviewBook();

        // printReviewBook();

        if (reviewBook.size()==0){
            cout << "Nothing to Review!" << endl << endl;
            MainMenu();
        }

        for (int i=0; i < reviewBook.size() ; i++) {
            Word temp = reviewBook[i];
            string key = temp.getKey();
            string content = temp.getContent();
            string response;

            cout << key << endl;
            cout << "Do you Remember? y/n" << endl;

            cin >> response;
            if (response == "y") {
                cout << content
                     << endl << endl;
                Remember(i);
                continue;
            }
            else if (response == "n") {
                cout << content
                     << endl << endl;
                Forget(i);
                continue;
            }
            else if (response == "q") {
                MainMenu();
            }
            else {
                cout << "Invalid input" << endl;
                continue;
            }
        }

        // Call Review() until there are nothing to review
        //
    }

//======================================================================
//  
    bool sortReBook(){}

//======================================================================
//  
    void Remember(int i){
        Word temp = reviewBook[i];
        string key = temp.getKey();
        temp.increaseReviewCycle();
        temp.resetNextReviewTime();
        temp.setInReviewBook(0);
        dictionary[key] = temp;
    }

//======================================================================
//  
    void Forget(int i){
        Word temp = reviewBook[i];
        string key = temp.getKey();
        temp.resetReviewCycle();
        temp.resetNextReviewTime();
        temp.setInReviewBook(0);
        dictionary[key] = temp;
    }

//======================================================================
//  
    void ManageReviewBook(){}

//======================================================================
//  
    int getReviewBookSize() {
        return reviewBook.size();
    }

//======================================================================
//  
    void printReviewBook(){
        cout << "Review book size is: "
             << reviewBook.size() << endl;
        for(int i=0; i < reviewBook.size(); i++) {
            cout << "key:"
                 << reviewBook[i].getKey()
                 << " "
                 << "content:"
                 << reviewBook[i].getContent()
                 << endl;
        }
    }

//======================================================================
//  
    void printDictionary(){
        cout << "Dictionary size is: "
             << dictionary.size() << endl;

        map<string,Word>::iterator it;
        for (it=dictionary.begin(); it != dictionary.end(); it++) {
            Word temp = it->second;
            string key = temp.getKey();
            string content = temp.getContent();
            cout << "key:" << key << " "
                 << "content:" << content << endl;
        }
    }

//======================================================================
//  
    Dictionary (string dicName){
        name = dicName;
    }

private:

    /*----- data members -----*/

    string name;
    map<string,Word> dictionary;
    vector<Word> reviewBook;

};

#endif // MEMORIZER_H
