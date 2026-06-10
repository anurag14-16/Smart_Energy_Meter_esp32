#define BLYNK_TEMPLATE_ID "TMPL3vt9wQp12"
#define BLYNK_TEMPLATE_NAME "Smart energy meter"
#define BLYNK_AUTH_TOKEN "0dHrlWSbx08xjOs3S1aJeA_MODM-kj27"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Pin definitions
#define VOLTAGE_PIN 34
#define CURRENT_PIN 35
#define ALERT_LED   2

// LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
float voltage    = 0.0;
float current    = 0.0;
float power      = 0.0;
float energy_Wh  = 0.0;
float energy_kWh = 0.0;

unsigned long lastTime    = 0;
unsigned long currentTime = 0;
float deltaT = 0.0;

// ─── SETUP ───────────────────────────────────────
void setup() {
    Serial.begin(115200);
    pinMode(ALERT_LED, OUTPUT);

    Wire.begin(21, 22);
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smart Energy");
    lcd.setCursor(0, 1);
    lcd.print("Meter v1.0");
    delay(2000);
    lcd.clear();

    lastTime = millis();
}

// ─── LOOP ────────────────────────────────────────
void loop() {

    // 1. Read ADC
    int rawV = analogRead(VOLTAGE_PIN);
    int rawI = analogRead(CURRENT_PIN);

    // 2. Convert to real values
    voltage = 180.0 + (rawV / 4095.0) * 60.0;
    current = (rawI  / 4095.0) * 10.0;

    // 3. Calculate power
    power = voltage * current;

    // 4. Calculate energy
    currentTime = millis();
    deltaT      = (currentTime - lastTime) / 1000.0;
    lastTime    = currentTime;
    energy_Wh  += power * (deltaT / 3600.0);
    energy_kWh  = energy_Wh / 1000.0;

    // 5. Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V:");
    lcd.print(voltage, 1);
    lcd.print("V I:");
    lcd.print(current, 2);
    lcd.print("A");

    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(power, 0);
    lcd.print("W ");
    lcd.print(energy_kWh, 4);
    lcd.print("kWh");

    // 6. Alert logic
    if (voltage > 240.0 || current > 9.0) {
        digitalWrite(ALERT_LED, HIGH);
        Serial.println("ALERT: Threshold exceeded!");
    } else {
        digitalWrite(ALERT_LED, LOW);
    }

    // 7. Send to Blynk
    Blynk.virtualWrite(V0, voltage);
    Blynk.virtualWrite(V1, current);
    Blynk.virtualWrite(V2, power);
    Blynk.virtualWrite(V3, energy_kWh);

    // 8. Debug serial
    Serial.print("V:"); Serial.print(voltage);
    Serial.print(" I:"); Serial.print(current);
    Serial.print(" P:"); Serial.print(power);
    Serial.print(" kWh:"); Serial.println(energy_kWh);

    // 9. Run Blynk
    Blynk.run();

    delay(1000);
}
