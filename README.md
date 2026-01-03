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

---

# 🔐 Access Control Door System (Embedded)

An embedded system project for controlling and securing door access using authentication mechanisms and microcontroller-based logic.
This project demonstrates core embedded concepts such as GPIO control, input validation, state management, and hardware–software integration.

---

## 📌 Project Overview

The **Access Control Door System** is designed to allow or deny access based on predefined authorization rules.
It simulates a real-world access control solution commonly used in offices, labs, and secured areas.

Key goals of the project:
- Secure door access
- Reliable authentication handling
- Clear system states (idle, access granted, access denied)
- Embedded-friendly and resource-efficient design

---

## 🧠 System Features

- 🔑 User authentication (e.g. keypad / ID input)
- 🚪 Door lock control (relay / motor / solenoid logic)
- 🔔 Status indicators (LEDs / buzzer)
- ⏱️ Timed access and auto-lock
- ⚠️ Invalid access detection
- 🔄 Reset and retry mechanism

---

## 🏗️ System Architecture

```
ESP32 Microcontroller with:
- Input I/O: Keypad, RFID Reader, Buttons
- Output I/O: Door Lock (Relay), LED Status, Buzzer
- Access Control State Machine (IDLE -> VALIDATE -> GRANT/DENY -> AUTO_LOCK)
- Authentication Manager (Credential Storage & Validation)
- Timer & Lock Control Module (Auto-lock after timeout)
```

---

## 🚀 How It Works

1. **Idle State**: System waits for user input.
2. **User Input**: User provides PIN, RFID card, or ID.
3. **Validation**: System checks input against stored credentials.
4. **Access Granted**:
   - Door unlocks (relay/solenoid activates for defined duration).
   - Green LED indicator illuminates.
   - Optional buzzer beep.
5. **Access Denied**:
   - Door remains locked.
   - Red LED indicator illuminates.
   - Alert buzzer sounds (multiple beeps).
6. **Auto-Lock**: Door automatically locks after timeout.
7. **Return to Idle**: System resets and waits for next input.

---

## 🧪 Testing & Validation

- **Functional Testing**: Verify valid/invalid access scenarios.
- **Timing Verification**: Confirm auto-lock behavior and delays.
- **Input Edge-Case Handling**: Test boundary conditions (empty input, partial codes, etc.).
- **Hardware Signal Validation**: Verify GPIO states for locks, LEDs, and indicators.
- **State Transition Testing**: Ensure system flows correctly through all states.

---

## 🔮 Future Improvements

- **Multi-factor Authentication**: Combine PIN + RFID for enhanced security.
- **User Management Dashboard**: Add/remove users and modify access permissions.
- **Audit Logging**: Store access attempts (successful & failed) with timestamps.
- **Wireless Integration**: Connect via Wi-Fi/Bluetooth for remote monitoring.
- **Cloud Sync**: Sync credentials with cloud for centralized access control.
- **Biometric Support**: Integrate fingerprint or facial recognition.
- **Emergency Override**: Master key or emergency bypass mechanism.
- **SMS/Email Alerts**: Notify administrators of unauthorized access attempts.
- **Multiple Door Support**: Extend to control and monitor multiple doors.
- **OTA Updates**: Deploy firmware updates over the network.

---

## 🧬 Algorithm Logic

### Authentication Flow (Pseudocode)

```c
// Access Control State Machine
void accessControlStateMachine() {
    while (true) {
        switch (currentState) {
            case IDLE:
                displayIdleMessage();
                if (inputReceived()) {
                    userInput = readUserInput();  // PIN or RFID
                    currentState = VALIDATING;
                }
                break;

            case VALIDATING:
                if (validateCredentials(userInput)) {
                    currentState = ACCESS_GRANTED;
                } else {
                    invalidAttempts++;
                    if (invalidAttempts >= MAX_ATTEMPTS) {
                        currentState = LOCKED_OUT;
                    } else {
                        currentState = ACCESS_DENIED;
                    }
                }
                break;

            case ACCESS_GRANTED:
                activateDoorLock();            // Unlock door
                setLED(GREEN);                 // Green light
                playSound(SUCCESS_BEEP);       // Success sound
                startTimer(UNLOCK_DURATION);   // 5 seconds
                if (timerExpired()) {
                    currentState = AUTO_LOCK;
                }
                break;

            case ACCESS_DENIED:
                keepDoorLocked();
                setLED(RED);                   // Red light
                playSound(DENIED_ALARM);       // Alert
                delay(FEEDBACK_DURATION);
                invalidAttempts = 0;
                currentState = IDLE;
                break;

            case AUTO_LOCK:
                deactivateDoorLock();          // Re-lock
                setLED(OFF);
                currentState = IDLE;
                break;
        }
    }
}
```

### Credential Validation

```c
bool validateCredentials(String input) {
    for (int i = 0; i < USER_COUNT; i++) {
        if (strcmp(input, validUsers[i].credential) == 0) {
            return true;  // Access granted
        }
    }
    return false;  // Access denied
}
```

### State Diagram

```
IDLE (Wait for input)
  |
  v (User provides PIN/ID)
VALIDATING (Check credentials)
  |
  +---> ACCESS_GRANTED (Valid)
  |        |
  |        v
  |     Unlock Door
  |     Green LED ON
  |     Play Success Beep
  |        |
  |        v (5 sec timeout)
  |     AUTO_LOCK
  |        |
  |        v
  |     Lock Door
  |     LED OFF
  |        |
  |        +---> IDLE
  |
  +---> ACCESS_DENIED (Invalid)
           |
           v
        Lock Door (stays)
        Red LED ON
        Play Alert Beep
           |
           v (2 sec delay)
        IDLE (reset attempts)
```

### Timing Parameters

| Parameter | Value | Description |
|-----------|-------|-------------|
| UNLOCK_DURATION | 5 seconds | How long the door stays unlocked |
| FEEDBACK_DURATION | 2 seconds | How long to display denied message |
| LOCKOUT_DURATION | 30 seconds | Lockout period after max attempts |
| MAX_ATTEMPTS | 3 | Max invalid attempts before lockout |
| DEBOUNCE_TIME | 20ms | Input debouncing for buttons |
| GPIO_DELAY | 10ms | Relay activation delay |

---
