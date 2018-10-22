/*
 * ======== Standard MSP430 includes ========

 #include <msp430.h>
 */
//#include <msp430g2553.h>
#include <msp430.h>
#include <stdio.h>
#include "C:/MSP430_LaunchPad/Workspace/ScienceFairGrace010214/src/grace/foo.h"
#include "C:/MSP430_LaunchPad/Workspace/ScienceFairGrace010214/src/grace/PWMSpeed.h"

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/Grace.h>

#define uchar unsigned char
#define uint unsigned int
#define SCL       BIT6;
#define SDA       BIT7;

uchar R_word;
uchar ACK_Flag1;
uchar read_buffer_iic[2] = { 0 };
uchar write_buffer_iic[2] = { 0 };

char buff[10];
int t;
int t1; //temporary t for for calculation
volatile int z;
volatile int j;
volatile int p;
volatile int e;
volatile int o;
int rec;
long int dummytemp;
int firststop;
int secondstop;
int set;
int speed[5] = {0,0,0,0,0};
int setpoint[5] = {0,0,0,0,0};
int aaa;
int speed1;

int PWMSpeed(int y){    /* Function definition */
	y = y;
	return speed1;
}

int tempHigh, tempLow;
int send_array[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int recbuffer[9]={0, 0, 0, 0, 0, 0, 0, 0 ,0 };

void delay(uint v);
void Start(void);
void Stop(void);
void Send_Byte(uchar Byte);
void ACK(void);
void ACK_0(void);
void NOACK(void);
void Receive_Byte(void);
void I2C_75_write(uint T_addr, uchar W_addr, uchar dat);
void I2C_75_Read(uint T_addr, uint R_addr, uchar n);

/*
 2 : Outside Temperature (0x94) (T1)
 3 : Before Cooler Temperature (0x96) (T2)
 0 : Cold Heat Sink Temperature (0x90) (T3)
 6 : After Cooler Temperature A (0x9C) (T4)
 7 : After Cooler Temperature B (0x9E) (T5)
 5 : Before Heat Exchanger Temperature (0x9A) (T6)
 4 : Outlet Temperature (0x98) (T7)
 1 : Hot Heat Sink Temperature (0x92) (T8)
 */
unsigned int TMPADDR[] = { 0x94, 0x96, 0x90, 0x9C, 0x9E, 0x9A, 0x98, 0x92 };

/*
 *  ======== main ========
 */
int main(void) {
	Grace_init();                   // Activate Grace-generated configuration

	int dummyint;

	for (j = 0; j < 8; j++) {
		I2C_75_write(TMPADDR[j], 0x01, 0x60); //Configure T1-T8 to 12-bit Sensors
	}

	while (1) {
		for (p = 0; p < 8; p++) {
			//READ TEMPERATURE SENSOR
			I2C_75_Read(TMPADDR[p], 0, 2);
			tempHigh = read_buffer_iic[0];
			tempLow = read_buffer_iic[1];

			t1 = 0;
			if (tempHigh > 0x7F) {
				t1 = tempHigh;
				t1 = t1 << 8;
				t1 = t1 + tempLow; //combine tempHigh AND tempLow
				t1 = 0 - t1; 		//Calculate negative value
				tempLow = t1 & 0x0ff; //Filter out tempHigh
				tempLow = tempLow >> 4; //tempLow value
				tempHigh = t1 & 0xff00; //Filter out tempLow
				tempHigh = tempHigh >> 8; //tempHigh Value
				t1 = 1; // t1=1 mean value is negative
				t = (int) (tempLow * 6.25); //Convert tempLow to degree C
			} else {
				tempLow = tempLow >> 4;
				t = (int) (tempLow * 6.25); //Convert tempLow to degree C
			}

			//t1 means + or -. (t1=1 is "-")

			dummyint = tempHigh * 100 + t; //calculate final temperature x100
			if (t1 == 1) {
				dummyint = dummyint * -1;
			}
			send_array[p] = dummyint; //save temperature into array (Dummyint is the temperature multiplied by 100)
		}
		/*send_array[0] = -2509;
		send_array[1] = 512;
		send_array[2] = -321;*/
		//send_array[8] = 49;
		//send_array[9] = 312;

		/*TXByte = 0x3b;			//print a "'" between value
		 Transmit();*/
		if(foo(0) != 0){ //where data is received
			int j = 0;
			int amountofdataS;
			int amountofdataT;

			for (j = 0; j < 9; j++){
				if (foo(0) != 0){
					recbuffer[j] = foo(j); //data is put in array
				}
			}
			if(recbuffer[0] == 'M'){
				set = recbuffer[1];
			}
			if(recbuffer[0] == 0x53){
				for(e = 0; e <5 ; e++){
					if(recbuffer[e+1] != 'e'){
						speed[e] = recbuffer[e+1];
					}else{
						amountofdataS = e;
						break;
					}
				}
				switch(amountofdataS){
					case 3:
						send_array[8] = (speed[0] - 48) * 100 + (speed[1] - 48) * 10 + (speed[2] - 48);
						speed1 = send_array[8];
						break;
					case 2:
						send_array[8] = (speed[0] - 48) * 10 + (speed[1] - 48);
						speed1 = send_array[8];
						break;
					case 1:
						send_array[8] = speed[0] - 48;
						speed1 = send_array[8];
						break;
				}
				TA1CCTL2 = CM_0 | CCIS_0 | OUTMOD_7;

				/* TA1CCR0, Timer_A Capture/Compare Register 0 */
				TA1CCR0 = 100;

				/* TA1CCR2, Timer_A Capture/Compare Register 2 */
				dummytemp = speed1;
				TA1CCR2 = speed1;
				//TA1CCR2 = (speed1 / 100) * TA1CCR0;

				  /*
				     * TA1CTL, Timer_A3 Control Register
				     *
				     * TASSEL_1 -- ACLK
				     * ID_0 -- Divider - /1
				     * MC_1 -- Up Mode
				     */
				    TA1CTL = TASSEL_1 | ID_0 | MC_1;
			}
			if(recbuffer[0] == 'T'){
				for(e = 0; e <5 ; e++){
					if(recbuffer[e+1] != 'e'){
						setpoint[e] = recbuffer[e+1];
					}else{
						amountofdataT = e;
						break;
					}
				}
				switch(amountofdataT){
					case 3:
						send_array[9] = (setpoint[0] - 48) * 100 + (setpoint[1] - 48) * 10 + (setpoint[2] - 48);
						break;
					case 2:
						send_array[9] = (setpoint[0] - 48) * 10 + (setpoint[1] - 48);
						break;
					case 1:
						send_array[9] = setpoint[0] - 48;
						break;
				}
			}
			for (e = 0; e < 9; e++){
			recbuffer[e] = 0;
			}
		}

		aaa = P1OUT & 0x01;
		if (aaa == 1) {
			for (o = 0; o < 11; o++) {
				//while (!(IFG2&UCA0TXIFG)); // USCI_A0 TX buffer ready?
				//UCA0TXBUF = send_array[o]; //If negative, send "-"
				for (e = 0; e < 11; e++) {
					buff[e] = 0;
				}

				sprintf(buff, "%d", send_array[o]);
				for (e = 0; e < 5; e++) {
					if (buff[e] == 0) {
						break;
					}

					while (!(IFG2 & UCA0TXIFG))
						; // USCI_A0 TX buffer ready?
					UCA0TXBUF = buff[e];
				}

				while (!(IFG2 & UCA0TXIFG))
					; // USCI_A0 TX buffer ready?
				UCA0TXBUF = 0x2C; //send a "," in between each value

				while (!(IFG2 & UCA0TXIFG))
					; // USCI_A0 TX buffer ready?
				UCA0TXBUF = 0x20; //send a " " in between each value
			}

			while (!(IFG2 & UCA0TXIFG))
				; // USCI_A0 TX buffer ready?
			UCA0TXBUF = 0x3b;	 //print a ";" between value

			//TXByte = 0x13;			//print a ";" between value
			//Transmit();

			/*TXByte = 0xD;
			 Transmit();
			 TXByte = 0xA;
			 Transmit();*/

			while (!(IFG2 & UCA0TXIFG))
				; // USCI_A0 TX buffer ready?
			UCA0TXBUF = 0xD;	 //print a newline

			while (!(IFG2 & UCA0TXIFG))
				; // USCI_A0 TX buffer ready?
			UCA0TXBUF = 0xA;	 //carriage return
		}
		P1OUT &= ~BIT0;
	}
	return (0);
}

//------------------------I2C Subroutines----------------------------------------------
void delay(uint v) {
	while (v != 0)
		v--;
}
void Start(void) {
	P1OUT &= ~SCL
	;
	P1OUT &= ~SDA
	;
	P1DIR &= ~SDA
	;			//SDA=1
	P1DIR &= ~SCL
	; 			//SCL=1
	delay(6);
	P1DIR |= SDA
	;
	delay(6);
	P1DIR |= SCL
	;
}

void Stop(void) {
	P1DIR |= SDA
	;		//SDA = 0
	P1DIR &= ~SCL
	;		//SCL = 1
	delay(6);
	P1DIR &= ~SDA
	;		//SDA = 1
	P1DIR |= SCL
	;		//SCL = 0
	P1DIR |= SDA
	;		//SDA = 0
}

void Send_Byte(uchar Byte) {
	uint i;
	for (i = 0; i < 8; i++) {
		if (Byte & 0x80) {
			P1DIR &= ~SDA
			;
		} else {
			P1DIR |= SDA
			;
		}
		P1DIR &= ~SCL
		;
		delay(3);
		Byte = Byte << 1;
		P1DIR |= SCL
		;
		delay(3);
	}
}

void ACK(void) {
	P1DIR &= ~SDA
	;
	P1DIR &= ~SCL
	;
	ACK_Flag1 = 0;
	delay(6);
	if ((P1IN & BIT7))
		ACK_Flag1 = 1;
	P1DIR |= SCL
	;
	delay(3);
}

void ACK_0(void) {
	P1DIR |= SCL
	;
	P1DIR |= SDA
	;
	delay(6);
	P1DIR &= ~SCL
	;
	P1DIR |= SCL
	;
	delay(6);
}

void NOACK(void) {
	P1DIR &= ~SDA
	;
	delay(6);
	P1DIR &= ~SCL
	;
	delay(6);
	P1DIR |= SCL
	;
	delay(6);
	P1DIR |= SDA
	;
}

void Receive_Byte(void) {
	uint j;
	R_word = 0x00;
	P1DIR &= ~SDA
	;
	for (j = 0; j < 8; j++) {
		R_word = R_word << 1;
		P1DIR &= ~SCL
		;
		delay(3);
		if ((P1IN & BIT7)== BIT7 )
			R_word++;
		P1DIR |= SCL
		;
		delay(1);
	}

}
//  写 n 个字节   ACK_Flag 表示是曬正葧
void I2C_75_write(uint T_addr, uchar W_addr, uchar dat) {
	Start();
	delay(20);
	Send_Byte(T_addr);          //write a byte :slave device
	ACK();
	Send_Byte(W_addr);    // write a byte :e2prom address
	ACK();
	Send_Byte(dat);
	ACK();
	Stop();
	delay(800);
}

//  读 n 个字节    ACK_Flag 表示是曬正葧
void I2C_75_Read(uint T_addr, uint R_addr, uchar n) {
	uchar i = 0;
	Start();
	Send_Byte(T_addr);
	ACK();
	Send_Byte(R_addr);
	ACK();
	Start();
	Send_Byte(T_addr + 1);
	ACK();
	for (i = 0; i < n - 1; i++) {
		Receive_Byte();
		ACK_0();

		read_buffer_iic[i] = R_word;
	}
	Receive_Byte();
	ACK_0();    //NOACK();
	read_buffer_iic[i] = R_word;
	Stop();
}
