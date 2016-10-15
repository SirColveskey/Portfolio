/*===================================================*/
/*       WELCOME TO THE TEXT FILE INDEX              */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 9/18/2015                         */
/*        UPDATED: 9/18/2015                         */
/*===================================================*/

// Purpose: Single function program to read a text file
//          and sort the contents, numerating character
//          word, and number values.
//          The top 10 occuring values are printed in
//          order of occurance with various sub rules.
//
// Method:  Map and Multimap containers are used in
//          order to numerate and keep track of the
//          various words/numbers/characters which are
//          being numerated.
//          Order is modified by appending a character
//          to the front of strings where appropriate.
// 
// Possible Improvements:
//          Replace the maps numMap and wordMap with
//          vector of pairs to eliminate the need for
//          order maps.
//          Create sub functions to improve clarity.

#include <cctype>    //tolower, isdigit, isalpha
#include <string>    //string container used
#include <iostream>  //cout stream used
#include <iomanip>   //table formatting used
#include <map>       //map container used, and multimap

using namespace std; 

int main()
{
  map<char, int> charMap;         //counts occurances
  map<string, int> numMap;
  map<string, char> numOrd;       //orders occurances
  map<string, int> wordMap;
  map<string, char> wordOrd;
  multimap<int, char> charList;   //sorts by frequency
  multimap<int, string> numList;
  multimap<int, string> wordList;
  bool wordON=0;
  char current=0;
  char next=0;
  int numBuilder;
  string builder="";
  char wordCount=65;
  char numCount=65;

  next=cin.peek();


  while(next != EOF) //when the stream isn't over
  {
    cin.get(current);
    ++charMap[current];
    next=cin.peek();


    // NUMBERS ****************************************************************************************************

    if(isdigit(current))
    {
      if(isdigit(next)) //if there is another digit to the number
      {
        builder=builder+current; //builder is a construction of x
      }
      else
      {
        
        /* Elaboration: The numCount, which is appended to the 
        front of the word after it is constructed allows for the ordering of 
        words and numbers in order of appearance, given same frequency. */
        
        builder=builder+current;
        if(numOrd.find(builder)==numOrd.end())
	{
	  numOrd.emplace(builder,numCount); 
	  builder=numCount+builder;
	  numCount=numCount + 1;
	}
	else //determines if a particular word already happened
	{    //thus prevents each word being unique
	  auto it=numOrd.find(builder);
	  char count=it->second;
	  builder=count+builder;
	}
        ++numMap[builder];
        builder.clear();
      }
    }
   
   
   
   // WORDS *********************************************************************************************************
   
    if(isalpha(current))
    {
      wordON=1;
    }
    if(wordON)
    {
      current=tolower(current);
      builder=builder+current;
    }
    if(!isalpha(next)&&isalpha(current))
    {
      if(wordON)
      {
        if(wordOrd.find(builder)==wordOrd.end())
           {
            wordOrd.emplace(builder,wordCount); 
            builder=wordCount+builder;        
	    wordCount=wordCount + 1;
	   // cout << wordCount << endl; //DEBUGGING
           }
        else
           {
             auto it=wordOrd.find(builder);
             char count=it->second;
	     builder=count+builder;
           }
        ++wordMap[builder];
      }
      builder.clear();
      wordON=0;
    }
  }

  //LOADING TO MULTIMAPS -- This allows for sorting by frequency! Suborder=order loaded
  for(std::map<char,int>::reverse_iterator it=charMap.rbegin(); it!=charMap.rend(); ++it)
  {
    charList.insert(pair<int,char>(it->second,it->first));
  }
  for(std::map<string,int>::reverse_iterator it=numMap.rbegin(); it!=numMap.rend(); 
++it)
  {
    numList.insert(pair<int,string>(it->second,it->first));
  }
  for(std::map<string,int>::reverse_iterator it=wordMap.rbegin(); 
it!=wordMap.rend(); ++it)
  {
    wordList.insert(pair<int,string>(it->second,it->first));
  }
  
  /* \/\/\/\/\/\/\/\/\/ OUTPUT \/\/\/\/\/\/\/\/\/\/ */

  //PRINTING CHARACTERS -- prints top 10 most used
  cout << "Total " << charList.size() << " different characters, ";
  if(charList.size()>10){ cout<< "10"; } else {cout<<charList.size();} 
  cout <<  " most used characters: " << '\n';
  int counter=0;
  for(std::multimap<int,char>::reverse_iterator rit=charList.rbegin(); 
rit!=charList.rend(); ++rit)
  {
    cout <<"No. " << counter <<": ";
    counter++;
    if(rit->second != '\n' && rit->second != '\t') //special case for newline char
      cout << left << setw(17) << rit->second << rit->first << '\n';
    else if(rit->second == '\t') //special case for newline char
      cout << left << setw(17) << "\\t" << rit->first << '\n';
    else
      cout << left << setw(17) << "\\n" << rit->first << '\n';
    if(counter==10){break;}
  }
  cout << endl;

  //PRINTING WORDS
  cout << "Total " << wordList.size() << " different words, "; 
  if(wordList.size()>10){ cout<< "10"; } else {cout<<wordList.size();}
  cout << " most used words: " << '\n';
  counter=0;
  for(std::multimap<int,string>::reverse_iterator rit=wordList.rbegin(); 
rit!=wordList.rend(); ++rit)
  {
    
    rit->second.front()=0;
    cout << "No. " << counter << ": " << left << setw(18) << rit->second << rit->first << '\n';
    counter++;
    if(counter==10){break;}
  }
  cout << endl;

  //PRINTING NUMBERS
  cout << "Total " << numList.size() << " different numbers, ";
  if(numList.size()>10){ cout<< "10"; } else {cout<<numList.size();}
  cout << " most used numbers: " << '\n';
  counter=0;
  for(std::multimap<int,string>::reverse_iterator rit=numList.rbegin(); 
rit!=numList.rend(); ++rit)
  {
    rit->second.front()=0;
    cout << "No. " << counter <<": " << left << setw(18) << rit->second << rit->first << '\n';
    counter++;
    if(counter==10){break;}
  }

  return 0;
}
