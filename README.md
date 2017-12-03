# μDMA testing on Tiva TM4C123

Code for testing μDMA capabilities of Tiva TM4C123 using Tiva Ware libraries.

In this example the user send characters via UART port (using [Energia IDE](http://energia.nu/), for example), and all the text typed is showed at user's console. The transportation of data is made by μDMA in burst mode.

### Configuration instructions

Please [check the wiki](https://github.com/LincolnUehara/blinkyTM4C123/wiki) to see all configurations needed to your machine.

In this example it is used Uniflash.

Please edit makefile or see more details on wiki to adjust to your convenience.

### Operating instructions

To build the binary, just type command "make all". To clean the directory, type "make clean". To flash onto device, type "make flash".

### License and Manifest

This project is licensed under the BSD-EULA License. See [TI-BSD-EULA.txt](https://github.com/LincolnUehara/blinkyTM4C123/blob/master/doc/TI-BSD-EULA.txt) file for more details.

Check the [MANIFEST.txt](https://github.com/LincolnUehara/blinkyTM4C123/blob/master/doc/MANIFEST.txt) file to see more details about libraries offered by Texas Instruments.

### Author

Lincoln Uehara
