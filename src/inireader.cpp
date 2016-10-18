/*
 * File:   iniReader.c++
 * Author: benmaynard
 *
 * Created on August 26, 2010, 2:49 PM
 */

#include <unordered_map>

#include "Log.h"

#include "inireader.h"

using namespace std;

static unordered_map<string, string> *ini = NULL;

static string parseOptionName(string value);
static string parseOptionValue(string value);
static string trim(string str, bool left, bool right);

void xsaitekpanels::parseIniFile(const char *fileName)
{
    ifstream infile;
    unordered_map<string, string> *newINI = NULL;
    string key;

    infile.open(fileName);

    //Does the file exist?
    if (infile.is_open() != true)
        return;

    newINI = new unordered_map<std::string, std::string>;

    while (!infile.eof())       // To get you all the lines.
    {
        string line;

        getline(infile, line);   // Saves the line in STRING.

        /* trim leading whitespace */
        line = trim(line, true, false);

        /* Is the option a comment */
        if (line[0] == '#' || line[0] == ';')
            continue;

        key = parseOptionName(line);
        if (key.length() > 0)
            (*newINI)[key] = parseOptionValue(line);
    }

    infile.close();

    if (ini != NULL)
        delete ini;
    ini = newINI;
}

void xsaitekpanels::cleanupIniReader()
{
    if (ini != NULL) {
        delete ini;
        ini = NULL;
    }
}

string xsaitekpanels::getOptionToString(string key)
{
    return (getOption(key, ""));
}

string xsaitekpanels::getOption(string key, string dfl_value)
{
    if (ini == NULL || ini->find(key) == ini->end())
        return (dfl_value);
    return ((*ini)[key]);
}

int xsaitekpanels::getOptionToInt(string key)
{
    return (getOption(key, 0));
}

int xsaitekpanels::getOption(string key, int dfl_value)
{
    if (ini == NULL || ini->find(key) == ini->end())
        return (dfl_value);
    return (atoi((*ini)[key].c_str()));
}

double xsaitekpanels::getOptionToDouble(string key)
{
    return (getOption(key, 0.0));
}

double xsaitekpanels::getOption(string key, double dfl_value)
{
    if (ini == NULL || ini->find(key) == ini->end())
        return (dfl_value);
    return (atof((*ini)[key].c_str()));
}

static string parseOptionName(string value)
{
    size_t found = value.find('=');

    if (found == string::npos)
        return "";

    return (trim(value.substr(0, found - 1), true, true));
}

static string parseOptionValue(string value)
{
    size_t found = value.find('=');

    if (found == string::npos)
        return ("");

    return (trim(value.substr(found + 1), true, true));
}

static string trim(string str, bool left, bool right)
{
    int n = str.length();
    int s = 0, e = n - 1;

    if (left) {
        for (; s < n; s++) {
            if (!isspace(str[s]))
                break;
        }
    }
    if (right) {
        for (e = n - 1; e >= 0; e--) {
            if (!isspace(str[e]))
                break;
        }
    }
    if (s <= e)
        return (str.substr(s, e - s + 1));
    else
        return ("");
}
