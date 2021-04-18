#include <Servo.h>
int Aspeed,Bspeed,speed,Halt=90,center=90;      // motor speeds
int FRQ,TD;
float cm,A,B,distance;
Servo servoLeft,servoRight,servoScan;    // create servo object/s to control the servo/s 

void setup() 
{ 
  servoLeft.attach(2);        // attaches the servo/motor on pin 11 
  servoRight.attach(3);       // attaches the servo/motor on pin 12
  servoScan.attach(4);        // U/S distance scanner.
  servoLeft.write(90);         // Stop motors from running
  servoRight.write(90);        // Stop command
  delay(300);
  pinMode(13, OUTPUT);

   for (int i=0; i <= 5000; i++)
  {
     sound(i,40);
  } 
    
  scan();
  delay(3000);
} 

void loop() 
  {    
  distance=scanner(cm);
  if(distance <=18)
    {
     Radar();
    }
    distance=scanner(cm);
    if(distance >10)
    {   
    forward(45);

 } 
  }
//==================================================================================================
void stop() 
{
servoLeft.write(90);
servoRight.write(90);
}
//==================================================================================================
void forward(int Aspeed)
{
servoLeft.write(Aspeed);
speed=Halt-Aspeed;
Bspeed=Halt+speed;
servoRight.write(Bspeed);
}
//==================================================================================================
 void backward(int Aspeed)
{
servoLeft.write(Aspeed);
speed=Halt-Aspeed;
Bspeed=Halt+speed;
servoRight.write(Bspeed);
}
//==================================================================================================
void turn(int Aspeed) 
{
servoLeft.write(Aspeed);
servoRight.write(Aspeed);
}
//==================================================================================================  
void scan()
{  
      servoScan.write(90);
      delay(1000);
   for (int i=0; i <= 180; i++)
     {
      servoScan.write(i);
      delay(20);
  }

      for (int i=180; i >= 0; i--)
     {
      servoScan.write(i);
      delay(20);
   }
       delay(1000);
       servoScan.write(90);
       delay(1500);
}
//=================================================================================================
void sound(int FRQ,int TD)
{
    tone(13,FRQ,TD);
}
//=================================================================================================

void Radar()
{
    stop();
    delay(200);
    backward(85);
    delay(500);
    stop();
    servoScan.write(0);
    delay(500);
    sound(2200,20);
    A=scanner(cm);
    delay(100);
    servoScan.write(180); 
    delay(500);
    sound(2200,20);
    B=scanner(cm);
    delay(100);
    servoScan.write(90);
    delay(100);

    if (A>B) 
    {
        turn(150);  //Then turn left
        delay(300);
      
    }
    else  
    {
        turn(30);  //Then turn right
        delay(300);
    }
}
 //======================================================================================================
 long scanner(long cm)
{
   const int pingPin=7, EchoPin=8;
    long duration;

    // The SRF005 is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse before to ensure a clean HIGH pulse:
    pinMode(pingPin, OUTPUT);
    pinMode(EchoPin, INPUT);  

    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(pingPin, LOW); 
    duration = pulseIn(EchoPin, HIGH);
    delay(100);

    // convert the time into a distance
    // inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
    return (cm);
}
//------------------------------------------------------------------
long microsecondsToCentimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimetre.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}
