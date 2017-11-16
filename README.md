# μDMA testing on Tiva TM4C123

Code for testing μDMA capabilities of Tiva TM4C123.
In this example the user send characters via UART port (using [Energia IDE](http://energia.nu/), for example), and all the text typed is showed at user's console. The transportation of data is made by μDMA in burst mode.

### Configuration instructions

Please set the following environment variables on your machine:
```
GCC_HOME=/path/to/GNU/toolchain
GCC_HOME_BIN=/path/to/GNU/toolchain/binaries
TIVA_LIB=/path/to/TIVA/libraries
TIVA_LIB_DRIVER=/path/to/TIVA/driver
TIVA_FLASH=/path/to/flash/folder
```
If you downloaded _TivaWare C Series 2.1.3.156_, the driver (_libdriver.a_) will be located at _TivaWare_C_Series-2.1.3.156/driverlib/gcc_.
Some C functions like _strcpy_ for Tiva embeded system is inside _lic.a_ file located at _$(GCC_HOME)/arm-none-eabi/lib/thumb/v7e-m/fpv4-sp/hard_.

*For Windows users:* Texas Instruments offers [LMFlash](http://www.ti.com/tool/LMFLASHPROGRAMMER), a flasher of binary to TM4C.

*For Linux users:* You can either use [Uniflash](http://www.ti.com/tool/UNIFLASH) or [Fabio Utzig's lm4tools](https://github.com/utzig/lm4tools) to flash the binary.

In our makefile is used Uniflash. Please edit makefile to adjust to your convenience. If you have no idea how to edit a makefile, please check [my article](https://www.embarcados.com.br/introducao-ao-makefile/) about it (available in portuguese, english and spanish languages).

If you are tottally lost on this, it's better to start from [Thiago Filadelfo's](https://github.com/trfiladelfo/unesp_mdt) tutorial or [Jorge Guzman's one](https://www.embarcados.com.br/ambiente-launchpad-tiva-c-no-ubuntu/).

### Operating instructions

To build the binary, just type command "make all". To clean the directory, type "make clean". To flash onto device, type "make flash".

### Purpose of the code

The code is used to study about μDMA settings and works. The results about some analysis will be inside /doc folder.

### License and Manifest

This project is licensed under the BSD-EULA License. See [TI-BSD-EULA.txt](https://github.com/LincolnUehara/blinkyTM4C123/blob/master/doc/TI-BSD-EULA.txt) file for more details.

Check the [MANIFEST.txt](https://github.com/LincolnUehara/blinkyTM4C123/blob/master/doc/MANIFEST.txt) file to see more details about libraries offered by Texas Instruments.

### Author

Lincoln Uehara
