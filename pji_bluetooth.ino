#include <SoftwareSerial.h>

SoftwareSerial bluetooth(0, 1); // RX, TX Arduino
char bl = ' ';

// Ponte H
int IN1 = 5;
int IN2 = 6;
int IN3 = 7;
int IN4 = 8;
int ENA = 9;
int ENB = 10;

int vel = 100;

void setup()
{
  // Inicializa a comunicação com o módulo bluetooth
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENA, OUTPUT);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void loop() {

  // Lê os dados do bluetooth
  if (bluetooth.available() > 0) { // Se existem dados para leitura
    bl = bluetooth.read(); //Variável para armazenar o dado atual
    //Serial.print(bl); //Printa o comando
    //Serial.print('\n'); //Printa o comando
  }

  if (isDigit(bl) == true || bl == 'q') {
    
    if (bl == 'q') {
      vel = 10;
    }
    else
    {
    vel = bl - '0';
    }
    defineSpeed(vel);
  }
  else if (bl == 'F') {
    forward();
  }

  else if (bl == 'B') {
    backward();
  }

  else if (bl == 'L') {
    left();
  }

  else if (bl == 'R') {
    right();
  }

  else if (bl == 'S') {
    Stop();
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

void Stop()
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
