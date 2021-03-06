/*********************************************************************
 *
 *               Test Fraise Versa1.0 
 *
 *********************************************************************
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Antoine Rousseau  nov 2015     Original.
 ********************************************************************/

/*
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA  02110-1301, USA.
*/

#define BOARD Versa1

#include <fruit.h>
#include <analog.h>
#include <switch.h>

unsigned char PERIOD=200;
unsigned char t,t2=0;	
t_delay mainLoop;
	

void highInterrupts()
{
	//Servo_ISR();
	
}

void lowInterrupts()
{}

void setup(void)
{
	//unsigned long tMain;
	
	fruitInit();			

	pinModeDigitalOut(LED);
	digitalClear(LED);

	analogInit();
	analogSelect(0,K1);
	analogSelect(1,K2);
	analogSelect(2,K3);
	analogSelect(3,K5);
	
	switchInit();
	switchSelect(0,K11);
	switchSelect(1,K12);
	//EEreadMain();
	
	delayStart(mainLoop, 5000);
	t=PERIOD;
}

void loop() {
// ---------- Main loop ------------
	fraiseService();
	analogService();
	switchService();

	//if(Elapsed(tMain)>Micros(5000UL))
	if(delayFinished(mainLoop))
	{
		//tMain=GetTime();
		delayStart(mainLoop, 5000);
		
		if (!switchSend()) analogSend();
		
		if(!t--){
			t=PERIOD;
			t2++;
			printf("Cs Hello ! t2= %d\n", t2);
		}
	}
}

void fraiseReceiveCharBroadcast()
{
	/*unsigned char c;
	
	printf("Brdcst: ");
	for(c=0;c<FrRXout_len;c++) printf("%c",FrRXgetchar());
	putchar('\n');*/
}

void fraiseReceiveBroadcast()
{
	/*unsigned char c;
	
	printf("brdcst: ");
	for(c=0;c<FrRXout_len;c++) printf("%d ",FrRXgetchar());
	putchar('\n');*/
}

void fraiseReceiveChar()
{
	unsigned char c;
	
	c=fraiseGetChar();
	if(c=='L'){	
		c=fraiseGetChar();
		digitalWrite(LED, c!='0');		
	}
	else if(c=='E') {
		printf("C");
		c = fraiseGetLen();
		while(c--) printf("%c",fraiseGetChar());
		putchar('\n');
	}	
}


void fraiseReceive()
{
	unsigned char c;//,c2;
	
	c=fraiseGetChar();

	switch(c) {
		PARAM_CHAR(1,t2); break;
		PARAM_CHAR(2,PERIOD); break;
		
		case 255 : EEwriteMain();break;
	}
}

void EEdeclareMain()
{
}
