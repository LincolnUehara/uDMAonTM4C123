# uDMA testing on Tiva TM4C123

Code for testing uDMA capabilities of Tiva TM4C123.

### Configuration instructions

Please set the following environment variables on your machine:
```
GCC_HOME=/path/to/GNU/toolchain
GCC_HOME_BIN=/path/to/GNU/toolchain/binaries
TIVA_LIB=/path/to/TIVA/libraries
TIVA_LIB_DRIVER=/path/to/TIVA/driver
TIVA_FLASH=/path/to/flash/folder
```

*For Windows users:* Texas Instruments offers [LMFlash](http://www.ti.com/tool/LMFLASHPROGRAMMER), a flasher of binary to TM4C.

*For Linux users:* You can either use [Uniflash](http://www.ti.com/tool/UNIFLASH) or [Fabio Utzig's lm4tools](https://github.com/utzig/lm4tools) to flash the binary.

In our makefile is used Uniflash.

### Operating instructions

To build the binary, just type command "make all". To clean the directory, type "make clean". To flash onto device, type "make flash".

### License and Manifest

This project is licensed under the BSD-EULA License. See [TI-BSD-EULA.txt](https://github.com/LincolnUehara/blinkyTM4C123/blob/master/doc/TI-BSD-EULA.txt) file for more details.

Check the [MANIFEST.txt](https://github.com/LincolnUehara/blinkyTM4C123/blob/master/doc/MANIFEST.txt) file to see more details of libraries offered by Texas Instruments.

### Author

Lincoln Uehara
