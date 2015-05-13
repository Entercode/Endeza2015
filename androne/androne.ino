#include <Servo.h>
#include <Wire.h>

// Servo
Servo servoL;    // Left side rudder
Servo servoR;    // Right side rudder
Servo servoU;    // Up side rudder
Servo motor;     // Main motor

float offL = 0;  // servo offset l
float offR = 0;  // servo offset r
float offU = 0;  // servo offset u

// Opatation
byte code[2];
byte op = 0;
byte vl = 0;
byte ack = 0xff;
byte nul = 0x00;

// Prototype
void initialize();
void calibration();
void command(byte op, byte val);

// Text
char s[128];

int k = 0;

void setup() {
  
  initialize();
  
}

void loop() {
  while(Serial.available() > 0) {
    
    // Read Oparation Code
    Serial.readBytes(&op, 1);
    if(op == ack) {
      Serial.print("Oparation waiting... ");
      Serial.readBytes(code, 2);
      Serial.print("Code: ");
      Serial.print(code[0], HEX);
      Serial.print(" : ");
      Serial.print(code[1], HEX);
      Serial.print(" ... ");
      Serial.readBytes(&op, 1);
      
      if(op == code[0]) {
        Serial.print(op, HEX);
        Serial.println("Checked");
        
        // Run Oparation Code
        command(code[0], code[1]);
        
      } else {
        Serial.println("Unchecked => Delete OP");
        code[0] = 0x00;
        code[1] = 0x00;
      }
    }
  }
}

void command(byte op, byte val) {
  // Run Oparation Code
  // 00 ~ 8f : androne
  // 80 ~ ff : controller
  // 00 nop
  // 01 calibration all
  // 02 calibration compass
  // 03 calibration gps
  // 04 calibration gyro
  // 10 arm check
  // 11 arm
  // 12 disarm
  // 20 control all(ML,MR,SL,SR,SU)
  // 21 control motor L(01 ~ fe)
  // 22 control motor R(01 ~ fe)
  // 23 control servo L(01 ~ fe)
  // 24 control servo R(01 ~ fe)
  // 25 control servo U(01 ~ fe)
  // 30 control anchor(01 / fe)
  // 31 text(Size,text...)
  // 40 test sos
  // 41 test speaker
  
  
  switch(op) {
    case 0x00:
      Serial.println("nop");
      break;
    case 0x01:
      
      break;
    case 0x02:
      
      break;
    case 0x03:
      
      break;
    case 0x04:
      
      break;
    case 0x10:
      Serial.println("arm check");
      break;
    case 0x11:  // arm
      Serial.println("arm");
      break;
    case 0x12:  // disarm
      Serial.println("disarm");
      break;
    case 0x20:
      Serial.println("control all");
      break;
    case 0x21:
      Serial.println("control motorL");
      break;
    case 0x22:  // arm
      Serial.println("control motorR");
      break;
    case 0x23:  // disarm
      Serial.println("control servoL");
      break;
    case 0x24:
      Serial.println("control servoR");
      break;
    case 0x25:
      Serial.println("control servoU");
      break;
    case 0x30:  // arm
      Serial.println("control anchor");
      break;
    case 0x31:  // text
      Serial.println("text");
      
      while(k >= 0 && k < 128) {
        s[k] = Serial.read();
        Serial.print(s[k]);
        k++;
        if(s[k] == 0x03) {
          Serial.print("EOT");
          k = -99;
        }
      }
      break;
    case 0x40:
      Serial.println("test sos");
      break;
    case 0x41:
      Serial.println("test speaker");
      break;  
    default:
      Serial.println("err: Unknown op code");
      break;
  }
}

void initialize() {
  pinMode(2, OUTPUT); // Flight indicator
  pinMode(3, OUTPUT); // Anchor 
  pinMode(4, INPUT);  // Multi purpose button
  
  servoL.attach(9);  // these pins should be PWM pins.
  servoR.attach(10);
  servoU.attach(11);
  
  
  Serial.begin(9600);
  
  if(digitalRead(4)) {
    calibration();
  }
}

void calibration() {
  bool f_isBtn = false;
  Serial.println("\n=== Calibration Mode ===");
  Serial.println("rotate servo horn to set neutral position.");
  Serial.println("Press the button to save calibration");
  
  while(!f_isBtn) {
    if(digitalRead(4)) {
      Serial.print("Saving");
      offL = servoL.read();
      delay(100);
      Serial.print("...");
      offR = servoR.read();
      delay(100);
      Serial.print("...");
      offU = servoU.read();
      delay(100);
      Serial.print("...OK");
    }
  }
  
  Serial.println("\nCalibration Finished!\n");
  delay(1000);
}
