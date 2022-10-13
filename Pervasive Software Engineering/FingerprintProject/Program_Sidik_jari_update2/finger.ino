uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:


      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:

      return p;
    case FINGERPRINT_PACKETRECIEVEERR:

      return p;
    case FINGERPRINT_IMAGEFAIL:

      return p;
    default:

      return p;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:

      delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:

      return p;
    case FINGERPRINT_PACKETRECIEVEERR:

      return p;
    case FINGERPRINT_FEATUREFAIL:

      return p;
    case FINGERPRINT_INVALIDIMAGE:

      return p;
    default:

      return p;
  }


  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {


  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {

    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {

    return p;
  } else {

    return p;
  }

}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
    lcd.clear();
    delay(15);
    lcd.setCursor(1, 0);
    lcd.print("Akses Ditolak");
    Serial.println("Salah");

    while (p != FINGERPRINT_NOFINGER) {
      p = finger.getImage();
      Serial.println("Lepaskan");
    }
    delay(2000);
    lcd.clear();
    delay(15);
    return -1;
  }
  lcd.clear();
  delay(15);
  digitalWrite(relay1, HIGH);
  lcd.setCursor(1, 0);
  lcd.print("Akses Diterima");
  lcd.setCursor (0, 1);
  lcd.print(F("AutoLock after "));
  for (int i = 5; i > 0; i--) {
    lcd.setCursor (15, 1); lcd.print(i);
    delay (1000);
  }
  digitalWrite(relay1, LOW);
  lcd.clear();
  delay(15);

  return finger.fingerID;
}
