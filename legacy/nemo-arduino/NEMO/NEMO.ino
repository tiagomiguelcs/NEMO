/* ---------------------------------------------------------------------------
//
//	NEMO, your friendly Arduino robot.
//
//  Copyright (C) 2024 Instituto de Telecomunicações (www.it.pt)
//  Copyright (C) 2024 Universidade da Beira Interior (www.ubi.pt)
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
#include <Servo.h> 
/* 
 <!> In the case of serial permission denied execute the following command:
     sudo chmod a+rw /dev/ttyACM0
*/

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
  myservo.attach(9);  // Attaches the servo on pin 9 to the servo object 
  int i;
   for(i=5;i<=8;i++)  // For Arduino Motor
    pinMode(i, OUTPUT);  //set pin 4,5,6,7
  myservo.write(90); delay(15);
}

/* The function that makes our little robot "alive". */
void loop(){
  // Check if there's data available on the Serial
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');  // Read until a newline character
    if (command == "F") {
      goForward();
    } else if (command == "B") {
      goBack();
      //turnLedOff();
    } else if (command == "S") {
      goStop();
    } else {
      Serial.println("Unknown command");
    }
  }

}

/* Auxiliary Function to stop MEMO from moving. */
void goStop(){
  digitalWrite(13, LOW); // TURN OFF LED
  Serial.println("[NEMO]: Stopping!"); 
  motor1(0,false);
  motor2(0,false);
}

/* Auxiliary Function to move MEMO forward. */
void goForward(){
  analogWrite(13, HIGH); // TURN ON LED
  Serial.println("[NEMO]: Going Forward!"); 
  motor1(255,true);  
  motor2(255,false);
}

/* Auxiliary function to move NEMO to the right. */
void goRight(){
   Serial.println("[NEMO]: Going Right!"); 
  motor1(255,true);
  motor2(255,true);
}

/* Auxiliary function to move NEMO to the left. */
void goLeft(){
  Serial.println("[NEMO]: Going left!"); 
  motor1(255,true);
  motor2(255,true);
}

/* Auxiliary function to reverse. */
void goBack(){
  Serial.println("[NEMO]: Going backward!"); 
  motor1(255,false);
  motor2(255,true);
}