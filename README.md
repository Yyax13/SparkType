# SparkType

SparkType turns a Digispark (ATtiny85 + V-USB) into a USB HID keyboard you drive from your own firmware. It keeps a readable USB identity so the device is easy to spot and audit.

The board enumerates as a standard boot-protocol keyboard. It also reports explicit Manufacturer and Product strings. Tools like `lsusb`, `dmesg`, USB Tree View, and USBDeview show exactly what it is, which gives sysadmins and incident responders a concrete IOC if someone misuses the hardware.

## Goals

- Drive a HID keyboard over V-USB on an ATtiny85
- Work on Linux and Windows
- Wrap the build and upload steps in a few `make` targets
- Publish a clear USB identity
- Give researchers a bench for HID internals, USB descriptors, BadUSB, detection, and incident response

## Design

End users see a generic HID keyboard. Administrators identify the device through its USB strings and descriptors. SparkType does not obfuscate, impersonate a commercial keyboard, or try to evade endpoint detection. A clear identity keeps the project traceable and pushes use toward labs and authorized testing.

## Architecture

- MCU: ATtiny85
- USB stack: V-USB
- USB class: HID keyboard, boot protocol
- Layout-driven ASCII mapping, with a PT-BR (ABNT2) implementation included
- Device identity and USB strings centralized in `src/config.h`, wired into V-USB through `vendor/arduino-libraries/DigisparkKeyboard/usbconfig.h`

Modules under `src`:

| Path | Role |
|------|------|
| `lib/SparkKeyboard` | Base keyboard class and the layout pattern |
| `lib/SparkKeyboard/layouts/pt-br` | ABNT2 key map plus UTF-8 `ç` / `Ç` handling |
| `lib/DigiKeyboardPtBr` | Earlier single-file PT-BR keyboard, kept for reference |
| `infra/HID/CONNECTION` | Connect, disconnect, and reconnect the USB device |
| `infra/HID/LEDS` | Read and restore Caps / Num / Scroll state, track LED replies |
| `infra/OS` | Detect Linux, Windows, or macOS from host LED traffic |
| `shared/utils/blink-alert` | Onboard LED blink helpers |
| `config.h` | VID, PID, version, and USB strings |

`SparkType.ino` calls `mainSetup()` and `mainLoop()`. Edit `src/main.cpp` to change behavior. It currently runs a small hello-world that blinks the LED and types a line.

## Requirements

Software:

- `arduino-cli`
- Digistump AVR core (`digistump:avr`)
- `make`
- Linux for development (upload is tested against `/dev/hidraw0`)

Hardware:

- Digispark (ATtiny85)
- A USB port

## Project structure

```
.
├── LICENSE
├── Makefile
├── README.md
├── SECURITY.md
├── SparkType.ino
├── arduino.yaml
├── src
│   ├── config.h
│   ├── main.cpp
│   ├── include
│   │   └── main.h
│   ├── infra
│   │   ├── HID
│   │   │   ├── CONNECTION
│   │   │   │   ├── main.cpp
│   │   │   │   └── main.h
│   │   │   └── LEDS
│   │   │       ├── main.cpp
│   │   │       └── main.h
│   │   └── OS
│   │       ├── main.cpp
│   │       └── main.h
│   ├── lib
│   │   ├── DigiKeyboardPtBr.cpp
│   │   ├── DigiKeyboardPtBr.h
│   │   └── SparkKeyboard
│   │       ├── ascii-map.txt
│   │       ├── base-mods.txt
│   │       ├── main.h
│   │       └── layouts
│   │           └── pt-br
│   │               ├── main.cpp
│   │               └── main.h
│   └── shared
│       └── utils
│           └── blink-alert
│               ├── main.cpp
│               └── main.h
└── vendor
    └── arduino-libraries
        └── DigisparkKeyboard
```

## Build

Compile:

```
make
```

`make compile` does the same thing. Remove artifacts with `make clean`, and run a full rebuild with `make rebuild`.

The Makefile wraps `arduino-cli` with:

- Board `digistump:avr:digispark-tiny`
- Libraries from `vendor/arduino-libraries`
- Output to `build/`

## Upload

```
make upload
```

The default port is `/dev/hidraw0`. Change `PORT` in the Makefile if your system assigns a different node.

The Digispark only enters its bootloader for a few seconds after power-up. Start the upload first, then plug the board in when the tool asks.

## USB identity

```
$ lsusb -v
idVendor        0x1209
idProduct       0x5153
iManufacturer   SparkType
iProduct        SparkType KeyStroke Injector
```

Values come from `src/config.h`:

| Field | Value |
|-------|-------|
| VID | `0x1209` |
| PID | `0x5153` |
| Vendor string | `SparkType` |
| Product string | `SparkType KeyStroke Injector` |
| Version bytes | `0x0200` |

`0x1209` is the shared pid.codes vendor ID. The strings stay explicit on purpose, so `lsusb`, `dmesg`, and Windows device tools surface something a responder can match.

## Windows behavior

Windows lists the board as `HID Keyboard Device` and `USB Input Device`. USB Tree View and USBDeview show the full descriptors. Windows caches devices by VID/PID, so a re-flashed board with the same IDs may reuse the old entry until you uninstall it.

## Adding a layout

`src/lib/SparkKeyboard` lets you add a keyboard layout as its own folder. The `pt-br` layout shows the pattern:

1. Create `src/lib/SparkKeyboard/layouts/<locale>/`.
2. In `main.h`, include `../../main.h`, define the modifier macros, and declare your `SparktypeKeyboard` instance.
3. In `main.cpp`, define the 128-entry ASCII map and implement `SparktypeKeyboard::write` and `SparktypeKeyboard::sendKeyReport`.
4. Include your layout header where you need it.

`src/lib/SparkKeyboard/base-mods.txt` documents the modifier macros, and `ascii-map.txt` documents the map format.

## Security

See [SECURITY.md](SECURITY.md) for supported use, detection guidance, and how to report issues.

## Disclaimer

SparkType is built for research, education, labs, CTFs, and internal testing with authorization. Do not run it without explicit permission. The author takes no responsibility for misuse.

## License

MIT. See [LICENSE](LICENSE). Bundled components keep their own licenses, notably V-USB and DigisparkKeyboard under `vendor/arduino-libraries/DigisparkKeyboard`.
