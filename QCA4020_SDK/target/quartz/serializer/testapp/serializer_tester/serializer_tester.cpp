// serializer_tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

   extern unsigned int TestBLE(void);
   extern unsigned int TestCOEX(void);
   extern unsigned int TestTWN(void);
   extern unsigned int TestZB(void);

#ifdef __cplusplus
}
#endif

int _tmain(int argc, _TCHAR* argv[])
{
   printf("Starting Test App....\n");
   printf("Testing BLE..........\n");
   TestBLE();
   printf("Testing COEX.........\n");
   TestCOEX();
   printf("Testing TWN..........\n");
   TestTWN();
   printf("Testing ZB...........\n");
   TestZB();
   return 0;
}

