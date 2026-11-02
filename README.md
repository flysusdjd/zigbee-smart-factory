# 智慧工厂 ZigBee 实训项目（CC2530 + Qt）

[English](README.en.md) | 中文

物联网实训项目的整理版：CC2530 无线节点跑 TI **Z-Stack 2.5.1a** 协议栈，组成「灯光节点 + 开关节点」的 ZigBee 网络；PC 端用 **Qt 5** 写了一个串口上位机，通过串口控制节点上的 LED。

![C](https://img.shields.io/badge/C-Z--Stack%202.5.1a-00599C)
![Qt](https://img.shields.io/badge/Qt-5.12-41CD52?logo=qt&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green)

## 内容

```text
.
├── firmware/                  # CC2530 ZigBee 下位机（IAR EW8051 工程）
│   └── HomeAutomation/
│       ├── Source/            # 应用层公共代码
│       ├── SampleLight/       # 灯节点：协调器/终端工程与源码
│       ├── SampleSwitch/      # 开关节点：协调器/终端工程与源码
│       └── SampleSwitchOta/   # OTA 升级示例
└── qt-host/                   # Qt 串口上位机（串口调试 + LED 控制）
```

## 下位机：Z-Stack 2.5.1a

1. 安装 **IAR Embedded Workbench for 8051 8.1** 与 **Z-Stack 2.5.1a**（TI 官网，仓库未附带 SDK，避免仓库体积过大）
2. 用 IAR 打开 `firmware/HomeAutomation/SampleLight/CC2530DB/SampleLight.eww`
3. 将 Z-Stack 的 `Components/`、`Projects/zstack/Libraries/` 路径按本地 SDK 位置调整后编译
4. 协调器烧写 `CoordinatorEB`，终端节点烧写 `EndDeviceEB`，用 SmartRF04EB 下载

## 上位机：Qt 串口控制

```bash
cd qt-host
qmake SerialLed.pro
mingw32-make        # 或直接用 Qt Creator 打开 .pro
```

串口参数默认 **9600 8N1**，在界面里选择 COM 口后即可发送开灯/关灯指令。

## 说明

- 仓库只保留源码与工程文件，已剔除 IAR/Qt 的编译产物、SDK 安装包、实训报告与演示视频
- Qt 资源文件里有一张图片在原始工程中缺失，已从 `img.qrc` 中移除，避免 `rcc` 报错

## 许可

[MIT License](LICENSE)
