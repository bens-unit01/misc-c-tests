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
#include "stdarg.h"
#include "FausseAlerteVitesse.h"
#include "AceSpreader.h"
#include "GenericTypes.h"
#include "MiscTests.h"

// $GPRMC,000231.42,A,4829.0005,N,00022.0016,E,0.16,212.28,220899,,,A*59



int main(void) {

//	testParsingAce(" -- %d %d \r\n", 20, 21);
//	testFausseAlerteVitesse();
//  testGpsParsing();
//  testGpsPUBXParsing();


//  MiscTests ------------
//	testCalcInt();
//	testCrc();
	testFuelLevelFilter();
}













