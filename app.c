// Alonso Vazquez Tena
// October 13, 2024
// Milestone 2: Embedded Application Release 1
// This is my own work.

// We must include these libraries for its utilities.
#include <stdio.h>
#include <stdlib.h>

// We must include the header files for app and hardware-related functions.
#include "app.h"
#include "hardware.h"

// This function starts the die simulator.
void start()
{
    // This integer seeks to store the result of the die roll.
    int result;    

    // This character seeks to store the user input for rolling or exiting.
    char input;    

    // This is the welcome message and the instructions the user must follow.
    printf("Welcome to the Die Simulator!\n\n");

    // This is the main loop to keep the program running until the user exits.
    do
    {
        // These are the instructions the user must follow.
        printf("Please press 'R' to roll or press 'Q' to exit program!\n\n");

        // This reads a character input from the user.
        input = getchar();  

        // This checks if the user pressed the 'r' key to roll the die.
        if(input == 'r' || input == 'R')
        {
            // This lets the user know what key button was detected as pressed.
            printf("\nKey button 'r' is pressed!\n\n");

            // This calls the roll function to get a die result.  
            result = roll();

            // This shows to the user was number was rolled.
            printf("%d was rolled!\n\n", result);

            // This sends the result to the FPGA for decoding.
            sendToFPGA(result);

            // This calls for the result to be decoded.
            fpgaDecoding(result);

            // This calls for the decoded result to be displayed to the rightmost 7-segment.
            displayOn7Segment(result);
        }
        // This checks if the user pressed the 'q' key to quit the program.
        else if(input == 'q' || input == 'Q')
        {
            // This lets the user know what key button was detected as pressed.
            printf("\nKey button 'q' is pressed!\n\n");
            // This exits the loop.
            break;  
        }
            
        // This loop consumes any extra input.
        while((input = getchar()) != '\n' && input != EOF) {}

    // This creates an infinite loop, breaks only when the user presses the 'q' key to exit.
    } while (1);
}

int main()
{
    // This starts the die simulator.
    start(); 

    // This informs the user that the program is exiting.
    printf("Bye bye! Exiting the program...\n\n");  

    // This returns when the program has successfully terminated.
    return EXIT_SUCCESS;
}