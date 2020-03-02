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
#include "string.h"
#include "time.h"
#include "stdbool.h"

typedef unsigned char       UINT8;
#define MODEM_GPS_ACQUIRE_PRESENTER		        "$GPSACP:"
// $GPRMC,000231.42,A,4829.0005,N,00022.0016,E,0.16,212.28,220899,,,A*59

void getCorrectedDate(int year, int month, int day, char * date);
typedef struct
{

}tt;
int main(void) {
     char* pu8Token, *ptr;
	 UINT8 u8Fix = 0, u8Counter = 0;
//	 UINT8 u8Data[255]= {"$GPRMC,000231.42,A,4829.0005,N,00022.0016,E,0.16,212.28,220899,,,A*59"};
//	 UINT8 u8Data[255]= {" $GPSACP: 080220.479,4542.82691N,01344.26820E,259.07,3,2.1,0.1,0.0,0.0,270705,09\r\n"};
	 // 220899
	 // 2208-1

//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,240113,04"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,2208-1,04"};
//	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,270899,04"};
	 UINT8 u8Data[255]= {" $GPSACP: 012647.000,2728.3033S,15302.3369E,1.50,-52.0,3,156.66,0.00,0.00,270700,04"};

	 UINT8 u8UTCTime[15];
	 UINT8 u8UTCDate[10];
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
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
bool isWrongDate1 = 	strstr((char*) u8UTCDate, (char*) "99") != NULL || strstr((char*) u8UTCDate, (char*) "-1") != NULL;
UINT8 tmp[3];
     tmp[0]= u8UTCDate[4];
     tmp[1]= u8UTCDate[5];
     tmp[2]= '\0';
     int t = atoi((char *)tmp);

bool     isWrongDate2 =  (t < 19);

    if(isWrongDate1 || isWrongDate2)
    {
    	   UINT8 u8Year[3], u8Month[3], u8Day[3];
    	   int year;

    	   if(isWrongDate1){
    		   u8Year[0]  = '9';
    		   u8Year[1]  = '9';
    		   year = atoi((char*)u8Year) + 1900;
    	   }else {
    		   u8Year[0]= u8UTCDate[4];
               u8Year[1]= u8UTCDate[5];
               year = atoi((char*)u8Year) + 2000;
    	   }

    	   u8Month[0] = u8UTCDate[2];
    	   u8Month[1] = u8UTCDate[3];
    	   u8Day[0]  = u8UTCDate[0];
    	   u8Day[1]  = u8UTCDate[1];
    	getCorrectedDate( year, atoi((char*)u8Month), atoi((char*)u8Day),  (char *)u8UTCDate);
       printf(" %s \r\n", u8UTCDate);
    }

	return EXIT_SUCCESS;

}


void getCorrectedDate(int year, int month, int day, char * date)
{

struct tm t = { .tm_year=year-1900, .tm_mon=month-1, .tm_mday=day };

    char u8Year[10];
    char u8Month[10];
    char u8Day[10];
    char u8Date[10];

    memset(u8Year, '0', sizeof(u8Year));
    memset(u8Month, '0', sizeof(u8Month));
    memset(u8Day, '0', sizeof(u8Day));
    memset(u8Date, '0', sizeof(u8Day));

	t.tm_mday += 7168;
	mktime(&t);

    printf("%s \r\n", asctime(&t));
    UINT8 y = t.tm_year - 100;
    UINT8 m = t.tm_mon +1;
    UINT8 d = t.tm_mday;

    printf("-- y: %d  m: %d d: %d \r\n", y, m, d);

     itoa(y, u8Year, 10);
     itoa(m, u8Month, 10);
     itoa(d, u8Day, 10);

     if(d < 10)
     {
    	u8Day[1] = u8Day[0];
    	u8Day[0] = '0';
     }

     if(m < 10)
     {
    	u8Month[1] = u8Month[0];
    	u8Month[0] = '0';
     }

    printf(" %s \r\n", u8Year);
    printf(" %s \r\n", u8Month);
    printf(" %s \r\n", u8Day);
    	   u8Date[5]  = u8Year[1];
    	   u8Date[4]  = u8Year[0];
    	   u8Date[3] = u8Month[1];
    	   u8Date[2] = u8Month[0];
    	   u8Date[1]  = u8Day[1];
    	   u8Date[0]  = u8Day[0];
    	   u8Date[6]  = '\0';
    printf(" %s \r\n", u8Date);
    strncpy((char*)date, (char*)u8Date, strlen((char*)u8Date)+1);

}









