# SparkType

**SparkType** is a HID-based project built on **Digispark (ATtiny85 + V-USB)**, focused on keystroke injection while maintaining an **explicit and auditable USB identity**.

The device enumerates as a standard USB keyboard, but exposes **clear USB strings** (Manufacturer / Product), allowing **system administrators and security teams** to use them as **IOCs (Indicators of Compromise)** if the device is misused.

---

## 🎯 Project Goals

- Implement a functional HID keyboard using V-USB
- Full compatibility with Linux and Windows
- Simple build and upload workflow via `arduino-cli`
- Explicit USB identity for auditability
- Serve as a research and lab platform for:
  - HID internals
  - USB descriptors
  - BadUSB concepts
  - Detection, defense, and incident response

---

## 🧠 Design Philosophy

- **End users** see only a generic HID keyboard
- **Administrators / blue teams** can clearly identify the device via:
  - `lsusb -v`
  - `dmesg`
  - USB Tree View (Windows)
- No aggressive obfuscation or device impersonation
- Explicit identity prioritizes traceability and responsible use

---

## 🧩 Architecture Overview

- MCU: **ATtiny85**
- USB stack: **V-USB**
- USB Class: **HID Keyboard (Boot Protocol)**
- Custom keyboard layouts (e.g. PT-BR)
- Modular internal structure:
  - HID handling
  - LED state control (Caps / Num / Scroll)
  - OS detection
  - TTY and utilities

---

## 🛠️ Requirements

### Software
- `arduino-cli`
- Digistump AVR core
- `make`
- Linux (recommended for development)

### Hardware
- Digispark (ATtiny85)
- Functional USB port

---

## 📦 Project Structure

```

.
├── Makefile
├── SparkType.ino
├── src
│   ├── infra
│   │   ├── HID
│   │   ├── OS
│   │   └── TTY
│   ├── lib
│   │   └── DigiKeyboardPtBr.*
│   └── shared
├── vendor
│   └── arduino-libraries
│       └── DigisparkKeyboard
└── build

```

---

## 🔧 Build

The project uses a minimal **Makefile** wrapping `arduino-cli`.

### Compile
```

make

```

or explicitly:
```

make compile

```

### Clean build artifacts
```

make clean

```

### Full rebuild
```

make rebuild

```

---

## 🚀 Uploading to Digispark

Default configuration:
- Board: `digistump:avr:digispark-tiny`
- Port: `/dev/hidraw0`

```

make upload

```

⚠️ **Note**: Digispark enters bootloader mode only for a few seconds after being plugged in.  
Run the upload command first, then connect the device.

---

## 🔍 USB Identity

Example enumeration on Linux:

```

ID 16c0:27db Van Ooijen Technische Informatica Keyboard
iManufacturer  SparkType
iProduct       SparkType KeyStroke Injector

```

- VID/PID follow the V-USB shared VID scheme
- USB strings are intentionally explicit
- Designed to support security monitoring and incident response

---

## 🪟 Windows Behavior

- Appears as:
  - `HID Keyboard Device`
  - `USB Input Device`
- Full descriptors visible via:
  - USB Tree View
  - USBDeview
- Windows aggressively caches devices by VID/PID

---

## ⚠️ Disclaimer

This project is intended for:
- research
- education
- controlled environments
- labs and CTFs
- internal testing

❌ **Do not use without explicit authorization.**  
The author assumes no responsibility for misuse.

---

## 📜 License

Please refer to the licenses of included components, especially:
- V-USB
- DigisparkKeyboard
