#include <Servo.h>
#define S0 6
#define S1 7
#define S2 9
#define S3 8
#define sensorOut 10
#define myServo 5
#define myServo1 4

Servo servo,servo1;
int r = 0;
int g = 0;
int b = 0;
int color[4][3] = {
  // mau hong
  {37, 61, 50},
  {59, 111, 90},
  // mau tim
  {60, 68, 51},
  {90, 128, 95}
};

void setup() {
  //setting output
  servo.attach(myServo);
  servo1.attach(myServo1);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  //setting input
  pinMode(sensorOut, INPUT);
   //setting f = 100kHz 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  servo.write(150);
  delay(2000);
 
  //begin serial communication
  Serial.begin(9600);
}

int readColor() {
  servo.write(130);
  delay(1000);
  servo.write(70);
  delay(5000);
  
  //red filter
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  r = pulseIn(sensorOut, LOW);
  delay(100);

  //green filter
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  g = pulseIn(sensorOut, LOW);
  delay(100);

  //blue filter
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  b = pulseIn(sensorOut, LOW);
  delay(100);

  Serial.println("R = " + (String)r + " ,G = " + (String)g + " ,B = " + (String)b);
  if ((r <= color[1][0] && r >= color[0][0]) && (g <= color[1][1] && g >= color[0][1]) && (b <= color[1][2] && b >= color[0][2])) {
    // servo1.write(90);
    // rCounter++;
    return 0;
  }
  else if ((r <= color[3][0] && r >= color[2][0]) && (g <= color[3][1] && g >= color[2][1]) && (b <= color[3][2] && b >= color[2][2])) {
    // servo1.write(45);
    // yCounter++;
    return 1;
  }
  return -1;
}

void loop() {
  int check = readColor();
  if (check == 0) {
    Serial.println("This is pink color!");
  }
  else if (check == 1) {
    Serial.println("This is purple color!");
  }
  else {
    Serial.println("No color!");
  }

  if(check == 0){
    servo1.write(70);
    delay(2000);
  }
  else if(check == 1){
    servo1.write(100);
    delay(2000);
  }
  else{
    servo1.write(130);
    delay(2000);
  }
  servo.write(40);
  delay(2000);
  servo.write(20);
  delay(2000);
  servo.write(150);
  delay(2000);

}