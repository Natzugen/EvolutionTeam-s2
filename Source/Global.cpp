/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Global.h"
//==========================================
//======DEFINES INFORMACION GLOBALES========
//==========================================
CHAR Character[11];
CHAR Conta[10];
FILE * SMDfile;
CHAR ConnectNotice[200];
CHAR ConnectNotice2[200];
CHAR GM[10];
CHAR sServer[50];
CHAR sLogin[50];
CHAR sPass[50];
CHAR sDataBase[50];
INT sOptions;

//=====================================================================================
//Message System
//=====================================================================================
CHAR MSG00[500];
CHAR MSG01[500];
CHAR MSG02[500];
CHAR MSG03[500];
CHAR MSG04[500];
CHAR MSG05[500];
CHAR MSG06[500];
CHAR MSG07[500];
CHAR MSG08[500];
CHAR MSG09[500];
CHAR MSG10[500];
CHAR MSG11[500];
CHAR MSG12[500];
CHAR MSG13[500];
CHAR MSG14[500];
CHAR MSG15[500];
CHAR MSG16[500];
CHAR MSG17[500];
CHAR MSG18[500];
CHAR MSG19[500];
CHAR MSG20[500];
CHAR MSG21[500];
CHAR MSG22[500];
CHAR MSG23[500];
CHAR MSG24[500];
CHAR MSG25[500];
CHAR MSG26[500];
CHAR MSG27[500];
CHAR MSG28[500];
CHAR MSG29[500];
CHAR MSG30[500];
CHAR MSG31[500];
CHAR MSG32[500];
CHAR MSG33[500];
CHAR MSG34[500];
CHAR MSG35[500];
CHAR MSG36[500];
CHAR MSG37[500];
CHAR MSG38[500];
CHAR MSG39[500];
CHAR MSG40[500];
CHAR MSG41[500];
CHAR MSG42[500];
CHAR MSG43[500];
CHAR MSG44[500];
CHAR MSG45[500];
CHAR MSG46[500];
CHAR MSG47[500];
CHAR MSG48[500];
CHAR MSG49[500];
CHAR MSG50[500];
CHAR MSG51[500];
CHAR MSG52[500];
CHAR MSG53[500];
CHAR MSG54[500];
CHAR MSG55[500];
CHAR MSG56[500];
CHAR MSG57[500];
CHAR MSG58[500];
CHAR MSG59[500];
CHAR MSG60[500];
CHAR MSG61[500];
CHAR MSG62[500];
CHAR MSG63[500];
CHAR MSG64[500];
CHAR MSG65[500];
CHAR MSG66[500];
CHAR MSG67[500];
CHAR MSG68[500];
CHAR MSG69[500];
CHAR MSG70[500];
CHAR MSG71[500];
CHAR MSG72[500];
CHAR MSG73[500];
CHAR MSG74[500];
CHAR MSG75[500];
CHAR MSG76[500];
CHAR MSG77[500];
CHAR MSG78[500];
CHAR MSG79[500];
CHAR MSG80[500];
CHAR MSG81[500];
CHAR MSG82[500];
CHAR MSG83[500];
CHAR MSG84[500];
CHAR MSG85[500];
CHAR MSG86[500];
CHAR MSG87[500];
CHAR MSG88[500];
CHAR MSG89[500];
CHAR MSG90[500];
CHAR MSG91[500];
CHAR MSG92[500];
CHAR MSG93[500];
CHAR MSG94[500];
CHAR MSG95[500];
CHAR MSG96[500];
CHAR MSG97[500];
CHAR MSG98[500];
CHAR MSG99[500];
CHAR MSG100[500];
CHAR MSG101[500];
CHAR MSG102[500];
CHAR MSG103[500];
CHAR MSG104[500];
CHAR MSG105[500];
CHAR MSG106[500];
CHAR MSG107[500];
CHAR MSG108[500];
CHAR MSG109[500];
CHAR MSG110[500];
CHAR MSG111[500];
CHAR MSG112[500];
CHAR MSG113[500];
CHAR MSG114[500];
CHAR MSG115[500];
CHAR MSG116[500];
CHAR MSG117[500];
CHAR MSG118[500];
CHAR MSG119[500];
CHAR MSG120[500];
CHAR MSG121[500];
CHAR MSG122[500];
CHAR MSG123[500];
CHAR MSG124[500];
CHAR MSG125[500];
CHAR MSG126[500];
CHAR MSG127[500];
CHAR MSG128[500];
CHAR MSG129[500];
CHAR MSG130[500];
CHAR MSG131[500];
CHAR MSG132[500];
CHAR MSG133[500];
CHAR MSG134[500];
CHAR MSG135[500];
CHAR MSG136[500];
CHAR MSG137[500];
CHAR MSG138[500];
CHAR MSG139[500];
CHAR MSG140[500];
CHAR MSG141[500];
CHAR MSG142[500];
CHAR MSG143[500];
CHAR MSG144[500];
CHAR MSG145[500];
CHAR MSG146[500];
CHAR MSG147[500];
CHAR MSG148[500];
CHAR MSG149[500];
CHAR MSG150[500];
CHAR MSG151[500];
CHAR MSG152[500];
CHAR MSG153[500];
CHAR MSG154[500];
CHAR MSG155[500];
CHAR MSG156[500];
CHAR MSG157[500];
CHAR MSG158[500];
CHAR MSG159[500];
CHAR MSG160[500];
CHAR MSG161[500];

char						GS_NAME[255]; //add para happyhour