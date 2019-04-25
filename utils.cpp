#ifndef UTILS_H
#define UTILS_H

#include "utils.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <locale>

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

/*
string to upper
*/
string toUpper(string _string)
{
    locale loc;
    string output = "";
    for (string::size_type i = 0; i < _string.length(); ++i)
        output += toupper(_string[i], loc);
    return output;
}

/*
string to lower
*/
string toLower(string _string)
{
    locale loc;
    string output = "";
    for (string::size_type i = 0; i < _string.length(); ++i)
        output += tolower(_string[i], loc);
    return output;
}

#endif // UTILS_H
