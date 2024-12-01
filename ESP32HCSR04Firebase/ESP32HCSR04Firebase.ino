#include <WiFi.h>
#include <FirebaseESP32.h>

// Definisi pin trigger dan echo
const int TRIGGER_PIN = 15;
const int ECHO_PIN = 2;

// WiFi dan Firebase konfigurasi
#define WIFI_SSID "Nethome-Visti"
#define WIFI_PASSWORD "@Bedahuluno14!"
#define DATABASE_URL "https://wifiscanfirebase-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyDRZfCQmKFdjUwuW-lq4P5S3k2wntpP26E" // Ganti dengan Web API Key Anda

FirebaseData fbdo;
FirebaseConfig config;
FirebaseAuth auth;

unsigned long lastSendTime = 0; // Untuk menyimpan waktu terakhir pengiriman
const unsigned long interval = 5000; // Interval pengiriman data (5 detik)

void setup() {
  // Inisialisasi pin dan komunikasi serial
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);

  // Koneksi ke Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long startMillis = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if (millis() - startMillis > 10000) {
      Serial.println("\nConnection failed!");
      return;
    }
  }
  Serial.println("\nConnected with IP: " + WiFi.localIP().toString());

  // Konfigurasi Firebase
  config.database_url = DATABASE_URL;
  config.api_key = API_KEY;

  // Autentikasi Firebase
  auth.user.email = "surya.rahayuda@gmail.com"; // Ganti dengan email pengguna
  auth.user.password = "123456";               // Ganti dengan password pengguna
  Firebase.begin(&config, &auth);

  Serial.println("Firebase initialized.");
}

void loop() {
  unsigned long currentMillis = millis();

  // Mengukur jarak menggunakan sensor ultrasonik
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance_cm = duration * 0.0343 / 2;

  // Cek apakah waktu yang telah berlalu lebih besar dari interval
  if (currentMillis - lastSendTime >= interval) {
    lastSendTime = currentMillis;

    // Kirim data jarak ke Firebase
    if (Firebase.setInt(fbdo, "/device/distance", distance_cm)) {
      Serial.print("Distance sent successfully: ");
      Serial.println(distance_cm);
    } else {
      Serial.print("Error sending distance: ");
      Serial.println(fbdo.errorReason());
    }
  }

  // Jeda pendek untuk stabilisasi
  delay(100);
}
