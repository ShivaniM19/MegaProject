
#include <ESP8266WiFi.h>

#include<Wire.h>
#include <time.h>
#include <SPI.h>

#include <Servo.h>

#include "HX711.h"
const int LOADCELL_DOUT_PIN = D1;
const int LOADCELL_SCK_PIN = D2;
HX711 scale;
/*********************/
Servo myservo;
Servo myservo1;
/***********************/
const int trigger =D3;
const int echo =D4;
long T;
float distanceCM;
/***************************/

float wt=100.00;
float c;

void setup()
{
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(120.f);  
  scale.tare();  
  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));    // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
     
  Serial.println("Readings:");
  long rohan;
   pinMode(D8,INPUT);
   myservo.attach(D5);
   myservo1.attach(D6);
  
   pinMode(trigger, OUTPUT);
   pinMode(echo, INPUT);
   /************************/

  
   /***************************/
  
}
void loop()
{
   myservo.write(0);
   myservo1.write(0);
int a=digitalRead(D8);
  Serial.print("Recived From Node1:");
  Serial.println(a);
  delay(1000);
  if(a==1)
  {
    dist();
         if (distanceCM<18)
        {          
           myservo.write(0);
           myservo1.write(0);
           Serial.println("Dispenser OFF");
          delay(1000);
         }
      else 
      {
         c=scale.get_units(10),1 ;
         Serial.print(c);
         delay(1000);
        
        while(c<wt)
        {
          Serial.print("Weight Processing:");
           Serial.println(scale.get_units(10), 1);
           Serial.println(" \t Dispenser ON");
          delay(1000);
          myservo1.write(180);
          c=scale.get_units(10),1 ;
        } 
        
      }       
          Serial.println("Weight>50gm");
           myservo1.write(0);
           myservo.write(180);
          delay(1000);
          
          
         }
      
    
  
    else
    {
      myservo1.write(0);
      myservo.write(0);
      }
  

      
}
void flapopen()
{
 myservo.write(180);
 }
 void flapclose()
{
 myservo.write(0);
 }

 /******************Distance***/
 void dist()
 {
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  delay(1000);
  }
 /*******************************(Loadcell)*/
  void load()
  {
  
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();              
  delay(1000);
  scale.power_up();
  
    }
