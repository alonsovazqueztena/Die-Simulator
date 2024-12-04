// Alonso Vazquez Tena
// December 1, 2024
// Milestone 4: Embedded Application Release 3
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

// These constants are defined as the possible return values for
// the pollKeys function.
#define DIE_ROLLED 1
#define EXIT_REQUEST 2

// This maps physical memory for FPGA I/O.
int initializeHardware(HardwareContext *context)
{
    // This opens /dev/men to give access to physical addresses if not done.
    if ((context->fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
    {
        printf("Error: Could not open \"/dev/mem\"...\n\n");
        return -1;
    }

    // This maps physical memory for the FPGA's lightweight bridge into the virtual
    // memory of the user-space.
    context->LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, context->fd, LW_BRIDGE_BASE);

    // This will print if the mapping has failed.
    if (context->LW_virtual == MAP_FAILED)
    {
        printf("Error: mmap() failed...\n\n");
        close(context->fd);
        return -1;
    }

    // This sets up pointers to the key button and 7-segment display registers.
    context->KEY_ptr = (volatile int *)(context->LW_virtual + KEY_BASE);
    context->HEX_ptr = (volatile int *)(context->LW_virtual + HEX3_HEX0_BASE);

    // This initialized the 7-segment display to the default value.
    *(context->HEX_ptr) = fpgaDecoding(0);

    // Here, the roll result will be initialized.
    context->rollResult = 0;

    return 0;
}

// This function cleans up the hardware resources by unmapping the
// virtual memory and closing the file descriptor.
void cleanupHardware(HardwareContext *context)
{
    // If the lightweight bridge virtual pointer is valid, unmap the physical memory.
    if (context->LW_virtual)
    {
        munmap(context->LW_virtual, LW_BRIDGE_SPAN);
        context->LW_virtual = NULL;
    }

    // If the file descriptor is valid, close it.
    if (context->fd != -1)
    {
        close(context->fd);
        context->fd = -1;
    }
}

// This function polls the key buttons and updates the state variables.
int pollKeys(HardwareContext *context, int *rollResult)
{
    int keyState = *(context->KEY_ptr);

    // If the key button 3 is pressed, the die will roll to generate 1-6.
    if (keyState & 0x8)
    {
        context->rollResult = (rand() % 6) + 1;
        *(context->HEX_ptr) = fpgaDecoding(context->rollResult);

        // This updates the result with the current result of the roll.
        // This is to be then displayed to the console.
        *rollResult = context->rollResult;

        // This clears the edgecapture register to reset the key state.
        *(context->KEY_ptr + 3) = 0xF;

        return DIE_ROLLED;
    }

    // If the key button 2 is pressed, the program will exit.
    if (keyState & 0x4)
    {
        // This clears the edgecapture register to reset the key state.
        *(context->KEY_ptr + 3) = 0xF;

        return EXIT_REQUEST;
    }

    // This clears the edgecapture register to reset the key state.
    *(context->KEY_ptr + 3) = 0xF;

    // If the action failed to go through, return a fail state.
    return -1;
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
