#define LED_PIN 25       // Pin LED
#define BUTTON_PIN 14    // Pin tombol (selain 25 dan 34)

void setup() {
  pinMode(LED_PIN, OUTPUT);       // Set LED sebagai output
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set tombol sebagai input dengan pull-up internal
  digitalWrite(LED_PIN, LOW);     // Awal LED mati

  Serial.begin(115200);           // Inisialisasi serial monitor
  Serial.println("Program dimulai. Tekan tombol untuk menyalakan LED.");
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN); // Baca status tombol

  if (buttonState == LOW) { // Tombol ditekan (LOW)
    digitalWrite(LED_PIN, HIGH); // Nyalakan LED
    Serial.println("Tombol ditekan - LED menyala");
  } else { // Tombol dilepas (HIGH)
    digitalWrite(LED_PIN, LOW); // Matikan LED
    Serial.println("Tombol dilepas - LED mati");
  }

  delay(50); // Tambahkan sedikit delay untuk mengurangi noise tombol
}
