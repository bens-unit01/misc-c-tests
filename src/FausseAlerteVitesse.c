/*
 * FausseAlerteVitesse.c
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */




// constantes de testFausseAlerteVitesse
#define OVERSPEED_DBG_DATA_SIZE                         120
#define OVERSPEED_SPEED_HISTORY_SIZE                    10
#define OVERSPEED_SPEED_INVALID                         0xFF

int testFausseAlerteVitesse(void){
	 printf("Test calcul indexe ...\n");
	      int u8TmpSpeed = 0;
	      int u8MaxSpeedIdx = 0;
	      int u8MinSpeed = 200;
	      int u8MaxSpeed = 0;
	      int u8CurrentIndex = 99;
	      int auSpeedHistory[] = { 41, 41,  41,  42,  42,  42,  42,  42,  43,  43,  43,  43,  43,  43,  42,  41,  40,  39,  38,  37,  36,  35,  33,  32,  29,  27,  24,  23,  23,  21,  19,  16,  13,  10,   7 ,  5 ,  2 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  1 ,  1 ,  1 ,  3 ,  7 , 10,  13,  16,  19,  21,  23,  24,  26,  28,  29,  31,  31,  33,  34,  35,  36,  37,  37,  38,  39,  40,  40,  40,  40,  40,  37,  34,  34,  31,  27,  23,  19,  15,  10,   6 ,  5 ,  5 ,  5 ,  4 ,  1,  30 , 12,  19,  25,  25,  30,  34,  38,  42,  45,  48,  51,  53,  56,  56,  57,  57,  58,  58,  58,  58,  58,  58,  58,  58,  58,  58,  57,  57};
	   /* for(int i = 0; i < 120; i++)
	    {
	        printf(" %d %d \n", auSpeedHistory[i], i);
	    }*/

	       int uOldestHistoryIndex = (OVERSPEED_DBG_DATA_SIZE + u8CurrentIndex - (OVERSPEED_SPEED_HISTORY_SIZE - 1))
	            % OVERSPEED_DBG_DATA_SIZE;
	      for(int i = 0; i < OVERSPEED_SPEED_HISTORY_SIZE; i++)
	      {
	          u8TmpSpeed = auSpeedHistory[(uOldestHistoryIndex + i) % OVERSPEED_DBG_DATA_SIZE];
	         if(u8TmpSpeed == OVERSPEED_SPEED_INVALID)
	         {
	            u8MaxSpeed = u8TmpSpeed;
	            printf("loop exit !!\n");
	            break;
	         }
	         else
	         {
	            if(u8TmpSpeed <=u8MinSpeed)
	            {
	               u8MinSpeed = u8TmpSpeed;
	               // We make sure to take the maximum speed that came after the minimum speed
	               u8MaxSpeed = 0;
	               u8MaxSpeedIdx = 0;
	            }

	            // We use '>=' to make sure we are taking the last occurrence
	            // of the maximum speed.
	            if(u8TmpSpeed >= u8MaxSpeed)
	            {
	               u8MaxSpeed = u8TmpSpeed;
	               u8MaxSpeedIdx = i;
	            }
	         }
	         printf(" u8TmpSpeed %d %d\n", u8TmpSpeed, i);
	      }
	      printf(" max: %d %d, min: %d \n", u8MaxSpeed, u8MaxSpeedIdx, u8MinSpeed);
	      if((u8MaxSpeed == OVERSPEED_SPEED_INVALID) ||(((u8MaxSpeed - u8MinSpeed) >= 37) && (u8MaxSpeedIdx == (OVERSPEED_SPEED_HISTORY_SIZE - 1))))
	      {
	        // bIsGpsStable = false;
	         printf("GPS unstable, holding the state for 2 min\n");
	      }

	    return 0;
}

