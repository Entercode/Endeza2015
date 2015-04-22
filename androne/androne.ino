#include <Servo.h>
#include <Wire.h>

Servo servoL;    // Left side rudder
Servo servoR;    // Right side rudder
Servo servoU;    // Up side rudder
Servo motor;     // Main motor

int op1 = 0;
int op2 = 0;
int tmp = 900;

bool f_waiting_data = false;
bool f_waiting_eop = false;


void setup() {
  pinMode(2, OUTPUT); // Flight indicator
  pinMode(3, OUTPUT); // Anchor 
  
  servoL.attach(9);
  servoR.attach(10);
  servoU.attach(11);
  
  
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0) {
    if(f_waiting_data == false) {
      op1 = Serial.read();
    }
    if(op1 / 100 == 0) { // もしop1がドローン向けの命令なら
      f_waiting_data = true;
      op2 = Serial.read();
      f_waiting_eop = true;
    }
    if(f_waiting_eop == true) {
      tmp = Serial.read();
      if(tmp == 109) {  // 完了コード受信
        f_waiting_data = false;
        f_waiting_eop = false;
        
        command(op1, op2);
        
      }
    }
  }
}

void command(int op1, int op2) {
  
}
