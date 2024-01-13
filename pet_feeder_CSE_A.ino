#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#include <time.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4  //D2
#define RST_PIN D3 //D1
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;


char input[12];
/**********************************/
LiquidCrystal_I2C lcd(0x3F, 16, 2);
/*****************************************/
unsigned long ch_no = 1889799;//Replace with ThingSpeak Channel number
const char * write_api = "LZUFYY9IIT8PZ6HC";//Replace with ThingSpeak write API
char ssid[] = "Priyanka10102020";
char pass[] = "Priya0906";

WiFiClient  client;
const char *str;
void setup()
{
  Serial.begin(9600);
  configTime(11 * 1800, 0, "pool.ntp.org", "time.nist.gov");
  Wire.begin(D2,D1);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(D8,OUTPUT);
    lcd.setCursor(0,0);
  lcd.print(" ***Wel-Come****");
  lcd.setCursor(0,1);
  lcd.print("CSE Department");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project Name:");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pet Feeder Automn");
   lcd.setCursor(0,1);
  lcd.print("Using IOT Tech");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project Guide:");
   lcd.setCursor(0,1);
  lcd.print("Mrs.Shikalgar Mam");
  delay(1500);
  lcd.clear();
   lcd.print("Project Members:");
   delay(1500);
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("Mr.Digvijay");
   lcd.setCursor(0,1);
   lcd.print("Ms.Shivani");
  delay(1500);
  lcd.clear();
  lcd.print("Ms Vishakha");
   lcd.setCursor(0,1);
  lcd.print("Ms.Priyanka");
   delay(2000);
   lcd.clear();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    lcd.clear();
     lcd.setCursor(0, 0);
    lcd.print("Waiting For");
    lcd.setCursor(0,1);
    lcd.print("WiFi Connection");
    delay(1000);
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi connected");
  delay(2000);
  lcd.clear();
  ThingSpeak.begin(client);
}
void loop()
{
  digitalWrite(D8,LOW);
  lcd.setCursor(0,0);
  lcd.print("Waiting For Pet");
  int a=digitalRead(D8);
    Serial.print("D8 Pin Status:");
    Serial.print(a);
  delay(1500);
  
  time_t now = time(nullptr);
  str = ctime(&now);
 
  Serial.println();
delay(1000);
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
 
  Serial.println();
  if (content.substring(1) == "0C D9 72 22") //change UID of the card that you want to give access
 
  {
    lcd.clear();
   
    Serial.print("Pet Name: Hello Bela");
    lcd.print("Hello Bela");
    lcd.setCursor(0,1);
    lcd.print(str);
    digitalWrite(D8,HIGH);
    int a=digitalRead(D8);
    Serial.print("D8 Pin Status:");
    Serial.print(a);
 
    Serial.println();
      
    delay(1000);
    statuss = 1;
    int rohan1=10;
         ThingSpeak.setField(1,str);
         ThingSpeak.setField(2,rohan1) ;
          ThingSpeak.writeFields(ch_no, write_api);
       
  }
if (content.substring(1) == "29 DD EE 6E") //change UID of the card that you want to give access
  {lcd.clear();
    
    Serial.print("Pet Name: Hello Tommy");
    lcd.print("Hello Tommy");
    delay(1000); 
    //senddata("Hello Tommy");
    int rohan=20;
    statuss = 1;
    lcd.setCursor(0,1);
    lcd.print(str);
    digitalWrite(D8,HIGH);
    int a=digitalRead(D8);
    Serial.print("D8 Pin Status:");
    Serial.print(a);
    Serial.println();
      
    delay(1000);
    delay(1000);
    ThingSpeak.setField(1,str);
    ThingSpeak.setField(2,rohan) ;
   ThingSpeak.writeFields(ch_no, write_api); 
   lcd.print("Data Updated");
   delay(1000);
  }
}
