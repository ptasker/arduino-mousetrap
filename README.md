# arduino-mousetrap

An Arduino-based mousetrap monitor that sends notifications when the trap is triggered.

Hardware used was an ESP32 and an IR beam break sensor similar to this: https://www.adafruit.com/product/2168?srsltid=AfmBOoolzEJG8JrsSuC1hItuO-w1DujxbfG6Z136mYsyZ4INAJtncOB1

## Configuration

1. Copy your environment variables to `.env`:

   ```
   NTFY_ENDPOINT=https://ntfy.sh/your-private-topic
   ```

2. Generate the configuration header file:

   ```bash
   python3 generate_config.py
   ```

   This will create `config.h` from your `.env` file.

3. Update the WiFi credentials in `mousetrap.ino`:
   ```cpp
   const char* WIFI_SSID = "your-wifi-name";
   const char* WIFI_PASS = "your-wifi-password";
   ```

## Usage

1. Upload `mousetrap.ino` to your Arduino ESP32
2. The device will connect to WiFi and monitor the beam sensor
3. When the beam is broken (trap triggered), it sends a notification to your configured ntfy endpoint

## Files

- `mousetrap.ino` - Main Arduino sketch
- `.env` - Environment variables (not committed to git)
- `config.h` - Generated configuration header (not committed to git)
- `generate_config.py` - Script to generate config.h from .env
