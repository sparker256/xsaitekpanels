// ****** radiopanels.cpp **********
// *****  William R. Good **********

#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"

#include "saitekpanels.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define testbit(x, y)  ( ( ((const char*)&(x))[(y)>>3] & 0x80 >> ((y)&0x07)) >> (7-((y)&0x07) ) )

// ********************** Radio Panel variables ***********************
static int radnum = 0, radionowrite[4] = {0, 0, 0, 0};
static int radiores = 0, radn;

static int updmepushed = 0, lodmepushed = 0;
static int updmeloop = 0, lodmeloop = 0;
static int uplastdmepos = 0, lolastdmepos = 0;

static int upxpdrpushed = 0, loxpdrpushed = 0;
static int upxpdrloop = 0, loxpdrloop = 0;
static int uplastxpdrpos = 0, lolastxpdrpos = 0;

static int upactcomfreq[4], upstbycomfreq[4], loactcomfreq[4], lostbycomfreq[4];
static int upactnavfreq[4], upstbynavfreq[4], loactnavfreq[4], lostbynavfreq[4];
static int upstbyadffreq[4], lostbyadffreq[4];
static int upactadffreq[4], loactadffreq[4];
static int updmedist[4], lodmedist[4];
static int updmenavspeed[4], lodmenavspeed[4];
static int updmespeed[4], lodmespeed[4];
static int updmedbncfninc[4], lodmedbncfninc[4];
static int updmedbncfndec[4], lodmedbncfndec[4];
static int updmefreqhnd, updmefreqfrc;
static int lodmefreqhnd, lodmefreqfrc;

static int upxpdrcode[4], loxpdrcode[4];
static int upxpdrmode[4], loxpdrmode[4];
static int upbaroset[4], lobaroset[4];

static int upstbyadf1dir[4], upstbyadf2dir[4];
static int lostbyadf1dir[4], lostbyadf2dir[4];

static int updmemode[4], lodmemode[4];
static int updmesource[4], lodmesource[4];
static int updmefreq[4], lodmefreq[4];

static int upcom1[4] = {0, 0, 0, 0}, upcom2[4] = {0, 0, 0, 0};
static int upnav1[4] = {0, 0, 0, 0}, upnav2[4] = {0, 0, 0, 0};
static int locom1[4] = {0, 0, 0, 0}, locom2[4] = {0, 0, 0, 0}; 
static int lonav1[4] = {0, 0, 0, 0}, lonav2[4] = {0, 0, 0, 0};

static int upcom1dbncfninc[4] = {0, 0, 0, 0}, upcom1dbncfndec[4] = {0, 0, 0, 0};
static int upcom1dbnccorinc[4] = {0, 0, 0, 0}, upcom1dbnccordec[4] = {0, 0, 0, 0};
static int upcom2dbncfninc[4] = {0, 0, 0, 0}, upcom2dbncfndec[4] = {0, 0, 0, 0,};
static int upcom2dbnccorinc[4] = {0, 0, 0, 0}, upcom2dbnccordec[4] = {0, 0, 0, 0};
static int upnav1dbncfninc[4] = {0, 0, 0, 0}, upnav1dbncfndec[4] = {0, 0, 0, 0};
static int upnav1dbnccorinc[4] = {0, 0, 0, 0}, upnav1dbnccordec[4] = {0, 0, 0, 0};
static int upnav2dbncfninc[4] = {0, 0, 0, 0}, upnav2dbncfndec[4] = {0, 0, 0, 0};
static int upnav2dbnccorinc[4] = {0, 0, 0, 0}, upnav2dbnccordec[4] = {0, 0, 0, 0};
static int upadfdbncfninc[4] = {0, 0, 0, 0}, upadfdbncfndec[4] = {0, 0, 0, 0};
static int upadfdbnccorinc[4] = {0, 0, 0, 0}, upadfdbnccordec[4] = {0, 0, 0, 0};
static int upadfdbdirfninc[4] = {0, 0, 0, 0}, upadfdbdirfndec[4] = {0, 0, 0, 0};
static int upadfdbdircorinc[4] = {0, 0, 0, 0}, upadfdbdircordec[4] = {0, 0, 0, 0};
static int upxpdrdbncfninc[4] = {0, 0, 0, 0}, upxpdrdbncfndec[4] = {0, 0, 0, 0};
static int upxpdrdbnccorinc[4] = {0, 0, 0, 0}, upxpdrdbnccordec[4] = {0, 0, 0, 0};
static int upqnhdbncfninc[4] = {0, 0, 0, 0}, upqnhdbncfndec[4] = {0, 0, 0, 0};
static int upqnhdbnccorinc[4] = {0, 0, 0, 0}, upqnhdbnccordec[4] = {0, 0, 0, 0};

static int locom1dbncfninc[4] = {0, 0, 0, 0}, locom1dbncfndec[4] = {0, 0, 0, 0};
static int locom1dbnccorinc[4] = {0, 0, 0, 0}, locom1dbnccordec[4] = {0, 0, 0, 0};
static int locom2dbncfninc[4] = {0, 0, 0, 0}, locom2dbncfndec[4] = {0, 0, 0, 0};
static int locom2dbnccorinc[4] = {0, 0, 0, 0}, locom2dbnccordec[4] = {0, 0, 0, 0};
static int lonav1dbncfninc[4] = {0, 0, 0, 0}, lonav1dbncfndec[4] = {0, 0, 0, 0};
static int lonav1dbnccorinc[4] = {0, 0, 0, 0}, lonav1dbnccordec[4] = {0, 0, 0, 0};
static int lonav2dbncfninc[4] = {0, 0, 0, 0}, lonav2dbncfndec[4] = {0, 0, 0, 0};
static int lonav2dbnccorinc[4] = {0, 0, 0, 0}, lonav2dbnccordec[4] = {0, 0, 0, 0};
static int loadfdbncfninc[4] = {0, 0, 0, 0}, loadfdbncfndec[4] = {0, 0, 0, 0};
static int loadfdbnccorinc[4] = {0, 0, 0, 0}, loadfdbnccordec[4] = {0, 0, 0, 0};
static int loadfdbdirfninc[4] = {0, 0, 0, 0}, loadfdbdirfndec[4] = {0, 0, 0, 0};
static int loadfdbdircorinc[4] = {0, 0, 0, 0}, loadfdbdircordec[4] = {0, 0, 0, 0};
static int loxpdrdbncfninc[4] = {0, 0, 0, 0}, loxpdrdbncfndec[4] = {0, 0, 0, 0};
static int loxpdrdbnccorinc[4] = {0, 0, 0, 0}, loxpdrdbnccordec[4] = {0, 0, 0, 0};
static int loqnhdbncfninc[4] = {0, 0, 0, 0}, loqnhdbncfndec[4] = {0, 0, 0, 0};
static int loqnhdbnccorinc[4] = {0, 0, 0, 0}, loqnhdbnccordec[4] = {0, 0, 0, 0};

static int rad1uprxpdrdigitremap, rad1lwrxpdrdigitremap;
static int rad2uprxpdrdigitremap, rad2lwrxpdrdigitremap;
static int rad3uprxpdrdigitremap, rad3lwrxpdrdigitremap;

static int rad1uprxpdrlastdigitremap, rad1lwrxpdrlastdigitremap;
static int rad2uprxpdrlastdigitremap, rad2lwrxpdrlastdigitremap;
static int rad3uprxpdrlastdigitremap, rad3lwrxpdrlastdigitremap;

static int rad1uprxpdrlastdigitcnt, rad1lwrxpdrlastdigitcnt;
static int rad2uprxpdrlastdigitcnt, rad2lwrxpdrlastdigitcnt;
static int rad3uprxpdrlastdigitcnt, rad3lwrxpdrlastdigitcnt;

static float updmedistf[4], lodmedistf[4];
static float updmenav1speedf[4], updmenav2speedf[4], lodmenav1speedf[4], lodmenav2speedf[4];
static float updmespeedf[4], lodmespeedf[4];

static float updmetime[4], lodmetime[4];
static float upbarosetf[4], lobarosetf[4];

static float UpNav1ObsDegm[4], UpNav2ObsDegm[4];
static float LoNav1ObsDegm[4], LoNav2ObsDegm[4];

static float UpAdf1CardDirDegm[4], UpAdf2CardDirDegm[4];
static float LoAdf1CardDirDegm[4], LoAdf2CardDirDegm[4];

static int upstbyadf1dirf[4], upstbyadf2dirf[4];
static int lostbyadf1dirf[4], lostbyadf2dirf[4];

static int radioaactv, radioadig1, radioarem1, radioadig2, radioarem2, radioadig3, radioarem3;
static int radioadig4, radioarem4, radioadig5, radioarem5, radioadig6;
static int radiobstby, radiobdig1, radiobrem1, radiobdig2, radiobrem2, radiobdig3, radiobrem3;
static int radiobdig4, radiobrem4, radiobdig5, radiobrem5, radiobdig6;
static int radiocactv, radiocdig1, radiocrem1, radiocdig2, radiocrem2, radiocdig3, radiocrem3;
static int radiocdig4, radiocrem4, radiocdig5, radiocrem5, radiocdig6;
static int radiodstby, radioddig1, radiodrem1, radioddig2, radiodrem2, radioddig3, radiodrem3;
static int radioddig4, radiodrem4, radioddig5, radiodrem5, radioddig6;

static int upxpdrsel[4] = {1, 1, 1, 1}, loxpdrsel[4] = {1, 1, 1, 1};
//static int upqnhsel[4] = {1, 1, 1, 1}, loqnhsel[4] = {1, 1, 1, 1};

static int upadfsel[4] = {1, 1, 1, 1}, loadfsel[4] = {1, 1, 1, 1};

static int upseldis[4] = {1, 1, 1, 1}, loseldis[4] = {1, 1, 1, 1};
static int lastupseldis[4] = {1, 1, 1, 1}, lastloseldis[4] = {1, 1, 1, 1};

static int UPPER_FINE_UP = 23, UPPER_FINE_DN = 22; 
static int UPPER_COARSE_UP = 21, UPPER_COARSE_DN = 20;
static int UPPER_COM1 = 7, UPPER_COM2 = 6;
static int UPPER_NAV1 = 5, UPPER_NAV2 = 4; 
static int UPPER_ADF = 3, UPPER_DME = 2;
static int UPPER_XPDR = 1, UPPER_ACT_STBY = 9;

static int LOWER_FINE_UP = 19, LOWER_FINE_DN = 18; 
static int LOWER_COARSE_UP = 17, LOWER_COARSE_DN = 16;
static int LOWER_COM1 = 0, LOWER_COM2 = 15;
static int LOWER_NAV1 = 14, LOWER_NAV2 = 13; 
static int LOWER_ADF = 12, LOWER_DME = 11;
static int LOWER_XPDR = 10, LOWER_ACT_STBY = 8;

static int Last_Upper_Fine_Up[4], Last_Upper_Fine_Dn[4];
static int Last_Lower_Fine_Up[4], Last_Lower_Fine_Dn[4];
static int Last_Upper_Coarse_Up[4], Last_Upper_Coarse_Dn[4];
static int Last_Lower_Coarse_Up[4], Last_Lower_Coarse_Dn[4];


static int upmodeturnoff, lomodeturnoff;

static unsigned char radiobuf[4][4];
static unsigned char radiowbuf[4][23];

char	radtestbuf[256];

// void process_upper_nav_com_freq();
// void process_lower_nav_com_freq();

void process_upper_com_freq();
void process_upper_nav_freq();
void process_lower_com_freq();
void process_lower_nav_freq();


void process_radio_menu()
{

    XPLMClearAllMenuItems(RadioMenuId);
    XPLMAppendMenuItem(RadioMenuId, "Radio Panel Widget", (void *) "RADIO_WIDGET", 1);

}

void process_radio_upper_display()
{

  // *************** Upper Display info **********************

  if (upseldis[radnum] == 1) { 
    process_upper_com_freq();
  } 

  else if (upseldis[radnum] == 2) { 
    process_upper_com_freq();
  } 

  else if (upseldis[radnum] == 3) { 
    process_upper_nav_freq();
  } 

  else if (upseldis[radnum] == 4) { 
    process_upper_nav_freq();
  } 

  else if (upseldis[radnum] == 5) {

    if(xpanelsfnbutton == 1) {
        radioaactv = upactadffreq[radnum];
        radioadig1 = 15, radioadig2 = 15;
        radioadig3 = radioaactv/100, radioarem3 =radioaactv%100;
        radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
        radioadig5 = radioarem4;

        radiobstby = upstbyadf1dirf[radnum];
        radiobdig1 = 15, radiobdig2 = 15;
        radiobdig3 = radiobstby/100, radiobrem3 =radiobstby%100;
        radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
        radiobdig5 = radiobrem4;
        radiobdig5 = radiobdig5;
    }

   if((xpanelsfnbutton == 0) || (rad1upradfswitchremap == 1) || (rad2upradfswitchremap == 1) ||  (rad3upradfswitchremap == 1)) {


    if (upadfsel[radnum] == 1) {
      radioaactv = upactadffreq[radnum];
      radioadig1 = 15;
      radioadig2 = radioaactv/1000, radioarem2 =radioaactv%1000;
      radioadig3 = radioarem2/100, radioarem3 =radioarem2%100;
      radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
      radioadig5 = radioarem4;

      radiobstby = upstbyadffreq[radnum];
      radiobdig1 = 15;
      radiobdig2 = radiobstby/1000, radiobrem2 =radiobstby%1000;
      radiobdig3 = radiobrem2/100, radiobrem3 =radiobrem2%100;
      radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
      radiobdig5 = radiobrem4;
      radiobdig5 = radiobdig5+208;
    }

    if (upadfsel[radnum] == 2) {
      radioaactv = upactadffreq[radnum];
      radioadig1 = 15;
      radioadig2 = radioaactv/1000, radioarem2 =radioaactv%1000;
      radioadig3 = radioarem2/100, radioarem3 =radioarem2%100;
      radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
      radioadig5 = radioarem4;

      radiobstby = upstbyadffreq[radnum];
      radiobdig1 = 15;
      radiobdig2 = radiobstby/1000, radiobrem2 =radiobstby%1000;
      radiobdig3 = radiobrem2/100, radiobrem3 =radiobrem2%100;
      radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
      radiobdig4 = radiobdig4+208, radiobdig5 = radiobrem4;
    }

    if (upadfsel[radnum] == 3) {
      radioaactv = upactadffreq[radnum];
      radioadig1 = 15;
      radioadig2 = radioaactv/1000, radioarem2 =radioaactv%1000;
      radioadig3 = radioarem2/100, radioarem3 =radioarem2%100;
      radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
      radioadig5 = radioarem4;

      radiobstby = upstbyadffreq[radnum];
      radiobdig1 = 15;
      radiobdig2 = radiobstby/1000, radiobrem2 =radiobstby%1000;
      radiobdig3 = radiobrem2/100, radiobrem3 =radiobrem2%100;
      radiobdig3 = radiobdig3+208;
      radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
      radiobdig5 = radiobrem4;
    }

    if (upadfsel[radnum] > 3) {
      radioaactv = upactadffreq[radnum];
      radioadig1 = 15;
      radioadig2 = radioaactv/1000, radioarem2 =radioaactv%1000;
      radioadig3 = radioarem2/100, radioarem3 =radioarem2%100;
      radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
      radioadig5 = radioarem4;

      radiobstby = upstbyadffreq[radnum];
      radiobdig1 = 15;
      radiobdig2 = radiobstby/1000, radiobrem2 =radiobstby%1000;
      radiobdig3 = radiobrem2/100, radiobrem3 =radiobrem2%100;
      radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
      radiobdig5 = radiobrem4;
    }

   }



  }

  else if (upseldis[radnum] == 6) {
      if (dmedistspeedenable == 0) {
          radioaactv = updmenavspeed[radnum];
          radioadig1 = 15, radioadig2 = 15;
          radioadig3 = radioaactv/100, radioarem3 =radioaactv%100;
          radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
          radioadig5 = radioarem4;

          radiobstby = updmedist[radnum];
          radiobdig1 = radiobstby/10000, radiobrem1 = radiobstby%10000;
          radiobdig2 = radiobrem1 /1000, radiobrem2 = radiobrem1%1000;
          radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
          radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
          radiobdig4 = radiobdig4+208, radiobdig5 = radiobrem4;

      } else if (dmedistspeedenable == 1) {
          radioaactv = updmedist[radnum];
          radioadig1 = radioaactv/10000, radioarem1 = radioaactv%10000;
          radioadig2 = radioarem1 /1000, radioarem2 = radioarem1%1000;
          radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
          radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
          radioadig4 = radioadig4+208, radioadig5 = radioarem4;

          radiobstby = updmenavspeed[radnum];
          radiobdig1 = 15, radiobdig2 = 15;
          radiobdig3 = radiobstby/100, radiobrem3 =radiobstby%100;
          radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
          radiobdig5 = radiobrem4;

      }

  }

  else if (upseldis[radnum] == 7) {
    radioaactv = updmefreq[radnum];
    radioadig1 = radioaactv/10000, radioarem1 = radioaactv%10000;
    radioadig2 = radioarem1 /1000, radioarem2 = radioarem1%1000;
    radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
    radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
    radioadig3 = radioadig3+208, radioadig5 = radioarem4;

    radiobstby = updmetime[radnum];
    radiobdig1 = 15,radiobdig2 = 15;
    radiobdig3 = radiobstby/100, radiobrem3 = radiobstby%100;
    radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
    radiobdig4 = radiobdig4, radiobdig5 = radiobrem4;

  }

  else if (upseldis[radnum] == 8) {
    radioaactv = updmenavspeed[radnum];
    radioadig1 = 15, radioadig2 = 15;
    radioadig3 = radioaactv/100, radioarem3 =radioaactv%100;
    radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
    radioadig5 = radioarem4;

    radiobstby = updmetime[radnum];
    radiobdig1 = 15,radiobdig2 = 15;
    radiobdig3 = radiobstby/100, radiobrem3 = radiobstby%100;
    radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
    radiobdig4 = radiobdig4, radiobdig5 = radiobrem4;

  }

  else if (upseldis[radnum] == 9) {

      if(xpanelsfnbutton == 0) {
          if (upxpdrsel[radnum] == 1) {
            radioaactv = upbaroset[radnum];
            radioadig1 = 15, radioadig2 = radioaactv/1000, radioarem2 = radioaactv%1000;
            radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
            if (metricpressenable == 0) {
                radioadig3 = radioadig3+208;
            }
            if (metricpressenable == 1) {
                radioadig3 = radioadig3;
            }
            radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
            radioadig5 = radioarem4;

            radiobstby = upxpdrcode[radnum];
            radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
            radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
            radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
            radiobdig5 = radiobrem4,  radiobdig5 = radiobdig5+208;
          }

          if (upxpdrsel[radnum] == 2) {
            radioaactv = upbaroset[radnum];
            radioadig1 = 15, radioadig2 = radioaactv/1000, radioarem2 = radioaactv%1000;
            radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
            if (metricpressenable == 0) {
                radioadig3 = radioadig3+208;
            }
            if (metricpressenable == 1) {
                radioadig3 = radioadig3;
            }
            radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
            radioadig5 = radioarem4;

            radiobstby = upxpdrcode[radnum];
            radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
            radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
            radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
            radiobdig4 = radiobdig4+208, radiobdig5 = radiobrem4;
          }

          if (upxpdrsel[radnum] == 3) {
            radioaactv = upbaroset[radnum];
            radioadig1 = 15, radioadig2 = radioaactv/1000, radioarem2 = radioaactv%1000;
            radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
            if (metricpressenable == 0) {
                radioadig3 = radioadig3+208;
            }
            if (metricpressenable == 1) {
                radioadig3 = radioadig3;
            }
            radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
            radioadig5 = radioarem4;

            radiobstby = upxpdrcode[radnum];
            radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
            radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
            radiobdig3 = radiobdig3+208;
            radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
            radiobdig5 = radiobrem4;
          }

          if (upxpdrsel[radnum] == 4) {
            radioaactv = upbaroset[radnum];
            radioadig1 = 15, radioadig2 = radioaactv/1000, radioarem2 = radioaactv%1000;
            radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
            if (metricpressenable == 0) {
                radioadig3 = radioadig3+208;
            }
            if (metricpressenable == 1) {
                radioadig3 = radioadig3;
            }
            radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
            radioadig5 = radioarem4;

            radiobstby = upxpdrcode[radnum];
            radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
            radiobdig2 = radiobdig2+208;
            radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
            radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
            radiobdig5 = radiobrem4;
          }



          if(testbit(radiobuf[radnum],UPPER_FINE_UP)) {
              upmodeturnoff = 0;
          }
          if(testbit(radiobuf[radnum],UPPER_FINE_DN)) {
              upmodeturnoff = 0;
          }

          if(testbit(radiobuf[radnum],UPPER_COARSE_UP)) {
              upmodeturnoff = 0;
          }
          if(testbit(radiobuf[radnum],UPPER_COARSE_DN)) {
              upmodeturnoff = 0;
          }

          if (upmodeturnoff == 200) {
             upxpdrsel[radnum] = 1;
             if (XPLMGetDatai(XpdrMode) == 0) {
                 radiobdig1 = 15+208;
             }
             if (XPLMGetDatai(XpdrMode) == 1) {
                 radiobdig2 = radiobdig2+208;
             }
             if (XPLMGetDatai(XpdrMode) == 2) {
                 radiobdig3 = radiobdig3+208;
             }
             if (XPLMGetDatai(XpdrMode) == 3) {
                 radiobdig4 = radiobdig4+208;
             }

          }
          else {
            upmodeturnoff++;

          }

      }

      if(xpanelsfnbutton == 1) {
            radioaactv = upbaroset[radnum];
            radioadig1 = 15+208, radioadig2 = radioaactv/1000, radioarem2 = radioaactv%1000;
            radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
            if (metricpressenable == 0) {
                radioadig3 = radioadig3+208;
            }
            if (metricpressenable == 1) {
                radioadig3 = radioadig3;
            }
            radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
            radioadig5 = radioarem4;

            radiobstby = upxpdrcode[radnum];
            radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
            radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
            radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
            radiobdig5 = radiobrem4,  radiobdig5 = radiobdig5;
      }

  }

  else if (upseldis[radnum] == 10) {
    radioadig1 = 15, radioadig2 = 15, radioadig3 = 15, radioadig4 = 15, radioadig5 = 15;
    radiobdig1 = 15, radiobdig2 = 15, radiobdig3 = 15, radiobdig4 = 15, radiobdig5 = 15;
  }

  else if (upseldis[radnum] == 11) {

      radioaactv = upbaroset[radnum];
      radioadig1 = 15, radioadig2 = radioaactv/1000, radioarem2 = radioaactv%1000;
      radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
      if (metricpressenable == 0) {
          radioadig3 = radioadig3+208;
      }
      if (metricpressenable == 1) {
          radioadig3 = radioadig3;
      }
      radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
      radioadig5 = radioarem4;


      if ((rad1uprxpdrswitchremap == 777) && (radnum == 0)) {
          radiobstby = rad1uprxpdrdigitremap;
          radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
          radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
          radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
          radiobdig5 = radiobrem4,  radiobdig5 = radiobdig5+208;

      } else if ((rad2uprxpdrswitchremap == 777) && (radnum == 1)) {
          radiobstby = rad2uprxpdrdigitremap;
          radiobdig1 = 15, radiobdig2 = radiobstby/1000, radiobrem2 = radiobstby%1000;
          radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
          radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
          radiobdig5 = radiobrem4,  radiobdig5 = radiobdig5+208;

      }




  }


}

void process_radio_lower_display()
{


  // ************************ Lower Display info ********************
  
  if (loseldis[radnum] == 1) { 
    process_lower_com_freq();
  } 

  else if (loseldis[radnum] == 2) { 
    process_lower_com_freq();
  } 

  else if (loseldis[radnum] == 3) { 
    process_lower_nav_freq();
  } 

  else if (loseldis[radnum] == 4) {
    process_lower_nav_freq();
  } 
  
  else if (loseldis[radnum] == 5) {

    if(xpanelsfnbutton == 1) {

        radiocactv = loactadffreq[radnum];
        radiocdig1 = 15, radiocdig2 = 15;
        radiocdig3 = radiocactv/100, radiocrem3 =radiocactv%100;
        radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
        radiocdig5 = radiocrem4;

       if (numadf == 1) {
          radiodstby = lostbyadf1dirf[radnum];
       } else if (numadf == 2) {
          radiodstby = lostbyadf2dirf[radnum];
        }
        radioddig1 = 15, radioddig2 = 15;
        radioddig3 = radiodstby/100, radiodrem3 = radiodstby%100;
        radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
        radioddig5 = radiodrem4;
        radioddig5 = radioddig5;

    }

    if((xpanelsfnbutton == 0) || (rad1lwradfswitchremap == 1) || (rad2lwradfswitchremap == 1) || (rad3lwradfswitchremap == 1)) {


    if (loadfsel[radnum] == 1) {
      radiocactv = loactadffreq[radnum];
      radiocdig1 = 15;
      radiocdig2 = radiocactv/1000, radiocrem2 =radiocactv%1000;
      radiocdig3 = radiocrem2/100, radiocrem3 =radiocrem2%100;
      radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
      radiocdig5 = radiocrem4;

      radiodstby = lostbyadffreq[radnum];
      radioddig1 = 15;
      radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
      radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
      radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
      radioddig5 = radiodrem4;
      radioddig5 = radioddig5+208;

    }

    if (loadfsel[radnum] == 2) {
      radiocactv = loactadffreq[radnum];
      radiocdig1 = 15;
      radiocdig2 = radiocactv/1000, radiocrem2 =radiocactv%1000;
      radiocdig3 = radiocrem2/100, radiocrem3 =radiocrem2%100;
      radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
      radiocdig5 = radiocrem4;

      radiodstby = lostbyadffreq[radnum];
      radioddig1 = 15;
      radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
      radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
      radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
      radioddig4 = radioddig4+208;
      radioddig5 = radiodrem4;
    }

    if (loadfsel[radnum] == 3) {
      radiocactv = loactadffreq[radnum];
      radiocdig1 = 15;
      radiocdig2 = radiocactv/1000, radiocrem2 =radiocactv%1000;
      radiocdig3 = radiocrem2/100, radiocrem3 =radiocrem2%100;
      radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
      radiocdig5 = radiocrem4;

      radiodstby = lostbyadffreq[radnum];
      radioddig1 = 15;
      radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
      radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
      radioddig3 = radioddig3+208;
      radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
      radioddig5 = radiodrem4;
    }

    if (loadfsel[radnum] > 3) {
      radiocactv = loactadffreq[radnum];
      radiocdig1 = 15;
      radiocdig2 = radiocactv/1000, radiocrem2 =radiocactv%1000;
      radiocdig3 = radiocrem2/100, radiocrem3 =radiocrem2%100;
      radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
      radiocdig5 = radiocrem4;

      radiodstby = lostbyadffreq[radnum];
      radioddig1 = 15;
      radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
      radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
      radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
      radioddig5 = radiodrem4;
    }


   }

  }


  else if (loseldis[radnum] == 6) {
      if (dmedistspeedenable == 0) {
          radiocactv = lodmenavspeed[radnum];
          radiocdig1 = 15, radiocdig2 = 15;
          radiocdig3 = radiocactv/100, radiocrem3 =radiocactv%100;
          radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
          radiocdig5 = radiocrem4;

          radiodstby = lodmedist[radnum];
          radioddig1 = radiodstby/10000, radiodrem1 = radiodstby%10000;
          radioddig2 = radiodrem1 /1000, radiodrem2 = radiodrem1%1000;
          radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
          radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
          radioddig4 = radioddig4+208, radioddig5 = radiodrem4;

      } else if (dmedistspeedenable == 1) {
          radiocactv = lodmedist[radnum];
          radiocdig1 = radiocactv/10000, radiocrem1 = radiocactv%10000;
          radiocdig2 = radiocrem1 /1000, radiocrem2 = radiocrem1%1000;
          radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
          radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
          radiocdig4 = radiocdig4+208, radiocdig5 = radiocrem4;

          radiodstby = lodmenavspeed[radnum];
          radioddig1 = 15, radioddig2 = 15;
          radioddig3 = radiodstby/100, radiodrem3 =radiodstby%100;
          radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
          radioddig5 = radiodrem4;

      }

  }

  else if (loseldis[radnum] == 7) {
    radiocactv = lodmefreq[radnum];
    radiocdig1 = radiocactv/10000, radiocrem1 = radiocactv%10000;
    radiocdig2 = radiocrem1 /1000, radiocrem2 = radiocrem1%1000;
    radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
    radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
    radiocdig3 = radiocdig3+208;
    radiocdig5 = radiocrem4;

    radiodstby = lodmetime[radnum];
    radioddig1 = 15, radioddig2 = 15;
    radioddig3 = radiodstby/100, radiodrem3 = radiodstby%100;
    radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
    radioddig4 = radioddig4, radioddig5 = radiodrem4;

  }

  else if (loseldis[radnum] == 8) {
    radiocactv = lodmespeed[radnum];
    radiocdig1 = 15, radiocdig2 = 15;
    radiocdig3 = radiocactv/100, radiocrem3 =radiocactv%100;
    radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
    radiocdig5 = radiocrem4;

    radiodstby = lodmetime[radnum];
    radioddig1 = 15, radioddig2 = 15;
    radioddig3 = radiodstby/100, radiodrem3 = radiodstby%100;
    radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
    radioddig4 = radioddig4, radioddig5 = radiodrem4;

  }


  else if (loseldis[radnum] == 9) {

    if(xpanelsfnbutton == 0) {
      if (loxpdrsel[radnum] == 1) {
        radiocactv = lobaroset[radnum];
        radiocdig1 = 15, radiocdig2 = radiocactv/1000, radiocrem2 = radiocactv%1000;
        radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
        if (metricpressenable == 0) {
            radiocdig3 = radiocdig3+208;
        }
        if (metricpressenable == 1) {
            radiocdig3 = radiocdig3;
        }
        radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
        radiocdig5 = radiocrem4;

        radiodstby = loxpdrcode[radnum];
        radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
        radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
        radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
        radioddig5 = radiodrem4, radioddig5 = radioddig5+208;
      }

      if (loxpdrsel[radnum] == 2) {
        radiocactv = lobaroset[radnum];
        radiocdig1 = 15, radiocdig2 = radiocactv/1000, radiocrem2 = radiocactv%1000;
        radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
        if (metricpressenable == 0) {
            radiocdig3 = radiocdig3+208;
        }
        if (metricpressenable == 1) {
            radiocdig3 = radiocdig3;
        }
        radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
        radiocdig5 = radiocrem4;

        radiodstby = loxpdrcode[radnum];
        radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
        radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
        radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
        radioddig4 = radioddig4+208;
        radioddig5 = radiodrem4;
      }

      if (loxpdrsel[radnum] == 3) {
        radiocactv = lobaroset[radnum];
        radiocdig1 = 15, radiocdig2 = radiocactv/1000, radiocrem2 = radiocactv%1000;
        radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
        if (metricpressenable == 0) {
            radiocdig3 = radiocdig3+208;
        }
        if (metricpressenable == 1) {
            radiocdig3 = radiocdig3;
        }
        radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
        radiocdig5 = radiocrem4;

        radiodstby = loxpdrcode[radnum];
        radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
        radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
        radioddig3 = radioddig3+208;
        radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
        radioddig5 = radiodrem4;
      }

      if (loxpdrsel[radnum] == 4) {
        radiocactv = lobaroset[radnum];
        radiocdig1 = 15, radiocdig2 = radiocactv/1000, radiocrem2 = radiocactv%1000;
        radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
        if (metricpressenable == 0) {
            radiocdig3 = radiocdig3+208;
        }
        if (metricpressenable == 1) {
            radiocdig3 = radiocdig3;
        }
        radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
        radiocdig5 = radiocrem4;

        radiodstby = loxpdrcode[radnum];
        radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
        radioddig2 = radioddig2+208;
        radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
        radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
        radioddig5 = radiodrem4;
      }

      if(testbit(radiobuf[radnum],LOWER_FINE_UP)) {
          lomodeturnoff = 0;
      }
      if(testbit(radiobuf[radnum],LOWER_FINE_DN)) {
          lomodeturnoff = 0;
      }

      if(testbit(radiobuf[radnum],LOWER_COARSE_UP)) {
          lomodeturnoff = 0;
      }
      if(testbit(radiobuf[radnum],LOWER_COARSE_DN)) {
          lomodeturnoff = 0;
      }

      if (lomodeturnoff == 200) {
         loxpdrsel[radnum] = 1;
         if (XPLMGetDatai(XpdrMode) == 0) {
             radioddig1 = 15+208;
         }
         if (XPLMGetDatai(XpdrMode) == 1) {
             radioddig2 = radioddig2+208;
         }
         if (XPLMGetDatai(XpdrMode) == 2) {
             radioddig3 = radioddig3+208;
         }
         if (XPLMGetDatai(XpdrMode) == 3) {
             radioddig4 = radioddig4+208;
         }

      }
      else {
        lomodeturnoff++;

      }



   }

    if(xpanelsfnbutton == 1) {
          radiocactv = lobaroset[radnum];
          radiocdig1 = 15+208, radiocdig2 = radiocactv/1000, radiocrem2 = radiocactv%1000;
          radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
          if (metricpressenable == 0) {
              radiocdig3 = radiocdig3+208;
          }
          if (metricpressenable == 1) {
              radiocdig3 = radiocdig3;
          }
          radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
          radiocdig5 = radiocrem4;

          radiodstby = upxpdrcode[radnum];
          radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
          radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
          radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
          radioddig5 = radiodrem4,  radioddig5 = radioddig5;
    }
  
  }

  else if (loseldis[radnum] == 10) {
    radiocdig1 = 15, radiocdig2 = 15, radiocdig3 = 15, radiocdig4 = 15, radiocdig5 = 15;
    radioddig1 = 15, radioddig2 = 15, radioddig3 = 15, radioddig4 = 15, radioddig5 = 15;
  } 

  else if (loseldis[radnum] == 11) {

      radiocactv = lobaroset[radnum];
      radiocdig1 = 15, radiocdig2 = radiocactv/1000, radiocrem2 = radiocactv%1000;
      radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
      if (metricpressenable == 0) {
          radiocdig3 = radiocdig3+208;
      }
      if (metricpressenable == 1) {
          radiocdig3 = radiocdig3;
      }
      radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
      radiocdig5 = radiocrem4;


      if ((rad1uprxpdrswitchremap == 777) && (radnum == 0)) {
          radiodstby = rad1lwrxpdrdigitremap;
          radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
          radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
          radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
          radioddig5 = radiodrem4,  radioddig5 = radioddig5+208;

      } else if ((rad2uprxpdrswitchremap == 777) && (radnum == 1)) {
          radiodstby = rad2lwrxpdrdigitremap;
          radioddig1 = 15, radioddig2 = radiodstby/1000, radiodrem2 = radiodstby%1000;
          radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
          radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
          radioddig5 = radiodrem4,  radioddig5 = radioddig5+208;

      }
  }

}

void process_radio_make_message()
{


// ****************** Make Message One Digit at A Time ************************
  char radioadigit1 = radioadig1, radioadigit2 = radioadig2, radioadigit3 = radioadig3;
  char radioadigit4 = radioadig4, radioadigit5 = radioadig5;
  char radiobdigit1 = radiobdig1, radiobdigit2 = radiobdig2, radiobdigit3 = radiobdig3;
  char radiobdigit4 = radiobdig4, radiobdigit5 = radiobdig5;	
  char radiocdigit1 = radiocdig1, radiocdigit2 = radiocdig2, radiocdigit3 = radiocdig3;
  char radiocdigit4 = radiocdig4, radiocdigit5 = radiocdig5;
  char radioddigit1 = radioddig1, radioddigit2 = radioddig2, radioddigit3 = radioddig3;
  char radioddigit4 = radioddig4, radioddigit5 = radioddig5;

// ******************* Load Array with Message of Digits *********************
  radiowbuf[radnum][0] = 0; 
  radiowbuf[radnum][1] = radioadigit1, radiowbuf[radnum][2] = radioadigit2, radiowbuf[radnum][3] = radioadigit3; 
  radiowbuf[radnum][4] = radioadigit4, radiowbuf[radnum][5] = radioadigit5;
  radiowbuf[radnum][6] = radiobdigit1, radiowbuf[radnum][7] = radiobdigit2, radiowbuf[radnum][8] = radiobdigit3; 
  radiowbuf[radnum][9] = radiobdigit4, radiowbuf[radnum][10] = radiobdigit5;
  radiowbuf[radnum][11] = radiocdigit1, radiowbuf[radnum][12] = radiocdigit2, radiowbuf[radnum][13] = radiocdigit3; 
  radiowbuf[radnum][14] = radiocdigit4, radiowbuf[radnum][15] = radiocdigit5;
  radiowbuf[radnum][16] = radioddigit1, radiowbuf[radnum][17] = radioddigit2, radiowbuf[radnum][18] = radioddigit3; 
  radiowbuf[radnum][19] = radioddigit4, radiowbuf[radnum][20] = radioddigit5;

}

// ***************** Create Datareferences for upper Switches ************
void process_upper_datareferences()
{
    if(testbit(radiobuf[radnum],UPPER_COM1)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCom1OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCom1OwnedDataRef, 1);
        } else if (radnum == 2) {
             XPLMSetDatai(Rad3UpperCom1OwnedDataRef, 1);
        }

    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCom1OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCom1OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCom1OwnedDataRef, 0);
        }

    }

    if(testbit(radiobuf[radnum],UPPER_COM2)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCom2OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCom2OwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCom2OwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCom2OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCom2OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCom2OwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_NAV1)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperNav1OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperNav1OwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperNav1OwnedDataRef, 1);
        }

    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperNav1OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperNav1OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperNav1OwnedDataRef, 0);
        }
    }

    if(testbit(radiobuf[radnum],UPPER_NAV2)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperNav2OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperNav2OwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperNav2OwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperNav2OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperNav2OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperNav2OwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_ADF)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperAdfOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperAdfOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperAdfOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperAdfOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperAdfOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperAdfOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_DME)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperDmeOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperDmeOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperDmeOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperDmeOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperDmeOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperDmeOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_XPDR)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperXpdrOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperXpdrOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperXpdrOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperXpdrOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperXpdrOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperXpdrOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_COARSE_UP)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCorseIncOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCorseIncOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCorseIncOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCorseIncOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCorseIncOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCorseIncOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_COARSE_DN)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCorseDecOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCorseDecOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCorseDecOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperCorseDecOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperCorseDecOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperCorseDecOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_FINE_UP)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperFineIncOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperFineIncOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperFineIncOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperFineIncOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperFineIncOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperFineIncOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_FINE_DN)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperFineDecOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperFineDecOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperFineDecOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperFineDecOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperFineDecOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperFineDecOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperActStbyOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperActStbyOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperActStbyOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1UpperActStbyOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2UpperActStbyOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3UpperActStbyOwnedDataRef, 0);
        }
    }


}



// ***************** Upper COM1 Switch Position *******************

void process_upper_com1_switch()
{
    if(testbit(radiobuf[radnum],UPPER_COM1)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            upseldis[radnum] = 10;
        } else {
           upseldis[radnum] = 1;
        }
        if (radiores > 0) {
            if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                upcom1dbncfninc[radnum]++;
                if (upcom1dbncfninc[radnum] > radspeed) {
                    if ((rad1uprcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom1FnUpRemapableCmd);
                    } else if ((rad2uprcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom1FnUpRemapableCmd);
                    } else if ((rad3uprcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom1FnUpRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com1StbyFineUp);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com1StbyFineUp_833);
                        }
                     }
                    upcom1dbncfninc[radnum] = 0;
                }
            }
            Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

            if((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                upcom1dbncfndec[radnum]++;
                if (upcom1dbncfndec[radnum] > radspeed) {
                    if ((rad1uprcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom1FnDnRemapableCmd);
                    } else if ((rad2uprcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom1FnDnRemapableCmd);
                    } else if ((rad3uprcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom1FnDnRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com1StbyFineDn);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com1StbyFineDn_833);
                        }
                    }
                    upcom1dbncfndec[radnum] = 0;
                }
            }
            Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

            if((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                upcom1dbnccorinc[radnum]++;
                if (upcom1dbnccorinc[radnum] > radspeed) {
                    if ((rad1uprcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom1CrsUpRemapableCmd);
                    } else if ((rad2uprcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom1CrsUpRemapableCmd);
                    } else if ((rad3uprcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom1CrsUpRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com1StbyCorseUp);
                    }
                    upcom1dbnccorinc[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

            if((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                upcom1dbnccordec[radnum]++;
                if (upcom1dbnccordec[radnum] > radspeed) {
                    if ((rad1uprcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom1CrsDnRemapableCmd);
                    } else if ((rad2uprcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom1CrsDnRemapableCmd);
                    } else if ((rad3uprcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom1CrsDnRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com1StbyCorseDn);
                    }
                    upcom1dbnccordec[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

            if (radnum == 0) {
                if (rad1uprcom1actstbybtnremap == 2) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad1UprCom1ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad1UprCom1ActStbyRemapableData, 0);
                    }
                } else if (rad1uprcom1actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Rad1UprCom1ActStbyRemapableCmd);
                    }
                } else {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Com1ActStby);
                    }
                }
            } else if (radnum == 1) {
                if (rad2uprcom1actstbybtnremap == 2) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad2UprCom1ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad2UprCom1ActStbyRemapableData, 0);

                    }
                } else if (rad2uprcom1actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Rad2UprCom1ActStbyRemapableCmd);
                    }
                } else {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Com1ActStby);
                    }
                }
           } else if (radnum == 2) {
                if (rad3uprcom1actstbybtnremap == 2) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad3UprCom1ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad3UprCom1ActStbyRemapableData, 0);
                    }
                } else if (rad3uprcom1actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Rad3UprCom1ActStbyRemapableCmd);
                    }
                } else {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Com1ActStby);
                    }
                }

           }

        }

        if ((rad1uprcom1switchremap == 1) && (radnum == 0)) {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad1UpperCom1ActRemapableData);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Rad1UpperCom1StbyRemapableData);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad1UpperCom1ActRemapableData);
                upstbycomfreq[radnum] = XPLMGetDatai(Rad1UpperCom1StbyRemapableData);
            }



        } else if ((rad2uprcom1switchremap == 1) && (radnum == 1)) {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad2UpperCom1ActRemapableData);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Rad2UpperCom1StbyRemapableData);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad2UpperCom1ActRemapableData);
                upstbycomfreq[radnum] = XPLMGetDatai(Rad2UpperCom1StbyRemapableData);
            }


        } else if ((rad3uprcom1switchremap == 1) && (radnum == 2)) {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad3UpperCom1ActRemapableData);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Rad3UpperCom1StbyRemapableData);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad3UpperCom1ActRemapableData);
                upstbycomfreq[radnum] = XPLMGetDatai(Rad3UpperCom1StbyRemapableData);
            }


        } else {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Com1ActFreq);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Com1StbyFreq);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Com1ActFreq_833);
                upstbycomfreq[radnum] = XPLMGetDatai(Com1StbyFreq_833);
            }

        }
        upcom1[radnum] = 1;
    }
}

// ***************** Upper COM2 Switch Position *******************
void process_upper_com2_switch()
{
    if(testbit(radiobuf[radnum],UPPER_COM2)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            upseldis[radnum] = 10;
        } else {
           upseldis[radnum] = 2;
        }
        if (radiores > 0) {
            if((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                upcom2dbncfninc[radnum]++;
                if (upcom2dbncfninc[radnum] > radspeed) {
                    if ((rad1uprcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom2FnUpRemapableCmd);
                    } else if ((rad2uprcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom2FnUpRemapableCmd);
                    } else if ((rad3uprcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom2FnUpRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com2StbyFineUp);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com2StbyFineUp_833);
                        }
                    }
                    upcom2dbncfninc[radnum] = 0;
                }
            }
            Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

            if((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                upcom2dbncfndec[radnum]++;
                if (upcom2dbncfndec[radnum] > radspeed) {
                    if ((rad1uprcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom2FnDnRemapableCmd);
                    } else if ((rad2uprcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom2FnDnRemapableCmd);
                    } else if ((rad3uprcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom2FnDnRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com2StbyFineDn);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com2StbyFineDn_833);
                        }
                    }
                    upcom2dbncfndec[radnum] = 0;
                }
            }
            Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

            if((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                upcom2dbnccorinc[radnum]++;
                if (upcom2dbnccorinc[radnum] > radspeed) {
                    if ((rad1uprcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom2CrsUpRemapableCmd);
                    } else if ((rad2uprcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom2CrsUpRemapableCmd);
                    } else if ((rad3uprcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom2CrsUpRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com2StbyCorseUp);
                    }
                    upcom2dbnccorinc[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

            if((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                upcom2dbnccordec[radnum]++;
                if (upcom2dbnccordec[radnum] > radspeed) {
                    if ((rad1uprcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1UprCom2CrsDnRemapableCmd);
                    } else if ((rad2uprcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2UprCom2CrsDnRemapableCmd);
                    } else if ((rad3uprcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3UprCom2CrsDnRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com2StbyCorseDn);
                    }
                    upcom2dbnccordec[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

            if (radnum == 0) {
                if (rad1uprcom2actstbybtnremap == 2) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad1UprCom2ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad1UprCom2ActStbyRemapableData, 0);
                    }
                } else if (rad1uprcom2actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Rad1UprCom2ActStbyRemapableCmd);
                    }
                } else {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Com2ActStby);
                    }
                }
            } else if (radnum == 1) {
                sprintf(radtestbuf, "Xsaitekpanels: rad2uprcom2actstbybtnremap ==  %d \n", rad2uprcom2actstbybtnremap);
                XPLMDebugString(radtestbuf);
                if (rad2uprcom2actstbybtnremap == 2) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad2UprCom2ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad2UprCom2ActStbyRemapableData, 0);
                    }
                } else if (rad2uprcom2actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Rad2UprCom2ActStbyRemapableCmd);
                    }
                } else {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Com2ActStby);
                    }
                }
            } else if (radnum == 2) {
                sprintf(radtestbuf, "Xsaitekpanels: rad3uprcom2actstbybtnremap ==  %d \n", rad3uprcom2actstbybtnremap);
                XPLMDebugString(radtestbuf);
                if (rad3uprcom2actstbybtnremap == 2) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad3UprCom2ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMSetDatai(Rad3UprCom2ActStbyRemapableData, 0);
                    }
                } else if (rad3uprcom2actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Rad3UprCom2ActStbyRemapableCmd);
                    }
                } else {
                    if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                        XPLMCommandOnce(Com2ActStby);
                    }
                }
            }
        }


        if ((rad1uprcom2switchremap == 1) && (radnum == 0)) {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad1UpperCom2ActRemapableData);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Rad1UpperCom2StbyRemapableData);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad1UpperCom2ActRemapableData);
                upstbycomfreq[radnum] = XPLMGetDatai(Rad1UpperCom2StbyRemapableData);
            }

        } else if ((rad2uprcom2switchremap == 1) && (radnum == 1)) {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad2UpperCom2ActRemapableData);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Rad2UpperCom2StbyRemapableData);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad2UpperCom2ActRemapableData);
                upstbycomfreq[radnum] = XPLMGetDatai(Rad2UpperCom2StbyRemapableData);
            }


        } else if ((rad3uprcom2switchremap == 1) && (radnum == 2)) {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad3UpperCom2ActRemapableData);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Rad3UpperCom2StbyRemapableData);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Rad3UpperCom2ActRemapableData);
                upstbycomfreq[radnum] = XPLMGetDatai(Rad3UpperCom2StbyRemapableData);
            }


        } else {
            if (channelspacing833enable == 0) {
                upactcomfreq[radnum] = XPLMGetDatai(Com2ActFreq);
                upactcomfreq[radnum] = upactcomfreq[radnum] * 10;
                upstbycomfreq[radnum] = XPLMGetDatai(Com2StbyFreq);
                upstbycomfreq[radnum] = upstbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                upactcomfreq[radnum] = XPLMGetDatai(Com2ActFreq_833);
                upstbycomfreq[radnum] = XPLMGetDatai(Com2StbyFreq_833);
            }

        }


        upcom2[radnum] = 1;
    }
}

// ***************** Upper NAV1 Switch Position *******************

void process_upper_nav1_switch()
{
    if(testbit(radiobuf[radnum],UPPER_NAV1)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            upseldis[radnum] = 10;
        } else {
           upseldis[radnum] = 3;
        }
        if (radiores > 0) {
            if((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                upnav1dbncfninc[radnum]++;
                if (upnav1dbncfninc[radnum] > radspeed) {
                    if(xpanelsfnbutton == 1) {
                        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprObs1FnUpRemapableCmd);
                        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprObs1FnUpRemapableCmd);
                        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprObs1FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs1Up);
                        }

                    } else {
                        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav1FnUpRemapableCmd);
                        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav1FnUpRemapableCmd);
                        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav1FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyFineUp);
                        }
                    }
                    upnav1dbncfninc[radnum] = 0;
                }
            }
            Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

            if((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                upnav1dbncfndec[radnum]++;
                if (upnav1dbncfndec[radnum] > radspeed) {
                    if(xpanelsfnbutton == 1) {
                        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprObs1FnDnRemapableCmd);
                        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprObs1FnDnRemapableCmd);
                        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprObs1FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs1Down);
                        }

                    } else {
                        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav1FnDnRemapableCmd);
                        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav1FnDnRemapableCmd);
                        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav1FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyFineDn);
                        }
                    }
                    upnav1dbncfndec[radnum] = 0;
                }
            }
            Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

            if((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                upnav1dbnccorinc[radnum]++;
                if (upnav1dbnccorinc[radnum] > radspeed) {
                    radn = 10;
                    if(xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1UprObs1CrsUpRemapableCmd);
                            } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2UprObs1CrsUpRemapableCmd);
                            } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3UprObs1CrsUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs1Up);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav1CrsUpRemapableCmd);
                        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav1CrsUpRemapableCmd);
                        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav1CrsUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyCorseUp);
                        }
                    }
                    upnav1dbnccorinc[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

            if((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                upnav1dbnccordec[radnum]++;
                if (upnav1dbnccordec[radnum] > radspeed) {
                    radn = 10;
                    if(xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1UprObs1CrsDnRemapableCmd);
                            } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2UprObs1CrsDnRemapableCmd);
                            } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3UprObs1CrsDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs1Down);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav1CrsDnRemapableCmd);
                        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav1CrsDnRemapableCmd);
                        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav1CrsDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyCorseDn);
                        }
                    }
                    upnav1dbnccordec[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

            if(testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                if ((rad1uprnav1actstbybtnremap == 1) && (radnum == 0)) {
                    XPLMCommandOnce(Rad1UprNav1ActStbyRemapableCmd);
                } else if ((rad2uprnav1actstbybtnremap == 1) && (radnum == 1)) {
                    XPLMCommandOnce(Rad2UprNav1ActStbyRemapableCmd);
                } else if ((rad3uprnav1actstbybtnremap == 1) && (radnum == 2)) {
                    XPLMCommandOnce(Rad3UprNav1ActStbyRemapableCmd);
                } else {
                    XPLMCommandOnce(Nav1ActStby);
                }
            }
        }

        if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
            upactnavfreq[radnum] = XPLMGetDatai(Rad1UpperNav1ActRemapableData);
            upstbynavfreq[radnum] = XPLMGetDatai(Rad1UpperNav1StbyRemapableData);
        } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
            upactnavfreq[radnum] = XPLMGetDatai(Rad2UpperNav1ActRemapableData);
            upstbynavfreq[radnum] = XPLMGetDatai(Rad2UpperNav1StbyRemapableData);
        } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
            upactnavfreq[radnum] = XPLMGetDatai(Rad3UpperNav1ActRemapableData);
            upstbynavfreq[radnum] = XPLMGetDatai(Rad3UpperNav1StbyRemapableData);
        } else {
            upactnavfreq[radnum] = XPLMGetDatai(Nav1ActFreq);
            upstbynavfreq[radnum] = XPLMGetDatai(Nav1StbyFreq);
        }
        upnav1[radnum] = 1;
    }

}

// ***************** Upper NAV2 Switch Position *******************

void process_upper_nav2_switch()
{
    if (testbit(radiobuf[radnum],UPPER_NAV2)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            upseldis[radnum] = 10;
        } else {
           upseldis[radnum] = 4;
        }

        if (radiores > 0) {
            if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                upnav2dbncfninc[radnum]++;
                if (upnav2dbncfninc[radnum] > radspeed) {
                    if(xpanelsfnbutton == 1) {
                        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprObs2FnUpRemapableCmd);
                        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprObs2FnUpRemapableCmd);
                        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprObs2FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs2Up);
                        }
                    } else {
                        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav2FnUpRemapableCmd);
                        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav2FnUpRemapableCmd);
                        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav2FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyFineUp);
                        }

                    }
                    upnav2dbncfninc[radnum] = 0;
                }
            }
            Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

            if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                upnav2dbncfndec[radnum]++;
                if (upnav2dbncfndec[radnum] > radspeed) {
                    if (xpanelsfnbutton == 1) {
                        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprObs2FnDnRemapableCmd);
                        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprObs2FnDnRemapableCmd);
                        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprObs2FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs2Down);
                        }
                    } else {
                        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav2FnDnRemapableCmd);
                        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav2FnDnRemapableCmd);
                        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav2FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyFineDn);
                        }
                    }
                    upnav2dbncfndec[radnum] = 0;
                }
            }
            Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

            if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                upnav2dbnccorinc[radnum]++;
                if (upnav2dbnccorinc[radnum] > radspeed) {
                    radn = 10;
                    if (xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1UprObs2CrsUpRemapableCmd);
                            } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2UprObs2CrsUpRemapableCmd);
                            } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3UprObs2CrsUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs2Up);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav2CrsUpRemapableCmd);
                        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav2CrsUpRemapableCmd);
                        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav2CrsUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyCorseUp);
                        }
                    }
                    upnav2dbnccorinc[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

            if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                upnav2dbnccordec[radnum]++;
                if (upnav2dbnccordec[radnum] > radspeed) {
                    radn = 10;
                    if (xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1UprObs2CrsDnRemapableCmd);
                            } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2UprObs2CrsDnRemapableCmd);
                            } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3UprObs2CrsDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs2Down);
                            }
                             --radn;
                        }
                    } else {
                        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprNav2CrsDnRemapableCmd);
                        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprNav2CrsDnRemapableCmd);
                        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprNav2CrsDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyCorseDn);
                        }
                    }
                    upnav2dbnccordec[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

            if (testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                if ((rad1uprnav2actstbybtnremap == 1) && (radnum == 0)) {
                    XPLMCommandOnce(Rad1UprNav2ActStbyRemapableCmd);
                } else if ((rad2uprnav2actstbybtnremap == 1) && (radnum == 1)) {
                    XPLMCommandOnce(Rad2UprNav2ActStbyRemapableCmd);
                } else if ((rad3uprnav2actstbybtnremap == 1) && (radnum == 2)) {
                    XPLMCommandOnce(Rad3UprNav2ActStbyRemapableCmd);
                } else {
                    XPLMCommandOnce(Nav2ActStby);
                }
            }
        }
        if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
            upactnavfreq[radnum] = XPLMGetDatai(Rad1UpperNav2ActRemapableData);
            upstbynavfreq[radnum] = XPLMGetDatai(Rad1UpperNav2StbyRemapableData);
        } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
            upactnavfreq[radnum] = XPLMGetDatai(Rad2UpperNav2ActRemapableData);
            upstbynavfreq[radnum] = XPLMGetDatai(Rad2UpperNav2StbyRemapableData);
        } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
            upactnavfreq[radnum] = XPLMGetDatai(Rad3UpperNav2ActRemapableData);
            upstbynavfreq[radnum] = XPLMGetDatai(Rad3UpperNav2StbyRemapableData);
        } else {
            upactnavfreq[radnum] = XPLMGetDatai(Nav2ActFreq);
            upstbynavfreq[radnum] = XPLMGetDatai(Nav2StbyFreq);
        }
        upnav2[radnum] = 1;
    }
}

// ***************** Upper AFD Switch Position *******************

void proecss_upper_adf_switch()
{
    if (testbit(radiobuf[radnum],UPPER_ADF)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            upseldis[radnum] = 10;
        } else {
           upseldis[radnum] = 5;
        }

        UpAdf1CardDirDegm[radnum] = XPLMGetDataf(Adf1CardDirDegm);
        upstbyadf1dir[radnum] = (int)(UpAdf1CardDirDegm[radnum]);
        if (xpanelsfnbutton == 1) {
            if ((rad1upradfswitchremap == 1) || (rad2upradfswitchremap == 1) ||  (rad3upradfswitchremap == 1)) {
                upactadffreq[radnum] = XPLMGetDatai(Adf1ActFreq);
                upstbyadffreq[radnum] = XPLMGetDatai(Adf1StbyFreq);
                return;
            }

            if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                upadfdbdirfninc[radnum]++;
                if (upadfdbdirfninc[radnum] > radspeed) {
                    upstbyadf1dir[radnum] = upstbyadf1dir[radnum] + 1;
                    upadfdbdirfninc[radnum] = 0;
                }
            }
            Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

            if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                upadfdbdirfndec[radnum]++;
                if (upadfdbdirfndec[radnum] > radspeed) {
                    upstbyadf1dir[radnum] = upstbyadf1dir[radnum] - 1;
                    upadfdbdirfndec[radnum] = 0;
                }
            }
            Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

            if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                upadfdbdircorinc[radnum]++;
                if (upadfdbdircorinc[radnum] > radspeed) {
                    upstbyadf1dir[radnum] = upstbyadf1dir[radnum] + 10;
                    upadfdbdircorinc[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

            if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                upadfdbdircordec[radnum]++;
                if (upadfdbdircordec[radnum] > radspeed) {
                    upstbyadf1dir[radnum] = upstbyadf1dir[radnum] - 10;
                    upadfdbdircordec[radnum] = 0;
                }
            }
            Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

            if (upstbyadf1dir[radnum] > 360) {
                upstbyadf1dir[radnum] = 1;
            }
            if (upstbyadf1dir[radnum] < 0) {
                upstbyadf1dir[radnum] = 360;
            }
            upstbyadf1dirf[radnum] = upstbyadf1dir[radnum];
            XPLMSetDataf(Adf1CardDirDegm, (float)upstbyadf1dirf[radnum]);
        }

        if (xpanelsfnbutton == 0) {
            if (upadfsel[radnum] == 1) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upadfdbncfninc[radnum]++;
                    if (upadfdbncfninc[radnum] > radspeed) {
                        if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprAdfFnUpRemapableCmd);
                        } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprAdfFnUpRemapableCmd);
                        } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprAdfFnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Afd1StbyOnesUp);
                        }
                        upadfdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upadfdbncfndec[radnum]++;
                    if (upadfdbncfndec[radnum] > radspeed) {
                        if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprAdfFnDnRemapableCmd);
                        } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprAdfFnDnRemapableCmd);
                        } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprAdfFnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Afd1StbyOnesDn);
                        }
                        upadfdbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);
            }


            if (upadfsel[radnum] == 2) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upadfdbncfninc[radnum]++;
                    if (upadfdbncfninc[radnum] > radspeed) {
                        if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprAdfFnUpRemapableCmd);
                        } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprAdfFnUpRemapableCmd);
                        } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprAdfFnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Afd1StbyTensUp);
                        }
                        upadfdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upadfdbncfndec[radnum]++;
                    if (upadfdbncfndec[radnum] > radspeed) {
                        if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprAdfFnDnRemapableCmd);
                        } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprAdfFnDnRemapableCmd);
                        } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprAdfFnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Afd1StbyTensDn);
                        }
                        upadfdbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);
            }


            if (upadfsel[radnum] == 3) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upadfdbncfninc[radnum]++;
                    if (upadfdbncfninc[radnum] > radspeed) {
                        if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprAdfFnUpRemapableCmd);
                        } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprAdfFnUpRemapableCmd);
                        } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprAdfFnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Afd1StbyHunUp);
                        }
                        upadfdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upadfdbncfndec[radnum]++;
                    if (upadfdbncfndec[radnum] > radspeed) {
                        if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1UprAdfFnDnRemapableCmd);
                        } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2UprAdfFnDnRemapableCmd);
                        } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3UprAdfFnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Afd1StbyHunDn);
                        }
                        upadfdbncfndec[radnum] = 0;
                    }

                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);
             }

            // Use the Coarse knob to select digit in the up direction
           if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
               upadfdbnccorinc[radnum] ++;
               if (upadfdbnccorinc[radnum] > radspeed) {
                   if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                       XPLMCommandOnce(Rad1UprAdfCrsUpRemapableCmd);
                   } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                       XPLMCommandOnce(Rad2UprAdfCrsUpRemapableCmd);
                   } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                       XPLMCommandOnce(Rad3UprAdfCrsUpRemapableCmd);
                   } else {
                       upadfsel[radnum] ++;
                       upadfdbnccorinc[radnum] = 0;
                       if (upadfsel[radnum] == 4) {
                           upadfsel[radnum] = 1;
                       }
                   }
               }
           }
           Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

           // Use the Coarse knob to select digit in the down direction
           if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
               upadfdbnccordec[radnum] ++;
               if (upadfdbnccordec[radnum] > radspeed) {
                   if ((rad1upradfswitchremap == 1) && (radnum == 0)) {
                       XPLMCommandOnce(Rad1UprAdfCrsDnRemapableCmd);
                   } else if ((rad2upradfswitchremap == 1) && (radnum == 1)) {
                       XPLMCommandOnce(Rad2UprAdfCrsDnRemapableCmd);
                   } else if ((rad3upradfswitchremap == 1) && (radnum == 2)) {
                       XPLMCommandOnce(Rad3UprAdfCrsDnRemapableCmd);
                   } else {
                       upadfsel[radnum] --;
                       upadfdbnccordec[radnum] = 0;
                       if (upadfsel[radnum] == 0) {
                           upadfsel[radnum] = 3;
                       }
                    }
               }

           }
           Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

           if (testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
               if ((rad1upradfactstbybtnremap == 1) && (radnum == 0)) {
                   XPLMCommandOnce(Rad1UprAdfActStbyRemapableCmd);
               } else if ((rad2upradfactstbybtnremap == 1) && (radnum == 1)) {
                   XPLMCommandOnce(Rad2UprAdfActStbyRemapableCmd);
               } else if ((rad3upradfactstbybtnremap == 1) && (radnum == 2)) {
                   XPLMCommandOnce(Rad3UprAdfActStbyRemapableCmd);
               } else {
                   XPLMCommandOnce(Adf1ActStby);
               }
            }
        }

        upactadffreq[radnum] = XPLMGetDatai(Adf1ActFreq);
        upstbyadffreq[radnum] = XPLMGetDatai(Adf1StbyFreq);
    }
}

// ***************** Upper DME Switch Position *******************

void process_upper_dme_switch()
{

    if (testbit(radiobuf[radnum],UPPER_DME)) {
        // ****** Function button is not pushed  *******
        // Set Dme mode with ACT/STBY button
        if (xpanelsfnbutton == 0) {
            if (updmepushed == 0) {
                if (XPLMGetDatai(DmeMode) == 0) {
                    if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                        XPLMSetDatai(DmeMode, 1);
                        updmepushed = 1;
                        uplastdmepos = 0;
                    }
                }
            }
            if (updmepushed == 0) {
                if (XPLMGetDatai(DmeMode) == 1) {
                    if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                        if (uplastdmepos == 0){
                            XPLMSetDatai(DmeMode, 2);
                            updmepushed = 1;
                        }
                        if (uplastdmepos == 2){
                            XPLMSetDatai(DmeMode, 0);
                            updmepushed = 1;
                        }
                    }
                }
            }
            if (updmepushed == 0) {
                if (XPLMGetDatai(DmeMode) == 2) {
                    if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                        XPLMSetDatai(DmeMode, 1);
                        updmepushed = 1;
                        uplastdmepos = 2;
                    }
                }
            }
            if (updmepushed == 1) {
                updmeloop++;
                if (updmeloop == 50) {
                    updmepushed = 0;
                    updmeloop = 0;
                }
            }
            // Get DME display mode, where 0 is remote, 1 is frequency, and 2 is groundspeed-time
            // Get Slave Source DME display selection of what NAV radio to display. 0 for Nav1, 1 for Nav2
            updmemode[radnum] = XPLMGetDatai(DmeMode);
            updmesource[radnum] = XPLMGetDatai(DmeSlvSource);
            // If Dme mode is 0 (remote) do following
            if (updmemode[radnum] == 0) {
                // Avionics and Battery must be on or blank display
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    upseldis[radnum] = 10;
                } else {
                    upseldis[radnum] = 6;
                }
                // Slave source is 0 so use Nav1 to get speed and distance
                if (updmesource[radnum] == 0) {
                    updmenav1speedf[radnum] = XPLMGetDataf(Nav1DmeSpeed);
                    updmenavspeed[radnum] = (int)(updmenav1speedf[radnum]);
                    updmedistf[radnum] = XPLMGetDataf(Nav1DmeNmDist);
                    updmedist[radnum] = (int)(updmedistf[radnum] * 10.0f);
                // Slave source is 1 so use Nav2 to get speed and distance
                } else if (updmesource[radnum] == 1) {
                    updmenav2speedf[radnum] = XPLMGetDataf(Nav2DmeSpeed);
                    updmenavspeed[radnum] = (int)(updmenav2speedf[radnum]);
                    updmedistf[radnum] = XPLMGetDataf(Nav2DmeNmDist);
                    updmedist[radnum] = (int)(updmedistf[radnum] * 10.0f);
                }
            }
            // If Dme mode is 1 (frequency) do the following
            if (updmemode[radnum] == 1) {
                // Avionics and Battery must be on or blank display
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    upseldis[radnum] = 10;
                } else {
                    upseldis[radnum] = 7;
                }
                // Get Dme frequency to be adjusted by silver knobs
                updmefreq[radnum] = XPLMGetDatai(DmeFreq);
                updmefreqhnd = updmefreq[radnum]/100;
                updmefreqfrc = updmefreq[radnum]%100;
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) ==0)) {
                    if (updmefreqfrc == 95) {
                        updmefreqfrc = 0;
                    }
                    updmedbncfninc[radnum]++;
                    if (updmedbncfninc[radnum] == 3) {
                        updmefreqfrc = updmefreqfrc + 5;
                        updmedbncfninc[radnum] = 0;
                     }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);


                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) ==0)) {
                    if (updmefreqfrc == 0) {
                        updmefreqfrc = 95;
                    }
                    updmedbncfndec[radnum]++;
                    if (updmedbncfndec[radnum] == 3) {
                        updmefreqfrc = updmefreqfrc - 5;
                        updmedbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

                if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                    if (updmefreqhnd == 117) {
                        updmefreqhnd = 108;
                    }
                    updmedbncfninc[radnum]++;
                    if (updmedbncfninc[radnum] == 3) {
                        updmefreqhnd = updmefreqhnd + 1;
                        updmedbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

                if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                    if (updmefreqhnd == 108) {
                        updmefreqhnd = 117;
                    }
                    updmedbncfndec[radnum]++;
                    if (updmedbncfndec[radnum] == 3) {
                        updmefreqhnd = updmefreqhnd - 1;
                        updmedbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

                updmefreq[radnum] = (updmefreqhnd * 100) + updmefreqfrc;
                XPLMSetDatai(DmeFreq, updmefreq[radnum]);
                updmetime[radnum] = XPLMGetDataf(DmeTime);
            }
            // if Dme mode is 2 (groundspeed-time) do the following
           if (updmemode[radnum] == 2) {
               // Avionics and Battery must be on or blank display
               if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                   upseldis[radnum] = 10;
                } else {
                   upseldis[radnum] = 8;
               }
               updmespeedf[radnum] = XPLMGetDataf(DmeSpeed);
               updmespeed[radnum] = (int)(updmespeedf[radnum]);
               updmetime[radnum] = XPLMGetDataf(DmeTime);
           }
        }

        // ****** Function button is pushed  *******
        if (xpanelsfnbutton == 1) {
            if (updmepushed == 0) {
                if (XPLMGetDatai(DmeSlvSource) == 0) {
                    if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                        XPLMSetDatai(DmeSlvSource, 1);
                        updmepushed = 1;
                        uplastdmepos = 0;
                    }
                }
            }
            if (updmepushed == 0) {
                if (XPLMGetDatai(DmeSlvSource) == 1) {
                    if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                        XPLMSetDatai(DmeSlvSource, 0);
                        updmepushed = 1;
                    }
                }
            }
            if (updmepushed == 1) {
                updmeloop++;
                if (updmeloop == 50) {
                    updmepushed = 0;
                    updmeloop = 0;
                }
            }
        }
    }
}

// ***************** Upper Transponder Switch Position *******************

void process_upper_xpdr_switch()
{
    if(testbit(radiobuf[radnum],UPPER_XPDR)) {
        if ((rad1uprxpdrswitchremap == 777) && (radnum == 0)) {
            if(xpanelsfnbutton == 0) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    upseldis[radnum] = 10;
                } else {
                   upseldis[radnum] = 9;
                }
                //upseldis[radnum] = 9;
                rad1uprxpdrlastdigitremap = 0;
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upxpdrdbncfninc[radnum]++;
                    if (upxpdrdbncfninc[radnum] > radspeed) {
                        rad1uprxpdrdigitremap++;
                        upxpdrdbncfninc[radnum] = 0;
                        if (rad1uprxpdrdigitremap > 7) {
                            rad1uprxpdrdigitremap = 0;
                        }
                        rad1uprxpdrlastdigitremap = 1;
                    }
                    rad1uprxpdrlastdigitcnt = 0;
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upxpdrdbncfninc[radnum]++;
                    if (upxpdrdbncfninc[radnum] > radspeed) {
                        rad1uprxpdrdigitremap--;
                        upxpdrdbncfninc[radnum] = 0;
                        if (rad1uprxpdrdigitremap < 0) {
                            rad1uprxpdrdigitremap = 7;
                        }
                        rad1uprxpdrlastdigitremap = 1;
                    }
                    rad1uprxpdrlastdigitcnt = 0;
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);


                if (rad1uprxpdrlastdigitremap == 0) {
                    if (rad1uprxpdrlastdigitcnt < 25) {
                        rad1uprxpdrlastdigitcnt++;
                    }
                }

                if (rad1uprxpdrlastdigitcnt < 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        upseldis[radnum] = 10;
                    } else {
                       upseldis[radnum] = 11;
                    }
                    //upseldis[radnum] = 11;
                }

                if (rad1uprxpdrlastdigitcnt == 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        upseldis[radnum] = 10;
                    } else {
                       upseldis[radnum] = 9;
                    }
                    //upseldis[radnum] = 9;
                    XPLMSetDatai(Rad1UpperXpdrRemapableData, rad1uprxpdrdigitremap);
                    rad1uprxpdrlastdigitcnt = rad1uprxpdrlastdigitcnt + 1;
                }


                // Use the ACT/STBY button to select XPDR mode

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1UpperXpdrRemapableMode) == 0) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(Rad1UpperXpdrRemapableMode, 1);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 0;
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1UpperXpdrRemapableMode) == 1) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 0) {
                                XPLMSetDatai(Rad1UpperXpdrRemapableMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 1;
                            }
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(Rad1UpperXpdrRemapableMode, 0);
                                upxpdrpushed = 1;
                            }
                        }
                      }
                    }
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1UpperXpdrRemapableMode) == 2) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 1) {
                                XPLMSetDatai(Rad1UpperXpdrRemapableMode, 3);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                            if (uplastxpdrpos == 3) {
                                XPLMSetDatai(Rad1UpperXpdrRemapableMode, 1);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                        }
                    }
                }
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1UpperXpdrRemapableMode) == 3) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(Rad1UpperXpdrRemapableMode, 4);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 3;
                            }
                            if (uplastxpdrpos == 4) {
                                XPLMSetDatai(Rad1UpperXpdrRemapableMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 3;
                            }
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1UpperXpdrRemapableMode) == 4) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(Rad1UpperXpdrRemapableMode, 3);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 4;
                        }
                    }
                }
                // if upxpdrloop is to low mode switch will not stop in position
                // if upxpdrloop is to high mode switch sometimes will not move
                // ToDo Need to find a better way
                if (upxpdrpushed == 1) {
                    upxpdrloop++;
                    if (upxpdrloop == 25) {
                        upxpdrpushed = 0;
                        upxpdrloop = 0;
                    }
                }
            }

            if (xpanelsfnbutton == 1) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upqnhdbncfninc[radnum]++;
                    if (upqnhdbncfninc[radnum] > radspeed) {
                        XPLMCommandOnce(Rad1UpperXpdrBaroUpRemapableCmd);
                        upqnhdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);


                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upqnhdbncfndec[radnum]++;
                    if (upqnhdbncfndec[radnum] > radspeed) {
                        XPLMCommandOnce(Rad1UpperXpdrBaroDnRemapableCmd);
                        upqnhdbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);


                if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                    upqnhdbnccorinc[radnum]++;
                    if (upqnhdbnccorinc[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad1UpperXpdrBaroUpRemapableCmd);
                            --radn;
                        }
                        upqnhdbnccorinc[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);


                if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                    upqnhdbnccordec[radnum]++;
                    if (upqnhdbnccordec[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad1UpperXpdrBaroDnRemapableCmd);
                            --radn;
                        }
                        upqnhdbnccordec[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);


                if (testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                    XPLMSetDatai(Rad1UpperXpdrBaroStdRemapableData, 1);

                }

            }


            upxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
            upxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
            upbarosetf[radnum] = XPLMGetDataf(BaroSetting);
            if (metricpressenable == 0) {
                upbarosetf[radnum] = upbarosetf[radnum] * 100.0;
                XPLMSetDatai(MetricPress, 0);
            }
            if (metricpressenable == 1) {
                upbarosetf[radnum] = upbarosetf[radnum] * 33.8639;
                XPLMSetDatai(MetricPress, 1);
            }
            upbaroset[radnum] = (int)upbarosetf[radnum];

        } else if ((rad2uprxpdrswitchremap == 777)  && (radnum == 1)) {

            if(xpanelsfnbutton == 0) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    upseldis[radnum] = 10;
                } else {
                   upseldis[radnum] = 9;
                }
                //upseldis[radnum] = 9;
                rad2uprxpdrlastdigitremap = 0;
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upxpdrdbncfninc[radnum]++;
                    if (upxpdrdbncfninc[radnum] > radspeed) {
                        rad2uprxpdrdigitremap++;
                        upxpdrdbncfninc[radnum] = 0;
                        if (rad2uprxpdrdigitremap > 7) {
                            rad2uprxpdrdigitremap = 0;
                        }
                        rad2uprxpdrlastdigitremap = 1;
                    }
                    rad2uprxpdrlastdigitcnt = 0;
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);


                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upxpdrdbncfninc[radnum]++;
                    if (upxpdrdbncfninc[radnum] > radspeed) {
                        rad2uprxpdrdigitremap--;
                        upxpdrdbncfninc[radnum] = 0;
                        if (rad2uprxpdrdigitremap < 0) {
                            rad2uprxpdrdigitremap = 7;
                        }
                        rad2uprxpdrlastdigitremap = 1;
                    }
                    rad2uprxpdrlastdigitcnt = 0;
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);


                if (rad2uprxpdrlastdigitremap == 0) {
                    if (rad2uprxpdrlastdigitcnt < 25) {
                        rad2uprxpdrlastdigitcnt++;
                    }
                }

                if (rad2uprxpdrlastdigitcnt < 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        upseldis[radnum] = 10;
                    } else {
                       upseldis[radnum] = 11;
                    }
                    //upseldis[radnum] = 11;
                }

                if (rad2uprxpdrlastdigitcnt == 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        upseldis[radnum] = 10;
                    } else {
                       upseldis[radnum] = 9;
                    }
                    //upseldis[radnum] = 9;
                    XPLMSetDatai(Rad2UpperXpdrRemapableData, rad2uprxpdrdigitremap);
                    rad2uprxpdrlastdigitcnt = rad2uprxpdrlastdigitcnt + 1;
                }

                // Use the ACT/STBY button to select XPDR mode

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad2UpperXpdrRemapableMode) == 0) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(Rad2UpperXpdrRemapableMode, 1);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 0;
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad2UpperXpdrRemapableMode) == 1) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 0) {
                                XPLMSetDatai(Rad2UpperXpdrRemapableMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 1;
                            }
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(Rad2UpperXpdrRemapableMode, 0);
                                upxpdrpushed = 1;
                            }
                        }
                      }
                    }
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad2UpperXpdrRemapableMode) == 2) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 1) {
                                XPLMSetDatai(Rad2UpperXpdrRemapableMode, 3);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                            if (uplastxpdrpos == 3) {
                                XPLMSetDatai(Rad2UpperXpdrRemapableMode, 1);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                        }
                    }
                }
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad2UpperXpdrRemapableMode) == 3) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(Rad2UpperXpdrRemapableMode, 4);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 3;
                            }
                            if (uplastxpdrpos == 4) {
                                XPLMSetDatai(Rad2UpperXpdrRemapableMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 3;
                            }
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad2UpperXpdrRemapableMode) == 4) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(Rad2UpperXpdrRemapableMode, 3);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 4;
                        }
                    }
                }
                // if upxpdrloop is to low mode switch will not stop in position
                // if upxpdrloop is to high mode switch sometimes will not move
                // ToDo Need to find a better way
                if (upxpdrpushed == 1) {
                    upxpdrloop++;
                    if (upxpdrloop == 25) {
                        upxpdrpushed = 0;
                        upxpdrloop = 0;
                    }
                }
            }

            if (xpanelsfnbutton == 1) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upqnhdbncfninc[radnum]++;
                    if (upqnhdbncfninc[radnum] > radspeed) {
                        XPLMCommandOnce(Rad2UpperXpdrBaroUpRemapableCmd);
                        upqnhdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);


                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upqnhdbncfndec[radnum]++;
                    if (upqnhdbncfndec[radnum] > radspeed) {
                        XPLMCommandOnce(Rad2UpperXpdrBaroDnRemapableCmd);
                        upqnhdbncfndec[radnum] = 0;
                    }
                }


                if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                    upqnhdbnccorinc[radnum]++;
                    if (upqnhdbnccorinc[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad2UpperXpdrBaroUpRemapableCmd);
                            --radn;
                        }
                        upqnhdbnccorinc[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);


                if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                    upqnhdbnccordec[radnum]++;
                    if (upqnhdbnccordec[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad2UpperXpdrBaroDnRemapableCmd);
                            --radn;
                        }
                        upqnhdbnccordec[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);


                if (testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                    XPLMSetDatai(Rad2UpperXpdrBaroStdRemapableData, 1);

                }

            }

            upxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
            upxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
            upbarosetf[radnum] = XPLMGetDataf(BaroSetting);
            if (metricpressenable == 0) {
                upbarosetf[radnum] = upbarosetf[radnum] * 100.0;
                XPLMSetDatai(MetricPress, 0);
            }
            if (metricpressenable == 1) {
                upbarosetf[radnum] = upbarosetf[radnum] * 33.8639;
                XPLMSetDatai(MetricPress, 1);
            }
            upbaroset[radnum] = (int)upbarosetf[radnum];




        } else if ((rad3uprxpdrswitchremap == 777)  && (radnum == 2)) {

            if(xpanelsfnbutton == 0) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    upseldis[radnum] = 10;
                } else {
                   upseldis[radnum] = 9;
                }
                //upseldis[radnum] = 9;
                rad3uprxpdrlastdigitremap = 0;
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upxpdrdbncfninc[radnum]++;
                    if (upxpdrdbncfninc[radnum] > radspeed) {
                        rad3uprxpdrdigitremap++;
                        upxpdrdbncfninc[radnum] = 0;
                        if (rad3uprxpdrdigitremap > 7) {
                            rad3uprxpdrdigitremap = 0;
                        }
                        rad3uprxpdrlastdigitremap = 1;
                    }
                    rad3uprxpdrlastdigitcnt = 0;
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);


                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upxpdrdbncfninc[radnum]++;
                    if (upxpdrdbncfninc[radnum] > radspeed) {
                        rad3uprxpdrdigitremap--;
                        upxpdrdbncfninc[radnum] = 0;
                        if (rad3uprxpdrdigitremap < 0) {
                            rad3uprxpdrdigitremap = 7;
                        }
                        rad3uprxpdrlastdigitremap = 1;
                    }
                    rad3uprxpdrlastdigitcnt = 0;
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);


                if (rad3uprxpdrlastdigitremap == 0) {
                    if (rad3uprxpdrlastdigitcnt < 25) {
                        rad3uprxpdrlastdigitcnt++;
                    }
                }

                if (rad3uprxpdrlastdigitcnt < 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        upseldis[radnum] = 10;
                    } else {
                       upseldis[radnum] = 11;
                    }
                    //upseldis[radnum] = 11;
                }

                if (rad3uprxpdrlastdigitcnt == 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        upseldis[radnum] = 10;
                    } else {
                       upseldis[radnum] = 9;
                    }
                    //upseldis[radnum] = 9;
                    XPLMSetDatai(Rad2UpperXpdrRemapableData, rad3uprxpdrdigitremap);
                    rad3uprxpdrlastdigitcnt = rad3uprxpdrlastdigitcnt + 1;
                }


                // Use the ACT/STBY button to select XPDR mode

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad3UpperXpdrRemapableMode) == 0) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(Rad3UpperXpdrRemapableMode, 1);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 0;
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad3UpperXpdrRemapableMode) == 1) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 0) {
                                XPLMSetDatai(Rad3UpperXpdrRemapableMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 1;
                            }
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(Rad3UpperXpdrRemapableMode, 0);
                                upxpdrpushed = 1;
                            }
                        }
                      }
                    }
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad3UpperXpdrRemapableMode) == 2) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 1) {
                                XPLMSetDatai(Rad3UpperXpdrRemapableMode, 3);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                            if (uplastxpdrpos == 3) {
                                XPLMSetDatai(Rad3UpperXpdrRemapableMode, 1);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                        }
                    }
                }
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad3UpperXpdrRemapableMode) == 3) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(Rad3UpperXpdrRemapableMode, 4);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 3;
                            }
                            if (uplastxpdrpos == 4) {
                                XPLMSetDatai(Rad3UpperXpdrRemapableMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 3;
                            }
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad3UpperXpdrRemapableMode) == 4) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(Rad3UpperXpdrRemapableMode, 3);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 4;
                        }
                    }
                }
                // if upxpdrloop is to low mode switch will not stop in position
                // if upxpdrloop is to high mode switch sometimes will not move
                // ToDo Need to find a better way
                if (upxpdrpushed == 1) {
                    upxpdrloop++;
                    if (upxpdrloop == 25) {
                        upxpdrpushed = 0;
                        upxpdrloop = 0;
                    }
                }
            }

            if (xpanelsfnbutton == 1) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upqnhdbncfninc[radnum]++;
                    if (upqnhdbncfninc[radnum] > radspeed) {
                        XPLMCommandOnce(Rad3UpperXpdrBaroUpRemapableCmd);
                        upqnhdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);


                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upqnhdbncfndec[radnum]++;
                    if (upqnhdbncfndec[radnum] > radspeed) {
                        XPLMCommandOnce(Rad3UpperXpdrBaroDnRemapableCmd);
                        upqnhdbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);


                if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                    upqnhdbnccorinc[radnum]++;
                    if (upqnhdbnccorinc[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad3UpperXpdrBaroUpRemapableCmd);
                            --radn;
                        }
                        upqnhdbnccorinc[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);


                if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                    upqnhdbnccordec[radnum]++;
                    if (upqnhdbnccordec[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad3UpperXpdrBaroDnRemapableCmd);
                            --radn;
                        }
                        upqnhdbnccordec[radnum] = 0;
                    }
                }

                if (testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                    XPLMSetDatai(Rad3UpperXpdrBaroStdRemapableData, 1);
                }
            }

            upxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
            upxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
            upbarosetf[radnum] = XPLMGetDataf(BaroSetting);
            if (metricpressenable == 0) {
                upbarosetf[radnum] = upbarosetf[radnum] * 100.0;
                XPLMSetDatai(MetricPress, 0);
            }
            if (metricpressenable == 1) {
                upbarosetf[radnum] = upbarosetf[radnum] * 33.8639;
                XPLMSetDatai(MetricPress, 1);
            }
            upbaroset[radnum] = (int)upbarosetf[radnum];


        } else {
            if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                upseldis[radnum] = 10;
            } else {
               upseldis[radnum] = 9;
            }


            // ****** Function button is not pushed  *******
            if (xpanelsfnbutton == 0) {
                if (upxpdrsel[radnum] == 1) {
                    if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                        upxpdrdbncfninc[radnum]++;
                        if (upxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrOnesUp);
                            upxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                    if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                        upxpdrdbncfndec[radnum]++;
                        if (upxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrOnesDn);
                            upxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

                } else if (upxpdrsel[radnum] == 2) {
                    if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                        upxpdrdbncfninc[radnum]++;
                        if (upxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrTensUp);
                            upxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                    if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                        upxpdrdbncfndec[radnum]++;
                        if (upxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrTensDn);
                            upxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

                } else if (upxpdrsel[radnum] == 3) {
                    if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                        upxpdrdbncfninc[radnum]++;
                        if (upxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrHunUp);
                            upxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                    if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                        upxpdrdbncfndec[radnum]++;
                        if (upxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrHunDn);
                            upxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

                } else if (upxpdrsel[radnum] == 4) {
                    if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                        upxpdrdbncfninc[radnum]++;
                        if (upxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrThUp);
                            upxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                    if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                        upxpdrdbncfndec[radnum]++;
                        if (upxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrThDn);
                            upxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);
                }

                // Use the Coarse knob to select digit in the up direction
                if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                    upxpdrdbnccorinc[radnum]++;
                    if (upxpdrdbnccorinc[radnum] > radspeed) {
                        upxpdrsel[radnum] ++;
                        upxpdrdbnccorinc[radnum] = 0;
                    }
                    if (upxpdrsel[radnum] == 5) {
                        upxpdrsel[radnum] = 1;
                    }
                }
                Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

                // Use the Coarse knob to select digit in the down direction
                if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                    upxpdrdbnccordec[radnum]++;
                    if (upxpdrdbnccordec[radnum] > radspeed) {
                        upxpdrsel[radnum] --;
                        upxpdrdbnccordec[radnum] = 0;
                    }
                    if (upxpdrsel[radnum] == 0) {
                        upxpdrsel[radnum] = 4;
                    }
                }
                Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);


                // Use the ACT/STBY button to select XPDR mode
                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 0) {
                        if(testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(XpdrMode, 1);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 0;
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 1) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 0) {
                                XPLMSetDatai(XpdrMode, 2);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 1;
                            }
                            if (uplastxpdrpos == 2) {
                                XPLMSetDatai(XpdrMode, 0);
                                upxpdrpushed = 1;
                            }
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 2) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            if (uplastxpdrpos == 1) {
                                XPLMSetDatai(XpdrMode, 3);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                            if (uplastxpdrpos == 3) {
                                XPLMSetDatai(XpdrMode, 1);
                                upxpdrpushed = 1;
                                uplastxpdrpos = 2;
                            }
                        }
                    }
                }

                if (upxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 3) {
                        if (testbit(radiobuf[radnum], UPPER_ACT_STBY)) {
                            XPLMSetDatai(XpdrMode, 2);
                            upxpdrpushed = 1;
                            uplastxpdrpos = 3;
                        }
                    }
                }

                // if upxpdrloop is to low mode switch will not stop in position
                // if upxpdrloop is to high mode switch sometimes will not move
                // ToDo Need to find a better way
                if (upxpdrpushed == 1) {
                    upxpdrloop++;
                    if (upxpdrloop == 25) {
                        upxpdrpushed = 0;
                        upxpdrloop = 0;
                    }

                }

            }

            // ****** Function button is pushed ******
            if (xpanelsfnbutton == 1) {
                if ((Last_Upper_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_UP) == 0)) {
                    upqnhdbncfninc[radnum]++;
                    if (upqnhdbncfninc[radnum] > radspeed) {
                        XPLMCommandOnce(BaroUp);
                        upqnhdbncfninc[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Up[radnum] = testbit(radiobuf[radnum],UPPER_FINE_UP);

                if ((Last_Upper_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_FINE_DN) == 0)) {
                    upqnhdbncfndec[radnum]++;
                    if (upqnhdbncfndec[radnum] > radspeed) {
                        XPLMCommandOnce(BaroDn);
                        upqnhdbncfndec[radnum] = 0;
                    }
                }
                Last_Upper_Fine_Dn[radnum] = testbit(radiobuf[radnum],UPPER_FINE_DN);

                if ((Last_Upper_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_UP) == 0)) {
                    upqnhdbnccorinc[radnum]++;
                    if (upqnhdbnccorinc[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(BaroUp);
                            --radn;
                        }
                        upqnhdbnccorinc[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Up[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_UP);

                if ((Last_Upper_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],UPPER_COARSE_DN) == 0)) {
                    upqnhdbnccordec[radnum]++;
                    if (upqnhdbnccordec[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(BaroDn);
                            --radn;
                        }
                        upqnhdbnccordec[radnum] = 0;
                    }
                }
                Last_Upper_Coarse_Dn[radnum] = testbit(radiobuf[radnum],UPPER_COARSE_DN);

                if (testbit(radiobuf[radnum],UPPER_ACT_STBY)) {
                    XPLMCommandOnce(Rad1UpperXpdrBaroStdRemapableData);
                }

            }

            upxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
            upxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
            upbarosetf[radnum] = XPLMGetDataf(BaroSetting);
            if (metricpressenable == 0) {
                upbarosetf[radnum] = upbarosetf[radnum] * 100.0;
                XPLMSetDatai(MetricPress, 0);
            }

            if (metricpressenable == 1) {
                upbarosetf[radnum] = upbarosetf[radnum] * 33.8639;
                XPLMSetDatai(MetricPress, 1);
            }
            upbaroset[radnum] = (int)upbarosetf[radnum];
        }
    }
}


// ***************** Create Datareferences for lower Switches ************
void process_lower_datareferences()
{
    if(testbit(radiobuf[radnum],LOWER_COM1)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCom1OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCom1OwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCom1OwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCom1OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCom1OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCom1OwnedDataRef, 0);
        }
    }

    if(testbit(radiobuf[radnum],LOWER_COM2)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCom2OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCom2OwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCom2OwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCom2OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCom2OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCom2OwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_NAV1)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerNav1OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerNav1OwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerNav1OwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerNav1OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerNav1OwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerNav1OwnedDataRef, 0);
        }
    }

    if(testbit(radiobuf[radnum],LOWER_NAV2)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerNav2OwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerNav2OwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerNav2OwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerNav2OwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_ADF)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerAdfOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerAdfOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerAdfOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerAdfOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerAdfOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerAdfOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_DME)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerDmeOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerDmeOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerDmeOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerDmeOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerDmeOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerDmeOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_XPDR)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerXpdrOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerXpdrOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerXpdrOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerXpdrOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerXpdrOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerXpdrOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_COARSE_UP)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCorseIncOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCorseIncOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCorseIncOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCorseIncOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCorseIncOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCorseIncOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_COARSE_DN)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCorseDecOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCorseDecOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCorseDecOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerCorseDecOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerCorseDecOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerCorseDecOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_FINE_UP)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerFineIncOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerFineIncOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerFineIncOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerFineIncOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerFineIncOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerFineIncOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_FINE_DN)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerFineDecOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerFineDecOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerFineDecOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerFineDecOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerFineDecOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerFineDecOwnedDataRef, 0);
        }
    }


    if(testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerActStbyOwnedDataRef, 1);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerActStbyOwnedDataRef, 1);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerActStbyOwnedDataRef, 1);
        }
    } else {
        if (radnum == 0) {
            XPLMSetDatai(Rad1LowerActStbyOwnedDataRef, 0);
        } else if (radnum == 1) {
            XPLMSetDatai(Rad2LowerActStbyOwnedDataRef, 0);
        } else if (radnum == 2) {
            XPLMSetDatai(Rad3LowerActStbyOwnedDataRef, 0);
        }
    }

}




// ***************** Lower COM1 Switch Position *******************
void process_lower_com1_switch()
{
    if (testbit(radiobuf[radnum],LOWER_COM1)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            loseldis[radnum] = 10;
        } else {
           loseldis[radnum] = 1;
        }

        if (radiores > 0) {
            if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                locom1dbncfninc[radnum]++;
                if (locom1dbncfninc[radnum] > radspeed) {
                    if ((rad1lwrcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom1FnUpRemapableCmd);
                    } else if ((rad2lwrcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom1FnUpRemapableCmd);
                    } else if ((rad3lwrcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom1FnUpRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com1StbyFineUp);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com1StbyFineUp_833);
                        }
                    }
                    locom1dbncfninc[radnum] = 0;
                }
            }
            Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


            if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                locom1dbncfndec[radnum]++;
                if (locom1dbncfndec[radnum] > radspeed) {
                    if ((rad1lwrcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom1FnDnRemapableCmd);
                    } else if ((rad2lwrcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom1FnDnRemapableCmd);
                    } else if ((rad3lwrcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom1FnDnRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com1StbyFineDn);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com1StbyFineDn_833);
                        }
                    }
                    locom1dbncfndec[radnum] = 0;
                }
            }
            Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);

            if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                locom1dbnccorinc[radnum]++;
                if (locom1dbnccorinc[radnum] > radspeed) {
                    if ((rad1lwrcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom1CrsUpRemapableCmd);
                    } else if ((rad2lwrcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom1CrsUpRemapableCmd);
                    } else if ((rad3lwrcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom1CrsUpRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com1StbyCorseUp);
                    }
                    locom1dbnccorinc[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);

            if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                locom1dbnccordec[radnum]++;
                if (locom1dbnccordec[radnum] > radspeed) {
                    if ((rad1lwrcom1switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom1CrsDnRemapableCmd);
                    } else if ((rad2lwrcom1switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom1CrsDnRemapableCmd);
                    } else if ((rad3lwrcom1switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom1CrsDnRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com1StbyCorseDn);
                    }
                    locom1dbnccordec[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);


            if (radnum == 0) {
                if (rad1lwrcom1actstbybtnremap == 2) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad1LowrCom1ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad1LowrCom1ActStbyRemapableData, 0);
                    }

                } else if (rad1lwrcom1actstbybtnremap == 1) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Rad1LowrCom1ActStbyRemapableCmd);
                    }
                } else {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Com1ActStby);
                    }
                }

            } else if (radnum == 1) {
                if (rad2lwrcom1actstbybtnremap == 2) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad2LowrCom1ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad2LowrCom1ActStbyRemapableData, 0);
                    }
                } else if (rad2lwrcom1actstbybtnremap == 1) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Rad2LowrCom1ActStbyRemapableCmd);
                    }
                } else {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Com1ActStby);
                    }
                }
            } else if (radnum == 2) {
                if (rad3lwrcom1actstbybtnremap == 2) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad3LowrCom1ActStbyRemapableData, 1);
                    } else if (!testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad3LowrCom1ActStbyRemapableData, 0);
                    }
                } else if (rad3lwrcom1actstbybtnremap == 1) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Rad3LowrCom1ActStbyRemapableCmd);
                    }
                } else {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Com1ActStby);
                    }
                }
            }
        }

        if ((rad1lwrcom1switchremap == 1) && (radnum == 0)) {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad1LowerCom1ActRemapableData);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Rad1LowerCom1StbyRemapableData);
                lostbycomfreq[radnum] = lostbycomfreq[radnum]  * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad1LowerCom1ActRemapableData);
                lostbycomfreq[radnum] = XPLMGetDatai(Rad1LowerCom1StbyRemapableData);
            }

        } else if ((rad2lwrcom1switchremap == 1) && (radnum == 1)) {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad2LowerCom1ActRemapableData);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Rad2LowerCom1StbyRemapableData);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad2LowerCom1ActRemapableData);
                lostbycomfreq[radnum] = XPLMGetDatai(Rad2LowerCom1StbyRemapableData);
            }


        } else if ((rad3lwrcom1switchremap == 1) && (radnum == 2)) {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad3LowerCom1ActRemapableData);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Rad3LowerCom1StbyRemapableData);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad3LowerCom1ActRemapableData);
                lostbycomfreq[radnum] = XPLMGetDatai(Rad3LowerCom1StbyRemapableData);
            }

        } else {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Com1ActFreq);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Com1StbyFreq);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Com1ActFreq_833);
                lostbycomfreq[radnum] = XPLMGetDatai(Com1StbyFreq_833);
            }
        }
        locom1[radnum] = 1;
    }
}

// ***************** Lower COM2 Switch Position *******************
void process_lower_com2_switch()
{
    if (testbit(radiobuf[radnum],LOWER_COM2)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            loseldis[radnum] = 10;
        } else {
            loseldis[radnum] = 2;
        }

        if (radiores > 0) {
            if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                locom2dbncfninc[radnum]++;
                if (locom2dbncfninc[radnum] > radspeed) {
                    if ((rad1lwrcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom2FnUpRemapableCmd);
                    } else if ((rad2lwrcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom2FnUpRemapableCmd);
                    } else if ((rad3lwrcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom2FnUpRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com2StbyFineUp);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com2StbyFineUp_833);
                        }
                    }
                    locom2dbncfninc[radnum] = 0;
                }
            }
            Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


            if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                locom2dbncfndec[radnum]++;
                if (locom2dbncfndec[radnum] > radspeed) {
                    if ((rad1lwrcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom2FnDnRemapableCmd);
                    } else if ((rad2lwrcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom2FnDnRemapableCmd);
                    } else if ((rad3lwrcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom2FnDnRemapableCmd);
                    } else {
                        if (channelspacing833enable == 0) {
                            XPLMCommandOnce(Com2StbyFineDn);
                        } else if (channelspacing833enable == 1) {
                            XPLMCommandOnce(Com2StbyFineDn_833);
                        }
                    }
                    locom2dbncfndec[radnum] = 0;
                }
            }
            Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);

            if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                locom2dbnccorinc[radnum]++;
                if (locom2dbnccorinc[radnum] > radspeed) {
                    if ((rad1lwrcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom2CrsUpRemapableCmd);
                    } else if ((rad2lwrcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom2CrsUpRemapableCmd);
                    } else if ((rad3lwrcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom2CrsUpRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com2StbyCorseUp);
                    }
                    locom2dbnccorinc[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


            if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                locom2dbnccordec[radnum]++;
                if (locom2dbnccordec[radnum] > radspeed) {
                    if ((rad1lwrcom2switchremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrCom2CrsDnRemapableCmd);
                    } else if ((rad2lwrcom2switchremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrCom2CrsDnRemapableCmd);
                    } else if ((rad3lwrcom2switchremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrCom2CrsDnRemapableCmd);
                    } else {
                        XPLMCommandOnce(Com2StbyCorseDn);
                    }
                    locom2dbnccordec[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

            if (radnum == 0) {
                if (rad1lwrcom2actstbybtnremap == 2) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad1LowrCom2ActStbyRemapableData, 1);
                    } else if(!testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad1LowrCom2ActStbyRemapableData, 0);
                    }
                } else if (rad1lwrcom2actstbybtnremap == 1) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Rad1LowrCom2ActStbyRemapableCmd);
                    }
                } else {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Com2ActStby);
                    }
                }

            } else if (radnum == 1) {
                if (rad2lwrcom2actstbybtnremap == 2) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad2LowrCom2ActStbyRemapableData, 1);
                    } else if (!testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad2LowrCom2ActStbyRemapableData, 0);
                    }
                } else if (rad2lwrcom2actstbybtnremap == 1) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Rad2LowrCom2ActStbyRemapableCmd);
                    }
                } else {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Com2ActStby);
                    }
                }

            } else if (radnum == 2) {
                if (rad3lwrcom2actstbybtnremap == 2) {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad3LowrCom2ActStbyRemapableData, 1);
                    } else if (!testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMSetDatai(Rad3LowrCom2ActStbyRemapableData, 0);
                    }
                } else if (rad3lwrcom2actstbybtnremap == 1) {
                    if(testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Rad3LowrCom2ActStbyRemapableCmd);
                    }
                } else {
                    if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                        XPLMCommandOnce(Com2ActStby);
                    }
                }
            }
        }

        if ((rad1lwrcom2switchremap == 1) && (radnum == 0)) {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad1LowerCom2ActRemapableData);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Rad1LowerCom2StbyRemapableData);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad1LowerCom2ActRemapableData);
                lostbycomfreq[radnum] = XPLMGetDatai(Rad1LowerCom2StbyRemapableData);
            }

        } else if ((rad2lwrcom2switchremap == 1) && (radnum == 1)) {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad2LowerCom2ActRemapableData);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Rad2LowerCom2StbyRemapableData);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad2LowerCom2ActRemapableData);
                lostbycomfreq[radnum] = XPLMGetDatai(Rad2LowerCom2StbyRemapableData);
            }

        } else if ((rad3lwrcom2switchremap == 1) && (radnum == 2)) {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad3LowerCom2ActRemapableData);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Rad3LowerCom2StbyRemapableData);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Rad3LowerCom2ActRemapableData);
                lostbycomfreq[radnum] = XPLMGetDatai(Rad3LowerCom2StbyRemapableData);
            }

        } else {
            if (channelspacing833enable == 0) {
                loactcomfreq[radnum] = XPLMGetDatai(Com2ActFreq);
                loactcomfreq[radnum] = loactcomfreq[radnum] * 10;
                lostbycomfreq[radnum] = XPLMGetDatai(Com2StbyFreq);
                lostbycomfreq[radnum] = lostbycomfreq[radnum] * 10;
            } else if (channelspacing833enable == 1) {
                loactcomfreq[radnum] = XPLMGetDatai(Com2ActFreq_833);
                lostbycomfreq[radnum] = XPLMGetDatai(Com2StbyFreq_833);
            }

        }
        locom2[radnum] = 1;
    }
}

// ***************** Lower NAV1 Switch Position *******************
void process_lower_nav1_switch()
{
    if (testbit(radiobuf[radnum],LOWER_NAV1)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            loseldis[radnum] = 10;
        } else {
           loseldis[radnum] = 3;
        }

        if (radiores > 0) {
            if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                lonav1dbncfninc[radnum]++;
                if (lonav1dbncfninc[radnum] > radspeed) {
                    if (xpanelsfnbutton == 1) {
                        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrObs1FnUpRemapableCmd);
                        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrObs1FnUpRemapableCmd);
                        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrObs1FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs1Up);
                        }
                    } else {
                        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav1FnUpRemapableCmd);
                        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav1FnUpRemapableCmd);
                        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav1FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyFineUp);
                        }
                    }
                    lonav1dbncfninc[radnum] = 0;
                }
            }
            Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


            if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                lonav1dbncfndec[radnum]++;
                if (lonav1dbncfndec[radnum] > radspeed) {
                    if (xpanelsfnbutton == 1) {
                        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrObs1FnDnRemapableCmd);
                        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrObs1FnDnRemapableCmd);
                        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrObs1FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs1Down);
                        }
                    } else {
                        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav1FnDnRemapableCmd);
                        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav1FnDnRemapableCmd);
                        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav1FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyFineDn);
                        }
                    }
                    lonav1dbncfndec[radnum] = 0;
                }
            }
            Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);


            if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                lonav1dbnccorinc[radnum]++;
                if (lonav1dbnccorinc[radnum] > radspeed) {
                    radn = 10;
                    if (xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrObs1CrsUpRemapableCmd);
                            } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrObs1CrsUpRemapableCmd);
                            } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrObs1CrsUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs1Up);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav1CrsUpRemapableCmd);
                        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav1CrsUpRemapableCmd);
                        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav1CrsUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyCorseUp);
                        }
                    }
                    lonav1dbnccorinc[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


            if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                lonav1dbnccordec[radnum]++;
                if (lonav1dbnccordec[radnum] > radspeed) {
                    radn = 10;
                    if (xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrObs1CrsDnRemapableCmd);
                            } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrObs1CrsDnRemapableCmd);
                            } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrObs1CrsDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs1Down);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav1CrsDnRemapableCmd);
                        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav1CrsDnRemapableCmd);
                        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav1CrsDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav1StbyCorseDn);
                        }
                    }
                    lonav1dbnccordec[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

            if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                if ((rad1lwrnav1actstbybtnremap == 1) && (radnum == 0)) {
                    XPLMCommandOnce(Rad1LowrNav1ActStbyRemapableCmd);
                } else if ((rad2lwrnav1actstbybtnremap == 1) && (radnum == 1)) {
                    XPLMCommandOnce(Rad2LowrNav1ActStbyRemapableCmd);
                } else if ((rad3lwrnav1actstbybtnremap == 1) && (radnum == 2)) {
                    XPLMCommandOnce(Rad3LowrNav1ActStbyRemapableCmd);
                } else {
                    XPLMCommandOnce(Nav1ActStby);
                }
            }
        }

        if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
            loactnavfreq[radnum] = XPLMGetDatai(Rad1LowerNav1ActRemapableData);
            lostbynavfreq[radnum] = XPLMGetDatai(Rad1LowerNav1StbyRemapableData);
        } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
            loactnavfreq[radnum] = XPLMGetDatai(Rad2LowerNav1ActRemapableData);
            lostbynavfreq[radnum] = XPLMGetDatai(Rad2LowerNav1StbyRemapableData);
        } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
            loactnavfreq[radnum] = XPLMGetDatai(Rad3LowerNav1ActRemapableData);
            lostbynavfreq[radnum] = XPLMGetDatai(Rad3LowerNav1StbyRemapableData);
        } else {
            loactnavfreq[radnum] = XPLMGetDatai(Nav1ActFreq);
            lostbynavfreq[radnum] = XPLMGetDatai(Nav1StbyFreq);
        }
        lonav1[radnum] = 0;
    }
}

// ***************** Lower NAV2 Switch Position *******************
void process_lower_nav2_switch()
{
    if (testbit(radiobuf[radnum],LOWER_NAV2)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            loseldis[radnum] = 10;
        } else {
            loseldis[radnum] = 4;
        }

        if (radiores > 0) {
            if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                lonav2dbncfninc[radnum]++;
                if (lonav2dbncfninc[radnum] > radspeed) {
                    if (xpanelsfnbutton == 1) {
                        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrObs2FnUpRemapableCmd);
                        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrObs2FnUpRemapableCmd);
                        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrObs2FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs2Up);
                        }
                    } else {
                        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav2FnUpRemapableCmd);
                        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav2FnUpRemapableCmd);
                        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav2FnUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyFineUp);
                        }
                    }
                    lonav2dbncfninc[radnum] = 0;
                }
            }
            Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


            if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                lonav2dbncfndec[radnum]++;
                if (lonav2dbncfndec[radnum] > radspeed) {
                    if (xpanelsfnbutton == 1) {
                        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrObs2FnDnRemapableCmd);
                        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrObs2FnDnRemapableCmd);
                        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrObs2FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Obs2Down);
                        }
                    } else {
                        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav2FnDnRemapableCmd);
                        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav2FnDnRemapableCmd);
                        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav2FnDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyFineDn);
                        }
                    }
                    lonav2dbncfndec[radnum] = 0;
                }
            }
            Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);


            if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                lonav2dbnccorinc[radnum]++;
                if (lonav2dbnccorinc[radnum] > radspeed) {
                    radn = 10;
                    if (xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrObs2CrsUpRemapableCmd);
                            } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrObs2CrsUpRemapableCmd);
                            } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrObs2CrsUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs2Up);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav2CrsUpRemapableCmd);
                        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav2CrsUpRemapableCmd);
                        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav2CrsUpRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyCorseUp);
                        }
                    }
                    lonav2dbnccorinc[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


            if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                lonav2dbnccordec[radnum]++;
                if (lonav2dbnccordec[radnum] > radspeed) {
                    radn = 10;
                    if (xpanelsfnbutton == 1) {
                        while (radn > 0) {
                            if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrObs2CrsDnRemapableCmd);
                            } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrObs2CrsDnRemapableCmd);
                            } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrObs2CrsDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Obs2Down);
                            }
                            --radn;
                        }
                    } else {
                        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrNav2CrsDnRemapableCmd);
                        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrNav2CrsDnRemapableCmd);
                        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrNav2CrsDnRemapableCmd);
                        } else {
                            XPLMCommandOnce(Nav2StbyCorseDn);
                        }
                    }
                    lonav2dbnccordec[radnum] = 0;
                }
            }
            Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);


            if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                if ((rad1lwrnav2actstbybtnremap == 1) && (radnum == 0)) {
                    XPLMCommandOnce(Rad1LowrNav2ActStbyRemapableCmd);
                } else if ((rad2lwrnav2actstbybtnremap == 1) && (radnum == 1)) {
                    XPLMCommandOnce(Rad2LowrNav2ActStbyRemapableCmd);
                } else if ((rad3lwrnav2actstbybtnremap == 1) && (radnum == 2)) {
                    XPLMCommandOnce(Rad3LowrNav2ActStbyRemapableCmd);
                } else {
                    XPLMCommandOnce(Nav2ActStby);
                }

            }
        }

        if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
            loactnavfreq[radnum] = XPLMGetDatai(Rad1LowerNav2ActRemapableData);
            lostbynavfreq[radnum] = XPLMGetDatai(Rad1LowerNav2StbyRemapableData);
        } else if ((rad2lwrnav2switchremap == 1) && (radnum == 1)) {
            loactnavfreq[radnum] = XPLMGetDatai(Rad2LowerNav2ActRemapableData);
            lostbynavfreq[radnum] = XPLMGetDatai(Rad2LowerNav2StbyRemapableData);
        } else if ((rad3lwrnav2switchremap == 1) && (radnum == 2)) {
            loactnavfreq[radnum] = XPLMGetDatai(Rad3LowerNav2ActRemapableData);
            lostbynavfreq[radnum] = XPLMGetDatai(Rad3LowerNav2StbyRemapableData);
        } else {
            loactnavfreq[radnum] = XPLMGetDatai(Nav2ActFreq);
            lostbynavfreq[radnum] = XPLMGetDatai(Nav2StbyFreq);
        }
        lonav2[radnum] = 0;
    }
}

// ***************** Lower ADF Switch Position *******************
void process_lower_adf_switch()
{
    if (testbit(radiobuf[radnum],LOWER_ADF)) {
        if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
            loseldis[radnum] = 10;
        } else {
           loseldis[radnum] = 5;
        }

        LoAdf1CardDirDegm[radnum] = XPLMGetDataf(Adf1CardDirDegm);
        lostbyadf1dir[radnum] = (int)(LoAdf1CardDirDegm[radnum]);

        LoAdf2CardDirDegm[radnum] = XPLMGetDataf(Adf2CardDirDegm);
        lostbyadf2dir[radnum] = (int)(LoAdf2CardDirDegm[radnum]);

        if (numadf == 1) {
            if (xpanelsfnbutton == 1) {
                if ((rad1lwradfswitchremap == 1) || (rad2lwradfswitchremap == 1) || (rad3lwradfswitchremap == 1)) {
                    loactadffreq[radnum] = XPLMGetDatai(Adf1ActFreq);
                    lostbyadffreq[radnum] = XPLMGetDatai(Adf1StbyFreq);
                    return;
                }
                if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                    loadfdbdirfninc[radnum]++;
                    if (loadfdbdirfninc[radnum] > radspeed) {
                        lostbyadf1dir[radnum] = lostbyadf1dir[radnum] + 1;
                        loadfdbdirfninc[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                    loadfdbdirfndec[radnum]++;
                    if (loadfdbdirfndec[radnum] > radspeed) {
                        lostbyadf1dir[radnum] = lostbyadf1dir[radnum] - 1;
                        loadfdbdirfndec[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);

                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loadfdbdircorinc[radnum]++;
                    if (loadfdbdircorinc[radnum] > radspeed) {
                        lostbyadf1dir[radnum] = lostbyadf1dir[radnum] + 10;
                        loadfdbdircorinc[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);

                if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    loadfdbdircordec[radnum]++;
                    if (loadfdbdircordec[radnum] > radspeed) {
                        lostbyadf1dir[radnum] = lostbyadf1dir[radnum] - 10;
                        loadfdbdircordec[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);


                if (lostbyadf1dir[radnum] > 360) {
                    lostbyadf1dir[radnum] = 1;
                }

                if (lostbyadf1dir[radnum] < 0) {
                lostbyadf1dir[radnum] = 360;
                }

                lostbyadf1dirf[radnum] = lostbyadf1dir[radnum];
                XPLMSetDataf(Adf1CardDirDegm, (float)lostbyadf1dirf[radnum]);

            }


            if (xpanelsfnbutton == 0) {
                if (loadfsel[radnum] == 1) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loadfdbncfninc[radnum]++;
                        if (loadfdbncfninc[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnUpRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnUpRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd1StbyOnesUp);
                            }
                            loadfdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loadfdbncfndec[radnum]++;
                        if (loadfdbncfndec[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnDnRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnDnRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd1StbyOnesDn);
                            }
                            loadfdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }


                if (loadfsel[radnum] == 2) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loadfdbncfninc[radnum]++;
                        if (loadfdbncfninc[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnUpRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnUpRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd1StbyTensUp);
                            }
                            loadfdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loadfdbncfndec[radnum]++;
                        if (loadfdbncfndec[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnDnRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnDnRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd1StbyTensDn);
                            }
                            loadfdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }


                if (loadfsel[radnum] == 3) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loadfdbncfninc[radnum]++;
                        if (loadfdbncfninc[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnUpRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnUpRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd1StbyHunUp);
                            }
                            loadfdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loadfdbncfndec[radnum]++;
                        if (loadfdbncfndec[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnDnRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnDnRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd1StbyHunDn);
                            }
                            loadfdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }


                // Use the Coarse knob to select digit in the up direction
                if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    loadfdbnccorinc[radnum] ++;
                    if(loadfdbnccorinc[radnum] == 3) {
                        if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrAdfCrsUpRemapableCmd);
                        } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrAdfCrsUpRemapableCmd);
                        } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrAdfCrsUpRemapableCmd);
                        } else {
                            loadfsel[radnum] ++;
                            loadfdbnccorinc[radnum] = 0;
                            if (loadfsel[radnum] == 4) {
                                loadfsel[radnum] = 1;
                            }
                        }
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

                // Use the Coarse knob to select digit in the down direction
                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loadfdbnccordec[radnum] ++;
                    if (loadfdbnccordec[radnum] == 3) {
                        if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrAdfCrsDnRemapableCmd);
                        } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrAdfCrsDnRemapableCmd);
                        } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrAdfCrsDnRemapableCmd);
                        } else {
                            loadfsel[radnum] --;
                            loadfdbnccordec[radnum] = 0;
                            if (loadfsel[radnum] == 0) {
                                loadfsel[radnum] = 3;
                            }
                        }
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);

                if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                    if ((rad1lwradfactstbybtnremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrAdfActStbyRemapableCmd);
                    } else if ((rad2lwradfactstbybtnremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrAdfActStbyRemapableCmd);
                    } else if ((rad3lwradfactstbybtnremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrAdfActStbyRemapableCmd);
                    } else {
                        XPLMCommandOnce(Adf1ActStby);
                    }
                 }
            }

            loactadffreq[radnum] = XPLMGetDatai(Adf1ActFreq);
            lostbyadffreq[radnum] = XPLMGetDatai(Adf1StbyFreq);

        }

        // Second ADF on the lower position
        if (numadf == 2) {
            if (xpanelsfnbutton == 1) {
                if ((rad1lwradfswitchremap == 1) || (rad2lwradfswitchremap == 1) || (rad3lwradfswitchremap == 1)) {
                    loactadffreq[radnum] = XPLMGetDatai(Adf2ActFreq);
                    lostbyadffreq[radnum] = XPLMGetDatai(Adf2StbyFreq);
                    return;
                }
                if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                    loadfdbdirfninc[radnum]++;
                    if (loadfdbdirfninc[radnum] > radspeed) {
                        lostbyadf2dir[radnum] = lostbyadf2dir[radnum] + 1;
                        loadfdbdirfninc[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                    loadfdbdirfndec[radnum]++;
                    if (loadfdbdirfndec[radnum] > radspeed) {
                        lostbyadf2dir[radnum] = lostbyadf2dir[radnum] - 1;
                        loadfdbdirfndec[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);

                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loadfdbdircorinc[radnum]++;
                    if (loadfdbdircorinc[radnum] > radspeed) {
                        lostbyadf2dir[radnum] = lostbyadf2dir[radnum] + 10;
                        loadfdbdircorinc[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


                if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    loadfdbdircordec[radnum]++;
                    if (loadfdbdircordec[radnum] > radspeed) {
                        lostbyadf2dir[radnum] = lostbyadf2dir[radnum] - 10;
                        loadfdbdircordec[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

                if (lostbyadf2dir[radnum] > 360) {
                    lostbyadf2dir[radnum] = 1;
                }

                if (lostbyadf2dir[radnum] < 0) {
                    lostbyadf2dir[radnum] = 360;
                }

                lostbyadf2dirf[radnum] = lostbyadf2dir[radnum];
                XPLMSetDataf(Adf2CardDirDegm, (float)lostbyadf2dirf[radnum]);
            }

            if (xpanelsfnbutton == 0) {
                if (loadfsel[radnum] == 1) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loadfdbncfninc[radnum]++;
                        if (loadfdbncfninc[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnUpRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnUpRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd2StbyOnesUp);
                            }
                            loadfdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loadfdbncfndec[radnum]++;
                        if (loadfdbncfndec[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnDnRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnDnRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd2StbyOnesDn);
                            }


                            loadfdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }

                if (loadfsel[radnum] == 2) {
                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loadfdbncfninc[radnum]++;
                        if (loadfdbncfninc[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnUpRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnUpRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd2StbyTensUp);
                            }
                            loadfdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loadfdbncfndec[radnum]++;
                        if (loadfdbncfndec[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnDnRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnDnRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd2StbyTensDn);
                            }
                            loadfdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }

                if (loadfsel[radnum] == 3) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loadfdbncfninc[radnum]++;
                        if (loadfdbncfninc[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnUpRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnUpRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnUpRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd2StbyHunUp);
                            }
                            loadfdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loadfdbncfndec[radnum]++;
                        if (loadfdbncfndec[radnum] > radspeed) {
                            if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                                XPLMCommandOnce(Rad1LowrAdfFnDnRemapableCmd);
                            } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                                XPLMCommandOnce(Rad2LowrAdfFnDnRemapableCmd);
                            } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                                XPLMCommandOnce(Rad3LowrAdfFnDnRemapableCmd);
                            } else {
                                XPLMCommandOnce(Afd2StbyHunDn);
                            }
                            loadfdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }

                // Use the Coarse knob to select digit in the up direction
                if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    loadfdbnccorinc[radnum] ++;
                    if(loadfdbnccorinc[radnum] > radspeed) {
                        if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrAdfCrsUpRemapableCmd);
                        } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrAdfCrsUpRemapableCmd);
                        } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrAdfCrsUpRemapableCmd);
                        } else {
                            loadfsel[radnum] ++;
                            loadfdbnccorinc[radnum] = 0;
                            if (loadfsel[radnum] == 4) {
                                loadfsel[radnum] = 1;
                            }
                        }
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

                // Use the Coarse knob to select digit in the down direction
                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loadfdbnccordec[radnum] ++;
                    if (loadfdbnccordec[radnum] > radspeed) {
                        if ((rad1lwradfswitchremap == 1) && (radnum == 0)) {
                            XPLMCommandOnce(Rad1LowrAdfCrsDnRemapableCmd);
                        } else if ((rad2lwradfswitchremap == 1) && (radnum == 1)) {
                            XPLMCommandOnce(Rad2LowrAdfCrsDnRemapableCmd);
                        } else if ((rad3lwradfswitchremap == 1) && (radnum == 2)) {
                            XPLMCommandOnce(Rad3LowrAdfCrsDnRemapableCmd);
                        } else {
                            loadfsel[radnum] --;
                            loadfdbnccordec[radnum] = 0;
                            if (loadfsel[radnum] == 0) {
                                loadfsel[radnum] = 3;
                            }
                        }
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);

                if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                    if ((rad1lwradfactstbybtnremap == 1) && (radnum == 0)) {
                        XPLMCommandOnce(Rad1LowrAdfActStbyRemapableCmd);
                    } else if ((rad2lwradfactstbybtnremap == 1) && (radnum == 1)) {
                        XPLMCommandOnce(Rad2LowrAdfActStbyRemapableCmd);
                    } else if ((rad3lwradfactstbybtnremap == 1) && (radnum == 2)) {
                        XPLMCommandOnce(Rad3LowrAdfActStbyRemapableCmd);
                    } else {
                        XPLMCommandOnce(Adf2ActStby);
                    }
                }
            }
            loactadffreq[radnum] = XPLMGetDatai(Adf2ActFreq);
            lostbyadffreq[radnum] = XPLMGetDatai(Adf2StbyFreq);
        }
    }
}

// ***************** Lower DME Switch Position *******************
void process_lower_dme_switch()
{
    if (testbit(radiobuf[radnum],LOWER_DME)) {
        // ****** Function button is not pushed  *******
        if (xpanelsfnbutton == 0) {
            if (lodmepushed == 0) {
                if (XPLMGetDatai(DmeMode) == 0) {
                    if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                        XPLMSetDatai(DmeMode, 1);
                        lodmepushed = 1;
                        lolastdmepos = 1;
                    }
                }
            }

            if (lodmepushed == 0) {
                if (XPLMGetDatai(DmeMode) == 1) {
                    if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                        XPLMSetDatai(DmeMode, 2);
                        lodmepushed = 1;
                        if (lolastdmepos == 2) {
                            XPLMSetDatai(DmeMode, 0);
                            lodmepushed = 1;
                        }
                    }
                }
            }

            if (lodmepushed == 0) {
                if (XPLMGetDatai(DmeMode) == 2) {
                    if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                        XPLMSetDatai(DmeMode, 1);
                        lodmepushed = 1;
                        lolastdmepos = 2;
                    }
                }
            }

            if (lodmepushed == 1) {
                lodmeloop++;
                if (lodmeloop == 50) {
                    lodmepushed = 0;
                    lodmeloop = 0;
                }
            }

            lodmemode[radnum] = XPLMGetDatai(DmeMode);
            lodmesource[radnum] = XPLMGetDatai(DmeSlvSource);
            if (lodmemode[radnum] == 0) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    loseldis[radnum] = 10;
                } else {
                    loseldis[radnum] = 6;
                }

                if (lodmesource[radnum] == 0) {
                    lodmenav1speedf[radnum] = XPLMGetDataf(Nav1DmeSpeed);
                    lodmenavspeed[radnum] = (int)(lodmenav1speedf[radnum]);
                    lodmedistf[radnum] = XPLMGetDataf(Nav1DmeNmDist);
                    lodmedist[radnum] = (int)(lodmedistf[radnum] * 10.0f);

                } else if (lodmesource[radnum] == 1) {
                    lodmenav2speedf[radnum] = XPLMGetDataf(Nav2DmeSpeed);
                    lodmenavspeed[radnum] = (int)(lodmenav2speedf[radnum]);
                    lodmedistf[radnum] = XPLMGetDataf(Nav2DmeNmDist);
                    lodmedist[radnum] = (int)(lodmedistf[radnum] * 10.0f);
                }
            }

            if (lodmemode[radnum] == 1) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    loseldis[radnum] = 10;
                } else {
                    loseldis[radnum] = 7;
                }
                lodmefreq[radnum] = XPLMGetDatai(DmeFreq);
                lodmefreqhnd = lodmefreq[radnum]/100;
                lodmefreqfrc = lodmefreq[radnum]%100;
                if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                    if (lodmefreqfrc == 95) {
                        lodmefreqfrc = 0;
                    }
                    lodmedbncfninc[radnum]++;
                    if (lodmedbncfninc[radnum] == 3) {
                        lodmefreqfrc = lodmefreqfrc + 5;
                        lodmedbncfninc[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                    if (lodmefreqfrc == 0) {
                        lodmefreqfrc = 95;
                    }
                    lodmedbncfndec[radnum]++;
                    if (lodmedbncfndec[radnum] == 3) {
                        lodmefreqfrc = lodmefreqfrc - 5;
                        lodmedbncfndec[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);


                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    if (lodmefreqhnd == 117) {
                        lodmefreqhnd = 108;
                    }
                    lodmedbncfninc[radnum]++;
                    if (lodmedbncfninc[radnum] == 3) {
                        lodmefreqhnd = lodmefreqhnd + 1;
                        lodmedbncfninc[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


                if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    if (lodmefreqhnd == 108) {
                        lodmefreqhnd = 117;
                    }
                    lodmedbncfndec[radnum]++;
                    if (lodmedbncfndec[radnum] == 3) {
                        lodmefreqhnd = lodmefreqhnd - 1;
                        lodmedbncfndec[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

                lodmefreq[radnum] = (lodmefreqhnd * 100) + lodmefreqfrc;
                XPLMSetDatai(DmeFreq, lodmefreq[radnum]);
                lodmetime[radnum] = XPLMGetDataf(DmeTime);
            }

            if (lodmemode[radnum] == 2) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    loseldis[radnum] = 10;
                } else {
                    loseldis[radnum] = 8;
                }
                lodmespeedf[radnum] = XPLMGetDataf(DmeSpeed);
                lodmespeed[radnum] = (int)(lodmespeedf[radnum]);
                lodmetime[radnum] = XPLMGetDataf(DmeTime);
            }
        }

        // ****** Function button is pushed  *******
        if (xpanelsfnbutton == 1) {
            if (lodmepushed == 0) {
                if (XPLMGetDatai(DmeSlvSource) == 0) {
                    if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                        XPLMSetDatai(DmeSlvSource, 1);
                        lodmepushed = 1;
                        lolastdmepos = 0;
                    }
                }
            }

            if (lodmepushed == 0) {
                if (XPLMGetDatai(DmeSlvSource) == 1) {
                    if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                        XPLMSetDatai(DmeSlvSource, 0);
                        lodmepushed = 1;
                    }
                }
            }

            if (lodmepushed == 1) {
                lodmeloop++;
                if (lodmeloop == 50) {
                    lodmepushed = 0;
                    lodmeloop = 0;
                }
            }
        }
    }
}

// ***************** Lower Transponder Switch Position *******************

void process_lower_xpdr_switch()
{
    if (testbit(radiobuf[radnum],LOWER_XPDR)) {
        if ((rad1lwrxpdrswitchremap == 777)  && (radnum == 0)) {
            if (xpanelsfnbutton == 0) {
                if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                    loseldis[radnum] = 10;
                } else {
                    loseldis[radnum] = 9;
                }
                rad1lwrxpdrlastdigitremap = 0;
                if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                    loxpdrdbncfninc[radnum]++;
                    if (loxpdrdbncfninc[radnum] > radspeed) {
                        rad1lwrxpdrdigitremap++;
                        loxpdrdbncfninc[radnum] = 0;
                        if (rad1lwrxpdrdigitremap > 7) {
                            rad1lwrxpdrdigitremap = 0;
                        }
                        rad1lwrxpdrlastdigitremap = 1;
                    }
                    rad1lwrxpdrlastdigitcnt = 0;
                }
                Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                    loxpdrdbncfninc[radnum]++;
                    if (loxpdrdbncfninc[radnum] > radspeed) {
                        rad1lwrxpdrdigitremap--;
                        loxpdrdbncfninc[radnum] = 0;
                        if (rad1lwrxpdrdigitremap < 0) {
                            rad1lwrxpdrdigitremap = 7;
                        }
                        rad1lwrxpdrlastdigitremap = 1;
                    }
                    rad1lwrxpdrlastdigitcnt = 0;
                }
                Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);

                if (rad1lwrxpdrlastdigitremap == 0) {
                    if (rad1lwrxpdrlastdigitcnt < 25) {
                        rad1lwrxpdrlastdigitcnt++;
                    }

                }

                if (rad1lwrxpdrlastdigitcnt < 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        loseldis[radnum] = 10;
                    } else {
                        loseldis[radnum] = 11;
                    }
                }

                if (rad1lwrxpdrlastdigitcnt == 25) {
                    if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                        loseldis[radnum] = 10;
                    } else {
                        loseldis[radnum] = 9;
                    }
                    XPLMSetDatai(Rad1LowerXpdrRemapableData, rad1lwrxpdrdigitremap);
                    rad1lwrxpdrlastdigitcnt = rad1lwrxpdrlastdigitcnt + 1;
                }

                // Use the ACT/STBY button to select XPDR mode
                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1LowerXpdrRemapableMode) == 0) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            XPLMSetDatai(Rad1LowerXpdrRemapableMode, 1);
                            loxpdrpushed = 1;
                            lolastxpdrpos = 0;
                        }
                    }
                }

                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1LowerXpdrRemapableMode) == 1) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            if (lolastxpdrpos == 0) {
                                XPLMSetDatai(Rad1LowerXpdrRemapableMode, 2);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 1;
                            }

                            if (lolastxpdrpos == 2) {
                                XPLMSetDatai(Rad1LowerXpdrRemapableMode, 0);
                                loxpdrpushed = 1;
                            }
                        }
                    }
                }

                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1LowerXpdrRemapableMode) == 2) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            if (lolastxpdrpos == 1) {
                                XPLMSetDatai(Rad1LowerXpdrRemapableMode, 3);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 2;
                            }
                            if (lolastxpdrpos == 3) {
                                XPLMSetDatai(Rad1LowerXpdrRemapableMode, 1);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 2;
                            }
                        }
                    }
                }

                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1LowerXpdrRemapableMode) == 3) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            if (lolastxpdrpos == 2) {
                                XPLMSetDatai(Rad1LowerXpdrRemapableMode, 4);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 3;
                            }
                            if (lolastxpdrpos == 4) {
                                XPLMSetDatai(Rad1LowerXpdrRemapableMode, 2);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 3;
                            }
                        }
                    }
                }

                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(Rad1LowerXpdrRemapableMode) == 4) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            XPLMSetDatai(Rad1LowerXpdrRemapableMode, 3);
                            loxpdrpushed = 1;
                            lolastxpdrpos = 4;
                        }
                    }
                }

                // if loxpdrloop is to low mode switch will not stop in position
                // if loxpdrloop is to high mode switch sometimes will not move
                // ToDo Need to find a better way
                if (loxpdrpushed == 1) {
                    loxpdrloop++;
                    if (loxpdrloop == 25) {
                        loxpdrpushed = 0;
                        loxpdrloop = 0;
                    }
                }
            }

            if (xpanelsfnbutton == 1) {
                if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                    loqnhdbncfninc[radnum]++;
                    if (loqnhdbncfninc[radnum] > radspeed) {
                        XPLMCommandOnce(Rad1LowrXpdrBaroUpRemapableCmd);
                        loqnhdbncfninc[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                    loqnhdbncfndec[radnum]++;
                    if (loqnhdbncfndec[radnum] > radspeed) {
                        XPLMCommandOnce(Rad1LowrXpdrBaroDnRemapableCmd);
                        loqnhdbncfndec[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);


                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loqnhdbnccorinc[radnum]++;
                    if (loqnhdbnccorinc[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(Rad1LowrXpdrBaroUpRemapableCmd);
                            --radn;
                        }
                        loqnhdbnccorinc[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


               if((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                 loqnhdbnccordec[radnum]++;
                 if (loqnhdbnccordec[radnum] > radspeed) {
                     radn = 10;
                     while (radn>0) {
                       XPLMCommandOnce(Rad1LowrXpdrBaroDnRemapableCmd);
                       --radn;
                     }
                     loqnhdbnccordec[radnum] = 0;
                 }
               }
               Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

               if(testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                 XPLMSetDatai(Rad1LowerXpdrBaroStdRemapableData, 1);
               }

           }


           loxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
           loxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
           lobarosetf[radnum] = XPLMGetDataf(BaroSetting);
           if (metricpressenable == 0) {
               lobarosetf[radnum] = lobarosetf[radnum] * 100.0;
               XPLMSetDatai(MetricPress, 0);
           }
           if (metricpressenable == 1) {
               lobarosetf[radnum] = lobarosetf[radnum] * 33.8639;
               XPLMSetDatai(MetricPress, 1);
           }
           lobaroset[radnum] = (int)lobarosetf[radnum];

       } else if ((rad2lwrxpdrswitchremap == 777) && (radnum == 1)) {


           if(xpanelsfnbutton == 0) {
               if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                   loseldis[radnum] = 10;
               } else {
                  loseldis[radnum] = 9;
               }

               //loseldis[radnum] = 9;
               rad2lwrxpdrlastdigitremap = 0;
               if((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                   loxpdrdbncfninc[radnum]++;
                   if (loxpdrdbncfninc[radnum] > radspeed) {
                       rad2lwrxpdrdigitremap++;
                       loxpdrdbncfninc[radnum] = 0;
                       if (rad2lwrxpdrdigitremap > 7) {
                           rad2lwrxpdrdigitremap = 0;
                       }
                       rad2lwrxpdrlastdigitremap = 1;
                   }
                   rad2lwrxpdrlastdigitcnt = 0;
               }
               Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

               if((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                   loxpdrdbncfninc[radnum]++;
                   if (loxpdrdbncfninc[radnum] > radspeed) {
                       rad2lwrxpdrdigitremap--;
                       loxpdrdbncfninc[radnum] = 0;
                       if (rad2lwrxpdrdigitremap < 0) {
                           rad2lwrxpdrdigitremap = 7;
                       }
                       rad2lwrxpdrlastdigitremap = 1;
                   }
                   rad2lwrxpdrlastdigitcnt = 0;
               }
               Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);

               if (rad2lwrxpdrlastdigitremap == 0) {
                   if (rad2lwrxpdrlastdigitcnt < 25) {
                       rad2lwrxpdrlastdigitcnt++;
                   }

               }
               if (rad2lwrxpdrlastdigitcnt < 25) {
                   if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                       loseldis[radnum] = 10;
                   } else {
                      loseldis[radnum] = 11;
                   }

                   //loseldis[radnum] = 11;
               }
               if (rad2lwrxpdrlastdigitcnt == 25) {
                   if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                       loseldis[radnum] = 10;
                   } else {
                      loseldis[radnum] = 9;
                   }

                   //loseldis[radnum] = 9;
                   XPLMSetDatai(Rad2LowerXpdrRemapableData, rad2lwrxpdrdigitremap);
                   rad2lwrxpdrlastdigitcnt = rad2lwrxpdrlastdigitcnt + 1;
               }



               // Use the ACT/STBY button to select XPDR mode

               if (loxpdrpushed == 0) {
                   if (XPLMGetDatai(Rad2LowerXpdrRemapableMode) == 0) {
                       if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                           XPLMSetDatai(Rad2LowerXpdrRemapableMode, 1);
                           loxpdrpushed = 1;
                           lolastxpdrpos = 0;
                       }
                   }
               }

               if (loxpdrpushed == 0) {
                   if (XPLMGetDatai(Rad2LowerXpdrRemapableMode) == 1) {
                       if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                           if (lolastxpdrpos == 0) {
                               XPLMSetDatai(Rad2LowerXpdrRemapableMode, 2);
                               loxpdrpushed = 1;
                               lolastxpdrpos = 1;
                           }
                           if (lolastxpdrpos == 2) {
                               XPLMSetDatai(Rad2LowerXpdrRemapableMode, 0);
                               loxpdrpushed = 1;
                           }
                       }
                   }
               }
               if (loxpdrpushed == 0) {
                   if (XPLMGetDatai(Rad2LowerXpdrRemapableMode) == 2) {
                       if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                           if (lolastxpdrpos == 1) {
                               XPLMSetDatai(Rad2LowerXpdrRemapableMode, 3);
                               loxpdrpushed = 1;
                               lolastxpdrpos = 2;
                           }
                           if (lolastxpdrpos == 3) {
                               XPLMSetDatai(Rad2LowerXpdrRemapableMode, 1);
                               loxpdrpushed = 1;
                               lolastxpdrpos = 2;
                           }
                       }
                   }
               }

               if (loxpdrpushed == 0) {
                   if (XPLMGetDatai(Rad2LowerXpdrRemapableMode) == 3) {
                       if(testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                           if (lolastxpdrpos == 2) {
                               XPLMSetDatai(Rad2LowerXpdrRemapableMode, 4);
                               loxpdrpushed = 1;
                               lolastxpdrpos = 3;
                           }
                           if (lolastxpdrpos == 4) {
                               XPLMSetDatai(Rad2LowerXpdrRemapableMode, 2);
                               loxpdrpushed = 1;
                               lolastxpdrpos = 3;
                           }
                       }
                   }
               }

               if (loxpdrpushed == 0) {
                   if (XPLMGetDatai(Rad2LowerXpdrRemapableMode) == 4) {
                       if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                           XPLMSetDatai(Rad2LowerXpdrRemapableMode, 3);
                           loxpdrpushed = 1;
                           lolastxpdrpos = 4;
                       }
                   }
               }

               // if loxpdrloop is to low mode switch will not stop in position
               // if loxpdrloop is to high mode switch sometimes will not move
               // ToDo Need to find a better way
               if (loxpdrpushed == 1) {
                   loxpdrloop++;
                   if (loxpdrloop == 25) {
                       loxpdrpushed = 0;
                       loxpdrloop = 0;
                   }
               }
           }

           if (xpanelsfnbutton == 1) {
               if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                   loqnhdbncfninc[radnum]++;
                   if (loqnhdbncfninc[radnum] > radspeed) {
                       XPLMCommandOnce(Rad2LowrXpdrBaroUpRemapableCmd);
                       loqnhdbncfninc[radnum] = 0;
                   }
               }
               Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


               if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                   loqnhdbncfndec[radnum]++;
                   if (loqnhdbncfndec[radnum] > radspeed) {
                       XPLMCommandOnce(Rad2LowrXpdrBaroDnRemapableCmd);
                       loqnhdbncfndec[radnum] = 0;
                   }
               }
               Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);


               if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                   loqnhdbnccorinc[radnum]++;
                   if (loqnhdbnccorinc[radnum] > radspeed) {
                       radn = 10;
                       while (radn>0) {
                           XPLMCommandOnce(Rad2LowrXpdrBaroUpRemapableCmd);
                           --radn;
                       }
                       loqnhdbnccorinc[radnum] = 0;
                   }
               }
               Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


               if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                   loqnhdbnccordec[radnum]++;
                   if (loqnhdbnccordec[radnum] > radspeed) {
                       radn = 10;
                       while (radn>0) {
                           XPLMCommandOnce(Rad2LowrXpdrBaroDnRemapableCmd);
                           --radn;
                       }
                       loqnhdbnccordec[radnum] = 0;
                   }
               }
               Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);


               if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                   XPLMSetDatai(Rad2LowerXpdrBaroStdRemapableData, 1);
               }
           }


           loxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
           loxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
           lobarosetf[radnum] = XPLMGetDataf(BaroSetting);
           if (metricpressenable == 0) {
               lobarosetf[radnum] = lobarosetf[radnum] * 100.0;
               XPLMSetDatai(MetricPress, 0);
           }
           if (metricpressenable == 1) {
               lobarosetf[radnum] = lobarosetf[radnum] * 33.8639;
               XPLMSetDatai(MetricPress, 1);
           }
           lobaroset[radnum] = (int)lobarosetf[radnum];

       } else {
            if ((XPLMGetDatai(AvPwrOn) == 0) | (XPLMGetDatai(BatPwrOn) == 0)) {
                loseldis[radnum] = 10;
            } else {
                loseldis[radnum] = 9;
            }


            // ****** Function button is not pushed  *******
            if (xpanelsfnbutton == 0) {
                if (loxpdrsel[radnum] == 1) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loxpdrdbncfninc[radnum]++;
                        if (loxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrOnesUp);
                            loxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loxpdrdbncfndec[radnum]++;
                        if (loxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrOnesDn);
                            loxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }

                if (loxpdrsel[radnum] == 2) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loxpdrdbncfninc[radnum]++;
                        if (loxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrTensUp);
                            loxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loxpdrdbncfndec[radnum]++;
                        if (loxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrTensDn);
                            loxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }

                if (loxpdrsel[radnum] == 3) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loxpdrdbncfninc[radnum]++;
                        if (loxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrHunUp);
                            loxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loxpdrdbncfndec[radnum]++;
                        if (loxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrHunDn);
                            loxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }


                if (loxpdrsel[radnum] == 4) {
                    if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                        loxpdrdbncfninc[radnum]++;
                        if (loxpdrdbncfninc[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrThUp);
                            loxpdrdbncfninc[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);


                    if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                        loxpdrdbncfndec[radnum]++;
                        if (loxpdrdbncfndec[radnum] > radspeed) {
                            XPLMCommandOnce(XpdrThDn);
                            loxpdrdbncfndec[radnum] = 0;
                        }
                    }
                    Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);
                }

                // Use the Coarse knob to select digit in the up direction
                if((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    loxpdrdbnccorinc[radnum]++;
                    if (loxpdrdbnccorinc[radnum] > radspeed) {
                        loxpdrsel[radnum] ++;
                        loxpdrdbnccorinc[radnum] = 0;
                    }
                    if (loxpdrsel[radnum] == 5) {
                        loxpdrsel[radnum] = 1;
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

                // Use the Coarse knob to select digit in the up direction
                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loxpdrdbnccordec[radnum]++;
                    if (loxpdrdbnccordec[radnum] > radspeed) {
                        loxpdrsel[radnum] --;
                        loxpdrdbnccordec[radnum] = 0;
                    }
                    if (loxpdrsel[radnum] == 0) {
                        loxpdrsel[radnum] = 4;
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);

                // Use the ACT/STBY button to select XPDR mode
                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 0) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            XPLMSetDatai(XpdrMode, 1);
                            loxpdrpushed = 1;
                            lolastxpdrpos = 0;
                        }
                    }
                }

                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 1) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            if (lolastxpdrpos == 0) {
                                XPLMSetDatai(XpdrMode, 2);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 1;
                            }

                            if (lolastxpdrpos == 2) {
                                XPLMSetDatai(XpdrMode, 0);
                                loxpdrpushed = 1;
                            }
                        }
                    }
                }

                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 2) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            if (lolastxpdrpos == 1) {
                                XPLMSetDatai(XpdrMode, 3);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 2;
                            }
                            if (lolastxpdrpos == 3) {
                                XPLMSetDatai(XpdrMode, 1);
                                loxpdrpushed = 1;
                                lolastxpdrpos = 2;
                            }
                        }
                    }
                }


                if (loxpdrpushed == 0) {
                    if (XPLMGetDatai(XpdrMode) == 3) {
                        if (testbit(radiobuf[radnum], LOWER_ACT_STBY)) {
                            XPLMSetDatai(XpdrMode, 2);
                            loxpdrpushed = 1;
                            lolastxpdrpos = 3;
                        }
                    }
                }

                // if loxpdrloop is to low mode switch will not stop in position
                // if loxpdrloop is to high mode switch sometimes will not move
                // ToDo Need to find a better way
                if (loxpdrpushed == 1) {
                    loxpdrloop++;
                    if (loxpdrloop == 25) {
                        loxpdrpushed = 0;
                        loxpdrloop = 0;
                    }
                }
            }


            // ****** Function button is pushed  *******
            if (xpanelsfnbutton == 1) {
                if ((Last_Lower_Fine_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_UP) == 0)) {
                    loqnhdbncfninc[radnum]++;
                    if (loqnhdbncfninc[radnum] > radspeed) {
                        XPLMCommandOnce(BaroUp);
                        loqnhdbncfninc[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Up[radnum] = testbit(radiobuf[radnum],LOWER_FINE_UP);

                if ((Last_Lower_Fine_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_FINE_DN) == 0)) {
                    loqnhdbncfndec[radnum]++;
                    if (loqnhdbncfndec[radnum] > radspeed) {
                        XPLMCommandOnce(BaroDn);
                        loqnhdbncfndec[radnum] = 0;
                    }
                }
                Last_Lower_Fine_Dn[radnum] = testbit(radiobuf[radnum],LOWER_FINE_DN);


                if ((Last_Lower_Coarse_Up[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_UP) == 0)) {
                    loqnhdbnccorinc[radnum]++;
                    if (loqnhdbnccorinc[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(BaroUp);
                            --radn;
                        }
                        loqnhdbnccorinc[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Up[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_UP);


                if ((Last_Lower_Coarse_Dn[radnum] == 1) && (testbit(radiobuf[radnum],LOWER_COARSE_DN) == 0)) {
                    loqnhdbnccordec[radnum]++;
                    if (loqnhdbnccordec[radnum] > radspeed) {
                        radn = 10;
                        while (radn>0) {
                            XPLMCommandOnce(BaroDn);
                            --radn;
                        }
                        loqnhdbnccordec[radnum] = 0;
                    }
                }
                Last_Lower_Coarse_Dn[radnum] = testbit(radiobuf[radnum],LOWER_COARSE_DN);

                if (testbit(radiobuf[radnum],LOWER_ACT_STBY)) {
                    XPLMCommandOnce(BaroStd);
                }
            }

            loxpdrcode[radnum] = XPLMGetDatai(XpdrCode);
            loxpdrmode[radnum] = XPLMGetDatai(XpdrMode);
            lobarosetf[radnum] = XPLMGetDataf(BaroSetting);
            if (metricpressenable == 0) {
                lobarosetf[radnum] = lobarosetf[radnum] * 100.0;
                XPLMSetDatai(MetricPress, 0);
            }

            if (metricpressenable == 1) {
                lobarosetf[radnum] = lobarosetf[radnum] * 33.8639;
                XPLMSetDatai(MetricPress, 1);
            }
            lobaroset[radnum] = (int)lobarosetf[radnum];
       }
   }
}

// ***************** Blank Display *******************

void process_radio_blank_display()
{


	if (XPLMGetDatai(AvPwrOn) == 0) {
          upseldis[radnum] = 10;
          loseldis[radnum] = 10;
	}

	if (XPLMGetDatai(BatPwrOn) == 0) {
          upseldis[radnum] = 10;
          loseldis[radnum] = 10;
	}

    if(switchcnt > 0)  {
        if (XPLMGetDatai(SwitchAvOwnedDataRef) == 0) {
              upseldis[radnum] = 10;
              loseldis[radnum] = 10;
        }

    } else {

    }


	if (XPLMGetDatai(Com1PwrOn) == 0) {
          if (upcom1[radnum] == 1) {
            upseldis[radnum] = 10;
          }
          if (locom1[radnum] == 1) {
            loseldis[radnum] = 10;
          }
	}

	if (XPLMGetDatai(Com2PwrOn) == 0) {
          if (upcom2[radnum] == 2) {
            upseldis[radnum] = 10;
          }
          if (locom2[radnum] == 2) {
            loseldis[radnum] = 10;
          }
	}

	if (XPLMGetDatai(Nav1PwrOn) == 0) {
          if (upnav1[radnum] == 3) {
            upseldis[radnum] = 10;
          }
          if (lonav1[radnum] == 3) {
            loseldis[radnum] = 10;
          }
	}

	if (XPLMGetDatai(Nav2PwrOn) == 0) {
          if (upnav2[radnum] == 4) {
            upseldis[radnum] = 10;
          }
          if (lonav2[radnum] == 4) {
            loseldis[radnum] = 10;
          }
	}

}

void process_upper_com_freq()

{
  radioaactv = upactcomfreq[radnum];
  radioadig1 = radioaactv/100000, radioarem1 = radioaactv%100000;
  radioadig2 = radioarem1 /10000, radioarem2 = radioarem1%10000;
  radioadig3 = radioarem2/1000, radioarem3 = radioarem2%1000;
  radioadig4 = radioarem3/100, radioarem4 = radioarem3%100;
  radioadig5 = radioarem4/10, radioarem5 = radioarem4%10;
  radioadig3 = radioadig3+208, radioadig6 = radioarem5;
  if (radioadig6 == 5) {
      radioadig5 = radioadig5 +208;
  }



  radiobstby = upstbycomfreq[radnum];
  radiobdig1 = radiobstby/100000, radiobrem1 = radiobstby%100000;
  radiobdig2 = radiobrem1 /10000, radiobrem2 = radiobrem1%10000;
  radiobdig3 = radiobrem2/1000, radiobrem3 = radiobrem2%1000;
  radiobdig4 = radiobrem3/100, radiobrem4 = radiobrem3%100;
  radiobdig5 = radiobrem4/10, radiobrem5 = radiobrem4%10;
  radiobdig3 = radiobdig3+208, radiobdig6 = radiobrem5;
  if (radiobdig6 == 5) {
      radiobdig5 = radiobdig5 +208;
  }




  return;
}

void process_upper_nav_freq()

{
  radioaactv = upactnavfreq[radnum];
  radioadig1 = radioaactv/10000, radioarem1 = radioaactv%10000;
  radioadig2 = radioarem1 /1000, radioarem2 = radioarem1%1000;
  radioadig3 = radioarem2/100, radioarem3 = radioarem2%100;
  radioadig4 = radioarem3/10, radioarem4 = radioarem3%10;
  radioadig3 = radioadig3+208, radioadig5 = radioarem4;

  if(xpanelsfnbutton == 0) {
      radiobstby = upstbynavfreq[radnum];
      radiobdig1 = radiobstby/10000, radiobrem1 = radiobstby%10000;
      radiobdig2 = radiobrem1 /1000, radiobrem2 = radiobrem1%1000;
      radiobdig3 = radiobrem2/100, radiobrem3 = radiobrem2%100;
      radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
      radiobdig3 = radiobdig3+208, radiobdig5 = radiobrem4;

  }
  if(xpanelsfnbutton == 1) {
      if (upseldis[radnum] == 3) {
          if ((rad1uprnav1switchremap == 1) && (radnum == 0)) {
              UpNav1ObsDegm[radnum] = XPLMGetDataf(Rad1UpperObs1RemapableDataf);
          } else if ((rad2uprnav1switchremap == 1) && (radnum == 1)) {
              UpNav1ObsDegm[radnum] = XPLMGetDataf(Rad2UpperObs1RemapableDataf);
          } else if ((rad3uprnav1switchremap == 1) && (radnum == 2)) {
              UpNav1ObsDegm[radnum] = XPLMGetDataf(Rad3UpperObs1RemapableDataf);
          } else {
              UpNav1ObsDegm[radnum] = XPLMGetDataf(Nav1ObsDegm);
          }

          //UpNav1ObsDegm[radnum] = XPLMGetDataf(Nav1ObsDegm);
          radiobstby = (int)(UpNav1ObsDegm[radnum]);
      } else if (upseldis[radnum] == 4) {
          if ((rad1uprnav2switchremap == 1) && (radnum == 0)) {
              UpNav2ObsDegm[radnum] = XPLMGetDataf(Rad1UpperObs2RemapableDataf);
          } else if ((rad2uprnav2switchremap == 1) && (radnum == 1)) {
              UpNav2ObsDegm[radnum] = XPLMGetDataf(Rad2UpperObs2RemapableDataf);
          } else if ((rad3uprnav2switchremap == 1) && (radnum == 2)) {
              UpNav2ObsDegm[radnum] = XPLMGetDataf(Rad3UpperObs2RemapableDataf);
          } else {
              UpNav2ObsDegm[radnum] = XPLMGetDataf(Nav2ObsDegm);
          }
          //UpNav2ObsDegm[radnum] = XPLMGetDataf(Nav2ObsDegm);
          radiobstby = (int)(UpNav2ObsDegm[radnum]);
      }
      radiobdig1 = 15, radiobdig2 = 15;
      //radiobstby = radiobstby + 10;
      radiobdig3 = radiobstby/100, radiobrem3 = radiobstby%100;
      radiobdig4 = radiobrem3/10, radiobrem4 = radiobrem3%10;
      radiobdig3 = radiobdig3, radiobdig5 = radiobrem4;
  }


  return;
}

void process_lower_com_freq()

{
  radiocactv = loactcomfreq[radnum];
  radiocdig1 = radiocactv/100000, radiocrem1 = radiocactv%100000;
  radiocdig2 = radiocrem1 /10000, radiocrem2 = radiocrem1%10000;
  radiocdig3 = radiocrem2/1000, radiocrem3 = radiocrem2%1000;
  radiocdig4 = radiocrem3/100, radiocrem4 = radiocrem3%100;
  radiocdig5 = radiocrem4/10, radiocrem5 = radiocrem4%10;
  radiocdig3 = radiocdig3+208, radiocdig6 = radiocrem5;
  if (radiocdig6 == 5) {
      radiocdig5 = radiocdig5 +208;
  }

  radiodstby = lostbycomfreq[radnum];
  radioddig1 = radiodstby/100000, radiodrem1 = radiodstby%100000;
  radioddig2 = radiodrem1 /10000, radiodrem2 = radiodrem1%10000;
  radioddig3 = radiodrem2/1000, radiodrem3 = radiodrem2%1000;
  radioddig4 = radiodrem3/100, radiodrem4 = radiodrem3%100;
  radioddig5 = radiodrem4/10, radiodrem5 = radiodrem4%10;
  radioddig3 = radioddig3+208, radioddig6 = radiodrem5;
  if (radioddig6 == 5) {
      radioddig5 = radioddig5 +208;
  }

  return;
}

void process_lower_nav_freq()

{
  radiocactv = loactnavfreq[radnum];
  radiocdig1 = radiocactv/10000, radiocrem1 = radiocactv%10000;
  radiocdig2 = radiocrem1 /1000, radiocrem2 = radiocrem1%1000;
  radiocdig3 = radiocrem2/100, radiocrem3 = radiocrem2%100;
  radiocdig4 = radiocrem3/10, radiocrem4 = radiocrem3%10;
  radiocdig3 = radiocdig3+208;
  radiocdig5 = radiocrem4;

  if(xpanelsfnbutton == 0) {

      radiodstby = lostbynavfreq[radnum];
      radioddig1 = radiodstby/10000, radiodrem1 = radiodstby%10000;
      radioddig2 = radiodrem1 /1000, radiodrem2 = radiodrem1%1000;
      radioddig3 = radiodrem2/100, radiodrem3 = radiodrem2%100;
      radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
      radioddig3 = radioddig3+208, radioddig5 = radiodrem4;
  }

  if(xpanelsfnbutton == 1) {

      if (loseldis[radnum] == 3) {
          if ((rad1lwrnav1switchremap == 1) && (radnum == 0)) {
              LoNav1ObsDegm[radnum] = XPLMGetDataf(Rad1LowerObs1RemapableDataf);
          } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
              UpNav1ObsDegm[radnum] = XPLMGetDataf(Rad2LowerObs1RemapableDataf);
          } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
              LoNav1ObsDegm[radnum] = XPLMGetDataf(Rad3LowerObs1RemapableDataf);
          } else {
              LoNav1ObsDegm[radnum] = XPLMGetDataf(Nav1ObsDegm);
          }

          //LoNav1ObsDegm[radnum] = XPLMGetDataf(Nav1ObsDegm);
          radiodstby = (int)(LoNav1ObsDegm[radnum]);
      } else if (loseldis[radnum] == 4) {
          if ((rad1lwrnav2switchremap == 1) && (radnum == 0)) {
              LoNav2ObsDegm[radnum] = XPLMGetDataf(Rad1LowerObs2RemapableDataf);
          } else if ((rad2lwrnav1switchremap == 1) && (radnum == 1)) {
              LoNav2ObsDegm[radnum] = XPLMGetDataf(Rad2LowerObs2RemapableDataf);
          } else if ((rad3lwrnav1switchremap == 1) && (radnum == 2)) {
              LoNav2ObsDegm[radnum] = XPLMGetDataf(Rad3LowerObs2RemapableDataf);
          } else {
              LoNav2ObsDegm[radnum] = XPLMGetDataf(Nav2ObsDegm);
          }

          //LoNav2ObsDegm[radnum] = XPLMGetDataf(Nav2ObsDegm);
          radiodstby = (int)(LoNav2ObsDegm[radnum]);
      }

      radioddig1 = 15, radioddig2 = 15;
      //radiodstby = radiodstby + 10;

      radioddig3 = radiodstby/100, radiodrem3 = radiodstby%100;
      radioddig4 = radiodrem3/10, radiodrem4 = radiodrem3%10;
      radioddig3 = radioddig3, radioddig5 = radiodrem4;
  }

  return;
}

// ***** Radio Panel Process  *******
void process_radio_panel()

{
    process_radio_menu();

// ******* Only do a read if something new to be read ********

  hid_set_nonblocking(radiohandle[radnum], 1);
  int radio_safety_cntr = 30;
  do{
    radiores = hid_read(radiohandle[radnum], radiobuf[radnum], sizeof(radiobuf[radnum]));

    process_upper_datareferences();
    process_upper_com1_switch();
    process_upper_com2_switch();
    process_upper_nav1_switch();
    process_upper_nav2_switch();
    proecss_upper_adf_switch();
    process_upper_dme_switch();
    process_upper_xpdr_switch();
    process_lower_datareferences();
    process_lower_com1_switch();
    process_lower_com2_switch();
    process_lower_nav1_switch();
    process_lower_nav2_switch();
    process_lower_adf_switch();
    process_lower_dme_switch();
    process_lower_xpdr_switch();
    if(radiores > 0){
        process_radio_blank_display();
        process_radio_upper_display();
        process_radio_lower_display();
        process_radio_make_message();
        hid_send_feature_report(radiohandle[radnum], radiowbuf[radnum], sizeof(radiowbuf[radnum]));
    }
    --radio_safety_cntr;
  }while((radiores > 0) && (radio_safety_cntr > 0));

  process_radio_blank_display();
  process_radio_upper_display();
  process_radio_lower_display();
  process_radio_make_message();

// ******* Write on changes or timeout ********

    if ((lastupseldis[radnum] != upseldis[radnum]) || (lastloseldis[radnum] != loseldis[radnum]) || (radionowrite[radnum] > 50) || (xpanelsfnbutton == 1)) {
        radres = hid_send_feature_report(radiohandle[radnum], radiowbuf[radnum], sizeof(radiowbuf[radnum]));
        radionowrite[radnum] = 1;
        lastupseldis[radnum] = upseldis[radnum];
        lastloseldis[radnum] = loseldis[radnum];
    }else{
        radionowrite[radnum]++;
    }

  // *********** loop untill all radios serviced *************
  // **************   then start again    *******************

    //printf("radnum = %d\n", radnum);
    radnum++;
    if (radnum == radcnt) {
      radnum = 0;
    }

    return;
  }
