 // ****** bippanel.cpp **********
// ****  William R. Good  ********


#if IBM
#include <windows.h>
BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return true;
}
#endif

#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMCamera.h"
#include "XPLMPlanes.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMMenus.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"

#include "hidapi.h"
#include "saitekpanels.h"

#include <vector>

#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

#define MAXTABLEELEMENTS 1000

//MAXINDICATORS is the Position of indicators in one row
#define MAXINDICATORS 8
// ********************** Bip Panel variables ***********************
float   LookAtThisValue;
int     LookAtThisIntValue;

static unsigned char bipwbuf[4][10];
static unsigned char lastbipwbuf[4][10];

static int bipchange, biploop[4], res, i[4];

struct  BipTableStructure
{
    char            Row; // A B or C
    int             Position; // 0 tru 7
    char            Color;  // G green R red A amber
    XPLMDataRef     DataRefToSet;
    XPLMDataTypeID  DataRefType;
    int             DataRefIndex;
    char            WhatToDo;
    float           FloatValueToSet;
    float           FloatLimit;
    char            CSVDebugString[512];
};

static BipTableStructure    BipTable[4][MAXTABLEELEMENTS];

static int                  LastTableElement[4] = {-1, -1, -1, -1};
static int                  ErrorInLine = 0;
static bool                 InSilentMode = false;

static char     MenuEntries[4][50][250];

static int      LastMenuEntry[4] = {0, 0, 0, 0};

bool ReadConfigFile(string PlaneICAO);
void WriteCSVTableToDisk(void);


void LetWidgetSay(string BipTextToDisplay)
{

    XPSetWidgetDescriptor(BipWidgetID, BipTextToDisplay.c_str());
    int x = XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_width")) - (int) XPLMMeasureString(xplmFont_Proportional, BipTextToDisplay.c_str(), BipTextToDisplay.length()) - 10;
    int y = XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_height")) - 35;
    XPSetWidgetGeometry(BipWidgetID, x, y, x+5, y-5);


}

void logMsg ( std::string message )
{
  std::string out = message + "\n";
  XPLMDebugString(const_cast<char *> (out.c_str()));
  if (!InSilentMode) XPLMSpeakString(message.c_str());
  stringstream  ErrorHelper;
  out.erase();
  ErrorHelper << ErrorInLine;
  ErrorHelper >> out;
  LetWidgetSay(message.append(" (in line no. ").append(out).append(")"));
}

void WriteCSVTableToDisk(void)
{
    time_t      rawtime;
    struct      tm * timeinfo;
    char        CSVFileName[512];

    time( &rawtime );
    timeinfo = localtime( &rawtime );

    strftime(CSVFileName, 512, "Resources/plugins/Xsaitekpanels/D2B_debug_%Y-%m-%d_%H%M%S.csv", timeinfo);
    ofstream CSVFile(CSVFileName);
    if (CSVFile.is_open() != true)
    {
        logMsg("Xdatareaf2BIP: Fatal Error: Unable to write a CSV.");
        return;
    }
    CSVFile << "\"Row\",\"Position\",\"Color\",\"DataRefToSet\",\"DataRefType\",\"DataRefIndex\"\"";
    CSVFile << "WhatToDo\",\"FloatLimit\",\"CSVDebugString\"\n";

    for (int i = 0; i < MAXTABLEELEMENTS; i++)
    {
        CSVFile << "\"" << BipTable[0][i].Row << "\",";
        CSVFile << "\"" << BipTable[0][i].Position << "\",";
        CSVFile << "\"" << BipTable[0][i].Color << "\",";
        CSVFile << "\"" << BipTable[0][i].DataRefToSet << "\",";
        CSVFile << "\"" << BipTable[0][i].DataRefType << "\",";
        CSVFile << "\"" << BipTable[0][i].DataRefIndex << "\",";
        CSVFile << "\"" << BipTable[0][i].WhatToDo << "\",";
        CSVFile << "\"" << BipTable[0][i].FloatLimit << "\",";
        CSVFile << "\"" << BipTable[0][i].CSVDebugString << "\"\n";
    }
    CSVFile.close();
}

string convert_Mac_Bip_Path(string bip_in_path) {

    std::size_t bip_len = bip_in_path.length();
    std::size_t bip_pos = bip_in_path.find(":");
    bip_in_path.erase (bip_in_path.begin()+0, bip_in_path.end()-(bip_len - bip_pos));

    int bip_count = 0;
    for (int i = 0; i < bip_in_path.size(); i++)
        if (bip_in_path[i] == ':') bip_count++;

    size_t bip_found;
    int n = bip_count;

    while (n>0) {
       bip_found = bip_in_path.find(":");
       bip_in_path.replace(bip_found, 1,"/");
       --n;
    }
    std::size_t bip_pos2 = bip_in_path.find("/Aircraft");
    std::string tmp_bip_in_path = bip_in_path.substr (bip_pos2);
    tmp_bip_in_path.insert(0,".");
    bip_in_path = tmp_bip_in_path;
    return bip_in_path;

}

bool ReadConfigFile(string PlaneICAO)
{

  string          LineToEncrypt[4];
  bool            CorrectICAO = true;
  char            RowString[1];
  int             BipPosition;
  char            ColorString[1];
  char            DataRefString[512];
  XPLMDataRef     DataRefNumber;
  XPLMDataTypeID  DataRefType;
  float           Argument, Limit;
  int             Index;
  int             i, i1;

  char           *bip1ConfigurationPath;
  char           *bip2ConfigurationPath;
  char           *bip3ConfigurationPath;
  const char     *foundd2bpath, *foundd2bpath2, *foundd2bpath3;

  PlaneICAO.erase(PlaneICAO.find(']')+1);
  LetWidgetSay(PlaneICAO);

  LastMenuEntry[0] = -1;
  LastMenuEntry[1] = -1;

  char xpsbipacfname[512];
  char xpsbipacfpath[512];
  XPLMGetNthAircraftModel(0, xpsbipacfname, xpsbipacfpath);

  if(strlen(xpsbipacfpath) == 0){
    return false;
  }

  std::string xpsbipd2b_path_name = xpsbipacfpath;
  std::string xpsbipd2b_path_name2;
  std::string xpsbipd2b_path_name3;
  std::size_t pos = xpsbipd2b_path_name.find(xpsbipacfname);
  xpsbipd2b_path_name = xpsbipd2b_path_name.substr(0, pos);

  #if APL && __MACH__
      std::string mac_converted_bip_path = convert_Mac_Bip_Path(xpsbipd2b_path_name);
      XPLMDebugString("\nXsaitekpanels: mac_converted_bip_path is\n");
      XPLMDebugString(mac_converted_bip_path.c_str());
      XPLMDebugString("\n");
      xpsbipd2b_path_name = mac_converted_bip_path;
  #endif

  xpsbipd2b_path_name2 = xpsbipd2b_path_name;
  xpsbipd2b_path_name3 = xpsbipd2b_path_name;


  if(bipnum == bipwcscmp0) {

      bip1ConfigurationPath = "./Resources/plugins/Xsaitekpanels/D2B_config.txt";

      xpsbipd2b_path_name.append("D2B_config.txt");

      std::vector<char> parse_d2b_path_name(xpsbipd2b_path_name.size() + 1);
      std::copy(xpsbipd2b_path_name.begin(), xpsbipd2b_path_name.end(), parse_d2b_path_name.begin());

      std::ifstream ifile(&parse_d2b_path_name[0]);
      if (ifile) {
          XPLMDebugString("\nXsaitekpanels: Found D2B_config.txt in the current aircraft path and it is\n");
          XPLMDebugString(&parse_d2b_path_name[0]);
          XPLMDebugString("\n");
          XPLMDebugString("\n");
          foundd2bpath = (&parse_d2b_path_name[0]);

      } else {
          std::ifstream ifile(bip1ConfigurationPath);
         if (ifile) {
             XPLMDebugString("\nXsaitekpanels: Found D2B_config.txt in the Xsaitekpanels plugin path and it is\n");
             XPLMDebugString(bip1ConfigurationPath);
             XPLMDebugString("\n");
             XPLMDebugString("\n");
             foundd2bpath = bip1ConfigurationPath;
         } else {
             return false;
         }
      }

    ifstream ReadBipFile;
    ReadBipFile.open(foundd2bpath);
    if (ReadBipFile.is_open() != true)
    {
      logMsg("Error: Can't read D2B_config config file!");
      return false;
    }
    ErrorInLine = 0;

    LastTableElement[bipwcscmp0] = -1;
    for (i = 0; i < MAXTABLEELEMENTS; i++)
    {
      BipTable[bipwcscmp0][i].Row = '0';
      BipTable[bipwcscmp0][i].Position = 0;
      BipTable[bipwcscmp0][i].Color = '0';
      BipTable[bipwcscmp0][i].DataRefToSet = NULL;
      BipTable[bipwcscmp0][i].DataRefType = 0;
      BipTable[bipwcscmp0][i].DataRefIndex = 0;
      BipTable[bipwcscmp0][i].WhatToDo = '0';
      BipTable[bipwcscmp0][i].FloatValueToSet = 0;
      BipTable[bipwcscmp0][i].FloatLimit = 0;
      BipTable[bipwcscmp0][i].CSVDebugString[0] = 0;
    }

    while (getline(ReadBipFile, LineToEncrypt[0]))
    {


        ErrorInLine++;
        if (LineToEncrypt[bipwcscmp0].find("#BE SILENT") == 0)
        {
            InSilentMode = true;
            continue;
        }
        if (LineToEncrypt[bipwcscmp0].find("#BE CHATTY") == 0)
        {
            InSilentMode = false;
            continue;
        }
        if (LineToEncrypt[bipwcscmp0].find("#SHOW ICAO") == 0)
        {
            XPShowWidget(BipWidgetID);
            continue;
        }
        if (LineToEncrypt[bipwcscmp0].find("#HIDE ICAO") == 0)
        {
            XPHideWidget(BipWidgetID);
            continue;
        }
        if (LineToEncrypt[bipwcscmp0].find("[") == 0)
        {
            if ((LineToEncrypt[bipwcscmp0].find("[DEFAULT]") == 0) || (LineToEncrypt[bipwcscmp0].find(PlaneICAO) == 0))
            {
                CorrectICAO = true;
            }
            else
            {
                CorrectICAO = false;
            }
            if ((LineToEncrypt[bipwcscmp0].find("[DEFAULT]") != 0) && (++LastMenuEntry[bipwcscmp0] < 50))
            {
                strcpy(MenuEntries[bipwcscmp0][LastMenuEntry[0]], LineToEncrypt[bipwcscmp0].c_str());

            }
        }
        if (!CorrectICAO) continue;

        if (LineToEncrypt[bipwcscmp0].find("#RESET AUTHORITY") == 0)
        {
            if (++LastTableElement[bipwcscmp0] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBipFile.close();
                LastTableElement[bipwcscmp0] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[0][LastTableElement[bipwcscmp0]].WhatToDo = 'T';
            continue;
        }

        if (sscanf(LineToEncrypt[bipwcscmp0].c_str(), "#SET BIP %c %i %c FROM ARRAY %s %i RANGE %f TO %f", RowString, &BipPosition, ColorString, DataRefString, &Index, &Argument, &Limit) == 7)
        {
            if (++LastTableElement[0] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBipFile.close();
                LastTableElement[bipwcscmp0] = MAXTABLEELEMENTS - 1;
                return false;
            }
            DataRefNumber = XPLMFindDataRef(DataRefString);
            if (DataRefNumber == NULL)
            {
                logMsg("Xdataref2BIP: A DataRef you want to use is not defined!");
                ReadBipFile.close();
                return false;
            }
            DataRefType = XPLMGetDataRefTypes(DataRefNumber);
            if (!((DataRefType == xplmType_IntArray) || (DataRefType == xplmType_FloatArray)))
            {
                logMsg("Xdataref2BIP: A DataRef you want to use can not be read (wrong type)!");
                ReadBipFile.close();
                return false;
            }

            if ((BipPosition >= MAXINDICATORS) || (BipPosition < 0))
            {
                logMsg("Xdataref2BIP: Indicator does not exist!");
                ReadBipFile.close();
                LastTableElement[bipwcscmp0] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].Row = *RowString;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].Position = BipPosition;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].Color = *ColorString;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].DataRefToSet = DataRefNumber;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].DataRefType = DataRefType;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].DataRefIndex = Index;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].FloatValueToSet = Argument;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].FloatLimit = Limit;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].WhatToDo = 'v';
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].CSVDebugString[0] = 0;
            strcpy(BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].CSVDebugString, DataRefString);
            continue;
        }
        if (sscanf(LineToEncrypt[bipwcscmp0].c_str(), "#SET BIP %c %i %c FROM DATAREF %s RANGE %f TO %f", RowString, &BipPosition, ColorString, DataRefString, &Argument, &Limit) == 6)
        {
            if (++LastTableElement[bipwcscmp0] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBipFile.close();
                LastTableElement[bipwcscmp0] = MAXTABLEELEMENTS - 1;
                return false;
            }
            DataRefNumber = XPLMFindDataRef(DataRefString);
            if (DataRefNumber == NULL)
            {
                logMsg("Xdataref2BIP: A DataRef you want to use is not defined!");
                ReadBipFile.close();
                return false;
            }
            DataRefType = XPLMGetDataRefTypes(DataRefNumber);
            if (!((DataRefType == xplmType_Int) || (DataRefType == xplmType_Float)))
            {
                logMsg("Xdataref2BIP: A DataRef you want to use can not be read (wrong type)!");
                ReadBipFile.close();
                return false;
            }
            if ((BipPosition >= MAXINDICATORS) || (BipPosition < 0))
            {
                logMsg("Xdataref2BIP: Indicator does not exist!");
                ReadBipFile.close();
                LastTableElement[bipwcscmp0] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].Row = *RowString;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].Position = BipPosition;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].Color = *ColorString;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].DataRefToSet = DataRefNumber;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].DataRefType = DataRefType;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].FloatValueToSet = Argument;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].FloatLimit = Limit;
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].WhatToDo = 'v';
            BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].CSVDebugString[0] = 0;
            strcpy(BipTable[bipwcscmp0][LastTableElement[bipwcscmp0]].CSVDebugString, DataRefString);
            continue;
        }


        if (LineToEncrypt[bipwcscmp0].find('#') == 0)
        {
            logMsg("Xdataref2BIP: Can't understand the line of code!");
            ReadBipFile.close();
            LastTableElement[bipwcscmp0] = MAXTABLEELEMENTS - 1;
            return false;
        }
    }

    ReadBipFile.close();

   }


    if(bipnum == bipwcscmp1) {

        bip2ConfigurationPath = "./Resources/plugins/Xsaitekpanels/D2B_config2.txt";

        xpsbipd2b_path_name2.append("D2B_config2.txt");

        std::vector<char> parse_d2b_path_name2(xpsbipd2b_path_name2.size() + 1);
        std::copy(xpsbipd2b_path_name2.begin(), xpsbipd2b_path_name2.end(), parse_d2b_path_name2.begin());

        std::ifstream ifile(&parse_d2b_path_name2[0]);
        if (ifile) {
            XPLMDebugString("\nXsaitekpanels: Found D2B_config2.txt in the current aircraft path and it is\n");
            XPLMDebugString(&parse_d2b_path_name2[0]);
            XPLMDebugString("\n");
            XPLMDebugString("\n");
            foundd2bpath2 = (&parse_d2b_path_name2[0]);

        } else {
            std::ifstream ifile(bip2ConfigurationPath);
           if (ifile) {
               XPLMDebugString("\nXsaitekpanels: Found D2B_config2.txt in the Xsaitekpanels plugin path and it is\n");
               XPLMDebugString(bip2ConfigurationPath);
               XPLMDebugString("\n");
               XPLMDebugString("\n");
               foundd2bpath2 = bip2ConfigurationPath;


           } else {
               return false;
           }
        }

      ifstream ReadBip2File;
      ReadBip2File.open(foundd2bpath2);

    if (ReadBip2File.is_open() != true)
    {
        logMsg("Error: Can't read D2B_config2 config file!");
        return false;
    }
    ErrorInLine = 0;

    LastTableElement[bipwcscmp1] = -1;
    for (i1 = 0; i1 < MAXTABLEELEMENTS; i1++)
    {
        BipTable[bipwcscmp1][i1].Row = '0';
        BipTable[bipwcscmp1][i1].Position = 0;
        BipTable[bipwcscmp1][i1].Color = '0';
        BipTable[bipwcscmp1][i1].DataRefToSet = NULL;
        BipTable[bipwcscmp1][i1].DataRefType = 0;
        BipTable[bipwcscmp1][i1].DataRefIndex = 0;
        BipTable[bipwcscmp1][i1].WhatToDo = '0';
        BipTable[bipwcscmp1][i1].FloatValueToSet = 0;
        BipTable[bipwcscmp1][i1].FloatLimit = 0;
        BipTable[bipwcscmp1][i1].CSVDebugString[0] = 0;
    }

    while (getline(ReadBip2File, LineToEncrypt[bipwcscmp1]))
    {


        ErrorInLine++;
        if (LineToEncrypt[bipwcscmp1].find("#BE SILENT") == 0)
        {
            InSilentMode = true;
            continue;
        }
        if (LineToEncrypt[bipwcscmp1].find("#BE CHATTY") == 0)
        {
            InSilentMode = false;
            continue;
        }
        if (LineToEncrypt[bipwcscmp1].find("#SHOW ICAO") == 0)
        {
            XPShowWidget(Bip2WidgetID);
            continue;
        }
        if (LineToEncrypt[bipwcscmp1].find("#HIDE ICAO") == 0)
        {
            XPHideWidget(Bip2WidgetID);
            continue;
        }
        if (LineToEncrypt[bipwcscmp1].find("[") == 0)
        {

            if ((LineToEncrypt[bipwcscmp1].find("[DEFAULT]") == 0) || (LineToEncrypt[bipwcscmp1].find(PlaneICAO) == 0))
            {
                CorrectICAO = true;
            }
            else
            {
                CorrectICAO = false;
            }

            if ((LineToEncrypt[bipwcscmp1].find("[DEFAULT]") != 0) && (++LastMenuEntry[bipwcscmp1] < 50))
            {
                strcpy(MenuEntries[bipwcscmp1][LastMenuEntry[bipwcscmp1]], LineToEncrypt[bipwcscmp1].c_str());

            }
        }
        if (!CorrectICAO) continue;

        if (LineToEncrypt[bipwcscmp1].find("#RESET AUTHORITY") == 0)
        {
            if (++LastTableElement[bipwcscmp1] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBip2File.close();
                LastTableElement[bipwcscmp1] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].WhatToDo = 'T';
            continue;
        }

        if (sscanf(LineToEncrypt[bipwcscmp1].c_str(), "#SET BIP %c %i %c FROM ARRAY %s %i RANGE %f TO %f", RowString, &BipPosition, ColorString, DataRefString, &Index, &Argument, &Limit) == 7)
        {
            if (++LastTableElement[bipwcscmp1] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBip2File.close();
                LastTableElement[bipwcscmp1] = MAXTABLEELEMENTS - 1;
                return false;
            }
            DataRefNumber = XPLMFindDataRef(DataRefString);
            if (DataRefNumber == NULL)
            {
                logMsg("Xdataref2BIP: A DataRef you want to use is not defined!");
                ReadBip2File.close();
                return false;
            }
            DataRefType = XPLMGetDataRefTypes(DataRefNumber);
            if (!((DataRefType == xplmType_IntArray) || (DataRefType == xplmType_FloatArray)))
            {
                logMsg("Xdataref2BIP: A DataRef you want to use can not be read (wrong type)!");
                ReadBip2File.close();
                return false;
            }

            if ((BipPosition >= MAXINDICATORS) || (BipPosition < 0))
            {
                logMsg("Xdataref2BIP: Indicator does not exist!");
                ReadBip2File.close();
                LastTableElement[bipwcscmp1] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].Row = *RowString;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].Position = BipPosition;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].Color = *ColorString;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].DataRefToSet = DataRefNumber;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].DataRefType = DataRefType;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].DataRefIndex = Index;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].FloatValueToSet = Argument;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].FloatLimit = Limit;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].WhatToDo = 'v';
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].CSVDebugString[0] = 0;
            strcpy(BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].CSVDebugString, DataRefString);
            continue;
        }
        if (sscanf(LineToEncrypt[bipwcscmp1].c_str(), "#SET BIP %c %i %c FROM DATAREF %s RANGE %f TO %f", RowString, &BipPosition, ColorString, DataRefString, &Argument, &Limit) == 6)
        {
            if (++LastTableElement[bipwcscmp1] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBip2File.close();
                LastTableElement[bipwcscmp1] = MAXTABLEELEMENTS - 1;
                return false;
            }
            DataRefNumber = XPLMFindDataRef(DataRefString);
            if (DataRefNumber == NULL)
            {
                logMsg("Xdataref2BIP: A DataRef you want to use is not defined!");
                ReadBip2File.close();
                return false;
            }
            DataRefType = XPLMGetDataRefTypes(DataRefNumber);
            if (!((DataRefType == xplmType_Int) || (DataRefType == xplmType_Float)))
            {
                logMsg("Xdataref2BIP: A DataRef you want to use can not be read (wrong type)!");
                ReadBip2File.close();
                return false;
            }
            if ((BipPosition >= MAXINDICATORS) || (BipPosition < 0))
            {
                logMsg("Xdataref2BIP: Indicator does not exist!");
                ReadBip2File.close();
                LastTableElement[bipwcscmp1] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].Row = *RowString;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].Position = BipPosition;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].Color = *ColorString;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].DataRefToSet = DataRefNumber;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].DataRefType = DataRefType;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].FloatValueToSet = Argument;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].FloatLimit = Limit;
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].WhatToDo = 'v';
            BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].CSVDebugString[0] = 0;
            strcpy(BipTable[bipwcscmp1][LastTableElement[bipwcscmp1]].CSVDebugString, DataRefString);
            continue;
        }


        if (LineToEncrypt[bipwcscmp1].find('#') == 0)
        {
            logMsg("Xdataref2BIP: Can't understand the line of code!");
            ReadBip2File.close();
            LastTableElement[bipwcscmp1] = MAXTABLEELEMENTS - 1;
            return false;
        }

    }

    ReadBip2File.close();

   }


    if(bipnum == bipwcscmp2) {

        bip3ConfigurationPath = "./Resources/plugins/Xsaitekpanels/D2B_config3.txt";

        xpsbipd2b_path_name3.append("D2B_config3.txt");

        std::vector<char> parse_d2b_path_name3(xpsbipd2b_path_name3.size() + 1);
        std::copy(xpsbipd2b_path_name3.begin(), xpsbipd2b_path_name3.end(), parse_d2b_path_name3.begin());

        std::ifstream ifile(&parse_d2b_path_name3[0]);
        if (ifile) {
            XPLMDebugString("\nXsaitekpanels: Found D2B_config3.txt in the current aircraft path and it is\n");
            XPLMDebugString(&parse_d2b_path_name3[0]);
            XPLMDebugString("\n");
            XPLMDebugString("\n");
            foundd2bpath3 = (&parse_d2b_path_name3[0]);

        } else {
            std::ifstream ifile(bip3ConfigurationPath);
           if (ifile) {
               XPLMDebugString("\nXsaitekpanels: Found D2B_config3.txt in the Xsaitekpanels plugin path and it is\n");
               XPLMDebugString(bip3ConfigurationPath);
               XPLMDebugString("\n");
               XPLMDebugString("\n");
               foundd2bpath3 = bip3ConfigurationPath;


           } else {
               return false;
           }
        }

      ifstream ReadBip3File;
      ReadBip3File.open(foundd2bpath3);

    if (ReadBip3File.is_open() != true)
    {
        logMsg("Error: Can't read D2B_config3 config file!");
        return false;
    }
    ErrorInLine = 0;

    LastTableElement[bipwcscmp1] = -1;
    for (i1 = 0; i1 < MAXTABLEELEMENTS; i1++)
    {
        BipTable[bipwcscmp2][i1].Row = '0';
        BipTable[bipwcscmp2][i1].Position = 0;
        BipTable[bipwcscmp2][i1].Color = '0';
        BipTable[bipwcscmp2][i1].DataRefToSet = NULL;
        BipTable[bipwcscmp2][i1].DataRefType = 0;
        BipTable[bipwcscmp2][i1].DataRefIndex = 0;
        BipTable[bipwcscmp2][i1].WhatToDo = '0';
        BipTable[bipwcscmp2][i1].FloatValueToSet = 0;
        BipTable[bipwcscmp2][i1].FloatLimit = 0;
        BipTable[bipwcscmp2][i1].CSVDebugString[0] = 0;
    }

    while (getline(ReadBip3File, LineToEncrypt[bipwcscmp2]))
    {


        ErrorInLine++;
        if (LineToEncrypt[bipwcscmp2].find("#BE SILENT") == 0)
        {
            InSilentMode = true;
            continue;
        }
        if (LineToEncrypt[bipwcscmp2].find("#BE CHATTY") == 0)
        {
            InSilentMode = false;
            continue;
        }
        if (LineToEncrypt[bipwcscmp2].find("#SHOW ICAO") == 0)
        {
            XPShowWidget(Bip3WidgetID);
            continue;
        }
        if (LineToEncrypt[bipwcscmp2].find("#HIDE ICAO") == 0)
        {
            XPHideWidget(Bip3WidgetID);
            continue;
        }
        if (LineToEncrypt[bipwcscmp2].find("[") == 0)
        {

            if ((LineToEncrypt[bipwcscmp2].find("[DEFAULT]") == 0) || (LineToEncrypt[bipwcscmp2].find(PlaneICAO) == 0))
            {
                CorrectICAO = true;
            }
            else
            {
                CorrectICAO = false;
            }

            if ((LineToEncrypt[bipwcscmp2].find("[DEFAULT]") != 0) && (++LastMenuEntry[bipwcscmp2] < 50))
            {
                strcpy(MenuEntries[bipwcscmp2][LastMenuEntry[bipwcscmp2]], LineToEncrypt[bipwcscmp2].c_str());

            }
        }
        if (!CorrectICAO) continue;

        if (LineToEncrypt[bipwcscmp2].find("#RESET AUTHORITY") == 0)
        {
            if (++LastTableElement[bipwcscmp2] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBip3File.close();
                LastTableElement[bipwcscmp2] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].WhatToDo = 'T';
            continue;
        }

        if (sscanf(LineToEncrypt[bipwcscmp2].c_str(), "#SET BIP %c %i %c FROM ARRAY %s %i RANGE %f TO %f", RowString, &BipPosition, ColorString, DataRefString, &Index, &Argument, &Limit) == 7)
        {
            if (++LastTableElement[bipwcscmp2] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref2BIP: Fatal Error: Too much code to handle!");
                ReadBip3File.close();
                LastTableElement[bipwcscmp2] = MAXTABLEELEMENTS - 1;
                return false;
            }
            DataRefNumber = XPLMFindDataRef(DataRefString);
            if (DataRefNumber == NULL)
            {
                logMsg("Xdataref3BIP: A DataRef you want to use is not defined!");
                ReadBip3File.close();
                return false;
            }
            DataRefType = XPLMGetDataRefTypes(DataRefNumber);
            if (!((DataRefType == xplmType_IntArray) || (DataRefType == xplmType_FloatArray)))
            {
                logMsg("Xdataref3BIP: A DataRef you want to use can not be read (wrong type)!");
                ReadBip3File.close();
                return false;
            }

            if ((BipPosition >= MAXINDICATORS) || (BipPosition < 0))
            {
                logMsg("Xdataref3BIP: Indicator does not exist!");
                ReadBip3File.close();
                LastTableElement[bipwcscmp2] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].Row = *RowString;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].Position = BipPosition;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].Color = *ColorString;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].DataRefToSet = DataRefNumber;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].DataRefType = DataRefType;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].DataRefIndex = Index;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].FloatValueToSet = Argument;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].FloatLimit = Limit;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].WhatToDo = 'v';
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].CSVDebugString[0] = 0;
            strcpy(BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].CSVDebugString, DataRefString);
            continue;
        }
        if (sscanf(LineToEncrypt[bipwcscmp2].c_str(), "#SET BIP %c %i %c FROM DATAREF %s RANGE %f TO %f", RowString, &BipPosition, ColorString, DataRefString, &Argument, &Limit) == 6)
        {
            if (++LastTableElement[bipwcscmp2] >= MAXTABLEELEMENTS)
            {
                logMsg("Xdataref3BIP: Fatal Error: Too much code to handle!");
                ReadBip3File.close();
                LastTableElement[bipwcscmp2] = MAXTABLEELEMENTS - 1;
                return false;
            }
            DataRefNumber = XPLMFindDataRef(DataRefString);
            if (DataRefNumber == NULL)
            {
                logMsg("Xdataref3BIP: A DataRef you want to use is not defined!");
                ReadBip3File.close();
                return false;
            }
            DataRefType = XPLMGetDataRefTypes(DataRefNumber);
            if (!((DataRefType == xplmType_Int) || (DataRefType == xplmType_Float)))
            {
                logMsg("Xdataref3BIP: A DataRef you want to use can not be read (wrong type)!");
                ReadBip3File.close();
                return false;
            }
            if ((BipPosition >= MAXINDICATORS) || (BipPosition < 0))
            {
                logMsg("Xdataref3BIP: Indicator does not exist!");
                ReadBip3File.close();
                LastTableElement[bipwcscmp2] = MAXTABLEELEMENTS - 1;
                return false;
            }
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].Row = *RowString;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].Position = BipPosition;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].Color = *ColorString;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].DataRefToSet = DataRefNumber;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].DataRefType = DataRefType;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].FloatValueToSet = Argument;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].FloatLimit = Limit;
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].WhatToDo = 'v';
            BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].CSVDebugString[0] = 0;
            strcpy(BipTable[bipwcscmp2][LastTableElement[bipwcscmp2]].CSVDebugString, DataRefString);
            continue;
        }


        if (LineToEncrypt[bipwcscmp2].find('#') == 0)
        {
            logMsg("Xdataref3BIP: Can't understand the line of code!");
            ReadBip3File.close();
            LastTableElement[bipwcscmp2] = MAXTABLEELEMENTS - 1;
            return false;
        }

    }

    ReadBip3File.close();
    //return true;

   }


return true;
}


void process_bip_what_to_do_v()

{

    for (i[bipnum] = 0; i[bipnum] <= LastTableElement[bipnum]; i[bipnum]++) {

        if (BipTable[bipnum][i[bipnum]].WhatToDo == 'v') {
            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_Float) LookAtThisValue = XPLMGetDataf(BipTable[bipnum][i[bipnum]].DataRefToSet);
            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_Int) LookAtThisValue = (float) XPLMGetDatai(BipTable[bipnum][i[bipnum]].DataRefToSet);
            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_FloatArray) XPLMGetDatavf(BipTable[bipnum][i[bipnum]].DataRefToSet, &LookAtThisValue, BipTable[bipnum][i[bipnum]].DataRefIndex, 1);
            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_IntArray) {
                XPLMGetDatavi(BipTable[bipnum][i[bipnum]].DataRefToSet, &LookAtThisIntValue, BipTable[bipnum][i[bipnum]].DataRefIndex, 1);
                LookAtThisValue = (float) LookAtThisIntValue;
            }
            if ((LookAtThisValue >= BipTable[bipnum][i[bipnum]].FloatValueToSet) && (LookAtThisValue <= BipTable[bipnum][i[bipnum]].FloatLimit)) {

                //printf("********************************  ON   **************************************\n");
                if (BipTable[bipnum][i[bipnum]].Row == 'A') {
                    if (BipTable[bipnum][i[bipnum]].Color == 'G') {
                        // Make BipTable[i].Position position Top Row Green
                        bipwbuf[bipnum][1] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                    if (BipTable[bipnum][i[bipnum]].Color == 'R') {
                        // Make BipTable[i].Position position Top Row Red
                        bipwbuf[bipnum][1] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                    if (BipTable[bipnum][i[bipnum]].Color == 'A') {
                        // Make BipTable[i].Position position Top Row Amber
                        bipwbuf[bipnum][1] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                    }    for (i[bipnum] = 0; i[bipnum] <= LastTableElement[bipnum]; i[bipnum]++) {

                        if (BipTable[bipnum][i[bipnum]].WhatToDo == 'v') {
                            // "#SET BIP %c %i %c FROM DATAREF %s RANGE %f TO %f" or "#SET BIP %s %i %s FROM ARRAY %s %i RANGE %f TO %f""
                            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_Float) LookAtThisValue = XPLMGetDataf(BipTable[bipnum][i[bipnum]].DataRefToSet);
                            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_Int) LookAtThisValue = (float) XPLMGetDatai(BipTable[bipnum][i[bipnum]].DataRefToSet);
                            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_FloatArray) XPLMGetDatavf(BipTable[bipnum][i[bipnum]].DataRefToSet, &LookAtThisValue, BipTable[bipnum][i[bipnum]].DataRefIndex, 1);
                            if (BipTable[bipnum][i[bipnum]].DataRefType == xplmType_IntArray) {
                                XPLMGetDatavi(BipTable[bipnum][i[bipnum]].DataRefToSet, &LookAtThisIntValue, BipTable[bipnum][i[bipnum]].DataRefIndex, 1);
                                LookAtThisValue = (float) LookAtThisIntValue;
                            }
                            if ((LookAtThisValue >= BipTable[bipnum][i[bipnum]].FloatValueToSet) && (LookAtThisValue <= BipTable[bipnum][i[bipnum]].FloatLimit)) {

                                //printf("********************************  ON   **************************************\n");
                                if (BipTable[bipnum][i[bipnum]].Row == 'A') {
                                    if (BipTable[bipnum][i[bipnum]].Color == 'G') {
                                        // Make BipTable[i].Position position Top Row Green
                                        bipwbuf[bipnum][1] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                    if (BipTable[bipnum][i[bipnum]].Color == 'R') {
                                        // Make BipTable[i].Position position Top Row Red
                                        bipwbuf[bipnum][1] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                    if (BipTable[bipnum][i[bipnum]].Color == 'A') {
                                        // Make BipTable[i].Position position Top Row Amber
                                        bipwbuf[bipnum][1] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                }

                                if (BipTable[bipnum][i[bipnum]].Row == 'B') {
                                    if (BipTable[bipnum][i[bipnum]].Color == 'G') {
                                        // Make BipTable[i].Position position Middle Row Green
                                        bipwbuf[bipnum][2] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                    if (BipTable[bipnum][i[bipnum]].Color == 'R') {
                                        // Make BipTable[i].Position position Middle Row Red
                                        bipwbuf[bipnum][2] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                    if (BipTable[bipnum][i[bipnum]].Color == 'A') {
                                        // Make BipTable[i].Position position Middle Row Amber
                                        bipwbuf[bipnum][2] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                }

                                if (BipTable[bipnum][i[bipnum]].Row == 'C') {
                                    if (BipTable[bipnum][i[bipnum]].Color == 'G') {
                                        // Make BipTable[i].Position position Bottom Row Green
                                        bipwbuf[bipnum][3] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                    if (BipTable[bipnum][i[bipnum]].Color == 'R') {
                                        // Make BipTable[i].Position position Bottom Row Red
                                        bipwbuf[bipnum][3] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                    if (BipTable[bipnum][i[bipnum]].Color == 'A') {
                                        // Make BipTable[i].Position position Bottom Row Amber
                                        bipwbuf[bipnum][3] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                                    }
                                }
                            }

                            else {
                                //printf("**********************   OFF   *********************************\n");
                                if (BipTable[bipnum][i[bipnum]].Row == 'A') {
                                    // Make BipTable[i].Position position Top Row Off
                                    bipwbuf[bipnum][1] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                                }
                                if (BipTable[bipnum][i[bipnum]].Row == 'B') {
                                    // Make BipTable[i].Position position Middle Row Off
                                    bipwbuf[bipnum][2] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                                }
                                if (BipTable[bipnum][i[bipnum]].Row == 'C')  {
                                    // Make BipTable[i].Position position Bottom Row Off
                                    bipwbuf[bipnum][3] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                                }


                            }

                        }

                    }
                }

                if (BipTable[bipnum][i[bipnum]].Row == 'B') {
                    if (BipTable[bipnum][i[bipnum]].Color == 'G') {
                        // Make BipTable[i].Position position Middle Row Green
                        bipwbuf[bipnum][2] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                    if (BipTable[bipnum][i[bipnum]].Color == 'R') {
                        // Make BipTable[i].Position position Middle Row Red
                        bipwbuf[bipnum][2] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                    if (BipTable[bipnum][i[bipnum]].Color == 'A') {
                        // Make BipTable[i].Position position Middle Row Amber
                        bipwbuf[bipnum][2] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                }

                if (BipTable[bipnum][i[bipnum]].Row == 'C') {
                    if (BipTable[bipnum][i[bipnum]].Color == 'G') {
                        // Make BipTable[i].Position position Bottom Row Green
                        bipwbuf[bipnum][3] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                    if (BipTable[bipnum][i[bipnum]].Color == 'R') {
                        // Make BipTable[i].Position position Bottom Row Red
                        bipwbuf[bipnum][3] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                    if (BipTable[bipnum][i[bipnum]].Color == 'A') {
                        // Make BipTable[i].Position position Bottom Row Amber
                        bipwbuf[bipnum][3] |= (1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] |= (1<<(BipTable[bipnum][i[bipnum]].Position));
                    }
                }
            }

            else {
                //printf("**********************   OFF   *********************************\n");
                if (BipTable[bipnum][i[bipnum]].Row == 'A') {
                    // Make BipTable[i].Position position Top Row Off
                    bipwbuf[bipnum][1] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][4] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                }
                if (BipTable[bipnum][i[bipnum]].Row == 'B') {
                    // Make BipTable[i].Position position Middle Row Off
                    bipwbuf[bipnum][2] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][5] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                }
                if (BipTable[bipnum][i[bipnum]].Row == 'C')  {
                    // Make BipTable[i].Position position Bottom Row Off
                    bipwbuf[bipnum][3] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position)), bipwbuf[bipnum][6] &= ~(1<<(BipTable[bipnum][i[bipnum]].Position));
                }


            }

        }

    }


 return;

}


// ***** BIP Panel Process  *******
void process_bip_panel()

{

    if (biploop[bipnum] < 2) {
      // Clear Display on first loop
      bipwbuf[bipnum][0] = 0xb8;  //0xb8 Report ID to display
      bipwbuf[bipnum][1] = 0, bipwbuf[bipnum][2] = 0, bipwbuf[bipnum][3] = 0;
      bipwbuf[bipnum][4] = 0, bipwbuf[bipnum][5] = 0, bipwbuf[bipnum][6] = 0;
      res = hid_send_feature_report(biphandle[bipnum], bipwbuf[bipnum], 10);
      biploop[bipnum]++;
    }


    process_bip_what_to_do_v();


    // Trying to only write on changes to improve FPS impact
    if(biploop[bipnum] == 2) {
        bipchange = memcmp(bipwbuf[bipnum], lastbipwbuf[bipnum], 10);
      if (bipchange == 0) {
      }
      if (bipchange != 0) {
        if (BatPwrIsOn()) {
            res = hid_send_feature_report(biphandle[bipnum], bipwbuf[bipnum], 10);
            memcpy(lastbipwbuf[bipnum], bipwbuf[bipnum], 10);
        }
      }
      if (!BatPwrIsOn()) {
            bipwbuf[bipnum][0] = 0xb8;  //0xb8 Report ID to display
            bipwbuf[bipnum][1] = 0, bipwbuf[bipnum][2] = 0, bipwbuf[bipnum][3] = 0;
            bipwbuf[bipnum][4] = 0, bipwbuf[bipnum][5] = 0, bipwbuf[bipnum][6] = 0;
            res = hid_send_feature_report(biphandle[bipnum], bipwbuf[bipnum], 10);
            memcpy(lastbipwbuf[bipnum], bipwbuf[bipnum], 10);
      }
  }

  // *********** loop untill all bips serviced *************
  // **************   then start again    *******************

  bipnum++;

  if (bipnum == bipcnt) {
    bipnum = 0;
  }

  return;
}
