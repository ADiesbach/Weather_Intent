#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<ctime>
#include<stdlib.h>

using namespace std;


vector<string> returnTargets(string fileName, string userInput){
// This function goes through the input string and cross-checks every word with the ones on a file
// It returns the "target words" (words from the input file)

  ifstream theFile;
  theFile.open(fileName);
  string word, wordInput;
  string city, country;
  vector<string> targets, uinput;

  string temp;
  int i, factCheck = 0;

  istringstream iss(userInput);
  while(iss>>temp){                     // This loop separates every word of the user input
    if (temp=="fact"){factCheck = 1;}
    uinput.push_back(temp);             // ... and stores them (separated) in a vector
  }


// Check every word of the input vs every word in the file
// if it is the same, then store in "targets"
  if (factCheck == 1){                // If the word "fact" is detected, return that;
    targets.push_back("fact");
  }
  else if (fileName == "data/cities.csv"){      // the "cities" file has its own loop because it has 2 columns (one for city, one for country)
    while (getline(theFile, city, ',') && getline(theFile, country, '\n')){
      for (i=0;i<uinput.size();i++){
        if (city == uinput[i]){
          targets.push_back(city);
          targets.push_back(country);
        }
      }
    }
  }
  else if (factCheck==0){             // for all the other files (single column)
    while (getline(theFile,word)){
      for (i=0;i<uinput.size();i++){
        if(word==uinput[i]){
            targets.push_back(word);
        }
      }
    }
  }

  theFile.close();
  return targets;
}



// Generates random fact from file
void printFact(){
  ifstream file;
  file.open("data/facts.csv");
  int i = 0, r;
  string line;

  srand(time(NULL));
  r = rand() % 13;

  while (getline(file,line)){
    if (i==r){cout<<line;}
    i++;
  }

}



int main(int argc, char *argv[]){
  int i=0;
  string userInput;
   cout << "Hello! Input sentence: ";
   getline(cin,userInput);            // grabs user input

   cout << endl << endl;

   vector<string> weatherTW, timeTW, citiesTW, factTW;

   time_t now = time(0);
   tm *ltm = localtime(&now);
   int currentday = ltm->tm_mday;
   int checkDate = currentday;

   factTW = returnTargets(" ",userInput);       // check for "fact"

   // Checks for target words (eg. today, weather, sunny, etc.)
   if (factTW.empty()){
     weatherTW = returnTargets("data/weatherWords.csv",userInput);
     timeTW = returnTargets("data/timeWords.csv", userInput);
     citiesTW = returnTargets("data/cities.csv", userInput);
   }

   // Calculates the date at which wheather should get checked from user intput
   // Default: today
   if (!timeTW.empty()){
      if (timeTW[0] == "tomorrow"){checkDate = currentday+1;}
      else if (timeTW[0] == "today"){;}
      else if (timeTW[0] == "yesterday"){checkDate = currentday-1;}
      else {checkDate = stoi(timeTW[0]);}
  }

   if (!factTW.empty()){
     printFact();
   }

   // Answer to general weather questions (eg. what is the weather?)
   if ((weatherTW.size()==1) and (weatherTW[0] == "weather")){
     if (!timeTW.empty()){
       cout << "The weather on day " << checkDate << " of month " << 1+ltm->tm_mon <<  " is [get weather]";
     }
     else {
       cout << "The weather today is [weather]";
     }
   }

   // Answer to yes/no questions (eg. Will it rain?)
   for (i=0; i<weatherTW.size();i++){
     if (weatherTW[i] == "sun" || weatherTW[i] == "rain" ||  weatherTW[i] == "clouds" ||  weatherTW[i] == "snow" || weatherTW[i] == "clouds" || weatherTW[i] == "storm" || weatherTW[i] == "wind"){
       cout << "There [will/will not] be " << weatherTW[i] << " on day " << checkDate << " of month " << 1+ltm->tm_mon;
     }
     else if (weatherTW[i] == "sunny" || weatherTW[i] == "rainy" ||  weatherTW[i] == "cloudy" ||  weatherTW[i] == "snowy" || weatherTW[i] == "stormy" || weatherTW[i] == "windy"){
       cout << "It [will/will not] be " << weatherTW[i] << " on day " << checkDate << " of month " << 1+ltm->tm_mon;
     }
   }

   // Addendum: city
   if (!citiesTW.empty()){
     cout << " in " << citiesTW[0] << ", " << citiesTW[1];
   }
   cout << endl;
   return 0;
}



// TO ADD:
// - take in days of the week as input
// - isolate number from a string (1st, 2nd, etc.)
