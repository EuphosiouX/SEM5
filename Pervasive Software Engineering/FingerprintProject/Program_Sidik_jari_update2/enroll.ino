uint8_t getFingerprintEnroll(int id) {
  int p = -1;
  lcd.clear();
  delay(15);
  lcd.setCursor(1, 0);
  lcd.print("Silahkan Scan");
  lcd.setCursor(3, 1);
  lcd.print("Sidik Jari");
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:

        break;
      case FINGERPRINT_NOFINGER:

        break;
      case FINGERPRINT_PACKETRECIEVEERR:

        break;
      case FINGERPRINT_IMAGEFAIL:

        break;
      default:

        break;
    }
  }

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:

      break;
    case FINGERPRINT_IMAGEMESS:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:

      return p;
    case FINGERPRINT_FEATUREFAIL:
      delay(200);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      delay(200);
      return p;
    default:

      return p;
  }
  lcd.clear();
  delay(15);
  lcd.setCursor(1, 0);
  lcd.print("Lepaskan Jari");
  Serial.println("Lepaskan jari");
  delay(1000);

  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  p = -1;
  lcd.clear();
  delay(15);
  lcd.setCursor(1, 0);
  lcd.print("Tempelkan Jari");
  Serial.println("Tempelkan jari");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:

        break;
      case FINGERPRINT_NOFINGER:

        break;
      case FINGERPRINT_PACKETRECIEVEERR:

        break;
      case FINGERPRINT_IMAGEFAIL:

        break;
      default:

        break;
    }
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:

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

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {


  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {

    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    lcd.clear();
    delay(15);
    lcd.setCursor(1, 0);
    lcd.print("Gagal Disimpan");
    delay(150);
    delay(2000);
    lcd.clear();
    delay(15);
    return p;
  } else {

    return p;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    delay(15);
    lcd.setCursor(4, 0);
    lcd.print("Berhasil");
    lcd.setCursor(4, 1);
    lcd.print("Disimpan");
    Serial.println("Disimpan");
    delay(2500);
    lcd.clear();
    delay(15);

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {

    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {

    return p;
  } else if (p == FINGERPRINT_FLASHERR) {

    return p;
  } else {

    return p;
  }
}
