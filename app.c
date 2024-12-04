// Alonso Vazquez Tena
// December 1, 2024
// Milestone 4: Embedded Application Release 3
// This is my own work.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// We must include the header file for hardware-related functions.
#include "hardware.h"

// These constants are defined as the possible return values for
// the pollKeys function.
#define DIE_ROLLED 1
#define EXIT_REQUEST 2

// This main function will hold all the application logic.
int main()
{

    // This creates a hardware context to handle the hardware state.
    HardwareContext context;

    // This variable will hold the roll result.
    int result;

    // This seeds the random number generator.
    srand(time(NULL));

    // This initializes the hardware.
    if (initializeHardware(&context) == -1)
        return EXIT_FAILURE;

    // This is the welcome message and the instructions.
    printf("Welcome to the Die Simulator!\n\n");
    printf("Please press and hold KEY3 to roll the die, or KEY2 to exit the program!\n\n");

    while (1)
    {
        // This polls for the key presses and determines what
        // actions to take based on the user input.
        int userInput = pollKeys(&context, &result);

        switch (userInput)
        {

        // If the roll button has been pressed, the program
        // will roll the die and display it to the user.
        case DIE_ROLLED:
            printf("%d was rolled!\n\n", result);
            break;

        // If the exit button has been pressed, the program exits the loop
        // and terminates.
        case EXIT_REQUEST:
            printf("Bye bye! Exiting the program...\n\n");
            cleanupHardware(&context);
            return EXIT_SUCCESS;

        // This continues the loop, meanwhile a user input is
        // sought for.
        default:
            break;
        }

        // This is a small delay to reduce CPU usage.
        usleep(100000);
    }
}
