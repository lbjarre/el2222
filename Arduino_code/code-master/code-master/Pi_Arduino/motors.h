const double MICRO_PER_SEC = 1000000.0;
//Motor Class with different paramters for configuring the connections
class Motor{
private:
  bool INVERSE;
  double Kp, Ki, Kd;
  unsigned long time_prev, time_now;
  double angular_vel, time_diff, prev_err = 0, integ_err = 0;
  double TICS_PER_ROTATION = 384; //This can be varied based on interrupt configuration
  int current_pwm = 0;
public:
  byte ENCODER_PIN, OUT1, OUT2, ENB;
  unsigned int tic_count;
  Motor(byte enc_pin, byte out1, byte out2, byte enb, bool inverse,
    double Kp, double Ki, double Kd);
  void calc_angular_vel();
  void rotate(double ref, bool reverse);
  double get_angular_vel();
  void tic_counter();
  void pid_controller(double ref);
};

//Initialize the motor parameters
Motor::Motor(byte enc_pin, byte out1, byte out2, byte enb, bool inverse,
  double Kp, double Kd, double Ki){
  this->ENCODER_PIN = enc_pin;
  this->OUT1 = out1;
  this->OUT2 = out2;
  this->ENB = enb;
  this->INVERSE = inverse;
  this->Kp = Kp;
  this->Kd = Kd;
  this->Ki = Ki;
  this->time_prev = micros();
  pinMode(enc_pin, INPUT_PULLUP);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(enb, OUTPUT);
}

//function to calculate angular velocity
void Motor::calc_angular_vel(){
  this->time_now = micros();
  this->time_diff = this->time_now - this->time_prev;
  this->angular_vel = 1000000*this->tic_count/(this->TICS_PER_ROTATION*this->time_diff);
  this->tic_count = 0;
  this->time_prev = micros();
}
//function to rotate the motor, parameters: reference velocity and direction of motor
void Motor::rotate(double ref, bool reverse){
  switch(this->INVERSE){
    case true:
      switch(reverse){
        case true:
          digitalWrite(this->OUT1, HIGH);
          digitalWrite(this->OUT2, LOW);
          break;
        case false:
          digitalWrite(this->OUT1, LOW);
          digitalWrite(this->OUT2, HIGH);
          break;
      }
    case false:
      switch(reverse){
        case true:
          digitalWrite(this->OUT1, LOW);
          digitalWrite(this->OUT2, HIGH);
          break;
        case false:
          digitalWrite(this->OUT1, HIGH);
          digitalWrite(this->OUT2, LOW);
          break;
      }
  }
  this->pid_controller(ref);
  analogWrite(this->ENB, current_pwm);
}

//control algorithm to maintain the speed
void Motor::pid_controller(double ref){
  double err = this->angular_vel - ref;
  this->current_pwm = Kp*err + Kd*(err - this->prev_err) + Ki*this->integ_err;
  this->prev_err = err;
  this->integ_err += err;
}
//function to read the current angular velocity of motors
double Motor::get_angular_vel(){
  return this->angular_vel;
}
//function to increment the tics for each motor.
void Motor::tic_counter(){
  this->tic_count++;
}
