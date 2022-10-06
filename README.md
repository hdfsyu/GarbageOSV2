# GarbageOSV2
GarbageOS, but its rewritten! and its better! but its still garbage :(
Aaaaaaaaaaaand also including Lisa kernel V2!
# Installing and compiling
## Dependencies
QEMU, build-essentials, mtools and WSL2 (if you are on windows)
### Installing tools
In order to install build-essentials and mtools, open up terminal (or WSL2 if you are on windows)
then type
`sudo apt update
sudo apt install mtools build-essentials`
In order to install QEMU (Linux) open up terminal and type
`sudo apt update
sudo apt install qemu qemu-user qemu-utils`
In order to install QEMU (Windows) go [here](https://qemu.org) and choose Windows, then download the installer file.
## Steps
All you gotta do is run the "run.sh" file in the root of the project dir, like this:
`./run.sh`
It will compile everything for you, and run it in QEMU
# Real Hardware
~Might be a bit buggy or something, also there are no good display drivers, so its gonna run at like 640x480~ It runs fine on my laptop, i used a usb and balenaetcher to flash the usb, also the display drivers are fine! so no need to worry about that.
# Notes and bugs
* Bug: ~The text that is shown at boot up (the most garbage os ever) is uncentered and overlaying text (on real machines) This is due to a fact that the X and Y positions of the text is screwed up, bug is getting fixed in next update~ Fixed! But now the text is on the right and it doesnt look good, but whatever, it's called GarbageOS...
* Note: When flashing to a USB stick, you must change the name of the EFI file (which is located in EFI/BOOT on the EFI partition of the USB stick).
* Note: When using QEMU to emulate the OS, there are a lot of EfiBootServiceData and EfiBootServicesCode strings on the screen, I don't know why, but QEMU has a lot of sections...
