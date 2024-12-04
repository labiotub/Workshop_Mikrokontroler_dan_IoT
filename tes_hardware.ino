// Pin konfigurasi
const int potPin = 34; // Pin ADC untuk potensiometer
const int ledPin = 25; // Pin PWM untuk LED

void setup() {
  // Konfigurasi pin
  pinMode(potPin, INPUT); // Potensiometer sebagai input
  pinMode(ledPin, OUTPUT); // LED sebagai output
  
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
}

void loop() {
  // Membaca nilai potensiometer (0-4095 untuk ESP32 ADC)
  int potValue = analogRead(potPin);
  
  // Konversi nilai potensiometer ke rentang PWM (0-255)
  int pwmValue = map(potValue, 0, 4095, 0, 255);
  
  analogWrite(ledPin, pwmValue);

  // Tampilkan nilai di Serial Monitor
  Serial.print("Potensiometer: ");
  Serial.print(potValue);
  Serial.print(" -> LED PWM: ");
  Serial.println(pwmValue);

  // Delay untuk stabilitas
  delay(50);
}
