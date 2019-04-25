#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

/*
string split implementation by using delimeter as a character.
*/
vector<string> split(string strToSplit, char delimeter);

/*
string split implementation by using delimeter as an another string
*/
vector<string> split(string stringToBeSplitted, string delimeter);

/*
string to upper
*/
string toUpper(string _string);
/*
string to lower
*/
string toLower(string _string);

#endif // UTILS_H
