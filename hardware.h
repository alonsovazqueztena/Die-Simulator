// Alonso Vazquez Tena
// November 20, 2024
// Milestone 3: Embedded Application Release 2
// This is my own work.

// We are defining the hardware header file here to ensure we declare the necessary functions.
#ifndef HARDWARE_H
#define HARDWARE_H

// This function maps physical memory for FPGA I/O.
int initializeHardware(void);

// This function cleans up the hardware resources by unmapping the
// virtual memory and closing the file descriptor.
void cleanupHardware(void);

// This function polls the key buttons and updates the state variables.
void pollKeys(void);

// This function checks the die roll result and exit flag.
int readHardwareStatus(int *result, int *exit);

// This function converts a decimal number to the corresponding 7-segment display encoding.
int fpgaDecoding(int decimal);

#endif
