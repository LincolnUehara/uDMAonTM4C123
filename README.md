# μDMA testing on Tiva TM4C123

[![License](https://img.shields.io/github/license/LincolnUehara/uDMAonTM4C123)](https://github.com/LincolnUehara/uDMAonTM4C123/blob/master/LICENSE)
![Maintenance](https://img.shields.io/maintenance/no/2018)

### Purpose

This code was intended to study the usage of μDMA on Tiva TM4C123, plus about compiling code using makefile. In this example the user sends characters via UART port (using [Energia IDE](http://energia.nu/), for example), and all the typed text is showed at user's console. The transportation of data is made by μDMA in burst mode.

I wrote [an article](https://www.embarcados.com.br/dma-direct-memory-access/) on _Embarcados_ about DMA.

### Configuration instructions

Please [check the wiki](https://github.com/LincolnUehara/uDMAonTM4C123/wiki) to see all configurations needed to your machine.

Please edit makefile or see more details on wiki to adjust to your convenience.

### Operating instructions

* To build the binary, just type command "make all".
* To clean the directory, type "make clean".
* To flash onto device, type "make flash".
* To see elf file properties, type "make readelf".

### Author

Lincoln Uehara
