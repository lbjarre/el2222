const byte LEFT_MOTOR_IN1 = 11;
const byte LEFT_MOTOR_IN2 = 10;
const byte LEFT_MOTOR_ENBL = 6;
const byte LEFT_MOTOR_HALL = 3;
unsigned int left_hall_count;
float left_wheel_speed = 0;
float t_prev = 0;


void setup() {
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_ENBL, OUTPUT);
  pinMode(LEFT_MOTOR_HALL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_MOTOR_HALL), hallCounter, RISING);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(left_hall_count);
  calcLeftSpeed();
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  analogWrite(LEFT_MOTOR_ENBL, 120);
  Serial.println(left_wheel_speed);

  delay(100);
}

void hallCounter(){
  left_hall_count++;
}

void calcLeftSpeed(){
  left_wheel_speed = float(left_hall_count)*1000.0/(384.0*(float(millis()) - t_prev));
  left_hall_count = 0;
  t_prev = float(millis());
}

