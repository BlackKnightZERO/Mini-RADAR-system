
//
//video link - https://drive.google.com/open?id=1nZYP8AoI14d165ZRJCccQgkkYxPneX0A
//

#include <LedControl.h>
#include <MaxMatrix.h>
#include <Servo.h>

#define trig 8
#define echo 9

int pos = 0;
int distance1 = 0;
int distance2 = 0;

int degree1 = 0;
int degree2 = 0;

int flag = 0;

int DIN = 6;
int CLK = 5;
int CS = 4;
int MAXINUSE = 1;
int x = 0;
int y = 0;

MaxMatrix m(DIN, CS, CLK, MAXINUSE);
LedControl lc = LedControl(6, 5, 4, 1);

Servo myservo;

long duration, distance;


void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  myservo.attach(7);
  Serial.begin(9600);

  m.init();
  m.setIntensity(8);


  lc.shutdown(0, false);
  lc.setIntensity(0, 8); 
  lc.clearDisplay(0); 
}



int USRun()
{
  delay(5);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration / 58;
  delay(160);
  Serial.print("--Calculating Distance ->   ");
  Serial.print(distance);

  if (distance <= 32)
  {
    Serial.print("---FOUND---");
    return distance;
  }
  return 1000;
}



void DotMatrixDisplay(int r, int deg)
{
  x = (deg / 11) - 5;
  y = r / 4 - 1;
  m.setDot(x, y, true);
  //delay(10);
  Serial.print("--- X , Y -> ");
  Serial.print(x);
  Serial.print("---");
  Serial.print(y);
  Serial.print("---");
}

void columns() 
{
  for (int col = 7; col >= 0; col--)
  {
    delay(10);
    lc.setColumn(0, col, B11111111);
    delay(10);
    lc.setColumn(0, col, (byte)0);
  }
}


void loop()
{

  columns();
  m.clear();

  int distance1 = 101;
  int distance2 = 101;

  for (pos = 45; pos <= 133; pos += 2)
  {


    Serial.println(" ");
    Serial.println("  ^_^");
    delay(10);
    distance1 = USRun();
    degree1 = pos;
    if (distance1 != 1000 && distance1 < 100)
    {

      Serial.print(" Distance1 -> ");
      Serial.print(distance1);
      Serial.print("       Degree1 -> ");
      Serial.print(degree1);

      DotMatrixDisplay(distance1, degree1);
    }

    myservo.write(pos);
    delay(100);

  }
  //delay(50);

  columns();
  m.clear();


  for (pos = 133; pos >= 45; pos -= 2)
  {
    Serial.println(" ");
    Serial.println("  ^_^");
    delay(10);
    distance2 = USRun();
    degree2 = pos;
    if (distance2 != 1000 && distance2 < 100)
    {
      Serial.print("Distance2 -> ");
      Serial.print(distance2);
      Serial.print("      Degree2 -> ");
      Serial.print(degree2);

      DotMatrixDisplay(distance2, degree2);
    }

    myservo.write(pos);
    delay(100);
  }
}
