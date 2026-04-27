/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box): 001  
  Group Member 1 (name & SID): Kristian Alexander George Coke 21216937
  Group Member 2 (name & SID): Oak Soe Oo 21228215
  
*/

// assign meaningful names to those pins that will be used

int long TIMEOUT = 0.00;


const int pinRR_Sensor = A1;
const int pinLL_Sensor = A0;
const int pinL_Sensor = A5;      //pin A5: left sensor 
const int pinB_Sensor = A4;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor 

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction
const int debugPin = 8;

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int rightSensor = 1;   // not sensing white
int LL = 1;
int RR = 1;

int countBumper = 0;   // bumper sensor not triggered yet

// Direction
const int LEFT = 0;
const int RIGHT = 1;
const int SPIN = 2;
const int STOP = 3;
const int LEFTB = 4;
const int RIGHTB = 5;

// Speed
int speed = 175;
int spin_speed = 175;
int sharp_turn_speed = 350;
int forward_delay_B = 250;
int time = 150;
int time_1 = 150;

int turnCounter = 0;
bool run = 0; 
// the setup function runs once when you press reset or power the board


//turn timeout
long last_turn_time = 0;

void setup ()
{
  // define pins as input and output
  pinMode(pinB_Sensor, INPUT);
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  pinMode(pinLL_Sensor, INPUT);
  pinMode(pinRR_Sensor, INPUT);
  
  pinMode(debugPin, OUTPUT);

  pinMode(pinL_DIR, OUTPUT);
  pinMode(pinR_DIR, OUTPUT);
  
  pinMode(pinL_PWM, OUTPUT);
  pinMode(pinR_PWM, OUTPUT);
  
  // initialize output pins
  digitalWrite(pinL_DIR, HIGH);   //forward direction    
  digitalWrite(pinR_DIR, HIGH);   //forward direction
  digitalWrite(debugPin, LOW);
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
    last_turn_time = millis();
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    countBumper = countBumper + 1;
    delay(400);     //to let the car leave the start position with no miscount
  }
  
  // car is tracking on the white line
  else if ( bumperSensor && countBumper == 1) 
  { 
      if ( !leftSensor && !rightSensor) {
      
        analogWrite(pinL_PWM, speed);
        analogWrite(pinR_PWM, speed);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);
        run = true;
        checkTurn(); 

      }

      if ( !leftSensor && rightSensor ) {
         
        analogWrite(pinL_PWM, speed);
        analogWrite(pinR_PWM, speed);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1); 
      }
    
      if ( leftSensor && !rightSensor ) {
      
        
        analogWrite(pinL_PWM, speed);
        analogWrite(pinR_PWM, speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 0); 
      }
      
      if ( leftSensor && rightSensor ) {
        analogWrite(pinL_PWM, speed);
        analogWrite(pinR_PWM, speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 1);
      }

  }
  else if ( !bumperSensor && countBumper == 1) {
    countBumper = countBumper + 1;
  }
  else if (countBumper == 2) {
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 0);
    digitalWrite(pinR_DIR, 0);
    delay(1300);
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }
  
  delay(1);
}

void turn(int direction) {
  if (direction == LEFT || direction == RIGHT) {
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, direction);
    digitalWrite(pinR_DIR, !direction); 
    delay(time);  
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    delay(time_1);  
  }
  else if (direction == SPIN) {
    analogWrite(pinL_PWM, spin_speed);
    analogWrite(pinR_PWM, spin_speed);
    digitalWrite(pinL_DIR, 0);
    digitalWrite(pinR_DIR, 1);
    delay(1400);
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    delay(100);
  }else if (direction == LEFTB ) {
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 0);
    digitalWrite(pinR_DIR, 1); 
    delay(sharp_turn_speed);  
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    delay(forward_delay_B);  
  }else if (direction == RIGHTB ) {
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 0); 
    delay(sharp_turn_speed);  
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1); 
    delay(forward_delay_B);  
  }
  else {
    countBumper = countBumper + 1;
  }
  run = false;
}

void forward(int speed, int dt ){
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, 1);
    digitalWrite(pinR_DIR, 1);
    delay(dt);
}

void checkTurn(){ 
  if ((millis() - last_turn_time) < TIMEOUT){
    return;
  }
  
  if (run == true){
    switch(turnCounter){
      case 1:
        turn(LEFT);
        speed = 200;
        break;
      case 2:
        turn(RIGHT);
        speed = 150;
        break;
      case 3:
        TIMEOUT = 500;
        turn(LEFT);
        speed = 140;
        break;
      case 4:
        turn(LEFT);
        break;
      case 5:
        if ((millis() - last_turn_time) < 1400){
          turnCounter -= 1; 
          checkTurn();
          return;
        }
        turn(SPIN);
        speed = 150;
        TIMEOUT = 0;
        break;
      case 6:
        turn(LEFTB);
        speed = 120;
        break;
      case 7:
        turn(LEFTB);
        break;
      case 8:
        turn(RIGHTB);
        TIMEOUT = 200;
        break;
      case 9:
        turn(RIGHTB); //
        break;
      case 10:
        sharp_turn_speed = 350;
        turn(LEFTB); //
        break;
      case 11:
        turn(LEFTB);
        break;
      case 12:
        turn(RIGHTB);
        break;
      case 13:
        turn(LEFTB);
        break;
      case 14:
        turn(LEFTB);
        speed = 170;
        break;
      case 15:
         // Curves after 90 degree turns
        turn(RIGHT);
        break;
      case 16:
        turn(LEFT);
        break;
      case 17:  // T Junction to Square
        turn(LEFT);
        break;
      case 18: 
        speed = 120;
        forward_delay_B = 50;
        turn(LEFTB);
        sharp_turn_speed = 250;
        break;
      case 19:
        turn(RIGHTB);
        break;
      case 20:
        turn(LEFTB);
        digitalWrite(debugPin, HIGH);
        break;
      case 21:
        turn(LEFTB);
        break;
      default:
        break;
    }
  }
  last_turn_time = millis();
  turnCounter++;
  return;
}
