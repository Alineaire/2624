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

#endif // UTILS_H
