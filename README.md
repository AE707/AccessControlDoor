# AccessControlDoor 🔐

AccessControlDoor is an ESP32‑based smart door access control system built with PlatformIO.
It is structured for scalable firmware development, filesystem‑based web UI/config, and easy customization for different hardware setups.

---

## Features

- **ESP32 firmware** using PlatformIO (C/C++) for reliable embedded development.
- **Modular structure** with `src`, `include`, `lib`, and `test` for clean, maintainable code.
- **LittleFS support** via `data/littlefs/` for storing web assets, configuration files, and other runtime data.
- Ready to integrate **door lock drivers** (relay, MOSFET, etc.) and authentication peripherals (keypad, RFID, sensors).
- VS Code **debug/build setup** through `.vscode` and `platformio.ini` for a smooth developer experience.

---

## Project Structure

```
AccessControlDoor/
├─ .vscode/          # VS Code + PlatformIO settings
├─ data/
│  └─ littlefs/      # Filesystem image content (web UI, JSON configs, etc.)
├─ include/          # Header files for modules and configuration
├─ lib/              # Reusable libraries / 3rd‑party components
├─ src/              # Main firmware source code
├─ test/             # Unit / integration tests (PlatformIO)
└─ platformio.ini    # PlatformIO environments & board configuration
```

---

## Requirements

### Hardware

- ESP32 development board compatible with the configuration in `platformio.ini`.
- Door‑lock driving hardware (relay module, MOSFET driver, or dedicated lock controller).
- Optional: keypad, RFID/NFC reader, magnetic/reed sensors, or other access peripherals.

### Software

- [VS Code](https://code.visualstudio.com/) with the PlatformIO extension **or** PlatformIO Core (CLI).
- Git (for cloning and version control).

---

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/AE707/AccessControlDoor.git
cd AccessControlDoor
```

### 2. Open in PlatformIO

- Open the folder in VS Code.
- PlatformIO will automatically read `platformio.ini` and install the required toolchains and libraries.

### 3. Build the firmware

```bash
pio run
```

### 4. Upload the firmware

Connect the ESP32 via USB, then:

```bash
pio run --target upload
```

### 5. Upload LittleFS filesystem (optional but recommended)

If you use the `data/littlefs/` folder for web UI or configs:

```bash
pio run --target uploadfs
```

---

## Configuration

- Adjust the **board**, **upload speed**, and other parameters in `platformio.ini` to match your ESP32 board.
- Place web assets (HTML/CSS/JS) and configuration files under `data/littlefs/` so they are available on the ESP32 at runtime.
- Implement or customize:
  - Authentication logic (PIN codes, card IDs, etc.) in `src/`
  - Door lock control (relay timing, lock/unlock patterns)
  - Logging, alerts, and any network features (Wi‑Fi, HTTP, MQTT, etc.)

---

## Development Notes

- Use the `include/` directory for shared headers to keep interfaces clear between modules.
- Place reusable code or external libraries in `lib/` to avoid cluttering `src/`.
- Add tests in `test/` and run them with PlatformIO's test runner to validate critical logic.

---

## Roadmap / Ideas

You can extend the project with:

- Web dashboard for door status, logs, and user management (served from LittleFS).
- Integration with MQTT or REST APIs for remote monitoring and control.
- Support for multiple authentication methods (RFID, keypad, mobile app).
- OTA updates for remote firmware deployment.

---

## License

This project is released under the **MIT License**.
You are free to use, modify, and distribute it, with proper attribution to the original author.
