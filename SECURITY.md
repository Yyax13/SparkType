# Security Policy

## Supported Use Cases

SparkType is designed for:
- Security research
- Educational purposes
- Controlled lab environments
- Capture The Flag (CTF) scenarios
- Internal testing with explicit authorization

Production or unauthorized deployment is **not supported**.

---

## Security Design Considerations

- The device enumerates as a standard HID keyboard
- USB Manufacturer and Product strings are **explicit and non-obfuscated**
- This enables:
  - Asset identification
  - IOC-based detection
  - Incident response and forensics

SparkType intentionally avoids stealth or impersonation techniques commonly associated with malicious BadUSB payloads.

---

## Detection & IOC Guidance

Security teams can identify SparkType via:
- USB Vendor ID / Product ID
- USB strings:
  - Manufacturer
  - Product
- HID descriptors
- Device behavior (HID keystroke injection)

Recommended tools:
- `lsusb -v` (Linux)
- `dmesg`
- USB Tree View (Windows)
- USBDeview

---

## Reporting Security Issues

If you discover:
- unintended stealth behavior
- descriptor inconsistencies
- vulnerabilities enabling misuse beyond intended scope

Please report responsibly by opening a **private issue** or contacting the maintainer directly.

---

## Non-Goals

SparkType explicitly does **not** aim to:
- Evade endpoint detection
- Impersonate commercial keyboards
- Bypass enterprise security controls
- Operate covertly in hostile environments

---

## Responsible Use

Users are responsible for ensuring:
- Legal authorization
- Compliance with local laws and organizational policies
- Ethical use aligned with research and defensive goals