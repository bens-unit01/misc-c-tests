/*
 ============================================================================
 Name        : d-tests.c
 Author      : Raouf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "string.h"
#include "time.h"
#include "stdbool.h"

typedef unsigned char       UINT8;
typedef unsigned char *     PUINT8;
typedef unsigned long int   UINT32;
typedef signed long int     INT32;
typedef unsigned long int * PUINT32;
typedef signed short int    INT16;


#define RTC_SECONDS_FROM_UNIX_EPOCH_TO_Y2K	        946684800
#define RTC_SECONDS_PER_MINUTE			        60
#define RTC_SECONDS_PER_HOUR				3600
#define RTC_SECONDS_PER_DAY				86400
#define RTC_SECONDS_PER_YEAR				31536000
static INT16 const RTC_DAYS_PER_MONTH[12]		= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#define MODEM_GPS_ACQUIRE_PRESENTER		        "$GPSACP:"
// $GPRMC,000231.42,A,4829.0005,N,00022.0016,E,0.16,212.28,220899,,,A*59

int testGpsParsing(void);
int testFilter(void);
int testCrc(void);
int testCalcInt(void);
int testParsingAce(void);


bool GPSPointConvertUTCToUNIX(PUINT8 pu8UTCDate, PUINT8 pu8UTCTime, PUINT32 pu32Unix);
void getCorrectedDate(char * utcDate);

typedef struct
{

}tt;


int main(void) {

// 	testGpsParsing();
//	testFilter();
//	testCrc();
//	testCalcInt();
	testParsingAce();
}

int testCalcInt(void){

UINT8 a = 5, b = 3;
   printf("1- (double)(a/b) : %f \r\n", (double)(a/b));
   printf("2- (double)a/b   : %f \r\n", (double)a/b);
   printf("3- (float)a/b    : %f \r\n", (float)a/b);
   printf("4- (float)a/b    : %.3f \r\n", (float)a/b);

   return 1;
}



char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

char * __strsep (char **stringp, const char *delim)
{
  char *begin, *end;
  begin = *stringp;
  if (begin == NULL)
    return NULL;
  // Find the end of the token.
  end = begin + strcspn (begin, delim);
  if (*end)
    {
//       Terminate the token and set *STRINGP past NUL character.
      *end++ = '\0';
      *stringp = end;
    }
  else
    // No more delimiters; this is the last token.
    *stringp = NULL;
  return begin;
}

void aceParseData(char* in)
{
   char* t2 = in;
   char sep[] = ";";
   char* token = strsep(&t2, sep);
   printf(" token: %s   \r\n", token);
   int pr = atoi(token);
   switch(pr)
   {
   case 0 :
	   // Time synchronization record
       token = strsep(&t2, sep);
       printf(" Version: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" SysTime: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" SysDate: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" Source: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" check: %s   \r\n", token);


       token = strsep(&t2, sep);
	   break;
   case 1 :
	   // Standard header record
	   printf("case 1: ------\n");

       token = strsep(&t2, sep);
       printf(" Version: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" SysTime: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" SysDate: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" Source: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" ManufID: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" EquipID: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" DriverID: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" Check: %s   \r\n", token);

	   break;
   case 8 :
	   // Spreader data record
	   printf("case 8: ------\n");

       token = strsep(&t2, sep);
       printf(" ManufID: %s   \r\n", token);

       token = strsep(&t2, sep);
       printf(" EquipID: %s   \r\n", token);

       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" Source: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SysTime: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SysDate: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprMode: %s   \r\n", token);


       token = strsep(&t2, sep); // SprSimSpd
       token = strsep(&t2, sep); // SprWidthSet
       token = strsep(&t2, sep);
       token = strsep(&t2, sep); // SprDosSet
       token = strsep(&t2, sep);
       printf(" SprWidth: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" SprDosRes1: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" SprBrinePerc: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprMaxOn: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprCntRes1: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" SprCntBrineKg: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprCntLen: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" DrivenLen: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" VehSpd: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprErr: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprErrCode: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" SprErrRpt: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" SprMatRes1: %s   \r\n", token);


       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       token = strsep(&t2, sep);
       printf(" FreeDef1: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" FreeDef2: %s   \r\n", token);


       token = strsep(&t2, sep);
       printf(" Check: %s   \r\n", token);



	   break;
   default:
	   printf("not supported \r\n");
	   break;
   }

}

int testParsingAce(void)
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

   char buf0[] = {"0;10;1556036;0521132;5"};
   char buf1[] = {"1;10;1556036;0521132;5;aceelectronic.ca;0000783FFF24;8888888888888888"};
   char buf2[] = {"8;aceelectronic.ca;0000783FFF24;;5;1617088;0521132;0;;1.0;;30;8;;;;;;20;0;2462;;;246;5394375;;1910;;36;0;;;;;;;02MAT A;;;;;;;;;;;;;;;;U3V46R0H21;M2-G0-DP1-DS1-SS00OFF"};
   puts("Ace parsing test - unit tests ... \r\n");
   printf("buf0: %s \n", buf0);
   printf("buf1: %s \n", buf1);
   printf("buf2: %s \n", buf2);

   aceParseData((char *)buf0);
   aceParseData((char *)buf1);
   aceParseData((char *)buf2);

	return 1;
}

int testFilter(void){

	float fFuelLevelFilterFast = 67.0;
	int uFuelLevelFilterFast = 67;
	int uFuelLevel = 125;

	puts("Filter test - unit tests ... \r\n");

	for(int i=0; i < 60; i++)
	{
	   uFuelLevelFilterFast = (UINT8) (((uFuelLevelFilterFast * 3) + uFuelLevel) >> 2);
	   fFuelLevelFilterFast = ((((fFuelLevelFilterFast * 5.0) + uFuelLevel) / 6.0)) + 0.001;
	   printf(" %u-\t%u %u %.3f \r\n", i, uFuelLevelFilterFast, (int)fFuelLevelFilterFast, fFuelLevelFilterFast);
	}

	return 1;
}

///* http://www.ccsinfo.com/forum/viewtopic.php?t=24977 */
unsigned short crc16(const unsigned char *buf, unsigned long count)
{
//        unsigned short crc = 0;
        unsigned short crc = 0xFFFF;
        int i;
        int j = 0, k = 0;
        while(count--) {
                printf(" %d 0x%x 0x%x - ", crc, crc, *buf);
                crc = crc ^ *buf++ << 8;

                for (i=0; i<8; i++) {
                        if (crc & 0x8000) {
                                crc = crc << 1 ^ 0x1021;
                                j++;
                        } else {
                                crc = crc << 1;
                                k++;
                        }
                }
        }
        printf("\n ---------------- %d %d \n", j, k);
        return crc;
}

void VimsAsciiToHex(PUINT8 pu8RxData, PUINT8 pu8Size)
{
	UINT32 u32TempData;
	UINT8 u8Index;

	for(u8Index =0; u8Index < *pu8Size; u8Index += 2)
	{
		sscanf((char*)(pu8RxData + u8Index), "%2x", &u32TempData);
		*(pu8RxData + (u8Index/2)) = (UINT8)u32TempData;
	}
	*pu8Size /= 2;
}

int testCrc(void){
// \0010;10;1556036;0521132;5\r\n2476\004
const unsigned char buf1[] = {0x30,  0x3b, 0x31, 0x30, 0x3b, 0x31, 0x35, 0x35,  0x36, 0x30, 0x33, 0x36, 0x3b, 0x30, 0x35, 0x32, 0x31, 0x31, 0x33, 0x32, 0x3b, 0x35, 0x0d, 0x0a};

// 8;aceelectronic.ca;123456789123;;5;1556036;0521132;0;;0.0;;0;0;;0;;;;20;0;0;;;0;0;;0;;0;0;;;;;;;02MAT A", ';' <repeats 16 times>, "U3V46R0H21;M0-G0-DP1-DS1-SS00OFF\r\n
const unsigned char buf2[] = {0x38, 0x3b, 0x61, 0x63, 0x65, 0x65, 0x6c, 0x65 , 0x63, 0x74, 0x72, 0x6f, 0x6e, 0x69, 0x63, 0x2e,
		0x63, 0x61, 0x3b, 0x31, 0x32, 0x33, 0x34, 0x35,  0x36, 0x37, 0x38, 0x39, 0x31, 0x32, 0x33, 0x3b,
		0x3b, 0x35, 0x3b, 0x31, 0x35, 0x35, 0x36, 0x30 , 0x33, 0x36, 0x3b, 0x30, 0x35, 0x32, 0x31, 0x31,
		0x33, 0x32, 0x3b, 0x30, 0x3b, 0x3b, 0x30, 0x2e , 0x30, 0x3b, 0x3b, 0x30, 0x3b, 0x30, 0x3b, 0x3b,
		0x30, 0x3b, 0x3b, 0x3b, 0x3b, 0x32, 0x30, 0x3b,  0x30, 0x3b, 0x30, 0x3b, 0x3b, 0x3b, 0x30, 0x3b,
		0x30, 0x3b, 0x3b, 0x30, 0x3b, 0x3b, 0x30, 0x3b,  0x30, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b,
		0x30, 0x32, 0x4d, 0x41, 0x54, 0x20, 0x41, 0x3b,  0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b,
		0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x55,  0x33, 0x56, 0x34, 0x36, 0x52, 0x30, 0x48, 0x32,
		0x31, 0x3b, 0x4d, 0x30, 0x2d, 0x47, 0x30, 0x2d,  0x44, 0x50, 0x31, 0x2d, 0x44, 0x53, 0x31, 0x2d,
		0x53, 0x53, 0x30, 0x30, 0x4f, 0x46, 0x46, 0x0d, 0x0a};

// \0018;aceelectronic.ca;123456789123;;5;1556036;0521132;0;;0.0;;0;0;;0;;;;20;0;0;;;0;0;;0;;0;0;;;;;;;02MAT A", ';' <repeats 16 times>, "U3V46R0H21;M0-G0-DP1-DS1-SS00OFF\r\n6777\004
const unsigned char buf3[] = {0x01, 0x38, 0x3b, 0x61, 0x63, 0x65, 0x65, 0x6c, 0x65 , 0x63, 0x74, 0x72, 0x6f, 0x6e, 0x69, 0x63, 0x2e,
		0x63, 0x61, 0x3b, 0x31, 0x32, 0x33, 0x34, 0x35,  0x36, 0x37, 0x38, 0x39, 0x31, 0x32, 0x33, 0x3b,
		0x3b, 0x35, 0x3b, 0x31, 0x35, 0x35, 0x36, 0x30 , 0x33, 0x36, 0x3b, 0x30, 0x35, 0x32, 0x31, 0x31,
		0x33, 0x32, 0x3b, 0x30, 0x3b, 0x3b, 0x30, 0x2e , 0x30, 0x3b, 0x3b, 0x30, 0x3b, 0x30, 0x3b, 0x3b,
		0x30, 0x3b, 0x3b, 0x3b, 0x3b, 0x32, 0x30, 0x3b,  0x30, 0x3b, 0x30, 0x3b, 0x3b, 0x3b, 0x30, 0x3b,
		0x30, 0x3b, 0x3b, 0x30, 0x3b, 0x3b, 0x30, 0x3b,  0x30, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b,
		0x30, 0x32, 0x4d, 0x41, 0x54, 0x20, 0x41, 0x3b,  0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b,
		0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x55,  0x33, 0x56, 0x34, 0x36, 0x52, 0x30, 0x48, 0x32,
		0x31, 0x3b, 0x4d, 0x30, 0x2d, 0x47, 0x30, 0x2d,  0x44, 0x50, 0x31, 0x2d, 0x44, 0x53, 0x31, 0x2d,
		0x53, 0x53, 0x30, 0x30, 0x4f, 0x46, 0x46, 0x0d, 0x0a, 0x36, 0x37, 0x37, 0x37, 0x04};

unsigned char buf4[4] = {0};

  int res1 = crc16(buf1, sizeof(buf1));
  printf(" buf size:  %d res : %d 0x%x \n", sizeof(buf1), res1, res1);

  printf("\n\n");

  int res2 = crc16(buf2, sizeof(buf2));
  printf(" buf size:  %d res : %d 0x%x \n", sizeof(buf2), res2, res2);

  int res3 = crc16(buf3 +1, sizeof(buf3) -6);
   printf(" buf size:  %d res : %d 0x%x \n", sizeof(buf3), res3, res3);

  const char st1[] = {'6', '7', '7', '7', '\0'};
  printf(" 1-  %s \n", st1);
 // VimsAsciiToHex(st, &size);
  printf(" 2-  %d  \n", atoi(st1));
  int number1 = (int)strtol(st1, NULL, 16);
  printf(" 3-  %d  \n", number1);

  const char st2[] = {',', '!', '7', '-', '\0'};
  int number2 = (int)strtol(st2, NULL, 16);
  printf(" 4-  %d  \n", number2);


  memcpy(buf4, buf3 + (sizeof(buf3) -5), 4);
  int number3 = (int)strtol((const char *)buf4, NULL, 16);
  printf(" 5-  0x%x  \n", number3);

  const char src[50] = "http://www.tutorialspoint.com";
  char dest1[50];
  char dest2[5] = {0};
  strcpy(dest1,"Heloooo!!");
  printf("Before memcpy dest = %s\n", dest1);

  memcpy(dest1, (src + 5), strlen(src)+1);
  memcpy(dest2, (buf3 + (sizeof(buf3) -5)), 4);

  printf("After memcpy dest1 = %s\n", dest1);
  printf("After memcpy dest2 = %s\n", dest2);

  return 0;
}

int testGpsParsing(void)
{
     char* pu8Token, *ptr;
	 UINT8 u8Fix = 0, u8Counter = 0;
//	 UINT8 u8Data[255]= {"$GPRMC,000231.42,A,4829.0005,N,00022.0016,E,0.16,212.28,220899,,,A*59"};
//	 UINT8 u8Data[255]= {" $GPSACP: 080220.479,4542.82691N,01344.26820E,259.07,3,2.1,0.1,0.0,0.0,270705,09\r\n"};
	 // 220899
	 // 2208-1

//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,240113,04"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,2308-1,04"};
	 UINT8 u8Data[255]= {"$GPSACP: 135427.000,4532.3023N,07339.4856W,1.50,57.0,3,213.18,1.05,0.56,0040618,05"};

//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,220805,04"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,290216,04"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,150709,04"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,220801,01"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,27070,04"};





	 UINT8 t1 = 0;
	 UINT8 t2 = 255;
	 printf("-- res: %d \r\n", t1 - t2);
	 UINT8 u8UTCTime[15];
	 UINT8 u8UTCDate[10];

	puts("GPS string parsing unit tests ... \r\n");
	printf((const char *)u8Data);
	printf("\r\n");


	if(strstr((char*)u8Data, (char*)MODEM_GPS_ACQUIRE_PRESENTER) == NULL)
	{
		printf(" error 1 \r\n");
	}
	else
	{
		printf(" success 1 \r\n");
	}

	   ptr = strchr((char*)u8Data, ',');
	   while(ptr != NULL)
	   {
	      u8Counter++;
	      ptr = strchr((char*)ptr + 1, ',');
	   }

	if(u8Counter != 10) {
		printf(" error 2 - count : %d \r\n", u8Counter);
	} else {
		printf(" success 2 \r\n");
	}

	   // Parse
	      pu8Token = strtok((char*)u8Data, (char*)" ");
	      pu8Token++;
	      pu8Token++;

	      // UTC
	      pu8Token = strtok(NULL, (char*)",");
	      strncpy((char*)u8UTCTime, (char*)pu8Token, strlen((char*)pu8Token)+1);

      printf((const char*)u8UTCTime);
      printf("\r\n");

	      pu8Token = strtok(NULL, (char*)","); // lat
	      pu8Token = strtok(NULL, (char*)","); // lon
	      pu8Token = strtok(NULL, (char*)","); // dilution HDOP
	      pu8Token = strtok(NULL, (char*)","); // Altitude
	      pu8Token = strtok(NULL, (char*)","); // Fix

	      u8Fix = atoi((char*)pu8Token);
      printf("u8Fix : %d \r\n", u8Fix);

	      pu8Token = strtok(NULL, (char*)",");
	      pu8Token = strtok(NULL, (char*)",");
	      pu8Token = strtok(NULL, (char*)",");
	      pu8Token = strtok(NULL, (char*)",");

	      strncpy((char*)u8UTCDate, (char*)pu8Token, strlen((char*)pu8Token)+1);

	  printf(" -- %c%c \r\n", u8UTCDate[4], u8UTCDate[5]);
	  printf("\r\n");
      printf((const char*)u8UTCDate);
	  printf("\r\n");

	char * str = strstr((char*) u8UTCDate, (char*) "99");
	if(str != NULL)
	{
		printf(str);
	    printf("\r\n");
	}
	else
	{
		printf("null \r\n");
	}

//    getCorrectedDate((char *) u8UTCDate);
    getCorrectedDate("0230805");
    getCorrectedDate("30805");
    getCorrectedDate("");
    printf("final result %s \r\n", u8UTCDate);


    UINT32 u32UnixTimestamp = 0;

    GPSPointConvertUTCToUNIX(u8UTCDate, u8UTCTime, &u32UnixTimestamp);

    printf("Unix timestamp : %u \r\n", (unsigned int)u32UnixTimestamp);

	return EXIT_SUCCESS;

}


void getCorrectedDate(char * utcDate)
{

	char acYear[3];
	char acMonth[3];
	char acDay[3];
	char acDate[10];

	size_t s = strlen(utcDate);
	if(s != 6)
	{
		printf( " --------- wrong date string lenght s: %d \r\n",s );
		return;
	}

	memset(acYear, '0', sizeof(acYear));
	memset(acMonth, '0', sizeof(acMonth));
	memset(acDay, '0', sizeof(acDay));
	memset(acDate, '0', sizeof(acDay));

	// We check if the year value is 99 or -1
	bool isWrongDate1 = strstr((char*) utcDate, (char*) "99") != NULL || strstr((char*) utcDate, (char*) "-1") != NULL;

	// We check if the year is between 2000 and 2018
	char tmpBuf[3];
	tmpBuf[0] = utcDate[4];
	tmpBuf[1] = utcDate[5];
	tmpBuf[2] = '\0';
	bool isWrongDate2 = (atoi(tmpBuf) < 19);
//	bool isWrongDate2 = (atoi(tmpBuf) < 29);

	  printf("[M] -------------------- Wrong date detected - date:  %s \r\n", acDate);
	// If the date is Ok, we don't change it
	if (isWrongDate1 || isWrongDate2) {
		UINT8 auYear[3], auMonth[3], auDay[3];
		int year, month, day;
       // extracting the day, month and the year
		if (isWrongDate1) {
			year = atoi((char*)"99") + 1900;
		} else {
			auYear[0] = utcDate[4];
			auYear[1] = utcDate[5];
			year = atoi((char*) auYear) + 2000;
		}

		auMonth[0] = utcDate[2];
		auMonth[1] = utcDate[3];
		auDay[0] = utcDate[0];
		auDay[1] = utcDate[1];

		struct tm t1 = { .tm_year = year - 1900, .tm_mon = atoi((char*) auMonth) - 1, .tm_mday =  atoi((char*) auDay) };


		// We add 1024 weeks (1024 * 7 days)
		t1.tm_mday += 7168;
		mktime(&t1);

		year = t1.tm_year - 100;
		month = t1.tm_mon + 1;
		day = t1.tm_mday;

        // converting the date back as a GPS date
	/*	itoa(year, acYear, 10);
		itoa(month, acMonth, 10);
		itoa(day, acDay, 10);
*/
		// snprintf (buff, sizeof(buf), "%d",n);
		snprintf((char*)acYear, sizeof(acYear), "%d", year);
		snprintf((char*)acMonth, sizeof(acMonth), "%d", month);
		snprintf((char*)acDay, sizeof(acDay), "%d", day);

		if (day < 10) {
			acDay[1] = acDay[0];
			acDay[0] = '0';
		}

		if (month < 10) {
			acMonth[1] = acMonth[0];
			acMonth[0] = '0';
		}

		acDate[5] = acYear[1];
		acDate[4] = acYear[0];
		acDate[3] = acMonth[1];
		acDate[2] = acMonth[0];
		acDate[1] = acDay[1];
		acDate[0] = acDay[0];
		acDate[6] = '\0';
		printf(" --+ %s \r\n", acDate);
		   printf("[M] -------------------- Date fixed %s \r\n", acDate);
		strncpy((char*) utcDate, (char*) acDate, strlen((char*) acDate) + 1);
	}
}



bool GPSPointConvertUTCToUNIX(PUINT8 pu8UTCDate, PUINT8 pu8UTCTime, PUINT32 pu32Unix)
{
   UINT8 RTCYear, RTCMonth, RTCDay, RTCHours, RTCMinutes, RTCSeconds;
   UINT32 TimeInSeconds;
   INT16 i=1;
   UINT8 u8Year[3], u8Month[3], u8Day[3], u8Hour[3], u8Min[3], u8Sec[3];

   memset(u8Year, 0, sizeof(u8Year));
   memset(u8Month, 0, sizeof(u8Month));
   memset(u8Day, 0, sizeof(u8Day));
   memset(u8Hour, 0, sizeof(u8Hour));
   memset(u8Min, 0, sizeof(u8Min));
   memset(u8Sec, 0, sizeof(u8Sec));

   u8Year[0] = pu8UTCDate[4];
   u8Year[1] = pu8UTCDate[5];
   u8Month[0] = pu8UTCDate[2];
   u8Month[1] = pu8UTCDate[3];
   u8Day[0] = pu8UTCDate[0];
   u8Day[1] = pu8UTCDate[1];
   u8Hour[0] = pu8UTCTime[0];
   u8Hour[1] = pu8UTCTime[1];
   u8Min[0] = pu8UTCTime[2];
   u8Min[1] = pu8UTCTime[3];
   u8Sec[0] = pu8UTCTime[4];
   u8Sec[1] = pu8UTCTime[5];

   RTCYear = atoi((char*)u8Year);
   RTCMonth = atoi((char*)u8Month) - 1;
   RTCDay = atoi((char*)u8Day);
   RTCHours = atoi((char*)u8Hour);
   RTCMinutes = atoi((char*)u8Min);
   RTCSeconds = atoi((char*)u8Sec);

   // Année sauf l'année en cours
   TimeInSeconds =  (UINT32)RTCYear * RTC_SECONDS_PER_YEAR;

   // Journées additionnelles pour années bissextiles (en plus de l'année bissextile de 2000)
   // sauf pour l'annee en cours
   if (RTCYear > 0)
      TimeInSeconds += (UINT32)(((RTCYear - 1) / 4) + 1) * RTC_SECONDS_PER_DAY;

   // Mois sans le mois en cours
   for (i=0; i<RTCMonth; ++i)
   {
      TimeInSeconds += (UINT32)RTC_DAYS_PER_MONTH[i] * RTC_SECONDS_PER_DAY;
   }

   // Journée additionnelle si l'année en cours est bissextile et qu'on est passé le 28 février
   if ((RTCMonth > 1) && (RTCYear % 4 == 0))
      TimeInSeconds += RTC_SECONDS_PER_DAY;

  // Jours sans la journée en cours
  TimeInSeconds += (UINT32)(RTCDay - 1) * RTC_SECONDS_PER_DAY;

  // Journée en cours
  TimeInSeconds += (UINT32)RTCHours * RTC_SECONDS_PER_HOUR;
  TimeInSeconds += (INT32)RTCMinutes * RTC_SECONDS_PER_MINUTE;
  TimeInSeconds += RTCSeconds;

  // Retourner le résultat incrémenté du nombre de secondes écoulé entre
  // le 01/01/1970 et le 01/01/2000
  *pu32Unix = TimeInSeconds + RTC_SECONDS_FROM_UNIX_EPOCH_TO_Y2K;

   return (*pu32Unix != -1);
}








