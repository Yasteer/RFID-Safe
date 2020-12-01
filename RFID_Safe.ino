// Yasteer Sewpersad RFID Safe
/* System Components: 
 *  1x RFID Reader & Key (NFC RFID 13.56Mhz RC522) 
 *  1x Servo
 *  1x Metal Box
 *  1x 3D Printed Latch Mechanism
 */
 
#include <Servo.h> 
#include <SPI.h>
#include <MFRC522.h> // Manually install library.

// Operation indicators:
#define LED_Unlocked    1
#define LED_Locked      2
#define LED_AddNewUser  3
#define Lock_Button     4

bool Lock_Requested = true;

// SPI output ports:
#define RST   9
#define SS    10
#define MOSI  11
#define MISO  12
#define SCK   13 // Clock.

MFRC522 rfid(SS, RST);

// RFID 
byte Master_Tag_ID[4] = {0,0,0,0}; // ID number of master tag.

// Servo
Servo M1;

void setup() {
  Serial.begin(9600);
  pinMode(Lock_Button, INPUT);
  
  // RFID ID Device comes with a SPI interface.
  SPI.begin();
  rfid.PCD_Init();

  // Set servo to pin 5 on the Uno.
  M1.attach(5, 1000, 2000);
  M1.writeMicroseconds(1000); // Lock safe.
}

void loop() {
  Lock_Requested = digitalRead(Lock_Button);
  if(Lock_Requested == true)
  {
    M1.writeMicroseconds(1000);
  }
  
  if (!rfid.PICC_IsNewCardPresent())
  {
    return; // If no card is detected, keep the safe locked. 
  }
  else
  {
      if (rfid.uid.uidByte[0] != Master_Tag_ID[0] || rfid.uid.uidByte[1] != Master_Tag_ID[1] || rfid.uid.uidByte[2] != Master_Tag_ID[2] || rfid.uid.uidByte[3] != Master_Tag_ID[3] || rfid.uid.uidByte[4] != Master_Tag_ID[4])
      {
        Serial.println("New PICC detected! PICC not authorised"); 
      }
      else
      {
        Serial.println("Master PICC deetcted! Unlocking the goods...");
        M1.writeMicroseconds(2000); // Unlock safe.
      }
  }

}
