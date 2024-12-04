#define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Your_Template_Name"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
const char* ssid = "Your_ssid";
const char* password = "Your_Password";

#define POT_PIN 34
#define LED_PIN 25

BlynkTimer timer;
bool ledOn = false; // Status LED (nyala/mati)

void readPotentiometer() {
  int potValue = analogRead(POT_PIN);                 // Baca nilai potensio
  float potPercentage = (potValue / 4095.0) * 100;   // Konversi ke persen
  Blynk.virtualWrite(V0, potPercentage);             // Kirim ke widget Gauge
  Serial.print("Potentiometer Value: ");             // Debug di Serial Monitor
  Serial.println(potPercentage);
  if(ledOn){
    analogWrite(LED_PIN, map(potValue, 0,4049, 0, 255));
  } else {
    // Jika LED mati, pastikan LED tidak menyala
    analogWrite(LED_PIN, 0);
  }
}

BLYNK_WRITE(V1) {
  int ledState = param.asInt();                      // Baca nilai dari switch
  ledOn = (ledState == 1);                          // Perbarui status LED
  digitalWrite(LED_PIN, ledState);                   // Kontrol LED
  Serial.print("LED State: ");                       // Debug di Serial Monitor
  Serial.println(ledState == HIGH ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);                              // Inisialisasi Serial Monitor
  Serial.println("Starting setup...");
  
  WiFi.begin(ssid, password);                        // Hubungkan ke WiFi
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {           // Tunggu koneksi WiFi
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);     // Hubungkan ke Blynk
  Serial.println("Connecting to Blynk...");
  pinMode(LED_PIN, OUTPUT);                          // Set LED pin sebagai output
  timer.setInterval(500L, readPotentiometer);        // Interval pembacaan potensio
}

void loop() {
  Blynk.run();                                       // Jalankan Blynk
  timer.run();                                       // Jalankan timer
}
