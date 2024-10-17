// Alonso Vazquez Tena
// October 13, 2024
// Milestone 2: Embedded Application Release 1
// This is my own work.

// We must include these libraries for its utilities.
#include <stdio.h>   
#include <stdlib.h>
#include <time.h>

// We must include the header file for hardware-related functions.
#include "hardware.h"

// This function simulates rolling a die.
int roll()
{
    // This informs the user that the die is rolling.
    printf("Rolling die...\n\n");

    // To allows for better randomness, we need to seed the random number generator with the current time.
    srand(time(0));

    // This generates a random number from 1 - 6.
    return (rand() % 6) + 1; 
}

// This function would contain the logic necessary to send the randomly generated number
// to the FPGA for BCD decoding.
int sendToFPGA(int number)
{
    // This prints to the user that the number has been sent to the FPGA for BCD decoding. 
    printf("Sending %d to the FPGA for BCD decoding...\n\n", number);
    return 0;
}

// This function would contain the logic necessary to decode the randomly generated number
// in the FPGA.
int fpgaDecoding(int number)
{
    // This prints to the user that the number is undergoing BCD decoding.
    printf("FPGA is decoding %d...\n\n", number);
    return 0;
}

// This function would contain the logic necessary to display the decoded randomly generated number
// on the rightmost 7-segment depending on the value.
int displayOn7Segment(int number)
{
    // This prints to the user that the 7-segment display is currently showing the rolled number.
    printf("The 7-segment display shows: %d\n\n", number);
    return 0;
}