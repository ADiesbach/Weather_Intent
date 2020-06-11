#include<iostream>

#include "findIntent.cpp"

using namespace std;



int main(int argc, char *argv[]){
  string userInput;
  cout << "Hello! Input sentence: ";
  getline(cin,userInput);            // grabs user input
  cout << endl << endl;
  generateResponse(userInput);
  return 0;
}



// TO ADD:
// - take in days of the week as input
// - isolate number from a string (1st, 2nd, etc.)
