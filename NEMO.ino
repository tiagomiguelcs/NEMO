/* ---------------------------------------------------------------------------
//
//	NEMO, your friendly Arduino robot.
//
//  Copyright (C) 2020 Instituto de Telecomunicações (www.it.pt)
//  Copyright (C) 2020 Universidade da Beira Interior (www.ubi.pt)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// 'images: Flaticon.com'. The logo of the application has been designed
//  using resources from Flaticon.com.
// ---------------------------------------------------------------------------
*/
#include <SharpIR.h>
#include <Servo.h> 

// ir: The pin where your sensor is attached
// 25: The number of readings the library will make before calculating a mean distance
// 93: The difference between two consecutive measurements to be taken as valid
// model: An int that determines your sensor: 1080 for GP2Y0A21Y, 20150 for GP2Y0A02Y
#define ir A0
#define model 1080
boolean done=false;
SharpIR sharp(ir, 25, 93, model);
 
Servo myservo;  // Creates servo object.
int pos         = 0; // Variable to store the servo position.
int pos_servo   = 0; // Default servo position.
int EN1         = 6; // Roboduino Motor 1 shield uses Pin 6
int EN2         = 5; // Roboduino Motor 2 shield uses Pin 5
int IN1         = 7;
int IN2         = 4; 

/* Power NEMO's Motor Shield 1*/
void motor1(int pwm, boolean reverse){
    analogWrite(EN1,pwm); // Set pwm control, 0 for stop, and 255 for maximum speed
    if(reverse)
        digitalWrite(IN1,HIGH);    
    else
        digitalWrite(IN1,LOW);    
}  
         
/* Power NEMO's Motor Shield 2*/
void motor2(int pwm, boolean reverse){
    analogWrite(EN2,pwm);
    if(reverse) 
        digitalWrite(IN2,HIGH);    
    else
        digitalWrite(IN2,LOW);
}

/* Arduino initialization */
void setup(){
  Serial.begin(9600);
  pinMode (ir, INPUT);
  myservo.attach(9);  // Attaches the servo on pin 9 to the servo object 
  int i;
   for(i=5;i<=8;i++)  // For Arduino Motor
    pinMode(i, OUTPUT);  //set pin 4,5,6,7
  myservo.write(90); delay(15);
}

/* The function that makes our little robot "alive". */
void loop(){
 unsigned long pepe1=millis();  // Takes the time before the loop begins.
 int dis=sharp.distance();      // Gets the distance from the sensor to the object.
 
 // Outputs to the serial monitor the mean distance to a object in front.
 Serial.print("[NEMO]: Mean distance to object: ");  
 Serial.println(dis);
 
 // If you set, 180  -> NEMO goes left
 // If you set, 90   -> NEMO goes forward
 // If you set, 0    -> NEMO goes Right
 if (dis <= 45){
   // "Iceberg right ahead!"
   Serial.println("[NEMO]: My path is obstructed! Trying to find a different one...");
   // "Stop all engines"
   motor1(0, false); 
   motor2(0, false);
   int i=myservo.read();
   int back=0;
   // Spins NEMO on itself in order to find a path that is not obstructed by an object.
   while(true){
     myservo.write(i); 
     delay(15);
     // Serial.println(i);
     // Serial.println(back);
     if (sharp.distance() > 45){ pos=i;  break; }
     if (i == 153) back++;
     if (i == 25) back++;
     switch(back){
         case 1:
            i--;
        case 0:
            i++;
        case 2:
            myservo.write(90); 
            delay(15); 
            goBack(); 
            delay(2000); 
            back=0; 
            break;
     }
   }
 }
 
 Serial.print("[NEMO]: Current servo position: ");
 Serial.println(pos);
 
 // Set direction
 if (pos > 100){ 
     goLeft(); 
     Serial.println("[NEMO]: Going left!"); 
     myservo.write(90); 
     delay(15); 
     pos=0; // reset position
     delay(500);    
}
if (pos < 90 && pos != 0){ 
    goRight(); 
    Serial.println("[NEMO]: Going right!"); 
    myservo.write(90); 
    delay(15); 
    pos=0; // reset position
    delay(500);  
}
 
goForward(); 
Serial.println("[NEMO]: Going forward!"); 
pos=0; 
myservo.write(90); 
delay(515);
}

/* Auxiliary Function to move MEMO forward. */
void goForward(){
  motor1(255,true);  
  motor2(255,false);
}

/* Auxiliary function to move NEMO to the right. */
void goRight(){
  motor1(255,true);
  motor2(255,true);
}

/* Auxiliary function to move NEMO to the left. */
void goLeft(){
  motor1(255,true);
  motor2(255,true);
}

/* Auxiliary function to reverse. */
void goBack(){
  motor1(255,false);
  motor2(255,true);
}