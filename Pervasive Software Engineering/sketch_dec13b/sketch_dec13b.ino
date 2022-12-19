#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2, 3); // Membuat RX Arduino menjadi pin 2 dan TX pin 
void setup()
{
  Serial.begin(115200);
  esp8266.begin(115200); 
}
 
void loop()
{
  if(esp8266.available()) // Mengecek apakah ESP mengirimkan pesan
  {
    while(esp8266.available())
    {
      char c = esp8266.read(); // Membaca karakter selanjutnya.
      Serial.write(c);
    }
  }

 

  if(Serial.available())
  {
      delay(500); 

    String command="";

    while(Serial.available()) // membaca perintah karakter by karakter
    {
    command+=(char)Serial.read();
    }
    esp8266.println(command); // mengirim karakter yang terpaca kepada ESP
  }
}