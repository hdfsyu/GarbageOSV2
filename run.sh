cd gnu-efi
make bootloader
cd ../kernel
make kernel
make link
make buildimg
make run
