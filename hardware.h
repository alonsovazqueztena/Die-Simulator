// Alonso Vazquez Tena
// October 13, 2024
// Milestone 2: Embedded Application Release 1
// This is my own work.

// We are defining the hardware header file here to ensure we declare the necessary functions.
#ifndef HARDWARE_H
#define HARDWARE_H

// This function simulates rolling a die and generating a number from 1-6.
int roll();

// This function would contain the logic necessary to send the randomly generated number
// to the FPGA for BCD decoding.
int sendToFPGA(int number);

// This function would contain the logic necessary to decode the randomly generated number
// in the FPGA.
int fpgaDecoding(int number);

// This function would contain the logic necessary to display the decoded randomly generated number
// on the rightmost 7-segment depending on the value.
int displayOn7Segment(int number);

// This is the end of the hardware header definition.
#endif
