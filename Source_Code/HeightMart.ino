
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLnG66Cxzw"
#define BLYNK_DEVICE_NAME "Tinggi Badan"
//#define BLYNK_AUTH_TOKEN "GMb1eChODpOXpf_HvD8jCQ0w3NIlhV7i"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#include <SPI.h> // pemanggil library SPI
#include <Wire.h> // pemanggil library komunikasi serial
#include <Adafruit_GFX.h> //pemanggilan library GFX
#include <Adafruit_SSD1306.h> //pemanggilan library OLED SSD1306
#include <HCSR04.h> //Memasukkan library HCSR04

#define SCREEN_ADDRESS 0x3C //alamat untuk I2C OLED

int jarak, tinggi;
HCSR04 hc(D6, D7);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire); //OLED menggunakan kolom 128 pixel dan baris 64 pixel

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BlynkTimer timer;

void sensor() {
  jarak = hc.dist();
  tinggi = 200 - jarak;
  Serial.print("Jarak (cm):");
  Serial.println(jarak);
  Serial.print("Tinggi (cm):");
  Serial.println(tinggi);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Tinggi (cm): ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(tinggi);
  display.display(); // menampilkan isi OLED
  display.clearDisplay(); // membersihkan tampilan
  //Blynk.virtualWrite(V3, jarak); //mengirimkan data jarak ke Virtual pin V3 di Blynk Cloud
  Blynk.virtualWrite(V2, tinggi); //mengirimkan data tinggi ke Virtual pin V2 di Blynk Cloud
}

void setup() {
  Serial.begin(115200);
  BlynkEdgent.begin();
  timer.setInterval(1000L, sensor);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.setTextSize(2); //ukuran teks
  display.setTextColor(SSD1306_WHITE); //warna OLED (putih)
  display.clearDisplay(); //membersihkan display oled

  // timer.setInterval(1000L, sensor);
  // Serial.begin(115200);
  // delay(100);
  // BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}
