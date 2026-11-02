# ZigBee Smart Factory Training Project (CC2530 + Qt)

English | [中文](README.md)

A cleaned-up IoT training project: CC2530 wireless nodes running TI **Z-Stack 2.5.1a** form a small ZigBee network (light node + switch node), while a **Qt 5** desktop tool on the PC drives the LEDs over a serial link.

![C](https://img.shields.io/badge/C-Z--Stack%202.5.1a-00599C)
![Qt](https://img.shields.io/badge/Qt-5.12-41CD52?logo=qt&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green)

## Layout

```text
.
├── firmware/                  # CC2530 ZigBee firmware (IAR EW8051 projects)
│   └── HomeAutomation/
│       ├── Source/            # shared application code
│       ├── SampleLight/       # light node: coordinator/end-device projects
│       ├── SampleSwitch/      # switch node
│       └── SampleSwitchOta/   # OTA upgrade sample
└── qt-host/                   # Qt serial console (LED control)
```

## Firmware: Z-Stack 2.5.1a

1. Install **IAR Embedded Workbench for 8051 8.1** and **Z-Stack 2.5.1a** from TI (the SDK is not vendored here, to keep the repository small)
2. Open `firmware/HomeAutomation/SampleLight/CC2530DB/SampleLight.eww` in IAR
3. Point the `Components/` and `Projects/zstack/Libraries/` include paths at your local SDK copy
4. Flash the coordinator with `CoordinatorEB` and the end device with `EndDeviceEB` (SmartRF04EB)

## Host: Qt serial console

```bash
cd qt-host
qmake SerialLed.pro
mingw32-make        # or open the .pro in Qt Creator
```

Serial defaults to **9600 8N1**; pick the COM port in the UI and send the light on/off commands.

## Notes

- Only sources and project files are tracked — IAR/Qt build outputs, SDK installers, the training report and demo video were removed
- One image referenced by the original Qt resource file was missing; the entry was dropped from `img.qrc` so `rcc` no longer fails

## License

[MIT License](LICENSE)
