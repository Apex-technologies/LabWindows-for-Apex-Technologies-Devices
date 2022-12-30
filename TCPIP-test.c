/*********************************************************************/
/* This example demonstrates opening a simple TCPIP connection to    */ 
/* Apex Technologies device and does a read and write operation.     */
/*                                                                   */
/* The general flow of the code is                                   */
/*      Open Resource Manager                                        */
/*      Open a session to the TCP/IP                                 */
/*      Perform a read and write operation                           */
/*      Close all VISA Sessions                                      */
/*********************************************************************/


#include <ansi_c.h>
#include <userint.h>
#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static char outputBuffer[VI_FIND_BUFLEN];
static ViSession defaultRM, instr;
static ViStatus status;
static ViUInt32 count;
static ViUInt16 portNo;

int main(void)
{
	//char idnQuery[] = "*IDN?\n";
	
	char Query1[40]="TLS[01]:TPDB09\n";

	ViUInt32 returnCount = 0;
	char idnResponse[1024];
    char message[1024];
		
   /* First we will need to open the default resource manager. */
   status = viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)
   {
      printf("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
   }  

   /* Now we will open a session via TCP/IP  */
   status = viOpen (defaultRM, "TCPIP::192.168.1.146::5900::SOCKET", VI_NULL, VI_NULL, &instr); //please enter the ethernet IP address and ethernet port number of the instrument here.
   if (status < VI_SUCCESS)
   {
      printf ("An error occurred opening the session to TCPIP::192.168.1.146::5900::SOCKET");
      viClose(defaultRM);
      exit (EXIT_FAILURE);
   }
    status = viClear(instr);
   
	 status = viSetAttribute(instr, VI_ATTR_TERMCHAR, 10);
     status = viSetAttribute(instr, VI_ATTR_TERMCHAR_EN, 1);        

    //status = viWrite(instr, (ViBuf)idnQuery, (ViUInt32)strlen(idnQuery), VI_NULL);
	status = viWrite(instr, (ViBuf)Query1, (ViUInt32)strlen(Query1), VI_NULL);
	
    status = viRead(instr, (ViBuf)idnResponse, 1024, &returnCount);
   idnResponse[returnCount] = 0; //terminate the string properly
        
   sprintf (message, "%s", idnResponse);
    MessagePopup ("Apex Technologies", message);
	 
	 status = viClose (instr);
     status = viClose (defaultRM);
  /* viSetAttribute (instr, VI_ATTR_TCPIP_NODELAY, VI_TRUE);
   
   status = viRead (instr, (ViBuf)outputBuffer, 25, &count);
   if (status < VI_SUCCESS)
   {
      printf("viRead failed with error code %x \n",status);
      viClose(defaultRM);
      exit (EXIT_FAILURE);
   }

   printf("The server response is:\n %s\n\n",outputBuffer);
   status = viGetAttribute (instr, VI_ATTR_TCPIP_ADDR, outputBuffer);
   printf(" Address:  %s\n",outputBuffer);
   
   status = viGetAttribute (instr, VI_ATTR_TCPIP_HOSTNAME, outputBuffer);
   printf(" Host Name:  %s\n",outputBuffer);
   
   status = viGetAttribute (instr, VI_ATTR_TCPIP_PORT, &portNo);
   printf(" Port:  %d\n",portNo);
   
   status = viGetAttribute (instr, VI_ATTR_RSRC_CLASS, outputBuffer);
   printf(" Resource Class:  %s\n",outputBuffer);

   status = viClose (instr);
   status = viClose (defaultRM);
   printf ("\nHit enter to continue.");
   fflush(stdin);
   getchar();*/

   return 0;  
}