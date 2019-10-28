//leveraged code: http://ww1.microchip.com/downloads/en/appnotes/s72052.pdf


#include <mcs51/8051.h>
#include <at89c51ed2.h>
#include <stdio.h>


//#include “SST89x5xxRDx.h”
// This program generates a pulse by comparing the CL register with the
// value stored in CCAP0L. If CL >= CCAP0L then the output is HIGH.
// If CL < CCAP0L then the output is LOW.
// The duty cycle is determined by the value stored in CCAP0H.
// The HEADER FILE “SST89X5xxRDx.h” is an SST proprietary header file that defines SST’s SFRs.
// This file can be found on the SST website, or the BSL Demo Kit.

//Leveraged Code: 2052-FF51_Using-PCA-03.000-AN.fm
_sdcc_external_startup()
{
    // Note: Here is where you would put code to enable your internal RAM
    //       This code runs early in uC initialization and should be kept
    //       as small as possible. See section 4.1.4 of SDCC 3.9.0 Manual
    return 0;
}
// Note: In a function file, each function should have a small explanation of its args and returns

// putchar takes a char and TX's it. Blocking. No return value.
int putchar (int c)
{
    // Note: Compare the asm generated for the next three lines
    //       They all accomplish the same thing, but is the asm the same?
    while (!TI);
    //while (TI == 0);
    //while ((SCON & 0x02) == 0);

    SBUF = c;           // load serial port with transmit value
    TI = 0;             // clear TI flag

    return c;
}

int getchar (void)
{
    // Note: Compare the asm generated for the next three lines
    //       They all accomplish the same thing, but is the asm the same?
    while (!RI);
    //while ((SCON & 0x01) == 0);
    //while (RI == 0);

    RI = 0;                         // clear RI flag
    return SBUF;                    // return character from SBUF
}


char user_charr;

void main()
{
user_charr=getchar();
putchar(user_charr);

if(user_charr == 'w')
{
CKCON0 = 0x01;
CCAP4L = 0xFF; // Setup PCA module 4 for Watchdog Timer
CCAP4H = 0xFF;
CCAPM4 = 0x48;
//CCON
CMOD = CMOD | 0x40;
int z= '8';
putchar(z);
CL = 0x00;
CH = 0x00;
CR = 1;
int b= '3';
for(int i=0;i<5;i++)
{
   putchar(b);
}
//char ip_user;
//getchar(ip_user)
}


else if(user_charr == 'p')
{
CKCON0 = 0x01;
CMOD = 0x02; // Setup PCA timer
CL = 0x00;
CH = 0x00;
CCAP0L = 0x8C; // Set the initial value same as CCAP0H
CCAP0H = 0x8C; // 75% Duty Cycle
CCAPM0 = 0x42; // Setup PCA module 0 in PWM mode.
CR = 1; // Start PCA Timer.

while (1)
{}
}

else if (user_charr == 'r')
{
CMOD = 0x02;
CL = 0x00;
CH = 0x00;
CCAP0L = 0x8C;
CCAP0H = 0x8C;
CCAPM0 = 0x42;
CR = 1;
}

else if (user_charr =='i') //idle mode
{
PCON = 0x01;
}

else if(user_charr == 'd')
{
    PCON=0x02;
    printf("power down mode start");
}



}



