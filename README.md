# 🔐 AccessControlDoor — ESP32 Smart Door Access Control System

AccessControlDoor is an ESP32-based access control firmware built with PlatformIO, designed for secure and modular embedded door systems.
The project showcases key embedded concepts including GPIO control, authentication logic, state management, and hardware–software integration.

---

## 🚀 Key Features

- 🧠 **Built for ESP32** using PlatformIO (C/C++)
- 🧩 **Modular directory structure** (src, include, lib, test)
- 💾 **LittleFS filesystem support** for storing web UI assets and configs
- 🧪 **Fully integrated** with PlatformIO development workflow
- ⚙️ **Pre-configured VS Code** debug/build setup
- 🖥️ **Optional web UI and config** via LittleFS
- 🔌 **Easy integration** of:
  - Door lock drivers (relay / MOSFET)
  - Authentication peripherals (keypad / RFID)
  - Sensors (magnetic / reed / PIR)

---

## 📂 Project Structure

```
AccessControlDoor/
├─ .vscode/          # VS Code + PlatformIO configs
├─ data/
│  └─ littlefs/      # Filesystem content (web UI, JSON configs, etc.)
├─ include/          # Header files for modules and configuration
├─ lib/              # Reusable libraries / 3rd-party components
├─ src/              # Main firmware code
├─ test/             # Unit & integration tests (PlatformIO)
├─ platformio.ini    # Build environments & board configuration
└─ README.md         # This file
```

---

## 🧰 Requirements

### 🔌 Hardware

- **ESP32 development board** compatible with your setup
- **Door lock driver** (relay / MOSFET / external controller)
- **Optional peripherals**:
  - Keypad / RFID reader
  - Magnetic / reed sensor
  - LEDs / buzzer indicators

### 💻 Software

- **VS Code** with PlatformIO extension **OR** PlatformIO Core (CLI)
- **Git** (for cloning and version control)
- **USB cable** for ESP32 programming

---

## 📦 Getting Started

### 1️⃣ Clone this repository

```bash
git clone https://github.com/AE707/AccessControlDoor.git
cd AccessControlDoor
```

### 2️⃣ Open in PlatformIO

- Open folder in **VS Code**
- **PlatformIO will install** required frameworks automatically

### 3️⃣ Build firmware

```bash
pio run
```

### 4️⃣ Upload firmware to ESP32

```bash
pio run --target upload
```

### 5️⃣ Upload LittleFS (optional)

If you use the `data/littlefs/` directory for web UI/config files:

```bash
pio run --target uploadfs
```

---

## ⚙️ Configuration

- **Update `platformio.ini`** to match your specific ESP32 board and upload settings
- **Add or customize** web UI assets and JSON configs under `data/littlefs/`
- **Implement or extend**:
  - Authentication logic (PIN, RFID tag list, etc.)
  - Door lock timing, alert logic, feedback mechanisms
  - Networking (HTTP, Wi-Fi management, MQTT, REST API)

---

## 📈 Development Notes

- Use `include/` for shared headers and interfaces
- Place reusable external libraries in `lib/`
- Add tests to `test/` and execute using PlatformIO's test runner
- Use **LittleFS** for serving web UI and storing device configs

---

## 📌 System Overview

The system allows or denies door access based on predefined authorization rules, simulating real-world secure entry systems used in offices, labs, and restricted areas.

**Key goals of the project:**
- Secure door access
- Reliable authentication handling
- Clear system states (idle, access granted, access denied)
- Embedded-friendly and resource-efficient design

---

## 🧠 System Features & Architecture

### Core Features

- 🔑 **User authentication** (keypad / ID input)
- 🚪 **Door lock control** (relay / motor / solenoid logic)
- 🔔 **Status indicators** (LEDs / buzzer)
- ⏱️ **Timed access and auto-lock**
- ⚠️ **Invalid access detection**
- 🔄 **Reset and retry mechanism**

### System Architecture

```
ESP32 Microcontroller with:
- Input I/O:  Keypad, RFID Reader, Buttons
- Output I/O: Door Lock (Relay), LED Status, Buzzer
- Access Control State Machine (IDLE → VALIDATE → GRANT/DENY → AUTO_LOCK)
- Authentication Manager (Credential Storage & Validation)
- Timer & Lock Control Module (Auto-lock after timeout)
```

⚠️ Some features described represent the intended architecture and design goals; implementation may evolve as the project progresses.

---

## 🚀 How It Works

1. **Idle State**: System waits for user input
2. **User Input**: User provides PIN, RFID card, or ID
3. **Validation**: System checks input against stored credentials
4. **Access Granted**:
   - Door unlocks (relay/solenoid activates for defined duration)
   - Green LED indicator illuminates
   - Optional buzzer beep
5. **Access Denied**:
   - Door remains locked
   - Red LED indicator illuminates
   - Alert buzzer sounds (multiple beeps)
6. **Auto-Lock**: Door automatically locks after timeout
7. **Return to Idle**: System resets and waits for next input

---

## 🧪 Testing & Validation

- **Functional Testing**: Verify valid/invalid access scenarios
- **Timing Verification**: Confirm auto-lock behavior and delays
- **Input Edge-Case Handling**: Test boundary conditions (empty input, partial codes, etc.)
- **Hardware Signal Validation**: Verify GPIO states for locks, LEDs, and indicators
- **State Transition Testing**: Ensure system flows correctly through all states

---

## 🧬 Algorithm Logic

### Authentication Flow (Pseudocode)

**Note:** The following pseudocode illustrates the system logic and state machine design.  
          Actual implementation details may differ depending on hardware configuration.


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
  ↓ (User provides PIN/ID)
VALIDATING (Check credentials)
  ├─→ ACCESS_GRANTED (Valid)
  │     ↓
  │   Unlock Door
  │   Green LED ON
  │   Play Success Beep
  │     ↓ (5 sec timeout)
  │   AUTO_LOCK
  │     ↓
  │   Lock Door
  │   LED OFF
  │     ↓
  │   └──→ IDLE
  │
  └─→ ACCESS_DENIED (Invalid)
        ↓
      Lock Door (stays)
      Red LED ON
      Play Alert Beep
        ↓ (2 sec delay)
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

## 💡 Roadmap & Future Enhancements

You can enhance this project with:

- 📡 **Web dashboard** for status & user management (hosted via LittleFS)
- 📶 **Networking** (MQTT, REST API, remote control)
- 🔐 **Multi-factor authentication** (PIN + RFID combined)
- 🛠️ **Multiple authentication methods** (RFID, BLE, mobile app)
- 🔄 **OTA-based firmware updates**
- 📊 **Logging and event history** (audit trail)
- 🌐 **Cloud synchronization** for centralized management
- 🔏 **Emergency override** mechanisms
- 🔔 **SMS/Email alerts** for unauthorized attempts
- 🏢 **Multi-door support** for larger installations

---

## 📝 License

This project is licensed under the **MIT License** — you are free to use, modify, and share it with proper attribution.

---

## 🙌 About the Author

**Alaa Elghoul** — Embedded / Firmware Developer

**GitHub Profile:** [https://github.com/AE707](https://github.com/AE707)

---

*Last Updated: January 2026*
