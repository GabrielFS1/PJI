#include <SoftwareSerial.h>

SoftwareSerial bluetooth(0, 1); // RX, TX Arduino
char bl = ' ';

// H bridge pins
int IN1 = 5;
int IN2 = 6;
int IN3 = 7;
int IN4 = 8;
int ENA = 9;
int ENB = 10;

// Reflectance Sensors pins
int sensor_left = 11;
int sensor_center = 12;
int sensor_right = 13;

int left, center, right;

int vel = 100;

void setup()
{
  bluetooth.begin(9600);
  Serial.begin(9600);

  // Defines H bridge pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENA, OUTPUT);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);

  // Defines Reflectance Sensors pins
  pinMode(sensor_left, INPUT);
  pinMode(sensor_center, INPUT);
  pinMode(sensor_right, INPUT);
}

void loop()
{

  // Lê os dados do bluetooth
  if (bluetooth.available() > 0)
  {
    bl = bluetooth.read();

    // Changes the motors velocity
    if (isDigit(bl) == true || bl == 'q')
    {
      if (bl == 'q')
      {
        vel = 10;
      }
      else
      {
        vel = bl - '0';
      }
      defineSpeed(vel);
    }
  }

  // Reads the sensors
  left = digitalRead(sensor_left);
  center = digitalRead(sensor_center);
  right = digitalRead(sensor_right);

  if ((left == 0) && (center == 1) && (right == 0))
  {
    forward();
  }
  else if ((left == 1) && (center == 1) && (right == 0))
  {
    left();
  }
  else if ((left == 1) && (center == 0) && (right == 0))
  {
    left();
  }
  else if ((left == 0) && (center == 1) && (right == 1))
  {
    right();
  }
  else if ((left == 0) && (center == 0) && (right == 1))
  {
    right();
  }
  else if ((left == 1) && (center == 1) && (right == 1))
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

void defineSpeed(int vel)
{
  vel = map(vel, 0, 10, 0, 255);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}
