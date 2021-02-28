/*
 * AceSpreader.c
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */

#include "AceSpreader.h"
int testParsingAce(char* fmt, ...)
{


// Parse avec strtok
//#define T_TOK
#ifdef T_TOK
	char* pu8Token;

	printf("test de strtok ... \r\n");
	pu8Token = strtok((char*)buf1, (char*) ";");
	printf(" %s \r\n", pu8Token);
	int i = 0;
	while(pu8Token != NULL) {
	    i++;
	    printf ("i=%d\tToken: len(%d)\t%s \r\n", i, strlen(pu8Token), pu8Token);
	    pu8Token= strtok(NULL, (char *)";");
	}
#endif

//#define T_CSPN
#ifdef T_CSPN
	  char str1[] = "fcba73";
	  char keys[] = "1234567890";
	  int j;
	  j = strcspn (str1,keys);
	  printf ("The first number in str is at position %d.\n",j+1);
#endif

//#define T_CHR
#ifdef T_CHR
	  char str2[] = "This is a sample string";
	    char * pch;
	    printf ("Looking for the 's' character in \"%s\"...\n",str2);
	    pch = strchr(str2,'s');
	    while (pch!=NULL)
	    {
	      printf ("found at %d\n",pch - str2 + 1);
	      pch=strchr(pch+1,'s');
	    }
#endif

//#define T_SEP
#ifdef T_SEP

	char *token;
	char tmp_string[20];
	char delimiter[] = ":";
	strcpy ((char *)tmp_string, "1:2:3::4");
	printf(" tmp_string : %s \r\n", tmp_string);
	printf(" tmp_string : %s \r\n", tmp_string + 1);
    char* t1 = (char *)tmp_string;
	printf(" t1: %s - tmp_string: %s \r\n", t1, tmp_string);
	t1++;
	t1++;
	printf(" t1: %s - tmp_string: %s \r\n", t1, tmp_string);
	token = strsep(&t1, delimiter); // first token
	printf(" token : %s \r\n", token);
	int k = 0;
	while(token != NULL) {
	    k++;
	    printf ("i=%d\tToken: len(%d)\t%s ", k, strlen(token), token);
	    printf(" t1: %s - tmp_string: %s \r\n", t1, tmp_string);
	    token = strsep(&t1, delimiter);
	}
	printf(" t1: %s - tmp_string: %s \r\n", t1, tmp_string);

	strcpy ((char *)tmp_string, "1:2:3::4");
    t1 = (char *)tmp_string;

	token = __strsep(&t1, delimiter); // first token
	printf(" token : %s \r\n", token);
	k = 0;
	while(token != NULL) {
	    k++;
	    printf ("i=%d\tToken: len(%d)\t%s ", k, strlen(token), token);
	    printf(" t1: %s - tmp_string: %s \r\n", t1, tmp_string);
	    token = __strsep(&t1, delimiter);
	}
#endif

#define T_PRS
#ifdef T_PRS
   char buf0[] = {"0;10;1556036;0521132;5"};
   char buf1[] = {"1;10;1556036;0521132;5;aceelectronic.ca;0000783FFF24;8888888888888888"};
   char buf2[] = {"8;aceelectronic.ca;0000783FFF24;;5;1617088;0521132;0;;1.0;;30;8;;;;;;20;0;2462;;;246;5394375;;1910;;36;0;;;;;;;02MAT A;;;;;;;;;;;;;;;;U3V46R0H21;M2-G0-DP1-DS1-SS00OFF"};
   char buf3[] = {"8;aceelectronic.ca;0000783FFF24;;5;1617088;0521132;0;;1.0;;30;8;;;;;;20;0;2462;;;246;5394375;;1910;;36;1;1-2-13;01OVS-02CVOR;;;;;02MAT A;;;;;;;;;;;;;;;;U3V46R0H21;M2-G0-DP1-DS1-SS00OFF"};
   puts("Ace parsing test - unit tests ... \r\n");
   printf("buf0: %s \n", buf0);
   printf("buf1: %s \n", buf1);
   printf("buf2: %s \n", buf2);

   aceParseData((char *)buf0);
   aceParseData((char *)buf1);
   aceParseData((char *)buf2);
   aceParseData((char *)buf3);
#endif

//#define T_VSP
#ifdef T_VSP

    printf("Test vsnprintf ... \r\n");


    UINT8 puNewDataStart[30] = "..";
    va_list ap;
    va_start (ap, fmt);
    const int nFormattingResult = vsnprintf((char*)(puNewDataStart + 1), 30, "----- %d %d", ap);
    printf(puNewDataStart);
    printf("      %d \r\n", nFormattingResult);
    printf("   strlen:  %d \r\n", strlen((char *)puNewDataStart));
    printf("   strlen:  %d \r\n", strlen((char *)fmt));
    va_end(ap);

#endif

/*    int a1 = 0;
    a1 |= 0x01 << 12;
    printf("-- %d", a1);
*/
	return 1;
}



void aceParseData(char* in)
{
   char* szInputString = in;
   char szSeparator[] = ";";
   char* token = strsep(&szInputString, szSeparator);
   printf(" token: %s   \r\n", token);
   int pr = atoi(token);
   UINT8 u8ComposedParams1 = 0;
   UINT8 u8ComposedParams2 = 0;
   char szEquipmentId[15] = {0};
   char szHardwareVersion[4]= {0};
   char szFirmwareversion[6]= {0};
   char szFreeDef1[11];


   switch(pr)
   {
   case 0 :
	   // Time synchronization record
	   printf("case 0: ------\n");
       token = strsep(&szInputString, szSeparator);
       printf(" (Version: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" SysTime: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" SysDate: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" Source: %s) \r\n", token);

	   break;
   case 1 :
	   // Standard header record
	   printf("case 1: ------\n");

       token = strsep(&szInputString, szSeparator);
       printf("(Version: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" SysTime: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" SysDate: %s", token);


       token = strsep(&szInputString, szSeparator);
       printf(" Source: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" ManufID: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" EquipID: %s", token);

       token = strsep(&szInputString, szSeparator);
       printf(" DriverID: %s) \r\n", token);

	   break;
   case 8 :
	   // Spreader data record
             printf("case 8: ------\n");
             token = strsep(&szInputString, szSeparator);
             printf("(ManufID: %s ", token);

             token = strsep(&szInputString, szSeparator);
             strcpy((char *) szEquipmentId, token);
             int stlen = strlen(token);
             printf("EquipID: %s %s %d ", token, szEquipmentId, stlen);

             token = strsep(&szInputString, szSeparator);
             if(*token == '\0')
             {
            	printf("test null ...\r\n");
             }
             token = strsep(&szInputString, szSeparator);
             printf("Source: %s ", token);

             token = strsep(&szInputString, szSeparator);
             printf("SysTime: %s ", token);

             token = strsep(&szInputString, szSeparator);
             printf("SysDate: %s ", token);

             token = strsep(&szInputString, szSeparator);
             UINT8 u8SprMode = atoi(token);
             if(u8SprMode <= 5)
             {
                 u8ComposedParams2 &= ~(0x07); // resetting the old value
                 u8ComposedParams2 |= u8SprMode; // setting the new value
             }
             printf("SprMode: %s %d ", token, u8ComposedParams2);

             token = strsep(&szInputString, szSeparator); // SprSimSpd
             token = strsep(&szInputString, szSeparator); // SprWidthSet
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator); // SprDosSet
             token = strsep(&szInputString, szSeparator);
             INT16 u16SprWidth = atoi(token);
             printf("SprWidth: %s %d ", token, u16SprWidth);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             INT16 u16SprDosRes1 = atoi(token);
             printf("SprDosRes1: %s %d ", token, u16SprDosRes1);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             printf("SprBrinePerc: %s ", token);
             UINT8 u8SprBrinePerc = atoi(token);

             token = strsep(&szInputString, szSeparator);
             UINT8 u8SprMaxOn = atoi(token);
             u8ComposedParams2 &= ~(0x40); // resetting the old value
             u8ComposedParams2 |= u8SprMaxOn << 6; // setting the new value
             printf("SprMaxOn: %s %d ", token, u8ComposedParams2);


             token = strsep(&szInputString, szSeparator);
             printf("SprCntRes1: %s  ", token);
             UINT32 u32SprCntRes1 = atoi(token);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             printf("SprCntBrineKg: %s ", token);
             UINT32 u32SprCntBrineKg = atoi(token);

             token = strsep(&szInputString, szSeparator);
             printf("SprCntLen: %s  ", token);
             UINT32 u32SprCntLen = atoi(token);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             printf("DrivenLen: %s ", token);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             printf("VehSpd: %s ", token);

             token = strsep(&szInputString, szSeparator);
             printf("SprErr: %s ", token);
             bool bIsSprErr = (atoi(token) == 1)? true : false;

             token = strsep(&szInputString, szSeparator);
             printf("SprErrCode: %s ", token);
             int resErr = 0;
             if(bIsSprErr)
             {
            	 char* sep = "-";
            	 char* tErrRank = strsep(&token, sep);
            	 while(tErrRank != NULL)
            	 {
            	     tErrRank = strsep(&token, sep);
            	     int rank = atoi(tErrRank);
            	     rank--;
                     resErr |= (0x01 << rank);
            		 printf(" -- %s %d", tErrRank, resErr);

            	 }
             }
             printf(" -- %d %x ", resErr, resErr);
             token = strsep(&szInputString, szSeparator);
             printf("SprErrRpt: %s ", token);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             char szSprMatRes1[25];
             strcpy((char *) szSprMatRes1, token);
             UINT8 u8SprMatRes1Code = 2;
             if(strcmp((char *)szSprMatRes1, "00SEL") == 0 || strcmp((char *)szSprMatRes1, "01SABLE") == 0)
    		 {
                 u8SprMatRes1Code = (UINT8)(szSprMatRes1[1] - '0');
    	     }
             u8ComposedParams2 &= ~(0x38); // resetting the old value
             u8ComposedParams2 |=  u8SprMatRes1Code << 3;// setting the new value
             printf("SprMatRes1: %s  %d ", token, u8ComposedParams2);

             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             token = strsep(&szInputString, szSeparator);
             printf("FreeDef1: %s ", token);
		     strcpy((char *)szFreeDef1, token);
	         if (strlen(token) == 10)
		     {
               szHardwareVersion[0] = szFreeDef1[8];
               szHardwareVersion[1] = '.';
               szHardwareVersion[2] = szFreeDef1[9];

           	// Setting the firmware version
               szFirmwareversion[0] = szFreeDef1[3];
           	   szFirmwareversion[1] = '.';
               szFirmwareversion[2] = szFreeDef1[4];
               szFirmwareversion[3] = '.';
               szFirmwareversion[4] = szFreeDef1[6];
               szFirmwareversion[5] = '\0';

		     }
             printf("FreeDef1: %s %s %s ", token, szHardwareVersion, szFirmwareversion);

             token = strsep(&szInputString, szSeparator);
             char szFreeDef2[25];
             strcpy((char *) szFreeDef2, token);
             if(token != NULL)
             {
                char szFreeDef2[25];
                strcpy((char *) szFreeDef2, token);
                if(szFreeDef2[1] >= '0' && szFreeDef2[1] <= '2')
                {
                  u8ComposedParams1 &= ~(0x03); // resetting the old value
                  u8ComposedParams1 |= (UINT8)(szFreeDef2[1] - '0'); // setting the new value
                }

                if(szFreeDef2[8] >= '0' && szFreeDef2[8] <= '3')
                {
                  u8ComposedParams1 &= ~(0x0C); // resetting the old value
                  u8ComposedParams1 |= ((UINT8)(szFreeDef2[1] - '0')) << 2; // setting the new value
                }

                if(szFreeDef2[12] == '0' || szFreeDef2[12] == '1')
                {
                  u8ComposedParams1 &= ~(0x10); // resetting the old value
                  u8ComposedParams1 |= ((UINT8)(szFreeDef2[1] - '0')) << 4; // setting the new value
                }

                if(szFreeDef2[17] == '0' || szFreeDef2[17] == '1')
                {
                  u8ComposedParams1 &= ~(0x20); // resetting the old value
                  u8ComposedParams1 |= ((UINT8)(szFreeDef2[1] - '0')) << 5; // setting the new value
                }
             printf("FreeDef2: %s %d ", token, u8ComposedParams1);

             }


	   break;
   default:
	   printf("not supported \r\n");
	   break;
   }


   if(pr == 8)
   	{
   		UINT8 puDataToSend[45] = {0};
   		int index = 0;
   		puDataToSend[0] = 0x00; // Ace manufacturer ID
   		puDataToSend[1] = strlen((char *) szEquipmentId);
   		ToolsPutArrayToBuffer((UINT8*)puDataToSend + 2, (UINT8*)szEquipmentId, puDataToSend[1]);
   		index = puDataToSend[1] + 2;
   		puDataToSend[index] = strlen((char *) szHardwareVersion);
   		index++;
   		ToolsPutArrayToBuffer((UINT8*)puDataToSend + index, (UINT8*)szHardwareVersion, puDataToSend[index -1]);

   		index += puDataToSend[index -1];
   		puDataToSend[index] = strlen((char *) szFirmwareversion);
   		index++;
   		ToolsPutArrayToBuffer((UINT8*)puDataToSend + index, (UINT8*)szFirmwareversion, puDataToSend[index -1]);

   	    index += puDataToSend[index -1];
   		puDataToSend[index] = strlen((char *) szFreeDef1);
   		index++;
   		ToolsPutArrayToBuffer((UINT8*)puDataToSend + index, (UINT8*)szFreeDef1, puDataToSend[index -1]);


   		printf("--- puDataToSend: %s \r\n", puDataToSend);

   	}


}

