/*
made by gada888 in Luoyang China.Date:2020-11-20
*/ 
#include <SoftwareSerial.h>
SoftwareSerial Serial1(7, 8); //TX,RX
#include "Servo.h"  
// Declare the Servo pin 
int servoPin1 = 9; 
int servoPin2 = 10; 
// Create a servo object 
Servo Servo1, Servo2;

int inputPin = 2; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status

unsigned char order[4] = {0xAA,0x06,0x00,0xB0};

void setup() {

// We need to attach the servo to the used pin number 
   Servo1.attach(servoPin1);
   Servo2.attach(servoPin2);
pinMode(inputPin, INPUT); // declare sensor as input

Serial.begin(115200);
Serial1.begin(9600);
volume(0x1E);
}
void loop(){
  
val = digitalRead(inputPin); // read input value

if (val == HIGH) { // check if the input is HIGH

// Make servo go to 0 degrees 
Servo1.write(0); // Set Servo 1 to 0 degrees
Servo2.write(90); // Set Servo 2 to 90 degrees 
Servo1.write(0); // Set Servo 1 to 0 degrees
Servo2.write(90); // Set Servo 2 to 90 degrees 
delay(500);
   // Make servo go to 90 degrees
Servo1.write(90); // Set Servo 1 to 0 degrees
Servo2.write(0); // Set Servo 2 to 90 degrees  
Servo1.write(90); // Set Servo 1 to 0 degrees
Servo2.write(0); // Set Servo 2 to 90 degrees 
delay(500);

if (pirState == LOW) {
// we have just turned on
Serial.println("Motion detected!");
// We only want to print on the output change, not state
pirState = HIGH;
play(0x01);
}
} else {

if (pirState == HIGH){
// we have just turned off
Serial.println("Motion ended!");
// We only want to print on the output change, not state
pirState = LOW;
}
}
}
// =========FUNCTION============
void play(unsigned char Track)
{
unsigned char play[6] = {0xAA,0x07,0x02,0x00,Track,Track+0xB3};//0xB3=0xAA+0x07+0x02+0x00,å³æœ€åŽä¸€ä½ä¸ºæ ¡éªŒå’?
Serial1.write(play,6);
}
void volume( unsigned char vol)
{
unsigned char volume[5] = {0xAA,0x13,0x01,vol,vol+0xBE};//0xBE=0xAA+0x13+0x01,å³æœ€åŽä¸€ä½ä¸ºæ ¡éªŒå’?
Serial1.write(volume,5);
}