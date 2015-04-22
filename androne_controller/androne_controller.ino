

int degLR;
int degUD;
int pwmVal;

void setup() {
  Serial.begin(9600);
}

void loop() {
  degLR = analogRead(A0);
  degUD = analogRead(A1);
  pwmVal = digitalRead();
}
