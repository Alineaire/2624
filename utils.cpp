#ifndef UTILS_H
#define UTILS_H

#include "utils.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <locale>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

using namespace std;

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

string toUpper(string _string)
{
    locale loc;
    string output = "";
    for (string::size_type i = 0; i < _string.length(); ++i)
        output += toupper(_string[i], loc);
    return output;
}

string toLower(string _string)
{
    locale loc;
    string output = "";
    for (string::size_type i = 0; i < _string.length(); ++i)
        output += tolower(_string[i], loc);
    return output;
}

bool beginWith(const string str, const string needle)
{
    return (!str.compare(0, needle.length(), needle));
}

bool endWith(const string str, const string needle)
{
    if (str.length() >= needle.length())
    {
        return (0 == str.compare (str.length() - needle.length(), needle.length(), needle));
    }
    return false;
}

void getFilesLocation(string folder, vector<string>& filesNameList, string typeFile)
{
	DIR *dir;
	struct dirent *entry;
	struct stat info;

	if ((dir = opendir(folder.c_str())) == NULL)
	{
		perror("opendir() error");
	}
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
            string path = folder + (endWith(folder, "/") ? "" : "/") + entry->d_name;
			// If the current file is a typeFile file, we add it to the list
			if (endWith(entry->d_name, typeFile))
			{
				filesNameList.push_back(path);
			}

			if (entry->d_name[0] != '.')
			{
				stat(path.c_str(), &info);
				// If the current file is a directory, we go in and check the content
				if (S_ISDIR(info.st_mode))
					getFilesLocation(path, filesNameList, typeFile);
			}
		}
		closedir(dir);
	}
}

#endif // UTILS_H
