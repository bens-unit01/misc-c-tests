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
void getCorrectedDate(char * utcDate);
int testFilter(void);
bool GPSPointConvertUTCToUNIX(PUINT8 pu8UTCDate, PUINT8 pu8UTCTime, PUINT32 pu32Unix);

typedef struct
{

}tt;


int main(void) {

// 	testGpsParsing();
	testFilter();
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

   // Ann�e sauf l'ann�e en cours
   TimeInSeconds =  (UINT32)RTCYear * RTC_SECONDS_PER_YEAR;

   // Journ�es additionnelles pour ann�es bissextiles (en plus de l'ann�e bissextile de 2000)
   // sauf pour l'annee en cours
   if (RTCYear > 0)
      TimeInSeconds += (UINT32)(((RTCYear - 1) / 4) + 1) * RTC_SECONDS_PER_DAY;

   // Mois sans le mois en cours
   for (i=0; i<RTCMonth; ++i)
   {
      TimeInSeconds += (UINT32)RTC_DAYS_PER_MONTH[i] * RTC_SECONDS_PER_DAY;
   }

   // Journ�e additionnelle si l'ann�e en cours est bissextile et qu'on est pass� le 28 f�vrier
   if ((RTCMonth > 1) && (RTCYear % 4 == 0))
      TimeInSeconds += RTC_SECONDS_PER_DAY;

  // Jours sans la journ�e en cours
  TimeInSeconds += (UINT32)(RTCDay - 1) * RTC_SECONDS_PER_DAY;

  // Journ�e en cours
  TimeInSeconds += (UINT32)RTCHours * RTC_SECONDS_PER_HOUR;
  TimeInSeconds += (INT32)RTCMinutes * RTC_SECONDS_PER_MINUTE;
  TimeInSeconds += RTCSeconds;

  // Retourner le r�sultat incr�ment� du nombre de secondes �coul� entre
  // le 01/01/1970 et le 01/01/2000
  *pu32Unix = TimeInSeconds + RTC_SECONDS_FROM_UNIX_EPOCH_TO_Y2K;

   return (*pu32Unix != -1);
}








