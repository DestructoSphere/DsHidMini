# DsHidMini

Virtual HID Mini-user-mode driver for Sony DualShock 3 Controllers

## Summary

TBD

## Features

- Bluetooth support if used in conjunction with [BthPS3](https://github.com/ViGEm/BthPS3)
- Automatically pairs the controller to Windows Bluetooth (if Bluetooth host radio is present)
- Sony `sixaxis.sys` compatibility (both wired **and wireless**)
- Quick disconnect (on Bluetooth) by pressing `L1 + R1 + PS` together for over one second
- LED indicates battery charge level on wireless (4 = Full, 1 = Low)

### Planned/Work in progress

Rough road map with useful features (in no particular order):

- Implement support for Navigation controller
- Implement auto-disconnect on wireless after idle timeout to save battery
- Implement/expose more options to control pairing behavior
- UI tool for configuration file
- UDP server for `cemuhook` compatibility
  - See [ds4drv](https://github.com/TheDrHax/ds4drv-cemuhook) 
- Test power behavior (like, what happens when the system wants to sleep with controllers connected etc.)
- Integrate ViGEm client SDK for XInput support
- Add remapping capabilities 
  - See [jfes](https://github.com/dmitrii-eremin/jfes) 
  - Might be redundant due to existing tools
- Add configurable Turbo Mode for buttons
  - Might be redundant due to existing tools
- Test and document setup with PCSX2, RetroArch

## How it works

TBD

## How to build

### Prerequisites

- [Step 1: Install Visual Studio 2019](<https://docs.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk#download-icon-step-1-install-visual-studio-2019>)
- [Step 2: Install WDK for Windows 10, version 2004](<https://docs.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk#download-icon-step-2-install-wdk-for-windows-10-version-2004>)
- [Step 3: Clone the Driver Module Framework (DMF)](https://github.com/microsoft/DMF) into the same parent directory.
  - Build the `DmfU` project with Release and Debug configurations for all architectures (x64 and Win32).

You can build individual projects of the solution within Visual Studio.

## Sources & 3rd party credits

- [Eleccelerator Wiki - DualShock 3](http://eleccelerator.com/wiki/index.php?title=DualShock_3)
- [Eleccelerator - USB Descriptor and Request Parser](http://eleccelerator.com/usbdescreqparser/)
- [HID Usage Tables](https://usb.org/sites/default/files/documents/hut1_12v2.pdf)
- [Arduino - felis/USB_Host_Shield_2.0 - PS3 Information](https://github.com/felis/USB_Host_Shield_2.0/wiki/PS3-Information#USB)
- [PS3 and Wiimote Game Controllers on the Arduino Host Shield: Part 2](https://web.archive.org/web/20160326093555/https://www.circuitsathome.com/mcu/ps3-and-wiimote-game-controllers-on-the-arduino-host-shield-part-2)
- [ribbotson/USB-Host](https://github.com/ribbotson/USB-Host/tree/master/ps3/PS3USB)
- [HID: sony: Update device ids](https://patchwork.kernel.org/patch/9367441/)
- [ViGEm/FireShock](https://github.com/ViGEm/FireShock)
- [ViGEm/AirBender](https://github.com/ViGEm/AirBender)
- [ViGEm/WireShock](https://github.com/ViGEm/WireShock)
- [Microsoft/Driver Module Framework (DMF)](https://github.com/microsoft/DMF)
- [Microsoft - DMF - HID minidriver module](https://github.com/microsoft/DMF/issues/69)
- [Microsoft - DMF - VHidMini2DmfK and VHidMini2DmfU Sample Drivers](https://github.com/microsoft/DMF/tree/master/DmfSamples/VHidMini2Dmf)
- [linux/drivers/hid/hid-sony.c](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-sony.c)
- [Summary of the DPInst XML Elements](https://web.archive.org/web/20120623222252/http://msdn.microsoft.com/en-us/library/ff553383.aspx)
- [dpinst XML Element](https://docs.microsoft.com/en-us/windows-hardware/drivers/install/dpinst-xml-element)
- [Driver installation and updating made easy: DPInst.exe](https://docs.microsoft.com/en-us/archive/blogs/svengruenitz/driver-installation-and-updating-made-easy-dpinst-exe)
- [inih (INI Not Invented Here)](https://github.com/benhoyt/inih)
