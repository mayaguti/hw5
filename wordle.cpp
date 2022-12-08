// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generatePermutations(
	const std::string& in,
	const std::string& floating,
	std::set<std::string>& validSuggestions,
	int blanks);
void makeValid( 
	std::set<std::string>& validSuggestions, 
	const std::string& floating,
	const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> validSuggestions = {};

		//if no in
		if(in.empty()){
			return validSuggestions;
		}

		int blanks = 0;
		for(unsigned int i = 0; i < in.size(); i++){
			if(in[i]=='-'){
				blanks++;
			}
		}

		generatePermutations(in, floating, validSuggestions, blanks);
		makeValid(validSuggestions, floating, dict);

		return validSuggestions;
}

// Define any helper functions here
void generatePermutations(
	const std::string& in,
	const std::string& floating,
	std::set<std::string>& validSuggestions,
	int blanks)
{
    if (blanks < 1){ // base case
			validSuggestions.insert(in);
			return;
		}
		if(floating.length() == 0){ //permutation incomplete, no floating remain
			for(unsigned int i = 0; i < in.length(); i++){
				std::string inTemp = in;
				if(in[i] == '-'){
					for(int j = 0; j < 26; j++){
						inTemp[i] = (char)(j+97);
						generatePermutations(inTemp, floating, validSuggestions, blanks-1);
					}
				}
			}
		}
		else{ //permutation incomplete, floating remain
			for(unsigned int i = 0; i < in.length(); i++){
				std::string inTemp = in;
				if(in[i] == '-' && blanks >= (int)floating.length()){
					for(unsigned int j = 0; j < floating.length(); j++){
						inTemp[i] = floating[j];
						std::string floatingTemp = floating;
						floatingTemp.erase(j, 1);
						generatePermutations(inTemp, floatingTemp, validSuggestions, blanks-1);
					}
				}
			}
		}
}

// goes through set and removes invalid permutations
void makeValid( 
	std::set<std::string>& validSuggestions,
	const std::string& floating,
	const std::set<std::string>& dict)
{
	for(std::set<std::string>::iterator it = validSuggestions.begin(); it != validSuggestions.end(); it++){
		if(dict.find(*it) == dict.end()){
			validSuggestions.erase(it);
		}
	}
	for(std::set<std::string>::iterator it = validSuggestions.begin(); it != validSuggestions.end(); it++){
		for(unsigned int i = 0; i < floating.length(); i++){
			std::string temp = *it;
			if(temp.find(floating[i], 0) == std::string::npos){
				validSuggestions.erase(it);
			}
		}
	}
	for(std::set<std::string>::iterator it = validSuggestions.begin(); it != validSuggestions.end(); it++){
		if(dict.find(*it) == dict.end()){
			validSuggestions.erase(it);
		}
	}
	return;
}