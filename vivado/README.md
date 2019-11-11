## Environment
Vivado2018.2
Zynqberry
Raspberry Pi camera 2
Windows (For linux, you can use SDK)

## How to use
1. Download zynqberry demo using RasPi camera from [trenz](https://shop.trenz-electronic.de/en/Download/?path=Trenz_Electronic/Modules_and_Module_Carriers/special/TE0726/Reference_Design)
1. mv BOOT.bin to /prebuild/boot_images/m/myboot/
1. edit design_basic_settings.cmd and rewrite @set SWAPP=u-boot to @set SWAPP=myboot
1. exec program_flash_binfile.cmd
