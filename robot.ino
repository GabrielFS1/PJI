#include <SoftwareSerial.h>

SoftwareSerial bluetooth(0, 1); // RX, TX Arduino

char bl = ' ';

// H bridge pins
int ENA = 3;
int IN1 = 4;
int IN2 = 5;

int IN3 = 8;
int IN4 = 7;
int ENB = 6;

int vel = 30;

// Reflectance Sensors pins
int sensor_left = 11;
int sensor_center = 10;
int sensor_right = 9;

int left_val, center_val, right_val;

/* Selects the control mode
false = Bluetooth control
true = Follower Line
*/
bool mode = false;

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);

    // Defines H bridge pins
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Defines Reflectance Sensors pins
    pinMode(sensor_left, INPUT);
    pinMode(sensor_center, INPUT);
    pinMode(sensor_right, INPUT);

    setVel(vel);
}

void loop()
{
    // Reads the bluetooth data
    if (bluetooth.available() > 0)
    {
        bl = bluetooth.read();
    }

    changesVel(bl);

    if (bl == 'x' || bl == 'X')
    {
        mode = modeSelection(bl);
    }

    if (mode == false)
    {
        bluetoothControl(bl);
    }
    else
    {
        follower();
    }
}

void follower()
{
    // Reads the sensors
    left_val = digitalRead(sensor_left);
    center_val = digitalRead(sensor_center);
    right_val = digitalRead(sensor_right);

    if ((left_val == 0) && (center_val == 1) && (right_val == 0))
    {
        setVel(vel);
        forward();
    }
    else if ((left_val == 1) && (center_val == 0) && (right_val == 0))
    {
        setVel(1.5 * vel);
        right();
    }
    else if ((left_val == 1) && (center_val == 1) && (right_val == 0))
    {
        setVel(1.5 * vel);
        right();
    }
    else if ((left_val == 0) && (center_val == 0) && (right_val == 1))
    {
        setVel(1.5 * vel);
        left();
    }
    else if ((left_val == 0) && (center_val == 1) && (right_val == 1))
    {
        setVel(1.5 * vel);
        left();
    }
}

void bluetoothControl(char bl)
{
    if (bl == 'F')
    {
        forward();
    }

    else if (bl == 'B')
    {
        backward();
    }

    else if (bl == 'L')
    {
        left();
    }

    else if (bl == 'R')
    {
        right();
    }

    else if (bl == 'S')
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

void backRight()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void backLeft()
{
    digitalWrite(IN1, LOW);
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

void changesVel(char letter)
{
    // Checks if the bluetooth command is changing the robot velocity
    if (isDigit(letter) == true || letter == 'q')
    {

        if (letter == 'q')
        {
            vel = 10;
        }
        else
        {
            vel = letter - '0';
        }
        setVel(vel);
    }
}

void setVel(int velocity)
{
    vel = map(vel, 0, 10, 0, 255);
    analogWrite(ENA, velocity);
    analogWrite(ENB, velocity);
}

bool modeSelection(char letter)
{
    // Selects Follower Line mode
    if (letter == 'X')
    {
        return true;
    }
    // Selects Bluetooth control
    else if (letter == 'x')
    {
        return false;
    }
}