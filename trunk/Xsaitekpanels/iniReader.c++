/*
 * File:   iniReader.c++
 * Author: benmaynard
 *
 * Created on August 26, 2010, 2:49 PM
 */

#include "iniReader.h"

using namespace std;

struct ConfigItems {
	std::string key;
	std::string value;
};
ConfigItems* iniItem[1024];

int i = 0;


void parseIniFile(char *fileName)
{
	std::string optionValue;
	ifstream infile;
	infile.open(fileName);

	//Does the file exist?
	if (infile.is_open() != true)
	{
		return;
	}

    std::string key;

	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, optionValue); // Saves the line in STRING.

		//Is the option a comment
		if (optionValue.substr(0, 1) == "#")
		{
			continue;
		}

		key = parseOptionName(optionValue);

		if (key.length() > 0)
		{
			iniItem[i] = new ConfigItems;
			iniItem[i]->key = key;
			iniItem[i]->value = parseOptionValue(optionValue);
			i++;
		}
	}

	i--;
	infile.close();
}

void cleanupIniReader()
{
	for (int x = 0; x <= i; x++)
	{
		delete iniItem[x];
	}

	i = 0;
}

std::string getOptionToString(std::string key)
{
	//Check to see if anything got parsed?
	if (i == 0)
	{
		return "";
	}

	for (int x = 0; x <= i; x++)
	{
		if (key == iniItem[x]->key)
		{
			return iniItem[x]->value;
		}
	}
	
	return "";
}

const char *getOptionToChar(std::string key)
{
	//Check to see if anything got parsed?
	if (i == 0)
	{
		return "";
	}

	for (int x = 0; x <= i; x++)
	{
		if (key == iniItem[x]->key)
		{
			return iniItem[x]->value.c_str();
		}
	}

	return "";
}

int getOptionToInt(std::string key)
{
	//Check to see if anything got parsed?
	if (i == 0)
	{
		return 0;
	}

	for (int x = 0; x <= i; x++)
	{
		if (key == iniItem[x]->key)
		{
			return atoi(iniItem[x]->value.c_str());
		}
	}

	return 0;
}

std::string parseOptionName(std::string value)
{
	size_t found;

	found = value.find('=');

	if (found > 100)
	{
		return "";
	}

	std::string key = value.substr(0, (found-1));
	key = trim(key);

	return key;
}

std::string parseOptionValue(std::string value)
{
	size_t found;

	found = value.find('=');

	if (found > 100)
	{
		return "";
	}

	std::string keyValue = value.substr((found+1));
	keyValue = trim(keyValue);

	return keyValue;
}

std::string trim(std::string s)
{
	return ltrim(rtrim(s));
}

// trim from start
std::string ltrim(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
std::string rtrim(std::string s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}
