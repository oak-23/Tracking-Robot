/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):  
  Group Member 1 (name & SID): Kristian Alexander George Coke 21216937
  Group Member 2 (name & SID): Oak Soe Oo 21228215
  
*/

// assign meaningful names to those pins that will be used

void checkTurn();

const int pinRR_Sensor = A1;
const int pinLL_Sensor = A0;
const int pinL_Sensor = A5;      //pin A5: left sensor 
const int pinB_Sensor = A4;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor 

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int rightSensor = 1;   // not sensing white

int countBumper = 0;   // bumper sensor not triggered yet

// Direction
const int LEFT = 0;
const int RIGHT = 1;
const int SPIN = 2;
const int STOP = 3;

int turnCounter = 0;
bool run = 0; 
// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinB_Sensor, INPUT);
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  pinMode(pinLL_Sensor, INPUT);
  pinMode(pinRR_Sensor, INPUT);
  
  pinMode(pinL_DIR, OUTPUT);
  pinMode(pinR_DIR, OUTPUT);
  
  pinMode(pinL_PWM, OUTPUT);
  pinMode(pinR_PWM, OUTPUT);
  
  // initialize output pins
  digitalWrite(pinL_DIR, HIGH);   //forward direction    
  digitalWrite(pinR_DIR, HIGH);   //forward direction
  analogWrite(pinL_PWM, 0);       //stop at the start position 
  analogWrite(pinR_PWM, 0);       //stop at the start position 
}

// the loop function runs over and over again forever

void loop() {

  // Arduino is reading the sensor measurements
  bumperSensor = digitalRead(pinB_Sensor);
  leftSensor = digitalRead(pinL_Sensor);
  rightSensor = digitalRead(pinR_Sensor);
  LL = digitalRead(pinLL_Sensor);
  RR = digitalRead(pinRR_Sensor);
  
  // car stops at the start position when bumper sensor no trigger
  if ( bumperSensor && (countBumper == 0 || countBumper == 2)) {
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }

  // bumper sensor is triggered at the start position for the 1st time
  else if ( !bumperSensor && countBumper == 0) {
    analogWrite(pinL_PWM, 200);
    analogWrite(pinR_PWM, 200);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    countBumper = countBumper + 1;
    delay(350);     //to let the car leave the start position with no miscount
  }
  
  // car is tracking on the white line
  else if ( bumperSensor && countBumper == 1) 
  { 
    if ( !leftSensor && !rightSensor && !LL  && !RR) {
        analogWrite(pinL_PWM, 200);
        analogWrite(pinR_PWM, 200);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);
        turnCounter++;
        run = true;
        checkTurn(); 
      }
    
    if ( !leftSensor && rightSensor ) {
        analogWrite(pinL_PWM, 200);
        analogWrite(pinR_PWM, 200);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);  
      }
    
    if ( leftSensor && !rightSensor ) {
        analogWrite(pinL_PWM, 200);
        analogWrite(pinR_PWM, 200);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 0);  
      }
    
    if ( leftSensor && rightSensor ) {
        analogWrite(pinL_PWM, 200);
        analogWrite(pinR_PWM, 200);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 1);  
      }
  }
  else if ( !bumperSensor && countBumper == 1) {
    countBumper = countBumper + 1;
  }
  else if (countBumper == 2) {
    analogWrite(pinL_PWM, 200);
    analogWrite(pinR_PWM, 200);
    digitalWrite(pinL_DIR, 0);
    digitalWrite(pinR_DIR, 0);
  }
  else if (countBumper == 3) {
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }
}

void turn(int direction) {
  if (direction == LEFT || direction == RIGHT) {
    analogWrite(pinL_PWM, 100);
    analogWrite(pinR_PWM, 100);
    digitalWrite(pinL_DIR, direction);
    digitalWrite(pinR_DIR, !direction); 
    delay(100);  
    analogWrite(pinL_PWM, 100);
    analogWrite(pinR_PWM, 100);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    delay(100);  
  }
  else if (direction == SPIN) {
    analogWrite(pinL_PWM, 200);
    analogWrite(pinR_PWM, 200);
    digitalWrite(pinL_DIR, 0);
    digitalWrite(pinR_DIR, 1);
    delay(1400);
  }
  else {
    countBumper = countBumper + 1;
  }
  run = false;
}

void checkTurn(){ 
  if (run == true){
    switch(turnCounter){
      case 1:
        turn(LEFT);
        break;
      case 2:
        turn(RIGHT);
        break;
      case 3:
        turn(LEFT);
        break;
      case 4:
        turn(SPIN);
        break;
      case 5:
        turn(LEFT);
        break;
      case 6:
        turn(RIGHT);
        break;
      case 7:
        turn(RIGHT);
        break;
      case 8:
        turn(LEFT);
        break;
      case 9:
        turn(RIGHT);
        break;
      case 10:
        turn(STOP);
        break;
      default:
        break;
    }
  }
}