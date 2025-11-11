#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

// --- CONFIG ---
const char *WIFI_SSID = "";
const char *WIFI_PASS = "";

// --- PINS ---
const int BEAM_PIN = 27; // Treedix OUT pin

bool beamOK = true; // current state

void setup()
{
    Serial.begin(115200);
    pinMode(BEAM_PIN, INPUT_PULLUP);

    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.println("Mousetrap monitor armed.");
}

void loop()
{
    // flipped logic: HIGH = beam intact, LOW = beam broken
    beamOK = (digitalRead(BEAM_PIN) == HIGH);

    if (!beamOK)
    {
        // beam just broke → one-shot notification
        Serial.println("🐭 Beam broken! Sending notification...");
        sendNotification();
    }

    delay(100); // small delay to avoid loop spam
}

void sendNotification()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi not connected, skipping notification.");
        return;
    }

    HTTPClient http;

    http.begin(NTFY_ENDPOINT);
    http.addHeader("Title", "Mousetrap");
    http.addHeader("Priority", "5");
    int code = http.POST("🐭 Trap triggered — check the mousetrap!");
    if (code > 0)
        Serial.printf("Notification sent (HTTP %d)\n", code);
    else
        Serial.printf("HTTP error: %s\n", http.errorToString(code).c_str());
    http.end();
}
