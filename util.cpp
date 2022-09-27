#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	set<string> results;

  rawWords = convToLower(rawWords);
  rawWords = trim(rawWords);
  rawWords = rawWords + " "; //adding space to the end of the word helps me retrieve the very last word

  string word = "";
  for (auto i : rawWords){
      if (i == ' '){ //end of the word
        if (word.length() >= 2){ //checking if word is >= 2 chars before adding
  
          string subWord = ""; 
          for (auto o : word){ //checking if word has punctuation 
              if (ispunct(o)) { //end of first half of the word containing puncuation 
                if (subWord.length() >= 2) { //only add this half of the word if it is >= 2 chars
                  results.insert(subWord);
                  subWord = "";
                }
                else { //if subWord is not greater than 2 chars, it is not a valid keyword, reset
                  subWord = "";
                }
              }
              else { //no puncuation yet, keep adding chars
              subWord = subWord + o;
              }
          }
          if (subWord.length() >= 2){ //to add the last word to the set
            results.insert(subWord);
          }
          word = "";
        } 
        else {
          word = "";
        }  
      } // end of if that checks for space 
      else { // there are more chars to be added to the word
        word = word + i;
      }
  }
return results;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

