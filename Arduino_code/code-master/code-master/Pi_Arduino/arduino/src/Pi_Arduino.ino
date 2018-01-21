#include "motors.h"

const double DEG_PER_TIC = (double)360/(double)384;
const double WHEEL_RADIUS = 0.06425/2;
const double ROBOT_BASE = 0.13;
unsigned long LOOP_DELAY = 200;
double linear_cmd = 0;
double angular_cmd = 0;
unsigned int left_enc_count, right_enc_count;
unsigned long time_prev, time_now;
double left_angular_vel, right_angular_vel;
bool left_reverse, right_reverse;
bool newData;
int counter = 0;
int cycles  = 20; //Default 40 cyles, one second
//Create motor objects with connections and  parameters
//arguements: encoder pin, to motor : out1, out2, enable pin,inverse direction,Kp,Ki,Kd
Motor left_motor(3,10,11,6,true,3,0,0.1);
Motor right_motor(2,8,9,5,false,3,0,0.1);

void setup() {
  //Serial communication initialization
  Serial.begin(9600);
  //Configure interrupt pins for encoders
  attachInterrupt(digitalPinToInterrupt(left_motor.ENCODER_PIN), left_tic_counter ,CHANGE);
  attachInterrupt(digitalPinToInterrupt(right_motor.ENCODER_PIN), right_tic_counter ,CHANGE);
}

void loop() {
  //function to read and intrepret the serial data received from raspberrypi
  newData = readSerialCmd(&left_angular_vel, &right_angular_vel
                          &left_reverse, &right_reverse);
  if(newData == 1){
    left_motor.calc_angular_vel();
    right_motor.calc_angular_vel();
    counter = 0;
    cycles  = 40;
  }
  else{
    counter += 1;
  }
    left_motor.rotate(left_angular_vel, left_reverse);
    right_motor.rotate(right_angular_vel, right_reverse);
  if(counter > cycles){
      left_angular_vel = 0;
      right_angular_vel = 0;
      counter = 0;
  }
    delay(LOOP_DELAY);//Defines control loop frequencyś }
}

//Callback functions when interrupt are triggered by encoders
void left_tic_counter(){
  left_motor.tic_counter();
}
void right_tic_counter(){
  right_motor.tic_counter();
}
