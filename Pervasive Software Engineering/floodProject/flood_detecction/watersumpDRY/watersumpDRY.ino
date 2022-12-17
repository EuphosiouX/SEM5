// include the library code:


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <NewPing.h> // Include  library used for measuring the distance using HC-SR 06 sonar sensor
#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN   7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
#define MOTORPIN 8 // Arduino pin tied to Relaypin of the Relay Circuit
//#define EXTRELAYPIN 13 // Arduino pin tied to vin pin of the External Relay Circuit
#define BUZZER 9 // Arduino pin tied to +ve terminal of the Buzzer

float val;

#include <EEPROM.h>
int addr = 0;
int addr2 = 1;
int flag;
byte readval;

#define buttonPin 10
int buttonState = 0;      // variable for reading the pushbutton status
float TankHeight, WaterLevelMAX, GapbwSonar, SonarReading, ActualReading,  Temp;
int percentage;
int DRYSensorPin = A0; // set A0 as the Spump water sensor pin
int DRYsensorValue = 0;  // variable to store the value coming from the sensor

void setup() {

  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.begin(20, 4); // set up the LCD's number of columns and rows:

  pinMode(MOTORPIN,OUTPUT);// Relay pin as output pin
 // pinMode(EXTRELAYPIN,OUTPUT);// External Relay pin as output pin
  digitalWrite(MOTORPIN,LOW); //Turn off the relay
//  digitalWrite(EXTRELAYPIN,HIGH); //Turn off the external relay(External Relay I used was turning on while giving LOW signal, Check your one while doing the program)
  pinMode(BUZZER,OUTPUT);// Buzzer pin as output pin
  digitalWrite(BUZZER,LOW);  //Turn off the Buzzer

  lcd.setCursor(0,0);
  lcd.print("SMART WATER LEVEL   ");
  lcd.setCursor(0,1);
  lcd.print("CONTROL SYSTEM      ");
  lcd.setCursor(0,2);
  lcd.print("USING ULTRASONIC   ");
  lcd.setCursor(0,3);
  lcd.print("AND ANDROID APP    ");
  delay(2000);
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Starting ARDUINO, ");
   lcd.setCursor(0,1);
   lcd.print("Press SCAN Button to");
   lcd.setCursor(0,2);
   lcd.print("Change Tank Height  ");
   lcd.setCursor(0,3);
   lcd.print("If Required  ");
   delay(2000);
  

 // delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Confirm Tank Must be");
  lcd.setCursor(0,1);
  lcd.print("Empty to Set Tank   ");
  lcd.setCursor(0,2);
  lcd.print("Height using Sonar  ");
  delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Now Scan to Change  ");
 lcd.setCursor(0,1);
 lcd.print("Tank Height to New  ");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Long Press Button...");
  for (int i=0; i<=5; i++)

{
  lcd.setCursor(0,1);
  lcd.print("  Hold :  ");
  lcd.print(5-i);
  lcd.print(" Seconds ");
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW)
  {
  TankHeight =sonar.ping_cm();
  EEPROM.write(addr, TankHeight);
  }
delay(1000);
}
 
  {TankHeight= EEPROM.read(addr);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tank New Height Set@");
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.print(TankHeight);
  lcd.print("cm ");
  lcd.setCursor(0,2);
  lcd.print("Cheers             ");
   lcd.setCursor(0,3);
  lcd.print("WELCOME to SMART    ");
 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,2);
  lcd.print("TANK HEIGHT: ");
  //lcd.print("cm ");
  lcd.setCursor(12,2);
  lcd.print(TankHeight);
  lcd.print("cm ");
  
  WaterLevelMAX=0.9*TankHeight;  // 10CM GAP BETWEEN MAX WATER LEVEL TO SONAR FIX
 // WaterLevelMAX= 5-TankHeight;
  GapbwSonar=TankHeight-WaterLevelMAX;}


}
void loop() {

  // put your main code here, to run repeatedly:


  delay(50); // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  SonarReading=sonar.ping_cm();
  DRYsensorValue=analogRead(DRYSensorPin);

  //Serial.println(DRYsensorValue);

  Temp= SonarReading-GapbwSonar;
  ActualReading= WaterLevelMAX-Temp;
  percentage=(ActualReading/WaterLevelMAX*100);
  Serial.println(percentage);
  //Serial.println(TankHeight);
  lcd.setCursor(0,0);
  lcd.print("WATER LEVEL:");
  lcd.print(percentage);
  lcd.print("%  ");
  if(DRYsensorValue>=100)

  {

  if(percentage<=20)

  {
   lcd.setCursor(0,3);
  lcd.print("SUMP: WATER FILLED ");
  lcd.setCursor(0,1);
  lcd.print("PUMP STATUS: RUNNING");
  digitalWrite(MOTORPIN,HIGH);
//  digitalWrite(EXTRELAYPIN,LOW);
  flag=1;
  EEPROM.write(addr2, flag);
  flag= EEPROM.read(addr2);

//  ZeroPercentage();

  }

  else if(percentage>20 && percentage<=100)

  {

  flag= EEPROM.read(addr2);
  if(percentage>20 && percentage<=100 && flag ==1)

  {
    digitalWrite(MOTORPIN,HIGH);
 //   digitalWrite(EXTRELAYPIN,LOW);
  lcd.setCursor(0,1);
  lcd.print("PUMP STATUS: RUNNING");
  }

   else if(percentage>20 && percentage<=100 && flag ==0)

  {
    digitalWrite(MOTORPIN,LOW);
 //   digitalWrite(EXTRELAYPIN,HIGH);
  lcd.setCursor(0,1);
  lcd.print("PUMP STATUS: OFF    ");

  }

   }

  else if(percentage>100)

  {

  delay(500);
  lcd.setCursor(0,1);
  lcd.print("PUMP STATUS: OFF    ");
  lcd.setCursor(0,0);
  lcd.print("Water Level:");
  lcd.print("100");
  lcd.print("%  ");
   digitalWrite(MOTORPIN,LOW);
 // digitalWrite(EXTRELAYPIN,HIGH);

  flag=0;

  EEPROM.write(addr2, flag);
  flag= EEPROM.read(addr2);

//  HundredPercentage();

  }

  }

 else if(DRYsensorValue<=100)

{

  flag= EEPROM.read(addr2);
  if(flag==1)

  { 
  //  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print("SUMP: WATER FILLED ");
  lcd.setCursor(0,1);
  lcd.print("PUMP STATUS: DRYRUN!");
  digitalWrite(BUZZER,HIGH);
  digitalWrite(MOTORPIN, LOW);
 // digitalWrite(EXTRELAYPIN, HIGH);
  delay(100);
  digitalWrite(BUZZER,LOW);
  delay(100);
  }

  else if(flag==0)

  {
  lcd.setCursor(0,3);
  lcd.print("SUMP: NOWATER/CHECK");
  }
}

}

 
