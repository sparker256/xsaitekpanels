/*
 * File:   iniReader.c++
 * Author: benmaynard
 *
 * Created on August 26, 2010, 2:49 PM
 */

#include <functional>
#include <cctype>
#include <map>
#include <vector>
#include <stdexcept>

#include "inireader.h"

using namespace std;

enum INILineType {
    EMPTY,
    KEY,
    COMMENT
};

struct INILine
{
    INILine(INILineType type, const std::string& value) : Type(type), Value(value) {}

    INILineType Type;
    std::string Value;
};

enum VariableType {
    INT,
    DOUBLE,
    STRING
};

struct INIVariable
{
    INIVariable() {}
    INIVariable(VariableType type, void* pointer) : Type(type), Pointer(pointer) {}

    std::string Get() const {
        char buff[100];

        switch (Type)
        {
            case VariableType::DOUBLE:
                snprintf(buff, sizeof(buff), "%f", *((double*) Pointer));
                return buff;
            case VariableType::INT:
                snprintf(buff, sizeof(buff), "%d", *((int*) Pointer));
                return buff;
        }

        return *((std::string*)Pointer);
    }

    void* Pointer;
    VariableType Type;
};

std::map<std::string, INIVariable> VariablesPointersMap;
std::vector<std::string> KeysFromUIPanel;

std::vector<INILine> INIFileStruct;

std::map<std::string, std::string> configMap;

void parseIniFile(char *fileName)
{
        std::string optionValue;
        std::ifstream infile;
        infile.open(fileName);

        cleanupIniReader();

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
                if (optionValue.substr(0, 1) == "#" || optionValue.substr(0, 1) == ";")
                {
                    INIFileStruct.push_back(INILine(INILineType::COMMENT, optionValue));
                    continue;
                }
                else
                {
                    key = parseOptionName(optionValue);

                    if (key.length() > 0)
                    {
                        INIFileStruct.push_back(INILine(INILineType::KEY, key));
                        configMap[key] = parseOptionValue(optionValue);
                    }
                    else
                    {
                        INIFileStruct.push_back(INILine(INILineType::EMPTY, optionValue));
                    }
                }
        }

        infile.close();
}

void saveIniFile(char* fileName)
{
    std::ofstream outfile;
    outfile.open(fileName, std::ios::trunc);

    for (const auto& line : INIFileStruct)
    {
        if (line.Type == INILineType::KEY)
        {
            std::string val = (VariablesPointersMap.find(line.Value) != VariablesPointersMap.end()) ? VariablesPointersMap[line.Value].Get() : configMap[line.Value];
            outfile << line.Value << " = " << val << std::endl;
        }
        else
        {
            outfile << line.Value << std::endl;
        }
    }

    for (const auto& uiKey : KeysFromUIPanel)
    {
        //UI modified variables that wasn't previously in INI file
        if (configMap.find(uiKey) == configMap.end())
        {
            std::string val = (VariablesPointersMap.find(uiKey) != VariablesPointersMap.end()) ? VariablesPointersMap[uiKey].Get() : configMap[uiKey];

            outfile << uiKey << " = " << val << std::endl;
        }
    }

    outfile.close();
}

void cleanupIniReader()
{
        configMap.clear();
        INIFileStruct.clear();
        VariablesPointersMap.clear();
        KeysFromUIPanel.clear();
}

std::string getOptionToString(std::string key)
{
    try {
        return configMap.at(key);
    }
    catch (const std::out_of_range& oor) {
        return "";
    }
}

const char *getOptionToChar(std::string key)
{
    try {
        return configMap.at(key).c_str();
    }
    catch (const std::out_of_range& oor) {
        return "";
    }
}

int getOptionToInt(std::string key)
{
    try {
        return atoi(configMap.at(key).c_str());
    }
    catch (const std::out_of_range& oor) {
        return 0;
    }
}

void readOptionAsInt(std::string key, int * value, bool UI_Configurable)
{
    if (UI_Configurable)
    {
        if (std::find(KeysFromUIPanel.begin(), KeysFromUIPanel.end(), key) == KeysFromUIPanel.end())
            KeysFromUIPanel.push_back(key);
    }

    VariablesPointersMap[key] = INIVariable(VariableType::INT, (void*)value);

    try {
        *value = atoi(configMap.at(key).c_str());
    }
    catch (const std::out_of_range& oor) {
    }
}

void readOptionAsDouble(std::string key, double* value, bool UI_Configurable)
{
    if (UI_Configurable)
    {
        if(std::find(KeysFromUIPanel.begin(), KeysFromUIPanel.end(), key) == KeysFromUIPanel.end())
            KeysFromUIPanel.push_back(key);
    }
       
    VariablesPointersMap[key] = INIVariable(VariableType::DOUBLE, (void*)value);

    try {
        *value = atof(configMap.at(key).c_str());
    }
    catch (const std::out_of_range& oor) {
    }
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
