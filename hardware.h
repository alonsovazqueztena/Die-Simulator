// Alonso Vazquez Tena
// December 1, 2024
// Milestone 4: Embedded Application Release 3
// This is my own work.

// We are defining the hardware header file here to ensure we declare the necessary functions.
#ifndef HARDWARE_H
#define HARDWARE_H

// This defines a structure to hold the hardware context.
typedef struct
{
    void *LW_virtual; // This is the virtual memory base for the FPGA lightweight bridge.

    // These are the pointers to the key button input and the 7-segment display.
    volatile int *KEY_ptr;
    volatile int *HEX_ptr;
    int fd; // This is the file descriptor for /dev/mem.

    // These are the state variables.
    int rollResult;
} HardwareContext;

// This function maps physical memory for FPGA I/O.
int initializeHardware(HardwareContext *context);

// This function cleans up the hardware resources by unmapping the
// virtual memory and closing the file descriptor.
void cleanupHardware(HardwareContext *context);

// This function polls the key buttons and updates the state variables.
int pollKeys(HardwareContext *context, int *rollResult);

// This function converts a decimal number to the corresponding 7-segment display encoding.
int fpgaDecoding(int decimal);

#endif
