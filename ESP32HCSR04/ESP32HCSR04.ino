// Definisi pin trigger dan echo pada Arduino
const int TRIGGER_PIN = 15;
const int ECHO_PIN = 2;

void setup() {
  // Inisialisasi pin sebagai input dan output
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Mengaktifkan komunikasi serial
  Serial.begin(9600);
}  

void loop() {
  // Set trigger pin ke LOW selama minimal 2 mikrodetik
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  
  // Set trigger pin ke HIGH selama minimal 10 mikrodetik
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // Mengukur durasi sinyal echo, yang akan dikonversi menjadi jarak
  long durasi = pulseIn(ECHO_PIN, HIGH);
  
  // Menghitung jarak berdasarkan durasi
  // Kecepatan suara di udara adalah 343 meter/detik atau 0.0343 cm/mikrodetik
  int jarak_cm = durasi * 0.0343 / 2;
  
  // Mencetak hasil ke serial monitor
  Serial.print("Jarak: ");
  Serial.print(jarak_cm);
  Serial.println(" cm");
  
  // Jeda selama 500ms sebelum mengukur kembali
  delay(500);
}