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

int str2num_Month(string str){
  if (str == "january"){return (1);}
  else if (str == "february"){return (2);}
  else if (str == "march"){return (3);}
  else if (str == "april"){return (4);}
  else if (str == "may"){return (5);}
  else if (str == "june"){return (6);}
  else if (str == "july"){return (7);}
  else if (str == "august"){return (8);}
  else if (str == "september"){return (9);}
  else if (str == "october"){return (10);}
  else if (str == "november"){return (11);}
  else if (str == "december"){return (12);}
  else {return (0);}
}




string generateResponse(string userInput){
  int i=0;

   vector<string> weatherTW, timeTW, citiesTW, factTW;
   string response = "INTENT: ";

   time_t now = time(0);
   tm *ltm = localtime(&now);
   int currentday = ltm->tm_mday;
   int checkDate = currentday;
   int checkMonth = 1+ltm->tm_mon;

   factTW = returnTargets(" ",userInput);       // check for "fact"
   if (!factTW.empty()){
     printFact();
     response.append("Fact");
     cout << endl <<response;
     return(response);
   }

   // Checks for target words (eg. today, weather, sunny, etc.)
   if (factTW.empty()){
     weatherTW = returnTargets("data/weatherWords.csv",userInput);
     timeTW = returnTargets("data/timeWords.csv", userInput);
     citiesTW = returnTargets("data/cities.csv", userInput);
   }

   // Calculates the date at which wheather should get checked from user intput
   // Default: today, current month
   for (i=0;i<timeTW.size();i++){
      if (timeTW[i] == "tomorrow"){checkDate = currentday+1;}
      else if (timeTW[i] == "today"){;}
      else if (timeTW[i] == "yesterday"){checkDate = currentday-1;}
      else if (str2num_Month(timeTW[i])!=0){checkMonth = str2num_Month(timeTW[i]);}
      else {checkDate = stoi(timeTW[i]);}
  }



   // Answer to general weather questions (eg. what is the weather?)
   if ((weatherTW.size()==1) and (weatherTW[0] == "weather")){
     response.append("Get weather");
     if (!timeTW.empty()){
       cout << "The weather on day " << checkDate << " of month " << checkMonth <<  " is [get weather]";
     }
     else {
       cout << "The weather today is [weather]";
     }
   }

   // Answer to yes/no questions (eg. Will it rain?)
   for (i=0; i<weatherTW.size();i++){
     if (weatherTW[i] == "sun" || weatherTW[i] == "rain" ||  weatherTW[i] == "clouds" ||  weatherTW[i] == "snow" || weatherTW[i] == "clouds" || weatherTW[i] == "storm" || weatherTW[i] == "wind"){
       response.append("Get [YES/NO] if ");
       response.append(weatherTW[i]);
       cout << "There [will/will not] be " << weatherTW[i] << " on day " << checkDate << " of month " << checkMonth;
     }
     else if (weatherTW[i] == "sunny" || weatherTW[i] == "rainy" ||  weatherTW[i] == "cloudy" ||  weatherTW[i] == "snowy" || weatherTW[i] == "stormy" || weatherTW[i] == "windy"){
       response.append("Get [YES/NO] if ");
       response.append(weatherTW[i]);
       cout << "It [will/will not] be " << weatherTW[i] << " on day " << checkDate << " of month " << checkMonth;
     }
   }

   if (!weatherTW.empty()){
     response.append(" On Day: ");
     response.append(to_string(checkDate));
     response.append(" Month: ");
     response.append(to_string(checkMonth));

   }



   // Addendum: city
   if (!citiesTW.empty()){
     response.append(" Location: ");
     response.append(citiesTW[0]);
     cout << " in " << citiesTW[0] << ", " << citiesTW[1];
   }

   if (response == "INTENT: "){cout << "Your question was not understood.";}

   cout <<endl<< response;
   cout << endl;
   return(response);
}
