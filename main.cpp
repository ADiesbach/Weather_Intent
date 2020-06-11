#include<iostream>

#include "findIntent.cpp"

using namespace std;



int main(int argc, char *argv[]){
  while (1){
    string userInput;
    char temp;
    cout << endl << endl << "Hello! Please write a question about the weather (can also add date + city), or ask for a fact!" << endl;
    cout << "(see ReadMe for example of questions.)"<< endl;
    cout << "Please write in lowercase letters." << endl << endl << ">";
    getline(cin,userInput);            // grabs user input
    cout << endl;
    generateResponse(userInput);
    cout <<endl<< "(Press enter to start again)";
    cin.get(temp);

  }
  return 0;
}
