# FIFO trigger level should be the same size as buffer and arbitration sizes

From TM4C official document:

1. "The receive interrupt changes state when (...) the FIFOs are enabled and the receive FIFO reaches the programmed trigger level, the RXRIS (UART Receive Raw Interrupt Status) bit is set."
2. In single request μDMA controller transfers only one item, and then stops to wait for another request. On the other hand, "...when a burst request is detected, the μDMA controller transfers the number of items that is the lesser of the arbitration size or the number of items remaining in the transfer. Therefore, the arbitration size should be the same as the number of data items that the peripheral can accommodate when making a burst request."
3. "It may be desirable to use only burst transfers and not allow single transfers. For example, perhaps the nature of the data is such that it only makes sense when transferred together as a single unit rather than one piece at a time."
4. "Each channel also has a configurable arbitration size. The arbitration size is the number of items that are transferred in a burst before the μDMA controller re-arbitrates for channel priority. Using the arbitration size, it is possible to control exactly how many items are transferred to or from a peripheral each time it makes a μDMA service request.
5. "The source and destination data size must be the same for any given transfer."
6. The arbitration size can also be thought of as a burst size. It is the maximum number of items that are transferred at any one time in a burst.

### In other words:
**ui32TransferSize (on uDMAChannelTransferSet) =** 
**UDMA_ARB_X (on uDMAChannelControlSet) =**
**UART_FIFO_RXX_8 (on UARTFIFOLevelSet)**

Tests were made and shows that any variant appears bug on system.

If you are curious and wanna see what happens, make a char buffer string of 8 R's, set ui32TransferSize as 6, and use UDMA_ARB_4 and UART_FIFO_RX1_8 flags. Type alphabets at input.

Input: ABCDEFGHIJKLMNOPQRSTUVXZ

Output: ABEFIJMNQRCCSTRRUVGGXZRR

![Figure1](https://github.com/LincolnUehara/uDMAonTM4C123/tree/master/doc/Figures/Tip1_Figure1.jpg)
![Figure2](https://github.com/LincolnUehara/uDMAonTM4C123/tree/master/doc/Figures/Tip1_Figure2.jpg)
