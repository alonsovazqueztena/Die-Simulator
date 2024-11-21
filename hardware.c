// Alonso Vazquez Tena
// November 20, 2024
// Milestone 3: Embedded Application Release 2
// This is my own work.

// We must include these libraries for its utilities.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "address_map_arm.h"

// We must include the header file for hardware-related functions.
#include "hardware.h"

// This is the virtual memory base for the FPGA lightweight bridge.
static void *LW_virtual;

// These are the pointers to the key button input and the 7-segment display.
static volatile int *KEY_ptr;
static volatile int *HEX_ptr;

// This is the file descriptor for /dev/mem.
static int fd = -1;

// These are the state variables.
static int rollResult = 0;
static int exitFlag = 0;

// This maps physical memory for FPGA I/O.
int initializeHardware()
{
    // This opens /dev/men to give access to physical addresses if not done.
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
    {
        printf("Error: Could not open \"/dev/mem\"...\n\n");
        return -1;
    }

    // This maps physical memory for the FPGA's lightweight bridge into the virtual
    // memory of the user-space.
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);

    // This will print if the mapping has failed.
    if (LW_virtual == MAP_FAILED)
    {
        printf("Error: mmap() failed...\n\n");
        close(fd);
        return -1;
    }

    // This sets up pointers to the key button and 7-segment display registers.
    KEY_ptr = (volatile int *)(LW_virtual + KEY_BASE);
    HEX_ptr = (volatile int *)(LW_virtual + HEX3_HEX0_BASE);

    // This initialized the 7-segment display to the default value.
    *HEX_ptr = fpgaDecoding(0);
    return 0;
}

// This function cleans up the hardware resources by unmapping the
// virtual memory and closing the file descriptor.
void cleanupHardware()
{
    // If the lightweight bridge virtual pointer is valid, unmap the physical memory.
    if (LW_virtual)
    {
        munmap(LW_virtual, LW_BRIDGE_SPAN);
        LW_virtual = NULL;
    }

    // If the file descriptor is valid, close it.
    if (fd != -1)
    {
        close(fd);
        fd = -1;
    }
}

// This function polls the key buttons and updates the state variables.
void pollKeys()
{
    int keyState = *KEY_ptr;

    // If the key button 3 is pressed, the die will roll to generate 1-6.
    if (keyState & 0x8)
    {
        rollResult = (rand() % 6) + 1;
        *HEX_ptr = fpgaDecoding(rollResult);
    }

    // If the key button 2 is pressed, the program will exit.
    if (keyState & 0x4)
        exitFlag = 1;

    // This clears the edgecapture register to reset the key state.
    *(KEY_ptr + 3) = 0xF;
}

// This function checks the die roll result and exit flag.
int readHardwareStatus(int *result, int *exit)
{
    *result = rollResult;
    *exit = exitFlag;

    // We reset exit flag every time the hardware status is read.
    exitFlag = 0;
    return 0;
}

// This function converts a decimal number to the corresponding 7-segment display encoding.
int fpgaDecoding(int decimal)
{
    switch (decimal)
    {
    case 1:
        return 0x06;
    case 2:
        return 0x5b;
    case 3:
        return 0x4f;
    case 4:
        return 0x66;
    case 5:
        return 0x6d;
    case 6:
        return 0x7d;
    default:
        return 0xff;
    }
}
