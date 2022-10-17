//Program by: Alim Mulyadi
//Created: 19/05/2021
//Program: Fingerprint Doorlock with add new user

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//------------------------------//
int tombol1 = A0;
int relay1 = 11;
int eadd = 0;
int getFingerprintIDez();
uint8_t getFingerprintEnroll(int id);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  eadd = EEPROM.read(0);
  if (eadd > 200)EEPROM.write(0, 0);

  pinMode(relay1, OUTPUT);
  pinMode(tombol1, INPUT_PULLUP);
  digitalWrite(relay1, HIGH);

  finger.begin(57600);
  if (finger.verifyPassword()) {

  } else {
    while (1);
  }
  eadd = EEPROM.read(0);
}

void loop() {
  int x;
  x = analogRead(0);
  lcd.setCursor (0, 0);
  lcd.print(F(" -System Ready- "));
  Serial.println(x);
  Serial.println(digitalRead(tombol1));

  if (60 < x && x < 200) {
    eadd += 1;
    if (eadd > 50)eadd = 0;
    EEPROM.write(0, eadd);
    getFingerprintEnroll(eadd);
    eadd = EEPROM.read(0);
  }

  else if (200 < x && x < 400) {
    finger.emptyDatabase();
    eadd = 0;
    EEPROM.write(0, eadd);
    lcd.clear();
    delay(15);
    lcd.setCursor(3, 0);
    lcd.print("Sidik Jari");
    lcd.setCursor(1, 1);
    lcd.print("Telah Dihapus");
    delay(2500);
    lcd.clear();
    delay(15);
    goto awal;
  }

awal:
  getFingerprintIDez();
  delay(100);
}
