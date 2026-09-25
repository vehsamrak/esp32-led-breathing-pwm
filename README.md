# ESP32 LED Breathing Effect (PWM)

Smooth exponential breathing effect on a red LED using ESP32 LEDC pulse width modulation (PWM)

## Requirements

- [arduino-cli](https://arduino.github.io/arduino-cli/)
- ESP32 core for arduino-cli
- red LED
- resistor 110 R

```bash
arduino-cli config init
arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

## Wiring

| LED       | Resistor | ESP32     |
|-----------|----------|-----------|
| Anode +   | 110 Ω    | GPIO 13   |
| Cathode − |          | GND       |

The anode (longer leg) connects to the resistor, cathode (shorter leg) to GND.

## Build & Upload

```bash
make build    # compile
make upload   # upload to /dev/ttyUSB0
make deploy   # build + upload
make logs     # monitor serial output
```

## How It Works

PWM brightness is controlled via a precomputed 32-step exponential lookup table. Human eye perceives brightness logarithmically, so a linear PWM ramp appears as a sharp jump at low levels and a long fade at high levels. Cubing the normalized step corrects this:

```
PWM = ((step / 31)^3) * 255
```

LEDC is configured at 5 kHz with 8-bit resolution (0–255 duty cycle).
