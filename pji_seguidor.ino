#include <SoftwareSerial.h>

// H bridge pins
int IN2 = 4; // red
int IN1 = 2; // brown
int IN3 = 5; // green
int IN4 = 7; // yellow
int ENA = 3; // purple
int ENB = 6; // blue

// Reflectance Sensors pins
int sensor_left = 10;
int sensor_center = 9;
int sensor_right = 8;

int left_val, center_val, right_val;

int vel = 45;

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

  if ((left_val == 0) && (center_val == 0) && (right_val == 0))
  {
    forward();
  }
  else if ((left_val == 0) && (center_val == 1) && (right_val == 0))
  {
    forward();
  }
  else if ((left_val == 1) && (center_val == 1) && (right_val == 0))
  {
    right();
  }
  else if ((left_val == 1) && (center_val == 0) && (right_val == 0))
  {
    right();
  }
  else if ((left_val == 0) && (center_val == 1) && (right_val == 1))
  {
    left();
  }
  else if ((left_val == 0) && (center_val == 0) && (right_val == 1))
  {
    left();
  }
  else if ((left_val == 1) && (center_val == 1) && (right_val == 1))
  {
    stop();
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
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
