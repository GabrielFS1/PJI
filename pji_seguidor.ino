#include <SoftwareSerial.h>

// H bridge pins
int ENA = 3;
int IN1 = 4;
int IN2 = 5;

int IN3 = 8;
int IN4 = 7;
int ENB = 6;

int vel = 30;

// Reflectance Sensors pins
int sensor_left = 11
;
int sensor_center = 10;
int sensor_right = 9;

int left_val, center_val, right_val;

void setup()
{
  Serial.begin(9600); 

  // Defines H bridge pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);

  // Defines Reflectance Sensors pins
  pinMode(sensor_left, INPUT);
  pinMode(sensor_center, INPUT);
  pinMode(sensor_right, INPUT);

}

void loop()
{

  // Reads the sensors
  left_val = digitalRead(sensor_left);
  center_val = digitalRead(sensor_center);
  right_val = digitalRead(sensor_right);
  Serial.print("left: ");
  Serial.print(left_val);
  Serial.print(" center: ");
  Serial.print(center_val);
  Serial.print(" right: ");
  Serial.print(right_val);
  Serial.print("\n");

  if ((left_val == 0) && (center_val == 1) && (right_val == 0))
  {
    set_vel(vel);
    forward();
  }
  else if ((left_val == 1) && (center_val == 0) && (right_val == 0))
  {
    set_vel(1.5 * vel);
    right();
  }
  else if ((left_val == 1) && (center_val == 1) && (right_val == 0))
  {
    set_vel(1.5 * vel);
    right();
  }
  else if ((left_val == 0) && (center_val == 0) && (right_val == 1))
  {
    set_vel(1.5 * vel);
    left();
  }
  else if ((left_val == 0) && (center_val == 1) && (right_val == 1))
  {
    set_vel(1.5 * vel);
    left();
  }
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void set_vel(int velocity)
{
  analogWrite(ENA, velocity);
  analogWrite(ENB, velocity);
}
