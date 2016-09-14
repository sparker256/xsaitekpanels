/*
 * File:   iniReader.c++
 * Author: benmaynard
 *
 * Created on August 26, 2010, 2:49 PM
 */

#include <functional>
#include <cctype>

#include "inireader.h"

using namespace std;

struct ConfigItems
{
    std::string key;
    std::string value;
};
static ConfigItems *iniItem[1300];

static int i = 0;

void xsaitekpanels::parseIniFile(const char *fileName)
{
    std::string optionValue;
    std::ifstream infile;
    infile.open(fileName);

    //Does the file exist?
    if (infile.is_open() != true) {
        return;
    }

    std::string key;

    while (!infile.eof())       // To get you all the lines.
    {
        getline(infile, optionValue);   // Saves the line in STRING.

        //Is the option a comment
        if (optionValue.substr(0, 1) == "#") {
            continue;
        }

        key = parseOptionName(optionValue);

        if (key.length() > 0) {
            iniItem[i] = new ConfigItems;
            iniItem[i]->key = key;
            iniItem[i]->value = parseOptionValue(optionValue);
            i++;
        }
    }

    i--;
    infile.close();
}

void xsaitekpanels::cleanupIniReader()
{
    for (int x = 0; x <= i; x++) {
        delete iniItem[x];
    }

    i = 0;
}

string xsaitekpanels::getOptionToString(string key)
{
    //Check to see if anything got parsed?
    if (i == 0) {
        return "";
    }

    for (int x = 0; x <= i; x++) {
        if (key == iniItem[x]->key) {
            return iniItem[x]->value;
        }
    }

    return "";
}

const char *xsaitekpanels::getOptionToChar(string key)
{
    //Check to see if anything got parsed?
    if (i == 0) {
        return "";
    }

    for (int x = 0; x <= i; x++) {
        if (key == iniItem[x]->key) {
            return iniItem[x]->value.c_str();
        }
    }

    return "";
}

int xsaitekpanels::getOptionToInt(string key)
{
    //Check to see if anything got parsed?
    if (i == 0) {
        return 0;
    }

    for (int x = 0; x <= i; x++) {
        if (key == iniItem[x]->key) {
            return atoi(iniItem[x]->value.c_str());
        }
    }

    return 0;
}

double xsaitekpanels::getOptionToFloat(string key)
{
    //Check to see if anything got parsed?
    if (i == 0) {
        return 0;
    }

    for (int x = 0; x <= i; x++) {
        if (key == iniItem[x]->key) {
            return atof(iniItem[x]->value.c_str());
        }
    }

    return 0;
}

string xsaitekpanels::parseOptionName(string value)
{
    size_t found;

    found = value.find('=');

    if (found > 100) {
        return "";
    }

    std::string key = value.substr(0, (found - 1));
    key = trim(key);

    return key;
}

string xsaitekpanels::parseOptionValue(string value)
{
    size_t found;

    found = value.find('=');

    if (found > 100) {
        return "";
    }

    std::string keyValue = value.substr((found + 1));
    keyValue = trim(keyValue);

    return keyValue;
}

string xsaitekpanels::trim(string s)
{
    return ltrim(rtrim(s));
}

// trim from start
string xsaitekpanels::ltrim(string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun < int, int >(std::isspace))));
    return s;
}

// trim from end
string xsaitekpanels::rtrim(string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun < int,
        int >(std::isspace))).base(), s.end());
    return s;
}
