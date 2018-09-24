# μDMA testing on Tiva TM4C123 [Version 1.0](https://github.com/LincolnUehara/uDMAonTM4C123/releases/latest)

In this example the user send characters via UART port (using [Energia IDE](http://energia.nu/), for example), and all the text typed is showed at user's console. The transportation of data is made by μDMA in burst mode.

### Configuration instructions

Please [check the wiki](https://github.com/LincolnUehara/uDMAonTM4C123/wiki) to see all configurations needed to your machine.

In this example it is used Uniflash.

Please edit makefile or see more details on wiki to adjust to your convenience.

### Operating instructions

* To build the binary, just type command "make all".
* To clean the directory, type "make clean".
* To flash onto device, type "make flash".
* To see elf file properties, type "make readelf".

### License and Manifest

This project is licensed under the BSD License. See [LICENSE](https://github.com/LincolnUehara/uDMAonTM4C123/blob/master/LICENSE) file for more details.

### Author

Lincoln Uehara
