#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL6tb7xB4vP"
#define BLYNK_DEVICE_NAME "schooMyIoT"
#define BLYNK_AUTH_TOKEN "XOyrGB63lhvQ57A2-G-mPeC6SSp-gnhL"

#define blynkLedPin 33 // BlynkステータスLEDのピン

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XOyrGB63lhvQ57A2-G-mPeC6SSp-gnhL";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AP01-01";
char pass[] = "1qaz2wsx";

#define press_pin 32
#define vibrationMotorPin 13 // 振動モジュールの制御ピン

#define on HIGH
#define off LOW

int ledStatus = 0;

float ain, vo, rf;

void setup() 
{
  Serial.begin(115200);
  pinMode(press_pin, INPUT);
  pinMode(vibrationMotorPin, OUTPUT); // 振動モジュールの制御ピン

  // Blynk初期化
  pinMode(blynkLedPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() 
{
  Blynk.run(); // Blynkを実行
  
  // digitalWrite(vibrationMotorPin, !ledStatus);
  // Serial.println("---------------");
  // Serial.printf("LED Status = %d\r\n", ledStatus);

  ain = analogRead(press_pin);
  vo = ain * 3.3 / 4096;
  rf = 10000 * vo / (3.3 - vo);

  if (rf <= 10000)
  {
    digitalWrite(vibrationMotorPin, on); 
    digitalWrite(blynkLedPin, on); // BlynkのLEDをON
    delay(5000);
  }
  else
  {
    digitalWrite(vibrationMotorPin, off);
    digitalWrite(blynkLedPin, off); // BlynkのLEDをOFF
    delay(1000);
  }
  
  digitalWrite(vibrationMotorPin, !ledStatus);
  Serial.println("---------------");
  Serial.printf("LED Status = %d\r\n", ledStatus);

  delay(1000);
}

BLYNK_WRITE(V0) // Blynk Virtual Pin
{
  ledStatus = param.asInt();
}




