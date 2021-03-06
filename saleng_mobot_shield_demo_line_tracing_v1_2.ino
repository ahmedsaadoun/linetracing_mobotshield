/* Hardware notes
 * 3 Saleng Trackers on pins headers
 * I1(left),I2(center) and I3(right)
 * Install right motor(s) on AIN1 & AIN2
 * Install left motor(s) on BIN1 & BIN2
 */

// change below to define if line 
// is black on white background or
// white on black background.
// These define the sensor value when
// under black and white surface
// You may also use the DO and ~DO
// pins of the Saleng Tracker to 
// change line configuration

#define BLK LOW  // line
#define WHT HIGH // background

// speed setting based on movement
// 255=full speed
#define SPEED_ON_TURNS 48
#define SPEED_FORWARD 64
#define SPEED_BACKWARD 32

#define AIN1 2 
#define BIN1 7
#define AIN2 4
#define BIN2 5
#define PWMA 3
#define PWMB 6
#define STBY 8
#define SENSOR_L A0
#define SENSOR_C 11
#define SENSOR_R 10

byte sensorL, sensorC, sensorR;


void speedSetting(byte val)
{
  analogWrite(PWMA,val);
  analogWrite(PWMB,val);
}

void forward()
{
  speedSetting(SPEED_FORWARD);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
}

void backward()
{
  speedSetting(SPEED_BACKWARD);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
}

void turnleft()
{
  speedSetting(SPEED_ON_TURNS);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
}

void turnright()
{
  speedSetting(SPEED_ON_TURNS);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
}

void motorstop()
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
}

void shortbreak()
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,HIGH);
}


void setup() {
  pinMode(SENSOR_L,INPUT);
  pinMode(SENSOR_C,INPUT);
  pinMode(SENSOR_R,INPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  digitalWrite(STBY,HIGH);//enable driver
  //we use a slow speed to avoid
  // overshooting lines
  // and conserve battery
  // full speed = 255
  speedSetting(64); 
  delay(5000); // add 5s delay 
  Serial.begin(115200);
}

void loop() {
  // read and store all sensors
  sensorL = digitalRead(SENSOR_L);
  sensorC = digitalRead(SENSOR_C);  
  sensorR = digitalRead(SENSOR_R);  

  if(sensorL == BLK && sensorC == BLK && sensorR == BLK)
  {
    backward(); // assume we overshot line
  }
  else if(sensorL == WHT && sensorC == BLK && sensorR == BLK)
  {
    turnleft();
  }
  else if(sensorL == WHT && sensorC == BLK && sensorR == WHT)
  {
    // confused! Just move forward
    forward();
  }  
  else if(sensorL == BLK && sensorC == BLK && sensorR == WHT)
  {
    turnright();
  }
  else if(sensorL == BLK && sensorC == WHT && sensorR == BLK)
  {
    forward();
  }  
  else if(sensorL == WHT && sensorC == WHT && sensorR == BLK)
  {
    turnleft();
  }
  else if(sensorL == WHT && sensorC == WHT && sensorR == WHT)
  {
    forward();
  }   
  else if(sensorL == BLK && sensorC == WHT && sensorR == WHT)
  {
    turnright();
  } 
    
} 

