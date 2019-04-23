#ifndef UTILS_H
#define UTILS_H

#include "utils.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

/*
string split implementation by using delimeter as a character.
*/
vector<string> split(string strToSplit, char delimeter)
{
    stringstream ss(strToSplit);
    string item;
	vector<string> splittedStrings;
    while (getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
    }
	return splittedStrings;
}

/*
string split implementation by using delimeter as an another string
*/
vector<string> split(string stringToBeSplitted, string delimeter)
{
	vector<string> splittedString;
	unsigned int startIndex = 0;
	unsigned int  endIndex = 0;
	while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
	{

		string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();
	}
	if(startIndex < stringToBeSplitted.size())
	{
		string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;

}

#endif // UTILS_H