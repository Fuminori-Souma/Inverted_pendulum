//配線：https://rb-station.com/blogs/article/l298n-arduino-dc-motor

int motors[2][3] = {{4,2,3},{8,7,9}};
void setup() {
    for(int i = 0; i < 2; i++){
        pinMode(motors[i][0], OUTPUT);
        pinMode(motors[i][1], OUTPUT);
        pinMode(motors[i][2], OUTPUT);
    }
}

void stop() {
  for (int i = 0; i < 2; i++) {
     digitalWrite(motors[i][0], LOW);
     digitalWrite(motors[i][1], LOW);
   }
}

// motorNum: 0,1 回転させるモーターの番号
// direction: -1,1 回転させる方向
// power: 0~255 回転スピード
void spin(int motorNum, int direction, int power) {
  if(direction == 1){
    digitalWrite(motors[motorNum][0], HIGH);
    digitalWrite(motors[motorNum][1], LOW);
  }
  if(direction == -1){
    digitalWrite(motors[motorNum][0], LOW);
    digitalWrite(motors[motorNum][1], HIGH);
  }
  analogWrite(motors[motorNum][2], power);
}

void loop() {
   spin(0,1,100);
   delay(1000);
   spin(1,1,100);
   delay(1000);
   spin(0,-1,200);
   delay(1000);
   spin(1,-1,200);
   delay(1000);
   stop();
}
