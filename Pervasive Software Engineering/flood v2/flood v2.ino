/*Water level monitoring system with the New Blynk app
   https://srituhobby.com
*/
//Include the library files
#define CAYENNE_PRINT Serial
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <CayenneMQTTESP8266.h>
#include <Ultrasonic.h>

// Define the component pins
#define trig D7
#define echo D8
#define buzzer D0
#define LED2 D3
#define LED3 D4
#define LED4 D5
#define LED5 D6
#define relay 3

#define BLYNK_TEMPLATE_ID "TMPLEv5QlYCc"
#define BLYNK_DEVICE_NAME "flood detection"
#define BLYNK_AUTH_TOKEN "gklT40sjY5RDmyqcA7TnvAMq6usDapGT"
BlynkTimer timer;
Ultrasonic ultrasonic(trig, echo);

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 20, 4);

char auth[] = "gklT40sjY5RDmyqcA7TnvAMq6usDapGT";//Enter your Auth token
char ssid[] = "BIZNET";//Enter your WIFI name
char pass[] = "Sinsin33";//Enter your WIFI password

char username[] = "b2bb5010-8d00-11ed-8d53-d7cd1025126a";
char mqtt_password[] = "89eea56a85af3ad2c56cfbbbab1c970677cf0a98";
char client_id[] = "bdf2aed0-8d03-11ed-b193-d9789b2af62b";

//Enter your tank max value(CM)
int MaxLevel = ultrasonic.read();

int Level1 = 75;
int Level2 = 50;
int Level3 = 25;

// long t;
int distance;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  digitalWrite(buzzer, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Cayenne.begin(username,mqtt_password,client_id,ssid,pass);

  lcd.setCursor(0, 0);
  lcd.print("Water level");
  lcd.setCursor(4, 1);
  lcd.print("Monitoring");
  delay(4000);
  lcd.clear();

  //Call the functions
  timer.setInterval(100L, ultrasonicc);
}

//Get the ultrasonic sensor values
void ultrasonicc() {
  // digitalWrite(trig, LOW);
  // delayMicroseconds(4);
  // digitalWrite(trig, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trig, LOW);
  // long t = pulseIn(echo, HIGH);
  // int distance = t / 29 / 2;
  distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  Serial.print("Max Distance: ");
  Serial.println(MaxLevel);

  int blynkDistance = (distance - MaxLevel) * -1 * 100 / MaxLevel;
  if (distance  <= MaxLevel) {
    Blynk.virtualWrite(V0, blynkDistance);
  } else {
    Blynk.virtualWrite(V0, 0);
  }
  lcd.setCursor(0, 0);
  lcd.print("WLevel:");

  if (Level1 <= distance * 100 / MaxLevel) {
    lcd.setCursor(8, 0);
    lcd.print("Empty");
    lcd.print("      ");
    digitalWrite(buzzer, HIGH);
  } else if (Level2 <= distance * 100 / MaxLevel && Level1 > distance * 100 / MaxLevel) {
    lcd.setCursor(8, 0);
    lcd.print("Low");
    lcd.print("      ");
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer,HIGH);
    delay(100);
  } else if (Level3 <= distance * 100 / MaxLevel && Level2 > distance * 100 / MaxLevel) {
    lcd.setCursor(8, 0);
    lcd.print("Medium");
    lcd.print("      ");
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer,HIGH);
    delay(500);
  } else if (Level3 >= distance * 100 / MaxLevel) {
     lcd.setCursor(8, 0);
    lcd.print("High");
    lcd.print("      ");
    digitalWrite(buzzer, LOW);
  }
}

//Get the button value
BLYNK_WRITE(V1) {
  bool Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor is ON ");
  } else {
    digitalWrite(relay, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Motor is OFF");
  }
}

CAYENNE_OUT(V0){

  do {
    // digitalWrite(trig, LOW);
    // delayMicroseconds(4);
    // digitalWrite(trig, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(trig, LOW);
    // long t = pulseIn(echo, HIGH);
    // int distance = t / 29 / 2;
    distance = ultrasonic.read();

      // delay(2000);

  } while  (isnan(distance));


    Cayenne.virtualWrite(V0, distance * 100 / MaxLevel);

  }

CAYENNE_OUT(V1){
  Serial.print(digitalRead(D3));
  Cayenne.virtualWrite(V1, digitalRead(D3));
}



void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
  Cayenne.loop();
}