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
In order to install QEMU (Windows) go (here)[qemu.org] and choose Windows, then download the installer file.
## Steps
All you gotta do is run the "run.sh" file in the root of the project dir, like this:
`./run.sh`
It will compile everything for you, and run it in QEMU
# Real Hardware
~Might be a bit buggy or something, also there are no good display drivers, so its gonna run at like 640x480~
It runs fine on my laptop, i used a usb and balenaetcher to flash the usb


