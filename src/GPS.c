/*
 * GPS.c
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */

#include "GPS.h"

#define MODEM_GPS_ACQUIRE_PRESENTER		        "$GPSACP:"


#define RTC_SECONDS_FROM_UNIX_EPOCH_TO_Y2K	        946684800
#define RTC_SECONDS_PER_MINUTE			        60
#define RTC_SECONDS_PER_HOUR				3600
#define RTC_SECONDS_PER_DAY				86400
#define RTC_SECONDS_PER_YEAR				31536000
#define GET_UNITS_STR(i)  ((i % 10) + '0')
#define GET_TENS_STR(i) ((((i % 100)- (i %10)) / 10) + '0')
static INT16 const RTC_DAYS_PER_MONTH[12]		= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// private functions
static bool GPSPointConvertUTCToUNIX(PUINT8 pu8UTCDate, PUINT8 pu8UTCTime, PUINT32 pu32Unix);
static void getCorrectedDate(char * utcDate);
static bool gpsPointStringExtractToken(IN const char* pszTokenStart,
                                       OUT const char** ppszNextToken,
                                       OUT char* pszTokenDestination,
                                       IN unsigned int uDestinationSize);

typedef struct
{
   UINT8 u8UTCTime[15];
   UINT8 u8Status;
   UINT8 u8Latitude[15];
   UINT8 u8LatitudeLocation;
   UINT8 u8Longitude[15];
   UINT8 u8LongitudeLocation;
   UINT8 u8GroundSpeed[10];
   UINT8 u8CourseOverGround[10];
   UINT8 u8UTCDate[10];
   UINT8 u8NavStat[3];
   UINT8 u8Hacc[10];
   UINT8 u8Vacc[10];
   UINT8 u8HDOP[10];
   UINT8 u8VDOP[10];
   UINT8 u8NumSvs[10];
}GPSPointStringTy, *pGPSPointStringTy;


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

    //getCorrectedDate((char *) u8UTCDate);
    getCorrectedDate("0230805");
    getCorrectedDate("30805");
    getCorrectedDate("");
    printf("final result %s %s\r\n", u8UTCDate, u8UTCTime);


    UINT32 u32UnixTimestamp = 0;

    GPSPointConvertUTCToUNIX(u8UTCDate, u8UTCTime, &u32UnixTimestamp);
    printf("Unix timestamp 01: %u \r\n", (unsigned int)u32UnixTimestamp);

    GPSPointConvertUTCToUNIX("200121", "165249.000", &u32UnixTimestamp);
    printf("Unix timestamp 02: %u \r\n", (unsigned int)u32UnixTimestamp);

    int year = 2021;
    int month = 1;
    int day = 20;
    int hours = 16;
    int min = 52;
    int sec = 49;

    char szDate[7] = {'\0'};  // Date format ddmmyy
    szDate[5] = GET_UNITS_STR(year);
    szDate[4] = GET_TENS_STR(year);
    szDate[3] = GET_UNITS_STR(month);
    szDate[2] = GET_TENS_STR(month);
    szDate[1] = GET_UNITS_STR(day);
    szDate[0] = GET_TENS_STR(day);

    char szTime[7] = {'\0'};  // Time format hhmmss
    szTime[5] = GET_UNITS_STR(sec);
    szTime[4] = GET_TENS_STR(sec);
    szTime[3] = GET_UNITS_STR(min);
    szTime[2] = GET_TENS_STR(min);
    szTime[1] = GET_UNITS_STR(hours);
    szTime[0] = GET_TENS_STR(hours);


    printf("Date : %s %s\n", szDate, szTime);
    GPSPointConvertUTCToUNIX(szDate, szTime, &u32UnixTimestamp);
    printf("Unix timestamp 03: %u \r\n", (unsigned int)u32UnixTimestamp);


	return EXIT_SUCCESS;

}



int testGpsPUBXParsing(void)
{
    UINT8 u8Data[] = "$PUBX,00,155900.00,4531.82930,N,07329.44138,W,-8.970,G3,8.3,13,0.314,58.22,-0.072,,2.39,3.74,3.22,5,0,0*6D";
    UINT8 u8DataTime[] = "$PUBX,04,031857.00,040221,357537.00,2143,18,-38493,-970.508,21*2C";


   gpsPUBXParsing(u8Data, u8DataTime);
}

int gpsPUBXParsing(uint8_t* u8Data, uint8_t* u8DataTime)
{
#define NMEA_INVALID_FIX_STR	",,,,,"

	printf("PUBX parsing test \n");
	printf(" input: %s\n", u8Data);
    GPSPointStringTy _GPSPointString;

       bool bStringIsComplete = false;

       memset(&_GPSPointString, 0, sizeof(_GPSPointString));


       if (true)
       {
          bool bParsingError = true;
          bool bPositionIsValid = false;

          // Clear variables

//          if (gpsPollPUBXString(this, u8Data, sizeof(u8Data), u8Command))
          if (true)
          {

              char aszTempOneCharString[2] = {0};

    #ifdef DEBUG_GPS_ENABLED
             printf("[GPS] GpsPointUpdate string from GPS is: \"%s\"!\n", u8Data);
    #endif


             // Here, we know we have a PUBX string in u8Data; parse it.

             // See if the message contains invalid data. In case the message contains
             // invalid data, the UTC time and date can be valid (which is why the
             // processing continues).
             bPositionIsValid = strstr((char*)u8Data, (char*)NMEA_INVALID_FIX_STR) == NULL;

             const char* pszTokenStart = (char*)u8Data;

             //== Field "$PUBX, 00"
             // Start parsing NMEA PUBX string, discard the "$PUBX," token and the class token "00" as well
             if ((gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT NULL, 16) == false) ||
                   (gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT NULL, 16) == false))

             {
    #ifdef DEBUG_GPS_ENABLED
                printf("[GPS] GpsPointUpdate xxRMC skipping failed!\r\n", u8Data);
    #endif
             }
             //== Field time - UTC
             else if (gpsPointStringExtractToken(pszTokenStart,
                                                 OUT &pszTokenStart,
                                                 OUT (char*)_GPSPointString.u8UTCTime,
                                                 sizeof(_GPSPointString.u8UTCTime)) == false)
             {
    #ifdef DEBUG_GPS_ENABLED
                printf("[GPS] GpsPointUpdate time extraction failed!\r\n");
    #endif

                // Parsing error; stop processing.
             }
             else if (_GPSPointString.u8UTCTime[0] == '\0')
             {
                // The field is empty; position is invalid.
                bPositionIsValid = false;

                // Empty token is not a parsing error.
                bParsingError = false;

                // The time field cannot be processed so nothing else can be useful
                // in the string; skip the remaining parsing.
             }
             else
             {


                //== Field lat - Latitude
                if (gpsPointStringExtractToken(pszTokenStart,
                                               OUT &pszTokenStart,
                                               OUT (char*)_GPSPointString.u8Latitude,
                                               sizeof(_GPSPointString.u8Latitude)) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate lat extraction failed!\r\n");
    #endif

                   // Parsing error; stop processing.
                }
                else
                {
                   if (_GPSPointString.u8Latitude[0] == '\0')
                   {
                      // The field is empty; position is invalid.
                      bPositionIsValid = false;
                   }

                   //== Field NS - Latitude N or S
                   if (gpsPointStringExtractToken(pszTokenStart,
                                                  OUT &pszTokenStart,
                                                  OUT aszTempOneCharString,
                                                  sizeof(aszTempOneCharString)) == false ||
                       ('N' != aszTempOneCharString[0] && 'S' != aszTempOneCharString[0] &&
                        '\0' != aszTempOneCharString[0]))
                   {
    #ifdef DEBUG_GPS_ENABLED
                      printf("[GPS] GpsPointUpdate NS extraction failed ('%c')!\r\n",
                             aszTempOneCharString[0]);
    #endif

                      // Parsing error; stop processing.
                   }
                   else
                   {
                      if (aszTempOneCharString[0] == '\0')
                      {
                         // The field is empty; position is invalid.
                         bPositionIsValid = false;
                      }
                      else
                      {
                         _GPSPointString.u8LatitudeLocation = aszTempOneCharString[0];
                      }

                      //== Field long - Longitude
                      if (gpsPointStringExtractToken(pszTokenStart,
                                                     OUT &pszTokenStart,
                                                     OUT (char*)_GPSPointString.u8Longitude,
                                                     sizeof(_GPSPointString.u8Longitude)) == false)
                      {
    #ifdef DEBUG_GPS_ENABLED
                         printf("[GPS] GpsPointUpdate long extraction failed!\r\n");
    #endif

                         // Parsing error; stop processing.
                      }
                      else
                      {
                         if (_GPSPointString.u8Longitude[0] == '\0')
                         {
                            // The field is empty; position is invalid.
                            bPositionIsValid = false;
                         }

                         //== Field EW - Longitude E or W
                         if (gpsPointStringExtractToken(pszTokenStart,
                                                        OUT &pszTokenStart,
                                                        OUT aszTempOneCharString,
                                                        sizeof(aszTempOneCharString)) == false ||
                             ('E' != aszTempOneCharString[0] && 'W' != aszTempOneCharString[0] &&
                              '\0' != aszTempOneCharString[0]))
                         {
    #ifdef DEBUG_GPS_ENABLED
                            printf("[GPS] GpsPointUpdate EW extraction failed ('%c')!\r\n",
                                   aszTempOneCharString[0]);
    #endif

                            // Parsing error; stop processing.
                         }
                         else
                         {
                            if (aszTempOneCharString[0] == '\0')
                            {
                               // The field is empty; position is invalid.
                               bPositionIsValid = false;
                            }
                            else
                            {
                               _GPSPointString.u8LongitudeLocation = aszTempOneCharString[0];
                               bParsingError = false;
                            }
                         }
                      }
                   }
                }
             }

             if(!bParsingError)
             {
                //== Field altRef
                if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT NULL, 16) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate altRef skipping failed!\r\n");
    #endif
                }
                //== Field navStat
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8NavStat,
                                                   sizeof(_GPSPointString.u8NavStat)) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate navSat extraction failed!\r\n");
    #endif
                }
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8Hacc,
                                                   sizeof(_GPSPointString.u8Hacc)) == false)

                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate hAcc extraction failed!\r\n");
    #endif

                }
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8Vacc,
                                                   sizeof(_GPSPointString.u8Vacc)) == false)

                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate vAcc extraction failed!\r\n");
    #endif

                }
                //== Speed Over Ground
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8GroundSpeed,
                                                   sizeof(_GPSPointString.u8GroundSpeed)) == false)

                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate SOG extraction failed!\r\n");
    #endif

                }
                //== Course Over Ground
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8CourseOverGround,
                                                   sizeof(_GPSPointString.u8CourseOverGround)) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate COG extraction failed!\r\n");
    #endif
                }
                //== field vVel, diffAge, we skip those two fields
                else if ((gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT NULL, 16) == false) ||
                   (gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT NULL, 16) == false))
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate vVel and diffAge skip failed!\r\n");
    #endif
                }
                //== field HDOP
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8HDOP,
                                                   sizeof(_GPSPointString.u8HDOP)) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate HDOP extraction failed!\r\n");
    #endif
                }
                //== field VDOP
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8VDOP,
                                                   sizeof(_GPSPointString.u8VDOP)) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate VDOP extraction failed!\r\n");
    #endif
                }
                // field TDOP, we skip it
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT NULL, 16) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate TDOP and diffAge skip failed!\r\n");
    #endif
                }
                //== field numSvs
                else if(gpsPointStringExtractToken(pszTokenStart, OUT &pszTokenStart, OUT (char*)_GPSPointString.u8NumSvs,
                                                   sizeof(_GPSPointString.u8NumSvs)) == false)
                {
    #ifdef DEBUG_GPS_ENABLED
                   printf("[GPS] GpsPointUpdate numSvs extraction failed!\r\n");
    #endif
                }
                else
                {

                   uint8_t u8TimeCommand[] = "$PUBX,04*37\r\n";
//                 if(gpsPollPUBXString(this, u8Data, sizeof(u8Data), u8TimeCommand))
                   if(true)
                   {

                      const char* pszTimeToken = (char*)u8DataTime;
                      //== skipping fields $PUBX,04 and time
                      if((gpsPointStringExtractToken(pszTimeToken, OUT &pszTimeToken, OUT NULL, 16) == false)
                            || (gpsPointStringExtractToken(pszTimeToken, OUT &pszTimeToken, OUT NULL, 16) == false)
                            || (gpsPointStringExtractToken(pszTimeToken, OUT &pszTimeToken, OUT NULL, 16) == false))
                      {
    #ifdef DEBUG_GPS_ENABLED
                         printf("[GPS] GpsPointUpdate $PUBX,04 and time skip failed!\r\n");
    #endif
                      }
                      //== field Date
                      else if(gpsPointStringExtractToken(pszTimeToken, OUT &pszTimeToken,
                                                         OUT (char*) _GPSPointString.u8UTCDate, sizeof(_GPSPointString.u8UTCDate)) == false)
                      {
    #ifdef DEBUG_GPS_ENABLED
                         printf("[GPS] GpsPointUpdate VDOP extraction failed!\r\n");
    #endif
                      }

                     printf("[GPS] GpsPointUpdate - GPS string : %s %s %c %s %c %s %s %s %s %s %s %s %s %s\n",
                             _GPSPointString.u8UTCTime,
                             _GPSPointString.u8Latitude,
                             _GPSPointString.u8LatitudeLocation,
                             _GPSPointString.u8Longitude,
                             _GPSPointString.u8LongitudeLocation,
                             _GPSPointString.u8NavStat,
                             _GPSPointString.u8Hacc,
                             _GPSPointString.u8Vacc,
                             _GPSPointString.u8GroundSpeed,
                             _GPSPointString.u8CourseOverGround,
                             _GPSPointString.u8HDOP,
                             _GPSPointString.u8VDOP,
                             _GPSPointString.u8NumSvs,
                             _GPSPointString.u8UTCDate
                             );


                      printf("bPositionIsValid: %u bParsingError: %u\r\n", bPositionIsValid, bParsingError);
                   }
                }
             }
          }
      }


  return 1;
}

static bool gpsPointStringExtractToken(IN const char* pszTokenStart,
                                       OUT const char** ppszNextToken,
                                       OUT char* pszTokenDestination,
                                       IN unsigned int uDestinationSize)
{
   bool bSuccess = false;

   // Reset OUT parameters.
   (*ppszNextToken) = NULL;
   if (pszTokenDestination != NULL &&
       uDestinationSize > 0)
   {
      (*pszTokenDestination) = '\0';
   }

   const char* pszNextSeparator = strchr(pszTokenStart, ',');

   if (pszNextSeparator != NULL)
   {
      const unsigned int uTokenSize = pszNextSeparator - pszTokenStart;
      if (uTokenSize < uDestinationSize)
      {
         if (uTokenSize > 0)
         {
            // Token is not empty.

            if (pszTokenDestination != NULL &&
                uDestinationSize > 0)
            {
               // Token is needed.

               // This will add '\0' characters at the end.
               strncpy(OUT pszTokenDestination,
                       pszTokenStart,
                       uTokenSize);
            }
         }

         bSuccess = true;
      }
      // else, token is too big to fit; consider parsing error.

      // Skip the separator.
      (*ppszNextToken) = pszNextSeparator + 1;
   }
   // else, no next separator; means no next token.

   return bSuccess;
}


static void getCorrectedDate(char * utcDate)
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




static bool GPSPointConvertUTCToUNIX(PUINT8 pu8UTCDate, PUINT8 pu8UTCTime, PUINT32 pu32Unix)
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



void getCorrectedDate2(int year, int month, int day, char * date)
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

		printf("-- y: %d  m: %d d: %d \r\n", y, m, d);

		itoa(y, u8Year, 10);
		itoa(m, u8Month, 10);
		itoa(d, u8Day, 10);

		if (d < 10) {
			u8Day[1] = u8Day[0];
			u8Day[0] = '0';
			u8Day[2] = '\0';
		}

		if (m < 10) {
			u8Month[1] = u8Month[0];
			u8Month[0] = '0';
			u8Month[2] = '\0';
		}

		printf(" %s \r\n", u8Year);
		printf(" %s \r\n", u8Month);
		printf(" %s \r\n", u8Day);
		u8Date[5] = u8Year[1];
		u8Date[4] = u8Year[0];
		u8Date[3] = u8Month[1];
		u8Date[2] = u8Month[0];
		u8Date[1] = u8Day[1];
		u8Date[0] = u8Day[0];
		u8Date[6] = '\0';
		printf(" %s \r\n", u8Date);
		char * utcDate;
		strncpy((char*) utcDate, (char*) u8Date, strlen((char*) u8Date) + 1);

}

void getCorrectedDate3(char * utcDate)
{

	char Year[3];
	char Month[3];
	char Day[3];
	char u8Date[10];
	int year;

	memset(Year, '0', sizeof(Year));
	memset(Month, '0', sizeof(Month));
	memset(Day, '0', sizeof(Day));
	memset(u8Date, '0', sizeof(Day));

	bool isWrongDate1 = strstr((char*) utcDate, (char*) "99") != NULL || strstr((char*) utcDate, (char*) "-1") != NULL;
	UINT8 tmp[3];
	tmp[0] = utcDate[4];
	tmp[1] = utcDate[5];
	tmp[2] = '\0';
	int t = atoi((char *) tmp);

	bool isWrongDate2 = (t < 19);

	if (isWrongDate1 || isWrongDate2) {
		UINT8 u8Year[3], u8Month[3], u8Day[3];

		if (isWrongDate1) {
			u8Year[0] = '9';
			u8Year[1] = '9';
			year = atoi((char*) u8Year) + 1900;
		} else {
			u8Year[0] = utcDate[4];
			u8Year[1] = utcDate[5];
			year = atoi((char*) u8Year) + 2000;
		}

		u8Month[0] = utcDate[2];
		u8Month[1] = utcDate[3];
		u8Day[0] = utcDate[0];
		u8Day[1] = utcDate[1];

		int y1, m1, d1;

		y1 = year;
		m1 = atoi((char*) u8Month);
		d1 = atoi((char*) u8Day);

		struct tm t1 = { .tm_year = y1 - 1900, .tm_mon = m1 - 1, .tm_mday = d1 };
		t1.tm_mday += 7168;
		mktime(&t1);

		printf("%s \r\n", asctime(&t1));
		UINT8 y = t1.tm_year - 100;
		UINT8 m = t1.tm_mon + 1;
		UINT8 d = t1.tm_mday;

		printf("-- y: %d  m: %d d: %d \r\n", y, m, d);

		itoa(y, Year, 10);
		itoa(m, Month, 10);
		itoa(d, Day, 10);

		if (d < 10) {
			Day[1] = Day[0];
			Day[0] = '0';
			Day[2] = '\0';
		}

		if (m < 10) {
			Month[1] = Month[0];
			Month[0] = '0';
			Month[2] = '\0';
		}

		printf(" %s \r\n", Year);
		printf(" %s \r\n", Month);
		printf(" %s \r\n", Day);
		u8Date[5] = Year[1];
		u8Date[4] = Year[0];
		u8Date[3] = Month[1];
		u8Date[2] = Month[0];
		u8Date[1] = Day[1];
		u8Date[0] = Day[0];
		u8Date[6] = '\0';
		printf(" %s \r\n", u8Date);
		strncpy((char*) utcDate, (char*) u8Date, strlen((char*) u8Date) + 1);
	}
}








