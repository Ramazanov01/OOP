#include <string>
#include <iostream>
using namespace std;
#include "WordString.h"
int main(){
WordString ws1, ws2;
//A WordString object can be initialized with a c-string;
WordString ws3("This is a c-string literal");
//A WordString object can be initialized with std::string object
string boringString = "Just another literal living in this main function";
WordString ws4(boringString);
//Lets print some string data
//This should print the following without quotes
//"Just another literal living in this main function"
cout<<ws4<<endl;
//As you can see, the data is exactly the same with the std::string content.
//So, WordString can be used like a std::string
//Return the std::string form of the data
string catcher = ws3.toString();
cout<<catcher<<endl;
//"This is a c-string literal" is printed.
ws3 = boringString;
//ws3 has the same contents with boringString.
//We can even get data from stdin
cin>>ws3;
cout<<ws3<<endl;
//Of course, the capture will stop with the first whitespace.
//You don't have to capture a sentence of words.
//WordString specific functionality
//return the number of words.
int c = ws4.numberOfWords();
cout<<c<<endl;
//This prints 8
//Returns one of the words as a copy (index starts from 0)
string word5 = ws4.get(5);
cout<<word5<<endl;
//prints "this" without quotes
//replace a word with a new one
string new_word = "new word one";
ws4.replace(3,new_word);
//replaces "living" with "new"
cout<<ws4.get(3)<<endl;
c = ws4.numberOfWords();
cout<<c<<endl;
//prints "new" without quotes
//The rest of the data is not modified.
cout<<ws4<<endl;
//This prints the following
//"Just another literal new in this main function"
//inserting new string. BE CAREFUL, INSERTED STRING MAY INCLUDE MULTIPLE WORDS
//add ONE space before and after the inserted string.
ws4.insertAfter(3,string("inserted string"));
cout<<ws4<<endl;
//This prints the following
//"Just another literal new inserted string in this main function"
//remove one word
//Remove one space before or after the removed word.
//Remove the space after if the removed word is the first word.
//Remove a space before, if it is not the first word.
//Do not remove any spaces it there is only one word in the object.
ws4.remove(4);
cout<<ws4<<endl;
 //Prints: "Just another literal new string in this main function"
 //Strip extra spaces.
 //Delete spaces if here are multiple concurrent spaces.
 //Example:
 //word1   word2 word3
 WordString ws5 = "word1            word2 word3";
 ws5.strip();
 //Stripped example:
//word1 word2 word3
 cout<<ws5<<endl;
 //Prints: "word1 word2 word3"
 //Adding two objects. Insert a space before the second operant.
 ws2 = ws4 + ws3;
 cout<<"ws2: "<<ws2<<endl;
 //Adding wordString and a string
 string additional_string("additional data");
 ws2 = ws4 + additional_string;
 }



