const int S0 = 7;
const int S1 = 6;
const int outPut= 5;
const int S2 = 4;
const int S3 = 3;
const int buzzer= 7;

unsigned int frequency = 0;
 
void setup()
{

Serial.begin(9600);
 
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);

pinMode(OutPut, INPUT);
pinMode(buzzer, OUTPUT);

digitalWrite(S0,HIGH);
digitalWrite(S1,HIGH);
}
void loop()
{

digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
frequency = pulseIn(outPut, LOW);
if(frequency>0)
digitalWrite(buzzer,HIGH);
else
digitalWrite(buzzer,LOW);

}
