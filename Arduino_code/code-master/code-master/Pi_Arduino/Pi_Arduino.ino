#include "motors.h"

const double DEG_PER_TIC = (double)360/(double)384;
const double WHEEL_RADIUS = 0.06425/2;
const double ROBOT_BASE = 0.13;
unsigned int left_enc_count, right_enc_count;
unsigned long time_prev, time_now;
double left_angular_vel, right_angular_vel;
//Create motor objects with connections and  parameters
//arguements: encoder pin, to motor : out1, out2, enable pin,inverse direction,Kp,Ki,Kd
Motor left_motor(3,10,11,6,false,1,0,0.25);
Motor right_motor(2,8,9,5,true,1,0,0.25);

void setup() {
  //Serial communication initialization
  Serial.begin(9600);
  //Configure interrupt pins for encoders
  attachInterrupt(digitalPinToInterrupt(left_motor.ENCODER_PIN), left_tic_counter ,CHANGE);
  attachInterrupt(digitalPinToInterrupt(right_motor.ENCODER_PIN), right_tic_counter ,CHANGE);
}

void loop() {
  //function to read and intrepret the serial data received from raspberrypi
  readSerialCmd();
  left_motor.calc_angular_vel();
  right_motor.calc_angular_vel();
  //move Robot - Use below functions to set reference speed and direction of motor.
  left_motor.rotate(120,1);
  right_motor.rotate(120,1);
  
  delay(50);//Defines control loop frequency 
  Serial.println(left_motor.get_angular_vel());
}

//Callback functions when interrupt are triggered by encoders
void left_tic_counter(){
  left_motor.tic_counter();
}
void right_tic_counter(){
  right_motor.tic_counter();
}

