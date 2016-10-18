/*
 * File:   iniReader.h
 * Author: benmaynard
 *
 * Created on August 26, 2010, 2:49 PM
 */

#ifndef INIREADER_H
#define	INIREADER_H

#include <string>
#include <fstream>
#include <algorithm>

namespace xsaitekpanels {

    /**
     * Parse a configuration file
     *
     * @param	fileName The name of the file to parse
     * @return	none
     */
    void parseIniFile(const char *fileName);

    /**
     * If you are finished with the config item, use this function
     * to cleanup the results
     *
     * @return none
     */
    void cleanupIniReader();

    /**
     * Return the value of the requested key in with the string type
     *
     * @param	key The option key
     * @return	string The value of the requested key
     */
    std::string getOptionToString(std::string key);
    std::string getOption(std::string key, std::string dfl_value);

    /**
     * Return the value of the requested key in with the int type
     *
     * @param	key The option key
     * @return	int The value of the requested key
     * @note	If item is not an integer (or does not exist) then 0 will
     *		be returned.
     */
    int getOptionToInt(std::string key);
    int getOption(std::string key, int dfl_value);

    /*
     * Same thing as getOptionToInt, but returning a double.
     */
    double getOptionToDouble(std::string key);
    double getOption(std::string key, double dfl_value);
}

#endif /* INIREADER_H */
