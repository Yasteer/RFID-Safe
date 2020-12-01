// Yasteer Sewpersad RFID Safe
/* System Components: 
 *  1x Servo
 *  1x Metal Box
 *  1x 3D Printed Latch Mechanism
 */
 
#include <Servo.h> 

int LED_Unlocked    = 8;
int LED_Locked      = 9;
int LED_AddNewUser  = 10;

Servo M1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  M1.attach(3, 1000, 2000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
